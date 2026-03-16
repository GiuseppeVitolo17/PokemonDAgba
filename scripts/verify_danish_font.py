#!/usr/bin/env python3
"""
Verify that Danish glyph tiles (0x09–0x0F) in the font PNG have pixel data.
If a tile is empty (all bg or same color), that character will not show in-game.
Run from repo root. Requires: graphics/fonts/latin_normal.png
"""

import os
import sys

try:
    from PIL import Image
except ImportError:
    print("Need Pillow: pip install Pillow", file=sys.stderr)
    sys.exit(1)

TILE = 16
NAMES = ("ø", "Ø", "å", "Å", "æ", "Æ", "Ö")
# Game palette index 0 is typically bg
BG_INDEX = 0


def main():
    path = "graphics/fonts/latin_normal.png"
    if not os.path.isfile(path):
        print("Not found:", path, file=sys.stderr)
        sys.exit(1)
    im = Image.open(path)
    if im.size != (256, 512):
        print("Expected 256x512, got", im.size, file=sys.stderr)
        sys.exit(1)
    if im.mode != "P":
        im = im.convert("P")
    pixels = im.load()
    empty = []
    for i in range(9, 16):
        x0, y0 = (i % 16) * TILE, (i // 16) * TILE
        colors = set()
        for dy in range(TILE):
            for dx in range(TILE):
                colors.add(pixels[x0 + dx, y0 + dy])
        non_bg = colors - {BG_INDEX}
        if not non_bg:
            empty.append((i, NAMES[i - 9]))
    if empty:
        print("Empty or bg-only tiles (character will NOT show in-game):", file=sys.stderr)
        for idx, name in empty:
            print("  Tile 0x%02X (%s) at column %d, row 0 (pixels x=%d–%d, y=0–%d)" % (idx, name, idx, idx * 16, idx * 16 + 15, TILE - 1), file=sys.stderr)
        print("\nDraw the missing glyphs in your tileset (e.g. Desktop image) in those 16x16 positions, then reimport.", file=sys.stderr)
        sys.exit(1)
    print("All Danish tiles (0x09–0x0F) have pixel data.")
    print("Tile order in first row: 9=ø 10=Ø 11=å 12=Å 13=æ 14=Æ 15=Ö")
    print("If some still don't show: run 'make clean-assets' then 'make' to rebuild .latfont from the PNG.")


if __name__ == "__main__":
    main()
