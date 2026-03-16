# Danish characters (æ, ø, å) in FireRed

Danish letters **Æ, Ø, Å** and **æ, ø, å** are in the character map (first row of the font, right after È, É, Ê, Ë).

## Charmap (first row: tiles 0x09–0x0F)

- **ø** = `0x09`, **Ø** = `0x0A`, **å** = `0x0B`, **Å** = `0x0C`, **æ** = `0x0D`, **Æ** = `0x0E`, **Ö** = `0x0F`

So in-game text can use **æ, ø, å** (and **Æ, Ø, Å**) and the preprocessor emits the correct bytes.

**Small font (menus, bag, etc.):** Run `python3 scripts/sync_danish_small_font.py` after updating `latin_normal.png` so FONT_SMALL shows the same Danish glyphs. The import script runs this automatically.

## Font graphics (so they appear correctly in-game)

### Option 1 (recommended): TTF font for best-looking glyphs

The built-in pixel glyphs are very basic. For **proper Danish letters** that match a pixel-font style:

1. **Download LanaPixel** (CC BY 4.0, has æ, ø, å):
   - OpenGameArt: [LanaPixel – localization-friendly pixel font](https://opengameart.org/content/lanapixel-localization-friendly-pixel-font) (extract the `.ttf` from the zip), or  
   - GitHub: [pixel-utf8-fonts/lanapixel/LanaPixel.ttf](https://github.com/ericoporto/pixel-utf8-fonts/blob/main/lanapixel/LanaPixel.ttf)

2. **Either** let the script download it, or put the TTF in the repo:
   ```bash
   # Auto-download LanaPixel into tools/fonts/ and patch
   (obsolete: patch script removed)
   ```
   Or place `LanaPixel.ttf` in `tools/fonts/` (see `tools/fonts/README.md`), then:
   ```bash
   python3 scripts/import_font_from_desktop.py
   ```
   The script renders Æ, Ø, Å, æ, ø, å from the TTF at 16×16 with a FireRed-style shadow.

3. **Patch all four Latin fonts** and rebuild:
   ```bash
   for f in graphics/fonts/latin_normal.png graphics/fonts/latin_small.png graphics/fonts/latin_male.png graphics/fonts/latin_female.png; do
     python3 scripts/import_font_from_desktop.py --font "$f"
   done
   make
   ```

Do **not** use the Pokemon Red (PokemonDA) font: it’s 8×8 and uses different tile indices, so the Danish glyphs don’t match our layout.

### Option 2: Built-in glyphs (no download)

```bash
python3 scripts/import_font_from_desktop.py
make
```

This uses simple 16×16 glyphs baked into the script. They work but look basic. Use Option 1 for better results.

### Option 3: Edit the font images by hand

The game’s **Latin font** is built from PNGs. To have Æ, Ø, Å, æ, ø, å **draw** correctly (instead of Œ, Ì, Î, œ, Ò, Ï), you can **edit the font images** and redraw those glyph slots:

| Byte | Use in font (glyph at row 0, col N) |
|------|-------------------------------------|
| 0x01 | **Å** (maiuscola) – col 1           |
| 0x08 | **Ø** – col 8                       |
| 0x09 | **ø** (minuscola) – col 9           |
| 0x0B | **å** (minuscola, es. "på","nå") – col 11 |
| 0x10 | **Æ** – col 0 row 1                |
| 0x25 | **æ** – col 5 row 2                |

**Files to edit** (in `graphics/fonts/`):

- `latin_normal.png` – main dialog font  
- `latin_small.png` – small font  
- `latin_male.png` – male player font  
- `latin_female.png` – female player font  

Glyph layout: **16 glyphs per row**, **8×8 or 8×16 pixels per glyph** (see `tools/rsfont/font.c`).  
Index in the image:

- `0x01` → **Å** – column 1, row 0  
- `0x08` → **Ø** – column 8, row 0  
- `0x09` → **ø** – column 9, row 0  
- `0x0B` → **å** (minuscola) – column 11, row 0  ← se nel Pokédex vedi Å, in questa cella del font va la **å minuscola**
- `0x10` → **Æ** – column 0, row 1  
- `0x25` → **æ** – column 5, row 2  

After editing the PNGs, run `make` to regenerate the `.latfont` files and rebuild the ROM.

Until you update the font graphics, in-game text will still show Œ, Ì, Î, œ, Ò, Ï in place of Æ, Ø, Å, æ, ø, å, but the correct bytes are already used and the build works.

---

## Analisi approfondita: perché nei dialoghi la å minuscola si vede normalmente

Nei dialoghi di gioco (messaggi NPC, finestre di testo in campo, menu messaggi) la **å minuscola** viene disegnata correttamente perché il testo usa sempre i font “normali”, le cui immagini sono state aggiornate con il glifo å. In altre schermate (es. Pokédex prima della modifica) veniva usato un font diverso, con un’immagine diversa dove la stessa posizione 0x0B aveva un glifo diverso.

### 1. Flusso del testo nei dialoghi

1. **Script / stringhe**  
   Le stringhe (es. `"Nå, hvad?"`) sono nel charmap: la **å** è mappata al **byte 0x0B**. Il preprocessore emette quindi 0x0B nel testo.

2. **Finestra di dialogo in campo**  
   In `src/field_message_box.c`:
   - `ExpandStringAndStartDrawFieldMessageBox(str)` chiama `StringExpandPlaceholders(gStringVar4, str)` e poi **`AddTextPrinterDiffStyle(TRUE)`**.
   - `StartDrawFieldMessageBox()` chiama di nuovo **`AddTextPrinterDiffStyle(TRUE)`**.

3. **Scelta del font per il dialogo**  
   In `src/new_menu_helpers.c`, **`AddTextPrinterDiffStyle`** sceglie il font in base al colore del testo dell’NPC:
   - **FONT_MALE** (testo blu) → `FontFunc_Male` → dati da **`latin_male.latfont`** (da `latin_male.png`)
   - **FONT_FEMALE** (testo rosso) → `FontFunc_Female` → **`latin_female.latfont`** (da `latin_female.png`)
   - **FONT_NORMAL** (neutro/Pokémon, grigio) → `FontFunc_Normal` → **`latin_normal.latfont`** (da `latin_normal.png`)

   Altri messaggi (es. menu principale) usano **`AddTextPrinterForMessage`**, che usa sempre **FONT_NORMAL** → `latin_normal`.

4. **Rendering**  
   `AddTextPrinterParameterized2` → `AddTextPrinter` (in `text_printer.c`) usa `gFonts[fontId].fontFunction`. Ogni carattere (incluso 0x0B) viene disegnato prendendo il **tile** corrispondente dall’immagine del font selezionato (`text.c`: `sFontNormalLatinGlyphs`, `sFontMaleLatinGlyphs`, `sFontFemaleLatinGlyphs` sono inclusi da `latin_normal.latfont`, `latin_male.latfont`, `latin_female.latfont`).

Quindi: **nei dialoghi il byte 0x0B (å) viene sempre disegnato con uno dei font normali (latin_normal / latin_male / latin_female)**. Se hai aggiornato `latin_normal.png` (e copiato su male/female) con la **å minuscola** nella posizione 0x0B (colonna 11, riga 0), nei dialoghi la å si vede normalmente.

### 2. Perché altrove (es. Pokédex) si vedeva male

- **Pokédex** (prima della modifica) usava **FONT_SMALL** in `src/pokedex_screen.c`.
- FONT_SMALL è servito da **`FontFunc_Small`** → **`latin_small.latfont`** → **`latin_small.png`** (`src/text.c`: `sFontSmallLatinGlyphs`).
- **`latin_small.png`** è un’**immagine diversa** da `latin_normal.png`. La **stessa posizione tile 0x0B** in quella immagine (nel font originale o non aggiornato) conteneva un altro glifo (es. maiuscola o carattere tedesco), quindi lo stesso byte 0x0B veniva disegnato come “Å” o altro.

Stessa charmap, stesso byte 0x0B; cambia solo **quale immagine font** viene usata:
- Dialoghi → FONT_NORMAL / MALE / FEMALE → `latin_normal` / `latin_male` / `latin_female` → tile 0x0B = å minuscola ✓  
- Pokédex (prima fix) → FONT_SMALL → `latin_small` → tile 0x0B = glifo sbagliato ✗  

La soluzione applicata è usare **FONT_NORMAL** anche nel Pokédex, così anche lì si usa `latin_normal` e la å torna corretta.

### 3. Riepilogo tecnico

| Contesto              | Funzione / percorso              | Font usato        | Immagine font (dati)     |
|-----------------------|-----------------------------------|-------------------|---------------------------|
| Dialoghi in campo     | `AddTextPrinterDiffStyle`         | FONT_NORMAL/MALE/FEMALE | latin_normal / latin_male / latin_female |
| Messaggi menu         | `AddTextPrinterForMessage`        | FONT_NORMAL       | latin_normal              |
| Pokédex (dopo fix)    | `pokedex_screen.c`               | FONT_NORMAL       | latin_normal              |
| Pokédex (prima)       | id.                              | FONT_SMALL        | latin_small               |
| Bag, Item PC, Shop…   | varie                            | FONT_SMALL dove usato | latin_small            |

In sintesi: **la å minuscola si vede bene nei dialoghi perché lì il gioco usa sempre i font “normali” (latin_normal / male / female), le cui immagini hanno il glifo å nella tile 0x0B; il Pokédex prima usava il font “small”, con un’immagine diversa dove 0x0B non era la å.**
