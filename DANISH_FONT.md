# Danish characters (æ, ø, å) in FireRed

Danish letters **Æ, Ø, Å** and **æ, ø, å** are now in the character map (same approach as [PokemonDA](https://github.com/GiuseppeVitolo17/PokemonDA) for Pokémon Red/Blue).

## Charmap

- **Æ** and **æ** use byte `0x10` (same slot as Œ) and `0x25` (same as œ).
- **Ø** and **ø** use byte `0x09` (same as Ì) and `0x0D` (same as Ò).
- **Å** and **å** use byte `0x0B` (same as Î) and `0x0C` (same as Ï).

So in-game text can use real **æ, ø, å** (and **Æ, Ø, Å**) and the preprocessor will emit the correct bytes.

## Font graphics (so they appear correctly in-game)

### Option 1 (recommended): TTF font for best-looking glyphs

The built-in pixel glyphs are very basic. For **proper Danish letters** that match a pixel-font style:

1. **Download LanaPixel** (CC BY 4.0, has æ, ø, å):
   - OpenGameArt: [LanaPixel – localization-friendly pixel font](https://opengameart.org/content/lanapixel-localization-friendly-pixel-font) (extract the `.ttf` from the zip), or  
   - GitHub: [pixel-utf8-fonts/lanapixel/LanaPixel.ttf](https://github.com/ericoporto/pixel-utf8-fonts/blob/main/lanapixel/LanaPixel.ttf)

2. **Either** let the script download it, or put the TTF in the repo:
   ```bash
   # Auto-download LanaPixel into tools/fonts/ and patch
   python3 scripts/patch_danish_font.py --fetch-lanapixel
   ```
   Or place `LanaPixel.ttf` in `tools/fonts/` (see `tools/fonts/README.md`), then:
   ```bash
   python3 scripts/patch_danish_font.py
   ```
   The script renders Æ, Ø, Å, æ, ø, å from the TTF at 16×16 with a FireRed-style shadow.

3. **Patch all four Latin fonts** and rebuild:
   ```bash
   for f in graphics/fonts/latin_normal.png graphics/fonts/latin_small.png graphics/fonts/latin_male.png graphics/fonts/latin_female.png; do
     python3 scripts/patch_danish_font.py --font "$f"
   done
   make
   ```

Do **not** use the Pokemon Red (PokemonDA) font: it’s 8×8 and uses different tile indices, so the Danish glyphs don’t match our layout.

### Option 2: Built-in glyphs (no download)

```bash
python3 scripts/patch_danish_font.py
make
```

This uses simple 16×16 glyphs baked into the script. They work but look basic. Use Option 1 for better results.

### Option 3: Edit the font images by hand

The game’s **Latin font** is built from PNGs. To have Æ, Ø, Å, æ, ø, å **draw** correctly (instead of Œ, Ì, Î, œ, Ò, Ï), you can **edit the font images** and redraw those glyph slots:

| Byte | Current glyph | Replace with |
|------|----------------|--------------|
| 0x09 | Ì              | **Ø**        |
| 0x0B | Î              | **Å**        |
| 0x0C | Ï              | **å**        |
| 0x0D | Ò              | **ø**        |
| 0x10 | Œ              | **Æ**        |
| 0x25 | œ              | **æ**        |

**Files to edit** (in `graphics/fonts/`):

- `latin_normal.png` – main dialog font  
- `latin_small.png` – small font  
- `latin_male.png` – male player font  
- `latin_female.png` – female player font  

Glyph layout: **16 glyphs per row**, **8×8 or 8×16 pixels per glyph** (see `tools/rsfont/font.c`).  
Index in the image:

- `0x09` → column 9, row 0  
- `0x0B` → column 11, row 0  
- `0x0C` → column 12, row 0  
- `0x0D` → column 13, row 0  
- `0x10` → column 0, row 1  
- `0x25` → column 5, row 2  

After editing the PNGs, run `make` to regenerate the `.latfont` files and rebuild the ROM.

Until you update the font graphics, in-game text will still show Œ, Ì, Î, œ, Ò, Ï in place of Æ, Ø, Å, æ, ø, å, but the correct bytes are already used and the build works.
