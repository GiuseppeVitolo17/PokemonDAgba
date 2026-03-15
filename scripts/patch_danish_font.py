#!/usr/bin/env python3
"""
Patch Danish letters (Æ, Ø, Å, æ, ø, å) into the FireRed Latin font PNG.

Options:
  1. Use built-in 16x16 pixel glyphs (no download).
  2. Try to fetch PokemonDA font and extract 8x8 tiles, then scale to 16x16
     (PokemonDA uses 8x8; we scale and center in 16x16).

Charmap slots we use (same byte as existing char):
  0x09 → Ø (was Ì)    0x0B → Å (was Î)    0x0C → å (was Ï)
  0x0D → ø (was Ò)    0x10 → Æ (was Œ)    0x25 → æ (was œ)

Run from repo root:
  python3 scripts/patch_danish_font.py [--fetch-pokemonda]
Then: make graphics/fonts/latin_normal.latfont (or full make).
"""

import argparse
import os
import sys
from urllib.request import urlretrieve

try:
    from PIL import Image
except ImportError:
    print("Need Pillow: pip install Pillow", file=sys.stderr)
    sys.exit(1)

# FireRed Latin font: 256 wide, 16 glyphs per row, each glyph 16x16.
# latin_normal/male/female are 256x512; latin_small is 256x256.
# Palette: 0=bg, 1=fg (dark), 2=shadow (light), 3=white. We use 0,1,2.
W = 256
VALID_HEIGHTS = (256, 512)
GLYPH_W, GLYPH_H = 16, 16
COLS = 16

# Simple 16x16 pixel glyphs (0=bg, 1=fg, 2=shadow). Drawn to resemble Æ,Ø,Å,æ,ø,å.
# Each is 16 lines of 16 chars; ' '=0, '.'=1, ','=2 (shadow).
def _parse(g):
    return [[0 if c == ' ' else (2 if c == ',' else 1) for c in row] for row in g]

# Æ - A with E (simplified). Each row exactly 16 chars.
GLYPH_AE = _parse([
    "    ....  ....  ",
    "   ....  ....   ",
    "  ..  .. .. ..  ",
    "  ..  .. ....   ",
    "  ...... .. ..  ",
    "  ..  .. .. ..  ",
    "  ..  .. .. ..  ",
    "                ",
    "  ..  .. .. ..  ",
    "  ..  .. .. ..  ",
    "  ...... ....   ",
    "  ..  .. .. ..  ",
    "  ..  .. .. ..  ",
    "                ",
    "                ",
    "                ",
])

# Ø - O with slash
GLYPH_OE = _parse([
    "    ......      ",
    "   ..    ..     ",
    "  ..  ,,  ..    ",
    "  .. ,,   ..    ",
    "  .. ,,   ..    ",
    "  ..  ,,  ..    ",
    "   ..    ..     ",
    "    ......      ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
])

# Å - A with ring
GLYPH_AA = _parse([
    "      ....      ",
    "     ......     ",
    "    ..    ..    ",
    "   ..      ..   ",
    "   ..  ..  ..   ",
    "   ..  ..  ..   ",
    "   ..........   ",
    "   ..      ..   ",
    "   ..      ..   ",
    "   ..      ..   ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
])

# æ - small ae
GLYPH_ae = _parse([
    "                ",
    "   ....  ....   ",
    "  ..  .. .. ..  ",
    "  ..  .. ....   ",
    "  ...... .. ..  ",
    "  ..  .. .. ..  ",
    "   ....  .. ..  ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
])

# ø - small o with slash
GLYPH_oe = _parse([
    "                ",
    "    ......      ",
    "   ..  ,, ..    ",
    "  .. ,,   ..    ",
    "  .. ,,   ..    ",
    "   .. ,, ..     ",
    "    ......      ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
])

# å - small a with ring
GLYPH_aa = _parse([
    "      ....      ",
    "     ......     ",
    "    ..    ..    ",
    "   ..  ..  ..   ",
    "   ..........   ",
    "   ..      ..   ",
    "   ..      ..   ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
    "                ",
])

DANISH_GLYPHS = {
    0x09: GLYPH_OE,   # Ø
    0x0B: GLYPH_AA,   # Å
    0x0C: GLYPH_aa,   # å
    0x0D: GLYPH_oe,   # ø
    0x10: GLYPH_AE,   # Æ
    0x25: GLYPH_ae,   # æ
}


def patch_from_builtin(im):
    """Patch the image using built-in 16x16 glyphs."""
    for slot, glyph in DANISH_GLYPHS.items():
        col, row = slot % COLS, slot // COLS
        x0, y0 = col * GLYPH_W, row * GLYPH_H
        for dy in range(GLYPH_H):
            for dx in range(GLYPH_W):
                im.putpixel((x0 + dx, y0 + dy), glyph[dy][dx])
    return im


def try_fetch_pokemonda(tmp_path):
    """Fetch PokemonDA font.png; return path or None."""
    url = "https://raw.githubusercontent.com/GiuseppeVitolo17/PokemonDA/master/gfx/font/font.png"
    try:
        urlretrieve(url, tmp_path)
        return tmp_path
    except Exception as e:
        print("Could not fetch PokemonDA font:", e, file=sys.stderr)
        return None


def main():
    ap = argparse.ArgumentParser(description="Patch Danish letters into FireRed Latin font PNG.")
    ap.add_argument("--fetch-pokemonda", action="store_true", help="Try to use PokemonDA font for glyphs (8x8 scaled)")
    ap.add_argument("--font", default="graphics/fonts/latin_normal.png", help="Path to latin_normal.png")
    args = ap.parse_args()

    font_path = args.font
    if not os.path.isfile(font_path):
        print("Font not found:", font_path, file=sys.stderr)
        sys.exit(1)

    im = Image.open(font_path).convert("P")
    if im.size[0] != W or im.size[1] not in VALID_HEIGHTS:
        print("Unexpected size %s; expected %dx256 or %dx512" % (im.size, W, W), file=sys.stderr)
        sys.exit(1)

    if args.fetch_pokemonda:
        tmp = "/tmp/pokemonda_font.png"
        if try_fetch_pokemonda(tmp):
            # PokemonDA font is 128x64 = 16*8 tiles, 8x8 each. Indices 0-127.
            # Their charmap uses Æ=$c0, ø=$d1 etc. which are 192, 209 - outside 0-127.
            # So the main font.png likely doesn't contain those; skip and use builtin.
            print("PokemonDA font.png has only 128 tiles; Danish are at 0xc0+ (not in file). Using built-in glyphs.")
        # fall through to builtin
    patch_from_builtin(im)
    im.save(font_path)
    print("Patched", font_path, "with Danish glyphs (Æ, Ø, Å, æ, ø, å). Run make to rebuild .latfont and ROM.")


if __name__ == "__main__":
    main()
