#!/usr/bin/env python3
# coding: utf-8
# -----------------------------------------------------------------------------
import argparse
import sys
import os
import json
import base64
import struct
from PIL import Image, ImageFont, ImageDraw
import configparser

from typing import List, Tuple

NB_MIN_PACKED_PIXELS = 3
NB_MAX_PACKED_PIXELS = 6
class Rle4bpp():

    @staticmethod
    def image_to_pixels(img, bpp: int) -> List[Tuple]:
        """
        Rotate and pack bitmap data of the character.
        """
        width, height = img.size

        color_indexes = []
        nb_colors = pow(2, bpp)
        base_threshold = int(256 / nb_colors)
        half_threshold = int(base_threshold / 2)

        # col first
        for col in reversed(range(width)):
            for row in range(height):
                # Return an index in the indexed colors list
                # top to bottom
                # Perform implicit rotation here (0,0) is left top in NBGL,
                # and generally left bottom for various canvas
                color_index = img.getpixel((col, row))
                color_index = int((color_index + half_threshold) / base_threshold)

                if color_index >= nb_colors:
                    color_index = nb_colors - 1

                color_indexes.append(color_index)

        return color_indexes


    @staticmethod
    def pixels_to_occurrences(pixels: List[int]) -> List[Tuple]:
        occurrences = []
        for pixel in pixels:
            if len(occurrences) == 0:
                occurrences.append((pixel, 1))
            else:
                color, cnt = occurrences[-1]
                if pixel == color:
                    occurrences[-1] = (pixel, cnt+1)
                else:
                    occurrences.append((pixel, 1))
        return occurrences

    # Fetch next single pixels that can be packed
    @classmethod
    def fetch_next_single_pixels(cls, occurrences: List[Tuple[int, int]]) -> List[int]:
        result = []
        for occurrence in occurrences:
            color, cnt = occurrence
            if cnt >= 2:
                break
            else:
                result.append(color)

        # Ensure pixels can be packed by groups
        nb_pixels = len(result)
        if (nb_pixels % NB_MAX_PACKED_PIXELS < NB_MIN_PACKED_PIXELS):
            return result[0:(nb_pixels - nb_pixels%NB_MIN_PACKED_PIXELS)]
        return result

    # Generate bytes from a list of single pixels
    def generate_packed_single_pixels_bytes(packed_occurences: List[int]) -> bytes:
        assert len(packed_occurences) >= 3
        assert len(packed_occurences) <= 6
        header = (0b10 << 2) | (len(packed_occurences) - 3)
        nibbles = [header]
        for occurrence in packed_occurences:
            nibbles.append(occurrence)

        result = []
        for i, nibble in enumerate(nibbles):
            if (i % 2) == 0:
                result.append(nibble << 4)
            else:
                result[-1] += nibble
        return bytes(result)

    @classmethod
    def handle_packed_pixels(cls, packed_occurences: List[int]) -> bytes:
        assert len(packed_occurences) >= 3
        result = bytes()
        for i in range(0, len(packed_occurences), NB_MAX_PACKED_PIXELS):
            result += cls.generate_packed_single_pixels_bytes(packed_occurences[i:i+NB_MAX_PACKED_PIXELS])
        return result

    @staticmethod
    def handle_white_occurrence(occurrence: Tuple[int, int]) -> bytes:
        _, cnt = occurrence
        unit_cnt_max = 64
        result = []

        for i in range(0, cnt, unit_cnt_max):
            diff_cnt = cnt - i
            if diff_cnt > unit_cnt_max:
                i_cnt = unit_cnt_max
            else:
                i_cnt = diff_cnt

            result.append((0b11 << 6) | (i_cnt-1))
        return bytes(result)

    @staticmethod
    def handle_non_white_occurrence(occurrence: Tuple[int, int]) -> bytes:
        color, cnt = occurrence
        unit_cnt_max = 8
        result = []

        for i in range(0, cnt, unit_cnt_max):
            diff_cnt = cnt - i
            if diff_cnt > unit_cnt_max:
                i_cnt = unit_cnt_max
            else:
                i_cnt = diff_cnt

            result.append((0 << 7) | (i_cnt-1) << 4 | color)

        return bytes(result)

    @classmethod
    def occurrences_to_rle(cls, occurrences: Tuple[int, int], bpp: int) -> bytes:
        result = bytes()
        WHITE_COLOR = pow(2, bpp) - 1
        i = 0
        while i < len(occurrences):
            # Check if next occurrences are packable in single occurrences
            single_pixels = cls.fetch_next_single_pixels(occurrences[i:])
            if len(single_pixels) > 0:
                # Pack single occurrences
                result += cls.handle_packed_pixels(single_pixels)
                i += len(single_pixels)
            else:
                # Encode next occurrence
                occurrence = occurrences[i]
                color, _ = occurrence
                if color == WHITE_COLOR:
                    result += cls.handle_white_occurrence(occurrence)
                else:
                    result += cls.handle_non_white_occurrence(occurrence)
                i += 1
        return result

    @classmethod
    def rle_4bpp(cls, img) -> bytes:
        bpp = 4
        pixels = cls.image_to_pixels(img, bpp)
        occurrences = cls.pixels_to_occurrences(pixels)
        return 1, cls.occurrences_to_rle(occurrences, bpp)

# -----------------------------------------------------------------------------
class Rle1bpp():
    """
    Class handling custom RLE encoding, optimized for 1PP.
    The generated bytes will contain alternances counts ZZZZOOOO with
    - ZZZZ: number of consecutives 0, from 0 to 15
    - OOOO: number of consecutives 1, from 0 to 15
    """
    # -------------------------------------------------------------------------
    @staticmethod
    def image_to_pixels(img):
        """
        Rotate and pack bitmap data of the character.
        return an array of pixels values.
        """
        width, height = img.size

        pixels = []
        # Intensity level value to be considered a white pixel
        white_threshold = 128
        white_pixel = 1
        black_pixel = 0

        # col first
        for col in reversed(range(width)):
            for row in range(height):
                # Return an index in the indexed colors list (0 or 1, here)
                # top to bottom
                # Perform implicit rotation here (0,0) is left top in NBGL,
                # and generally left bottom for various canvas
                if img.getpixel((col, row)) >= white_threshold:
                    pixels.append(white_pixel)
                else:
                    pixels.append(black_pixel)

        return pixels

    # -------------------------------------------------------------------------
    @staticmethod
    def encode_pass1(data):
        """
        Encode array of values using 'normal' RLE.
        Return an array of tuples containing (repeat, val)
        """
        output = []
        previous_value = -1
        count = 0
        for value in data:
            # Same value than before?
            if value == previous_value:
                count += 1
            else:
                # Store previous result
                if count:
                    pair = (count, previous_value)
                    output.append(pair)
                # Start a new count
                previous_value = value
                count = 1

        # Store previous result
        if count:
            pair = (count, previous_value)
            output.append(pair)

        return output

    # -------------------------------------------------------------------------
    @staticmethod
    def encode_pass2(pairs):
        """
        Encode alternance counts between pixels (nb of 0, then nb of 1, etc)
        The generated packed values will contain ZZZZOOOO ZZZZOOOO with
        - ZZZZ: number of consecutives 0, from 0 to 15
        - OOOO: number of consecutives 1, from 0 to 15
        """
        max_count = 15
        # First step: store alternances, and split if count > 15
        next_pixel = 0
        alternances = []
        for repeat, value in pairs:
            # Store a count of 0 pixel if next pixel is not the one expected
            if value != next_pixel:
                alternances.append(0)
                next_pixel ^= 1

            while repeat > max_count:
                # Store 15 pixels of value next_pixel
                alternances.append(max_count)
                repeat -= max_count
                # Store 0 pixel of alternate value
                alternances.append(0)

            if repeat:
                alternances.append(repeat)
                next_pixel ^= 1

        # Now read all those values and store them into quartets
        output = bytes()
        index = 0

        while index < len(alternances):
            zeros = alternances[index]
            index += 1
            if index < len(alternances):
                ones = alternances[index]
                index += 1
            else:
                ones = 0

            byte = (zeros << 4) | ones
            output += bytes([byte])

        return output

    # -------------------------------------------------------------------------
    @staticmethod
    def remove_duplicates(pairs):
        """
        Check if there are some duplicated pairs (same values) and merge them.
        """
        index = len(pairs) - 1
        while index >= 1:
            repeat1, value1 = pairs[index-1]
            repeat2, value2 = pairs[index]
            # Do we have identical consecutives values?
            if value1 == value2:
                repeat1 += repeat2
                # Merge them and remove last entry
                pairs[index-1] = (repeat1, value1)
                pairs.pop(index)
            index -= 1

        return pairs

    # -------------------------------------------------------------------------
    @classmethod
    def decode_pass2(cls, data):
        """
        Decode packed bytes into array of tuples containing (repeat, value).
        The provided packed values will contain ZZZZOOOO ZZZZOOOO with
        - ZZZZ: number of consecutives 0, from 0 to 15
        - OOOO: number of consecutives 1, from 0 to 15
        """
        pairs = []
        for byte in data:
            ones = byte & 0x0F
            byte >>= 4
            zeros = byte & 0x0F
            if zeros:
                pairs.append((zeros, 0))
            if ones:
                pairs.append((ones, 1))

        # There was a limitation on repeat count => remove duplicates
        pairs = cls.remove_duplicates(pairs)

        return pairs

    # -------------------------------------------------------------------------
    @classmethod
    def rle_1bpp(cls, img) -> bytes:
        """
        Input: image to compress
        - convert the picture to an array of pixels
        - convert the array of pixels to tuples of (repeat, value)
        - encode using custom RLE
        Output: array of compressed bytes
        """
        pixels = cls.image_to_pixels(img)
        pairs = cls.encode_pass1(pixels)
        encoded_data = cls.encode_pass2(pairs)

        # Check if encoding/decoding is fine
        pairs2 = cls.decode_pass2(encoded_data)
        assert pairs == pairs2

        return 1, encoded_data

# -----------------------------------------------------------------------------
class TTF2INC (object):
    """
    This class will contain methods to handle TTF fonts & generate .inc files
    """

# -------------------------------------------------------------------------
    def __init__(self, args):
        super().__init__()
        # Default value:
        self.unicode_needed = False
        self.basename = None
        self.directory = None
        # Be sure there are at least some mandatory characters
        self.unicode_chars = "�"
        self.ids = []
        # Store parameters:
        self.args = args
        #read config
        config = configparser.ConfigParser()
        config.read(args.init_file)

        print(args.init_file)
        self.configMain = config['main']
        self.first_character = int(self.configMain.get('firstChar','0x20'),16)
        self.last_character = int(self.configMain.get('lastChar','0x7A'),16)
        # first Line to be taken into glyphs
        self.firstLine = self.configMain.getint('firstLine',0)

        self.font_name = self.configMain.get('font')
        self.font_size = self.configMain.getint('fontSize')
        self.line_size = self.configMain.getint('lineSize')
        self.align_width = self.configMain.getboolean('align',False)
        self.crop = self.configMain.getboolean('crop',False)
        self.rle = self.configMain.getboolean('rle',True)
        self.bpp = self.configMain.getint('bpp',1)

        # Lookup font file among ttf and otf files
        font_file = None
        for ext in [".ttf", ".otf"]:
            font_file = os.path.join(os.path.dirname(args.init_file), self.font_name) + ext
            if os.path.exists(font_file):
                break

        try:
            self.font = ImageFont.truetype(font_file, self.font_size-1)
        except (BaseException, Exception) as error:
            sys.stderr.write(f"Error with font {self.font_name}: {error}\n")
            sys.exit(-1)

        # Get font metrics:
        # - ascent: distance from the baseline to the highest outline point.
        # - descent: distance from the baseline to the lowest outline point.
        # (descent is a negative value)
        self.ascent, self.descent = self.font.getmetrics()
        if self.args.verbose:
            sys.stdout.write(f"ascent={self.ascent}, descent={self.descent}, "\
                             f"size={self.font.size}, "\
                             f"font.height={self.font.font.height}\n")

        self.font_height = self.font.font.height

        if self.args.verbose:
            sys.stdout.write(f"height={self.font_height}\n")

    # -------------------------------------------------------------------------
    def __enter__(self):
        """
        Return an instance to this object.
        """
        return self

    # -------------------------------------------------------------------------
    def __exit__(self, exec_type, exec_value, traceback):
        """
        Do all the necessary cleanup.
        """

    # -------------------------------------------------------------------------
    def check_unicode(self, char):
        """
        Check if unicode is needed to encode provided character.
        """
        if ord(char) > 0x7F:
            self.unicode_needed = True

    # -------------------------------------------------------------------------
    def build_names(self):
        """
        Update the unicode_needed flag and Build filenames depending on font characteristics.
        """
        # Get the font basename, without extension:
        self.basename = os.path.splitext(
            os.path.basename(self.font_name))[0]
        self.basename = self.basename.replace("-","_")
        self.basename += f"_{self.font_size}px"
        if self.bpp != 4:
            self.basename += f"_{self.bpp}bpp"
        # If characters are using Unicode, update basename:
        if self.unicode_needed:
            self.basename += "_unicode"
        # Build the destination directory name, based on font+size[+unicode]+bpp:
        self.directory = os.path.join(os.path.dirname(self.args.init_file), f"nbgl_font_{self.basename}")
        # Create that directory if it doesn't exist:
        if not self.args.no_write and not os.path.exists(self.directory):
            if self.args.verbose:
                sys.stdout.write(f"Creating directory {self.directory}\n")
            os.mkdir(self.directory)

    # -------------------------------------------------------------------------
    def get_char_picture(self, char, bpp: int):
        """
        Return the bitmap corresponding to the provided character(s).
        """
        # Get the unicode value of that char:
        # (in fact there is a plane value from 0 to 16 then a 16-bit code)
        unicode_value = f"0x{ord(char):06X}"
        # Get text size of the character:
        left, top, right, bottom = self.font.getbbox(char)
        width, height = right - left, bottom - top

        # Build full path of the destination file:
        filename = f"nbgl_font_{self.basename}_{unicode_value}"
        fullpath = os.path.join(self.directory, filename)

        # STEP 1: Generate the .gif/.bmp file if it doesn't exist:
        found_file = None
        for ext in [".bmp", ".gif"]:
            if os.path.exists(fullpath + ext):
                found_file = fullpath + ext

        if (not found_file) or self.args.overwrite:
            # Generate and save the .GIF picture
            # Create a B&W Image with that size
            # get potential offsets to apply for this char
            offsetY = self.configMain.getint('%s_offsetY'%unicode_value,0)
            charY = self.firstLine+offsetY

            if self.align_width:
                # align on closest multiple of 4
                i = 6
                while i < 50:
                    if width <= i:
                        width = i-2
                        break
                    i+=4

            # nbgl driver inverts color when displaying 1BPP
            if bpp == 1:
                background_color = 'black'
                text_color = 'white'
            else:
                background_color = 'white'
                text_color = 'black'

            img = Image.new('L', (width, self.font.font.height), color=background_color)
            draw = ImageDraw.Draw(img)
            draw.text((0, 0),
                    char, font=self.font, fill=text_color)
            img = img.crop((0,charY,width,charY+self.font_size))

            if not self.args.no_write:
                # Save the .GIF file:
                if self.args.verbose:
                    sys.stdout.write(f"Saving {fullpath}.gif ({width}x{height})\n")
                img.save(fullpath + ".gif")
        else:
            # We will load the .GIF picture:
            if self.args.verbose:
                sys.stdout.write(f"Loading {fullpath}.gif\n")
            img = Image.open(found_file)
            img = img.convert('L')

        # img.show()
        return img

        # Minimal window/crop
    # -------------------------------------------------------------------------
    def align(self, val: int, target: int, go_up: bool) -> int:
        mod = val % target
        if mod == 0:
            return val

        if go_up:
            return val + target - mod
        else:
            return val - mod


    def get_minimal_window(self, img, bpp: int):
        width, height = img.size
        x_min = width
        y_min = height
        x_max = 0
        y_max = 0
        y_alignment = 4

        # nbgl driver inverts color when displaying 1BPP
        if bpp == 1:
            white_val = 0
        else:
            white_val = 255

        for x in range(0, width):
            for y in range(0, height):
                if img.getpixel((x, y)) == white_val:
                    continue

                if x < x_min:
                    x_min = x

                if y < y_min:
                    y_min = y

                if x+1 > x_max:
                    x_max = x+1

                if y+1 > y_max:
                    y_max = y+1

        # Check if it is an empty box
        if x_max < x_min:
            x_max = x_min = 0

        if y_max < y_min:
            y_max = y_min = 0

        # Align coords
        y_max = self.align(y_max, y_alignment, True)
        y_min = self.align(y_min, y_alignment, False)
        return ((x_min, y_min), (x_max, y_max))

    # -------------------------------------------------------------------------
    def image_to_packed_buffer(self, img, bpp: int):
        """
        Rotate and pack bitmap data of the character.
        """
        width, height = img.size

        current_byte = 0
        current_bit = 0
        image_data = []
        nb_colors = pow(2, bpp)
        base_threshold = int(256 / nb_colors)
        half_threshold = int(base_threshold / 2)

        # col first
        for col in reversed(range(width)):
            for row in range(height):
                # Return an index in the indexed colors list
                # top to bottom
                # Perform implicit rotation here (0,0) is left top in NBGL,
                # and generally left bottom for various canvas
                color_index = img.getpixel((col, row))
                color_index = int((color_index + half_threshold) / base_threshold)

                if color_index >= nb_colors:
                    color_index = nb_colors - 1

                # le encoded
                current_byte += color_index << ((8-bpp)-current_bit)
                current_bit += bpp

                if current_bit >= 8:
                    image_data.append(current_byte & 0xFF)
                    current_bit = 0
                    current_byte = 0

        # Handle last byte if any
        if current_bit > 0:
            image_data.append(current_byte & 0xFF)

        return bytes(image_data)

    # -------------------------------------------------------------------------
    @staticmethod
    def swap32(data):
        """
        Transform a Big Endian value into Little Endian one, and vice versa.
        """
        if isinstance(data, bytes):
            return [struct.unpack("<I", struct.pack(">I", i))[0] for i in data]

        result = (data & 0x000000FF) << 24
        result += (data & 0x0000FF00) << 8
        result += (data & 0x00FF0000) >> 8
        result += (data >> 24) & 0xFF
        return result

    # -------------------------------------------------------------------------
    def get_font_id_name(self):
        """
        Return the name of the font id.
        """
        # Those ids are defined in nbgl_font.h file, in nbgl_font_id_e enums.
        font_id = "BAGL_FONT"
        font_name = self.font_name.lower()
        if "open" in font_name and "sans" in font_name:
            font_id += "_OPEN_SANS"
            if "regular" in font_name:
                font_id += "_REGULAR"
            elif "extrabold" in font_name:
                font_id += "_EXTRABOLD"
            elif "semibold" in font_name:
                font_id += "_SEMIBOLD"
            elif "light" in font_name:
                font_id += "_LIGHT"
        elif "inter" in font_name:
            font_id += "_INTER"
            if "regular" in font_name:
                font_id += "_REGULAR"
            elif "extrabold" in font_name:
                font_id += "_EXTRABOLD"
            elif "semibold" in font_name:
                font_id += "_SEMIBOLD"
            elif "light" in font_name:
                font_id += "_LIGHT"
            elif "medium" in font_name:
                font_id += "_MEDIUM"
        elif "hma" in font_name:
            font_id += "_HM_ALPHA_MONO_MEDIUM"
        else:
            font_id += "_UNKNOWN"

        font_id += f"_{self.font_size}px"

        if self.bpp != 4:
            font_id += f"_{self.bpp}bpp"

        return font_id

    # -------------------------------------------------------------------------
    def get_font_id(self):
        """
        Return the font id.
        """
        # Those ids are defined in nbgl_fonts.h file, in nbgl_font_id_e enums.
        font_ids={
            "BAGL_FONT_INTER_REGULAR_24px": 0,
            "BAGL_FONT_INTER_SEMIBOLD_24px": 1,
            "BAGL_FONT_INTER_MEDIUM_32px": 2,
            "BAGL_FONT_HM_ALPHA_MONO_MEDIUM_32px": 3,
            "BAGL_FONT_INTER_REGULAR_24px_1bpp": 4,
            "BAGL_FONT_INTER_SEMIBOLD_24px_1bpp": 5,
            "BAGL_FONT_INTER_SEMIBOLD_32px_1bpp": 6,
        }
        font_id_name = self.get_font_id_name()
        if font_id_name in font_ids.keys():
            font_id = font_ids[font_id_name]
        else:
            font_id = 0        # BAGL_FONT_INTER_REGULAR_24px by default

        return font_id

    # -------------------------------------------------------------------------
    def read_ids(self, id_filename):
        """
        Read a text file (a .h actually) containing all IDs to use.
        """
        if not os.path.exists(id_filename):
            sys.stderr.write(f"Can't open file {id_filename}\n")
            sys.exit(-5)

        # Read the .h file and store each ID found
        with open(id_filename, "r") as id_file:
            for line in id_file:
                # Ignore lines that don't start with "
                if line[0] != '"':
                    continue
                # Remove leading "
                line = line.lstrip('"')
                # Remove trailing ",
                line = line.rstrip('",\n')
                self.ids.append(line)

    # -------------------------------------------------------------------------
    def add_unicode_chars(self, string, string_id):
        """
        Parse string and add unicode characters not already stored
        """
        # If we have a list of IDs, be sure that one is included in it
        if len(self.ids) != 0:
            if string_id not in self.ids:
                return

        for char in string:
            # Just check unicode characters
            # \b, \n, \f and \e\xAB will appear individually, as ASCII chars!
            if ord(char) > 0x7F and char not in self.unicode_chars:
                self.unicode_chars += char

    # -------------------------------------------------------------------------
    def parse_json_strings(self, filenames):
        """
        Parse the provided JSON file(s) and scan all unicode chars found in strings
        """
        for file in filenames.split():
            if not os.path.exists(file):
                sys.stderr.write(f"Can't open file {file}\n")
                sys.exit(-4)

            # Read the JSON file into json_data
            with open(file, "r") as json_file:
                json_data = json.load(json_file, strict=False)

            # Parse all strings contained in txt fields of json_data
            for category in json_data:
                # Skip Smartling related part of the JSON file
                if category.lower() == "smartling":
                    continue

                # Parse all "text" strings and add the unicode characters
                for string in json_data[category]:
                    if not "text" in string.keys() or not "id" in string.keys():
                        sys.stdout.write(f"Skipping {string} because it does "\
                                         "not contain \"text\" or \"id\"!\n")
                        continue
                    self.add_unicode_chars(string['text'], string['id'])

        return self.unicode_chars

# -----------------------------------------------------------------------------
def change_ext(filename, extension):
    """
    Change a filename extension
    """
    # Get the filename without current extension
    new_filename = os.path.splitext(filename)[0]
    # Add the new extension
    new_filename += extension

    return new_filename

# -----------------------------------------------------------------------------
# Program entry point:
# -----------------------------------------------------------------------------
if __name__ == "__main__":

    # -------------------------------------------------------------------------
    def main(args):

        with TTF2INC(args) as ttf:

            # If we provided a list of IDs to use, read the file!
            if args.id:
                ttf.read_ids(args.id)

            # If JSON filename(s) was provided, parse them to get the strings
            if args.json_filenames:
                string = ttf.parse_json_strings(args.json_filenames)
            # Use the provided string or generate all wanted ASCII characters:
            else:
                string = args.string
            if len(string) == 0:
                for value in range(ttf.first_character, ttf.last_character+1):
                    string += chr(value)

            for char in string:
                ttf.check_unicode(char)
            ttf.build_names()

            # create a mask with the string containing all chars
            mask = ttf.font.getmask(string, mode='1')
            mask_w, mask_h = mask.size

            # create an image (B&W) with the string containing all chars
            string_img = Image.new('1', (mask_w, ttf.font_height), color='black')
            draw = ImageDraw.Draw(string_img)

            # Compute 'real' font height & baseline from top:
            baseline = ttf.ascent - (ttf.font_height - ttf.font_size)
            if args.verbose:
                sys.stdout.write(f"Font height={ttf.font_size}, baseline={baseline}\n")

            # Now, handle all characters from the string:
            char_info = {}
            for char in string:
                try:
                    # We could have done everything in one step, from .ttf to
                    # .inc, but to allow manual editing of generated .gif
                    # files, we will process chars in two steps:
                    # - from .ttf to .gif
                    # - from .gif to .inc

                    # STEP 1: Generate the .gif file if it doesn't exist:
                    # (or load it otherwise)
                    img = ttf.get_char_picture(char, ttf.bpp)
                    width, height = img.size

                    # STEP 2: Crop image to its minimal window
                    if ttf.crop:
                        ((x_min, y_min), (x_max, y_max)) = \
                                ttf.get_minimal_window(img, bpp=ttf.bpp)
                        img = img.crop((x_min, y_min, x_max, y_max))
                    else:
                        x_min = 0
                        y_min = 0
                        x_max = width
                        y_max = height

                    # STEP 3: Get bitmap data based on .gif content:
                    image_data = ttf.image_to_packed_buffer(img, ttf.bpp)
                    encoding = 0
                    # Do we want to compress this font?
                    if ttf.rle:
                        if ttf.bpp == 4:
                            method, compressed_data = Rle4bpp.rle_4bpp(img)
                        else:
                            method, compressed_data = Rle1bpp.rle_1bpp(img)

                        # Is compressed size really better?
                        if len(compressed_data) < len(image_data):
                            image_data = compressed_data
                            encoding = method

                    # Store the information to process it later:
                    char_info[char] = {"bitmap": image_data,
                                       "width": width,
                                       "size": len(image_data),
                                       "offset": 0,
                                       "img":img,
                                       "x_min": x_min,
                                       "y_min": y_min,
                                       "x_max": x_max,
                                       "y_max": y_max,
                                       "encoding": encoding}

                except (BaseException, Exception) as error:
                    sys.stderr.write(f"An error occurred while processing char"
                                     f" '{char}' with font {ttf.font_name}"
                                     f" x {ttf.font_size}: {error}\n")
                    return 1

            # Last step: generate .inc file with bitmap data for all chars:
            # (the .inc file will be stored in src directory)
            if args.output_name:
                inc_filename = args.output_name
            else:
                filename = f"nbgl_font_{ttf.basename}.inc"
                inc_filename = os.path.join("../../../public_sdk/lib_bagl/src/", filename)

            # Force .inc extension for inc_filename
            inc_filename = change_ext(inc_filename, ".inc")

            # Build the corresponding .json file, if we need to
            if ttf.unicode_needed:
                inc_json = change_ext(inc_filename, ".json")
            else:
                inc_json = None

            if args.suffix:
                suffix = args.suffix
            else:
                suffix = ""
            if args.verbose:
                sys.stdout.write(f"Generating file {inc_filename}\n")

            ttf_info_list = []
            if args.append:
                mode = "a"
                # Read previous entries, if such file exists
                if inc_json and os.path.exists(inc_json):
                    with open(inc_json, "r") as json_file:
                        ttf_info_list = json.load(json_file, strict=False)
            else:
                mode = "w"

            ttf_info_dictionary = {}
            with open(inc_filename, mode) as inc:
                if not args.output_name:
                    inc.write("/* @BANNER@ */\n\n")
                # Write the array containing all bitmaps:
                inc.write('#include "nbgl_fonts.h"\n\n')
                inc.write(f"__attribute__ ((section(\"._nbgl_fonts_\"))) const unsigned char bitmap{ttf.basename.upper()}{suffix}[]"
                          f" = {{\n")
                offset = 0
                first_char = None
                ttf_info_dictionary["bitmap"] = bytes()
                bitmap_len = 0
                for char, info in sorted(char_info.items()):
                    image_data = info["bitmap"]
                    ttf_info_dictionary["bitmap"] += image_data
                    info["offset"] = offset
                    offset += info["size"]

                    # Keep track of first and last chars:
                    if not first_char:
                        first_char = ord(char)
                    last_char = ord(char)

                    if ttf.unicode_needed:
                        # Get the unicode value of that char:
                        # (plane value from 0 to 16 then a 16-bit code)
                        inc.write(f"//unicode 0x{ord(char):06X}\n")
                    else:
                        inc.write(f"//ascii 0x{ord(char):04X}\n")
                    for i in range(0, info["size"], 8):
                        inc.write("  " + ", ".join("0x{0:02X}".format(c) for c
                                                   in image_data[i:i+8]) + ",")
                        inc.write("\n")
                inc.write("};\n")

                # Serialize bitmap
                ttf_info_dictionary["bitmap"] = base64.b64encode(
                    ttf_info_dictionary["bitmap"]).decode('utf-8')

                # Write the array containing information about characters:
                if ttf.unicode_needed:
                    typedef = "nbgl_font_unicode_character_t"
                else:
                    typedef = "nbgl_font_character_t"

                inc.write(
                    f"\n __attribute__ ((section(\"._nbgl_fonts_\"))) const {typedef} characters"
                    f"{ttf.basename.upper()}{suffix}[{len(char_info)}] = {{\n")

                ttf_info_dictionary["nbgl_font_unicode_character"] = []

                for char, info in sorted(char_info.items()):
                    width = info["width"]
                    size = info["size"]
                    offset = info["offset"]
                    x_min = info["x_min"]
                    y_min = info["y_min"]
                    x_max = info["x_max"]
                    y_max = info["y_max"]
                    encoding = info["encoding"]
                    bitmap_len += len(info["bitmap"])
                    if ttf.unicode_needed:
                        unicode = f"0x{ord(char):06X}"
                        ttf_info_dictionary["nbgl_font_unicode_character"].append({
                            "char_unicode": ord(char),
                            "bitmap_byte_count": size,
                            "bitmap_offset": offset,
                            "char_width": width,
                            "x_min": x_min,
                            "y_min": y_min,
                            "x_max": x_max,
                            "y_max": y_max,
                            "encoding": encoding
                        })
                        inc.write(f"  {{ 0x{ord(char):06X}, {size:3}, {offset:4}, {width:3}, "
                                  f"{x_min}, {y_min}, {x_max}, {y_max}, {encoding} }}, //unicode {unicode}\n")
                    else:
                        # We'll use bitfieds to store x_min x_max y_min y_max
                        # => we need to change a little bit the meaning:
                        # - y_min = Y offset in pixels*4 (ie 3=>12)
                        y_min_mod4 = y_min // 4
                        # width_diff is Real width diff: x_max=width-width_diff
                        if bitmap_len == 0:
                            width_diff = 0
                        else:
                            width_diff = width - x_max
                        # real_height is (height/4)-1 => (y_max-y_min) / 4 - 1
                        real_height = (y_max // 4) - (y_min_mod4)
                        # If height is 0, it means there is nothing to draw...
                        if real_height:
                            real_height -= 1
                        # Here is the struct we'll use
                        # typedef struct {
                        # uint32_t encoding:1;
                        # uint32_t bitmap_offset:14;
                        # uint32_t char_width:5;
                        # uint32_t x_min:3;
                        # uint32_t y_min:3;
                        # uint32_t width_diff:3;
                        # uint32_t real_height:3;
                        # } nbgl_font_character_t;
                        # Check values does not exceed bitfield capabilities
                        val = ord(char)
                        if encoding >= pow(2, 1):
                            sys.stderr.write(f"encoding for char 0x{val:X}"\
                                             f"({char}) need too much bits "\
                                             f"(encoding={encoding})!\n")
                            return 2

                        if offset >= pow(2, 14):
                            sys.stderr.write(f"offset for char 0x{val:X}"\
                                             f"({char}) need too much bits "\
                                             f"(offset={offset})!\n")
                            return 3

                        if width >= pow(2, 5):
                            sys.stderr.write(f"width value for char 0x{val:X}"\
                                             f"({char}) need too much bits "\
                                             f"(width={width})!\n")
                            return 4

                        if x_min >= pow(2, 3):
                            sys.stderr.write(f"x_min value for char 0x{val:X}"\
                                             f"({char}) need too much bits "\
                                             f"(x_min={x_min})!\n")
                            return 5

                        if y_min_mod4 >= pow(2, 3):
                            sys.stderr.write(f"y_min value for char 0x{val:X}"\
                                             f"({char}) need too much bits "\
                                             f"(y_min={y_min_mod4})!\n")
                            return 6

                        if width_diff >= pow(2, 3):
                            sys.stderr.write(f"width_diff for char 0x{val:X}"\
                                             f"({char}) need too much bits "\
                                             f"(width_diff={width_diff})!\n")
                            sys.stderr.write(f"File: {inc_filename}")
                            return 7

                        if real_height >= pow(2, 3):
                            sys.stderr.write(f"real_height for char 0x{val:X}"\
                                             f"({char}) need too much bits "\
                                             f"(real_height={real_height})!\n")
                            return 8

                        inc.write(f"  {{ {encoding:1}, {offset:4}, {width:3},"\
                                  f"{x_min}, {y_min_mod4}, {width_diff}, "\
                                  f"{real_height} }},"\
                                  f" //asciii 0x{ord(char):04X}\n")
                inc.write("};\n")

                # Write the struct containing information about the font:
                if ttf.unicode_needed:
                    typedef = "nbgl_font_unicode_t"
                    ttf_info_dictionary["nbgl_font_unicode"] = {
                        "font_id": ttf.get_font_id(),
                        "bpp": ttf.bpp,
                        "char_height": ttf.font_size,
                        "baseline_height": baseline,
                        "line_height": ttf.line_size,
                        "char_kerning": 0,
                        "first_unicode_char": first_char,
                        "last_unicode_char" : last_char
                    }
                else:
                    typedef = "nbgl_font_t"
                inc.write(
                    f"\n __attribute__ ((section(\"._nbgl_fonts_\"))) const {typedef} font{ttf.basename.upper()}{suffix} = {{\n")
                inc.write(f"  {bitmap_len}, // bitmap len\n")
                inc.write(f"  {ttf.get_font_id_name()}, // font id\n")
                inc.write(f"  (uint8_t) NBGL_BPP_{ttf.bpp}, // bpp\n")
                inc.write(f"  {ttf.font_size}, // font height in pixels\n")
                inc.write(f"  {baseline}, // baseline height in pixels\n")
                inc.write(f"  {ttf.line_size}, // line height in pixels\n")
                inc.write( "  0, // kerning - specific to the font\n")
                inc.write(f"  0x{first_char:X}, // first character\n")
                inc.write(f"  0x{last_char:X}, // last character\n")
                if not suffix:
                    inc.write(f"  characters{ttf.basename.upper()},\n")
                    inc.write(f"  bitmap{ttf.basename.upper()}\n")
                inc.write("};\n")

                # Do we need to generate a JSON file with unicode related info?
                if ttf.unicode_needed:
                    ttf_info_list.append(ttf_info_dictionary)
                    with open(inc_json, "w") as json_file:
                        json.dump(ttf_info_list, json_file)
                        # Be sure there is a newline at the end of the file
                        json_file.write("\n")

                if args.test_align != None:
                    string_width = 0
                    for char, info in sorted(char_info.items()):
                        string_width+=info['width']
                    img = Image.new('1', (string_width, ttf.font_size), color='black')
                    current_width = 0
                    for char, info in sorted(char_info.items()):
                        img.paste(info['img'], (current_width, 0))
                        current_width += info['width']
                    draw = ImageDraw.Draw(img)
                    shape = [(0,args.test_align), (string_width, args.test_align)]
                    draw.line(shape, fill='white',width=0)

                    img.show()



        return 0

    # -------------------------------------------------------------------------
    # Parse arguments:
    parser = argparse.ArgumentParser(
        description="Convert a .ttf file into a .inc file (Build #221118.1041)")

    parser.add_argument(
        "--output",
        dest="output_name", type=str, required = True,
        help="C File Output name")

    parser.add_argument(
        "--suffix",
        dest="suffix", type=str,
        default=None,
        help="Suffix added to variable names ('%(default)s' by default)")

    parser.add_argument(
        "-c", "--chars", "--string",
        dest="string", type=str,
        default='',
        help="String with characters to convert ('' by default)")

    parser.add_argument(
        "-i", "--init",
        dest="init_file", type=str, required = True,
        help="init file for this font/size")

    parser.add_argument(
        "--test_align",
        dest="test_align", type=int,
        help="If set, creates a line at the given offset and save the whole string as a picture")

    parser.add_argument(
        "-j", "--json",
        dest="json_filenames", type=str,
        default=None,
        help="Full path of JSON filenames containing all strings ('%(default)s' by default)")

    parser.add_argument(
        "--id",
        dest="id", type=str,
        default=None,
        help="Filename containing all IDs to use ('%(default)s' by default)")

    parser.add_argument(
        "-a", "--append",
        dest="append", action='store_true',
        default=False,
        help="Append to existing INC file(s) ('%(default)s' by default)")

    parser.add_argument(
        "--no_write",
        dest="no_write", action='store_true',
        default=False,
        help="Don't create GIF file(s) ('%(default)s' by default)")

    parser.add_argument(
        "-o", "--overwrite",
        dest="overwrite", action='store_true',
        default=False,
        help="Overwrite existing GIF file(s) ('%(default)s' by default)")

    parser.add_argument(
        "-v", "--verbose",
        dest="verbose", action='store_true',
        default=False,
        help="Add verbosity to output ('%(default)s' by default)")

    # Call main function:
    EXIT_CODE = main(parser.parse_args())

    sys.exit(EXIT_CODE)
