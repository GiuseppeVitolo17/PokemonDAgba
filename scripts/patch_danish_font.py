#!/usr/bin/env python3
"""
Patch Danish letters (Æ, Ø, Å, æ, ø, å) into the FireRed Latin font PNG.

Options:
  1. --ttf PATH   Use a TTF font (recommended). Use LanaPixel or any pixel font
                  that has æ, ø, å. Renders at 16x16 with FireRed-style shadow.
  2. Built-in    Default: simple 16x16 glyphs (no download, look basic).
  3. --fetch-pokemonda  PokemonDA font (8x8); Danish slots not in their PNG, so
                        we fall back to built-in.

Charmap slots: 0x09→Ø  0x0B→Å  0x0C→å  0x0D→ø  0x10→Æ  0x25→æ

Recommended: Download LanaPixel (CC BY 4.0) from OpenGameArt or GitHub
  ericoporto/pixel-utf8-fonts, put LanaPixel.ttf in tools/fonts/ or pass --ttf.

Run: python3 scripts/patch_danish_font.py [--ttf LanaPixel.ttf]
Then: make
"""

import argparse
import os
import sys
from urllib.request import urlretrieve

try:
    from PIL import Image, ImageFont, ImageDraw
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

# For TTF: character -> slot (same as DANISH_GLYPHS keys)
TTF_CHARS = [
    ("Æ", 0x10), ("Ø", 0x09), ("Å", 0x0B),
    ("æ", 0x25), ("ø", 0x0D), ("å", 0x0C),
]


def render_glyph_from_ttf(font_path, char, size=28, cell=32, shadow_offset=2):
    """
    Render one character from a TTF into a 16x16 glyph with FireRed-style
    shadow. Returns a 16x16 list-of-rows of palette indices (0=bg, 1=fg, 2=shadow).
    """
    try:
        font = ImageFont.truetype(font_path, size)
    except Exception as e:
        print("Failed to load TTF:", e, file=sys.stderr)
        return None
    # Render at 2x resolution then downscale for crisp pixels
    img = Image.new("RGB", (cell, cell), (255, 255, 255))
    draw = ImageDraw.Draw(img)
    # Get bounding box to center the glyph
    try:
        bbox = draw.textbbox((0, 0), char, font=font)
        w, h = bbox[2] - bbox[0], bbox[3] - bbox[1]
        x, y = (cell - w) // 2 - bbox[0], (cell - h) // 2 - bbox[1]
    except AttributeError:
        w, h = draw.textsize(char, font=font)
        x, y = (cell - w) // 2, (cell - h) // 2
    # Shadow first (bottom-right), then main
    draw.text((x + shadow_offset, y + shadow_offset), char, font=font, fill=(180, 180, 180))
    draw.text((x, y), char, font=font, fill=(0, 0, 0))
    # Downscale to 16x16 with NEAREST to keep pixels sharp
    img_small = img.resize((GLYPH_W, GLYPH_H), getattr(Image, "Resampling", Image).NEAREST)
    # Convert to palette: white=0, grey=2, black=1
    glyph = []
    for py in range(GLYPH_H):
        row = []
        for px in range(GLYPH_W):
            r, g, b = img_small.getpixel((px, py))[:3]
            if r > 200 and g > 200 and b > 200:
                row.append(0)
            elif r < 80 and g < 80 and b < 80:
                row.append(1)
            else:
                row.append(2)
        glyph.append(row)
    return glyph


def patch_from_ttf(im, ttf_path):
    """Patch the image using glyphs rendered from a TTF file."""
    for char, slot in TTF_CHARS:
        glyph = render_glyph_from_ttf(ttf_path, char)
        if glyph is None:
            print("Falling back to built-in glyphs.", file=sys.stderr)
            return patch_from_builtin(im)
        col, row = slot % COLS, slot // COLS
        x0, y0 = col * GLYPH_W, row * GLYPH_H
        for dy in range(GLYPH_H):
            for dx in range(GLYPH_W):
                im.putpixel((x0 + dx, y0 + dy), glyph[dy][dx])
    return im


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


LANAPIXEL_URL = "https://github.com/ericoporto/pixel-utf8-fonts/raw/refs/heads/main/lanapixel/LanaPixel.ttf"
LANAPIXEL_DEST = "tools/fonts/LanaPixel.ttf"


def try_fetch_lanapixel():
    """Download LanaPixel.ttf to tools/fonts/; return path or None."""
    os.makedirs(os.path.dirname(LANAPIXEL_DEST), exist_ok=True)
    try:
        urlretrieve(LANAPIXEL_URL, LANAPIXEL_DEST)
        if os.path.isfile(LANAPIXEL_DEST) and os.path.getsize(LANAPIXEL_DEST) > 1000:
            return LANAPIXEL_DEST
    except Exception as e:
        print("Could not fetch LanaPixel:", e, file=sys.stderr)
    return None


def main():
    ap = argparse.ArgumentParser(description="Patch Danish letters into FireRed Latin font PNG.")
    ap.add_argument("--ttf", metavar="PATH", help="Use TTF font for glyphs (e.g. LanaPixel.ttf). Best quality.")
    ap.add_argument("--fetch-lanapixel", action="store_true", help="Download LanaPixel.ttf to tools/fonts/ and use it for glyphs")
    ap.add_argument("--fetch-pokemonda", action="store_true", help="Try PokemonDA font (Danish not in their PNG; falls back to built-in)")
    ap.add_argument("--font", default="graphics/fonts/latin_normal.png", help="Path to latin font PNG to patch")
    args = ap.parse_args()

    font_path = args.font
    if not os.path.isfile(font_path):
        print("Font not found:", font_path, file=sys.stderr)
        sys.exit(1)

    im = Image.open(font_path).convert("P")
    if im.size[0] != W or im.size[1] not in VALID_HEIGHTS:
        print("Unexpected size %s; expected %dx256 or %dx512" % (im.size, W, W), file=sys.stderr)
        sys.exit(1)

    ttf_path = args.ttf
    if args.fetch_lanapixel:
        print("Fetching LanaPixel.ttf...")
        ttf_path = try_fetch_lanapixel()
        if not ttf_path:
            print("Using built-in glyphs.", file=sys.stderr)
            ttf_path = None
    if not ttf_path and os.path.isfile(LANAPIXEL_DEST):
        ttf_path = LANAPIXEL_DEST
    if ttf_path:
        if not os.path.isfile(ttf_path):
            print("TTF not found:", ttf_path, "; using built-in glyphs.", file=sys.stderr)
            patch_from_builtin(im)
        else:
            print("Using TTF:", ttf_path)
            patch_from_ttf(im, ttf_path)
    elif args.fetch_pokemonda:
        tmp = "/tmp/pokemonda_font.png"
        if try_fetch_pokemonda(tmp):
            print("PokemonDA font.png has only 128 tiles; Danish at 0xc0+ not in file. Using built-in glyphs.")
        patch_from_builtin(im)
    else:
        patch_from_builtin(im)
    im.save(font_path)
    print("Patched", font_path, "with Danish glyphs (Æ, Ø, Å, æ, ø, å). Run make to rebuild .latfont and ROM.")


if __name__ == "__main__":
    main()
