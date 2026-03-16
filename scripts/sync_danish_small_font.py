#!/usr/bin/env python3
"""
Copy Danish glyph tiles (ø, Ø, å, Å, æ, Æ, Ö) from latin_normal.png to latin_small.png
so they show correctly when the game uses FONT_SMALL (menus, bag, shop, etc.).

Charmap positions: 0x09–0x0F = ø, Ø, å, Å, æ, Æ, Ö
Run from repo root after updating latin_normal (e.g. import_font_from_desktop.py).
"""

import os
import sys

try:
    from PIL import Image
except ImportError:
    print("Need Pillow: pip install Pillow", file=sys.stderr)
    sys.exit(1)

TILE = 16
# Danish + Ö at tile indices 9–15 (first row in both images)
DANISH_TILE_START = 9
DANISH_TILE_END = 16  # 0x0F + 1


def main():
    normal_path = "graphics/fonts/latin_normal.png"
    small_path = "graphics/fonts/latin_small.png"
    if not os.path.isfile(normal_path):
        print("Not found:", normal_path, file=sys.stderr)
        sys.exit(1)
    if not os.path.isfile(small_path):
        print("Not found:", small_path, file=sys.stderr)
        sys.exit(1)

    normal = Image.open(normal_path)
    small = Image.open(small_path)
    if normal.mode != small.mode:
        small = small.convert(normal.mode)
    if normal.size != (256, 512) or small.size != (256, 256):
        print("Expected latin_normal 256x512 and latin_small 256x256", file=sys.stderr)
        sys.exit(1)

    # First row: y 0..TILE
    for i in range(DANISH_TILE_START, DANISH_TILE_END):
        x = i * TILE
        box_n = (x, 0, x + TILE, TILE)
        box_s = (x, 0, x + TILE, TILE)
        tile = normal.crop(box_n)
        small.paste(tile, box_s)

    small.save(small_path)
    print("Synced Danish tiles (0x09–0x0F) from latin_normal to latin_small.")


if __name__ == "__main__":
    main()
