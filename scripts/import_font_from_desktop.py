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
            if a < 128:
                idx = 0
            else:
                s = r + g + b
                idx = 1 if s < 200 else (2 if s < 620 else 3)
            out.putpixel((x, y), idx)
    out.save(dest)
    print("Converted", src, "->", dest)

if __name__ == "__main__":
    main()
