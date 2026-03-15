# Fonts for Danish (æ, ø, å) glyphs

Put a **TTF pixel font** that includes Æ, Ø, Å, æ, ø, å here. The patch script will render these at 16×16 with a FireRed-style shadow.

## Recommended: LanaPixel

**LanaPixel** is a localization-friendly pixel font (CC BY 4.0) with Nordic characters.

1. Download from one of:
   - **OpenGameArt**: https://opengameart.org/content/lanapixel-localization-friendly-pixel-font  
     (Get e.g. `LanaPixel_BitmapOnly.zip` or `LanaPixel_Everything.zip`, extract the `.ttf`)
   - **GitHub**: https://github.com/ericoporto/pixel-utf8-fonts  
     (Clone or download, copy `lanapixel/LanaPixel.ttf` here)

2. Place the TTF in this folder:
   ```
   tools/fonts/LanaPixel.ttf
   ```

3. From the repo root, run:
   ```bash
   python3 scripts/patch_danish_font.py
   ```
   The script auto-detects `tools/fonts/LanaPixel.ttf`. Or pass it explicitly:
   ```bash
   python3 scripts/patch_danish_font.py --ttf tools/fonts/LanaPixel.ttf
   ```

4. Patch all four Latin fonts and rebuild:
   ```bash
   for f in graphics/fonts/latin_normal.png graphics/fonts/latin_small.png graphics/fonts/latin_male.png graphics/fonts/latin_female.png; do
     python3 scripts/patch_danish_font.py --font "$f"
   done
   make
   ```

## Other fonts

Any TTF that has the characters Æ, Ø, Å, æ, ø, å will work. Pixel or “bitmap-style” fonts usually look best at 16×16. Pass the path with `--ttf`.
