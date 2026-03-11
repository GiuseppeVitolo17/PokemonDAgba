# Prompt: Translate Pokémon LeafGreen to Danish

Copy the text below into a new agent when you start the LeafGreen translation project.

---

## Agent prompt (copy from here)

**Goal:** Translate the Pokémon LeafGreen disassembly (this repo) into **Danish**, the same way the Pokémon Red/Blue Danish project (pokered-da / PokemonDA) was done. Aim for a **full in-game translation** (dialogues, menus, system messages) and keep the repo buildable and CI-friendly.

**What to do:**

1. **Understand the layout**
   - Find where in-game text lives (often `text/`, `data/text/`, or similar). Keep **labels**, **directives** (`text_ram`, `para`, `line`, `cont`), and **placeholders** (`<PLAYER>`, `@`, `<RIVAL>`, etc.) **unchanged**. Only translate the **string content** inside `"..."`.
   - Keep or consistently localise token names (e.g. #MON, GYM, CENTER, MART). Match the style of the existing project if it already has partial translations.

2. **Translation rules**
   - Translate every player-facing string to Danish. Preserve line breaks and `text`/`line`/`para`/`cont` structure so the assembler and game layout stay valid.
   - After editing, ensure every line that has `text`/`line`/`para`/`cont` has an **even number of double-quotes** on that line (no unterminated strings). Use or add a **string checker tool** (e.g. a small C or script that scans such lines and reports `file:line: unclosed string` if the quote count is odd).

3. **Tools to use or add**
   - **String checker:** For each file under `text/` and `data/text/`, check that lines containing `text`, `line`, `para`, or `cont` have balanced quotes. Add a tool like `tools/check_strings.c` if missing, and run it on all text files before claiming translation is complete.
   - **Find remaining English:** Search for common English patterns (e.g. `"The `, `"You `, `"That's`, `"It's `, `"Don't`, `"Have `, `"What `, `received`, `obtained`, `congratulations`) in `text/**/*.asm` and `data/text/**/*.asm` to catch missed strings. Fix any you find.
   - **Build:** Ensure the project builds (e.g. `make` with RGBDS in PATH). Run a clean build after major changes and fix any assembly or link errors.

4. **README and docs**
   - Add or update a short **English README** (e.g. README.md): “Learn Danish with Pokémon” style intro, **ROM table** with **SHA1** hashes for a clean build (run build then `sha1sum` / `Get-FileHash -Algorithm SHA1` on the built ROMs), link to INSTALL, build badge and “See also” / pret links if appropriate.
   - Add or update **README_DA.md** (Danish) with the same structure and a note like “99% færdig” / “99% complete” when almost done.
   - Update **INSTALL.md** (or equivalent) for this repo: correct clone URL, project name, and build steps (including RGBDS version and PATH note for Windows).

5. **CI (GitHub Actions)**
   - If the workflow uses `actions/checkout@master`, change it to `actions/checkout@v4` to avoid deprecated ref errors.
   - If CI builds **rgbds** from source (e.g. gbdev/rgbds), add a step to install **build dependencies** (e.g. `build-essential`, `bison`, `libpng-dev`, `pkg-config` on Ubuntu) and run **`make -j$(nproc)`** before **`sudo make install`** so the build doesn’t fail.

6. **Git and history (optional)**
   - If the user wants commits under their name, set `git config user.name` and `git config user.email` for this repo (e.g. to their GitHub username and `...@users.noreply.github.com`). If they also want **past commits** rewritten to that identity, use `git filter-branch --env-filter` to set `GIT_AUTHOR_*` and `GIT_COMMITTER_*`, then `git push --force origin master` (only if they’re sure no one else depends on the current history).

7. **Workflow**
   - Translate in **batches** (e.g. by area or file). After each batch, run the string checker and a quick build. At the end, do a final pass for remaining English and update README/README_DA/INSTALL and CI as above.

**Do not:** Change logic, labels, or non-text assets. Only translate human-readable strings and update docs/CI as described.

---

## End of prompt

Use this in a new chat/agent for the LeafGreen repo. Adjust repo paths (e.g. `text/` vs `data/text/`) to match the LeafGreen disassembly structure when you start.
