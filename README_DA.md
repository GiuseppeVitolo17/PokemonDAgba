# Pokémon FireRed og LeafGreen (dansk)

**Lær dansk med Pokémon** — Dette er en dekompilering af Pokémon FireRed og LeafGreen med **dansk** spiltekst (dialoger, menuer, systembeskeder). Baseret på [pret/pokefirered](https://github.com/pret/pokefirered).

Byg: `make` (FireRed) eller `make leafgreen` (LeafGreen). Se [INSTALL.md](INSTALL.md) for at sætte udviklingsmiljøet op.

## Hurtig kompilering på macOS

I Terminal på macOS (tilpas sti hvis projektet ligger et andet sted):

```bash
cd ~/Documents/PokemonDAgba
brew install pkg-config libpng arm-none-eabi-gcc
cd ..
git clone https://github.com/pret/agbcc
cd agbcc
./build.sh
./install.sh ../PokemonDAgba
cd ../PokemonDAgba
make -j8
```

Dette bygger `pokefirered.gba` i projektmappen (som du f.eks. kan kopiere til Skrivebordet).

**Status:** Dansk oversættelse med **æ, ø, å** i charmap og font (data-tekster, evner, menuer, item-navne m.m. på dansk).

**Danske bogstaver:** Charmap og font understøtter **Æ, Ø, Å, æ, ø, å** (se `charmap.txt` og `DANISH_FONT.md`). Brug **å** (ikke â) i spiltekst.

**Se også:** [pret](https://pret.github.io/) · [pokefirered (original)](https://github.com/pret/pokefirered) · [README in English](README.md)
