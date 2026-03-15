#!/usr/bin/env python3
"""
Import a hand-edited 256x512 font PNG from Desktop into the game format.
You use exactly 4 colours; the script maps each pixel to the nearest of the
game's 4 palette colours (bg, fg, shadow, white). No threshold guessing.

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
    im = Image.open(src)
    if im.size != (256, 512):
        print("Expected 256x512, got", im.size, file=sys.stderr)
        sys.exit(1)
    if im.mode not in ("RGB", "RGBA", "P"):
        im = im.convert("RGBA")
    if im.mode == "P":
        im = im.convert("RGBA")

    out = Image.new("P", (256, 512))
    out.putpalette([c for rgb in PAL for c in rgb])

    for y in range(512):
        for x in range(256):
            p = im.getpixel((x, y))
            if len(p) == 4:
                r, g, b, a = p
                if a < 128:
                    out.putpixel((x, y), 0)
                    continue
            else:
                r, g, b = p[:3]
            # Nearest of the 4 game colours (no reordering)
            best_i = 0
            best_d = 1e9
            for i, (pr, pg, pb) in enumerate(PAL):
                d = (r - pr) ** 2 + (g - pg) ** 2 + (b - pb) ** 2
                if d < best_d:
                    best_d, best_i = d, i
            out.putpixel((x, y), best_i)

    out.save(dest)
    print("Converted", src, "->", dest, "(4-colour nearest-palette)")

if __name__ == "__main__":
    main()
