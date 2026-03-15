#!/usr/bin/env python3
"""
Import a hand-edited 256x512 RGBA font PNG from Desktop into the game format.
Converts to 4-color indexed (bg, fg, shadow, white) and overwrites latin_normal.png.

Usage (from repo root):
  python3 scripts/import_font_from_desktop.py [path_to_image.png]
Default path: ~/Desktop/Untitled.png
"""

import os
import sys

try:
    from PIL import Image
except ImportError:
    print("Need Pillow: pip install Pillow", file=sys.stderr)
    sys.exit(1)

# Game palette from tools/gbagfx/font.c
PAL = [
    (0x90, 0xC8, 0xFF),  # 0 = bg
    (0x38, 0x38, 0x38),  # 1 = fg
    (0xD8, 0xD8, 0xD8),  # 2 = shadow
    (0xFF, 0xFF, 0xFF),  # 3 = white
]

# Tile indices: period '.' = 0xAD, æ = 0x25 (charmap)
TILE_PERIOD = 0xAD   # row 10, col 13 -> x 208-223, y 160-175
TILE_AE = 0x25       # row 2, col 5  -> x 80-95, y 32-47


def cleanup_transparent_pixels(out):
    """Force to bg (0) pixels that should be transparent: under period, right of æ, last line of empty tiles."""
    w, h = out.size
    # 1) Under the period ".": tile 0xAD. Clear bottom part of tile (under the dot).
    tr, tc = TILE_PERIOD // 16, TILE_PERIOD % 16
    x0, y0 = tc * 16, tr * 16
    for dy in range(5, 16):  # rows 5-15 within tile (under the dot)
        for dx in range(16):
            out.putpixel((x0 + dx, y0 + dy), 0)
    # 2) Right of æ: tile 0x25. Clear right side of tile.
    tr, tc = TILE_AE // 16, TILE_AE % 16
    x0, y0 = tc * 16, tr * 16
    for dx in range(10, 16):  # columns 10-15 within tile
        for dy in range(16):
            out.putpixel((x0 + dx, y0 + dy), 0)
    # 3) Last line of each 16px tile: if row is mostly non-fg (stray pixels), clear to bg.
    for ty in range(h // 16):
        for tx in range(16):
            x0, y0 = tx * 16, ty * 16
            last_row = [out.getpixel((x0 + dx, y0 + 15)) for dx in range(16)]
            fg_count = sum(1 for c in last_row if c == 1)
            if fg_count <= 1:  # empty or stray pixel only
                for dx in range(16):
                    out.putpixel((x0 + dx, y0 + 15), 0)


def main():
    src = sys.argv[1] if len(sys.argv) > 1 else os.path.expanduser("~/Desktop/Untitled.png")
    dest = "graphics/fonts/latin_normal.png"
    if not os.path.isfile(src):
        print("File not found:", src, file=sys.stderr)
        sys.exit(1)
    im = Image.open(src).convert("RGBA")
    if im.size != (256, 512):
        print("Expected 256x512, got", im.size, file=sys.stderr)
        sys.exit(1)
    out = Image.new("P", (256, 512))
    out.putpalette([c for rgb in PAL for c in rgb])
    for y in range(512):
        for x in range(256):
            r, g, b, a = im.getpixel((x, y))
            if a < 140 or (r + g + b) > 660:  # stricter: more pixels become bg
                idx = 0
            else:
                s = r + g + b
                idx = 1 if s < 200 else (2 if s < 580 else 3)
            out.putpixel((x, y), idx)
    cleanup_transparent_pixels(out)
    out.save(dest)
    print("Converted", src, "->", dest, "(with transparent cleanup)")

if __name__ == "__main__":
    main()
