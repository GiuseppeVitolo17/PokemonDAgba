# Pokémon FireRed and LeafGreen (Danish)

**Lær dansk med Pokémon** — This is a decompilation of Pokémon FireRed and LeafGreen with **Danish** in-game translation (dialogues, menus, system messages). It is based on [pret/pokefirered](https://github.com/pret/pokefirered).

Original English ROM references:

* [**pokefirered.gba**](https://datomatic.no-intro.org/?page=show_record&s=23&n=1616) `sha1: 41cb23d8dccc8ebd7c649cd8fbb58eeace6e2fdc`
* [**pokeleafgreen.gba**](https://datomatic.no-intro.org/?page=show_record&s=23&n=1617) `sha1: 574fa542ffebb14be69902d1d36f1ec0a4afd71e`
* [**pokefirered_rev1.gba**](https://datomatic.no-intro.org/?page=show_record&s=23&n=1672) `sha1: dd5945db9b930750cb39d00c84da8571feebf417`
* [**pokeleafgreen_rev1.gba**](https://datomatic.no-intro.org/index.php?page=show_record&s=23&n=1668) `sha1: 7862c67bdecbe21d1d69ce082ce34327e1c6ed5e`

After building this repo (Danish strings), run `make` to produce **pokefirered.gba** (and optionally `make leafgreen`). To get SHA1 hashes of your build: on Linux/macOS use `sha1sum pokefirered.gba`; on Windows use `Get-FileHash -Algorithm SHA1 pokefirered.gba`.

To set up the repository, see [INSTALL.md](INSTALL.md).

**Project repository (push here to track progress):** [GiuseppeVitolo17/PokemonDAgba](https://github.com/GiuseppeVitolo17/PokemonDAgba)  
After cloning, add the remote and push:  
`git remote add origin https://github.com/GiuseppeVitolo17/PokemonDAgba.git`  
`git push -u origin master`

**Danish characters:** The GBA font in this engine does not include the letters **æ, ø, å**. In the source we use **ae, oe, aa** instead (e.g. TRÆNER → TRAENER, SKØNHED → SKOENHED, BÅL → BAAL). The charmap has ä, ö, ü (German) but not Danish-specific glyphs.

**See also:** [pret](https://pret.github.io/) · [pokefirered (original)](https://github.com/pret/pokefirered) · [README på dansk](README_DA.md)
