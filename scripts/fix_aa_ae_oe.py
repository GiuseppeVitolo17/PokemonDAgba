#!/usr/bin/env python3
"""
Replace aa→â, ae→ä, oe→ö (and uppercase) only inside string literals
in all game text files, so C identifiers and hex constants are not changed.
"""
import os
import re
import sys

# Substitutions: (from, to) - order matters: do longer first to avoid double-replace
SUBST = [
    ("AA", "Â"),
    ("aa", "â"),
    ("AE", "Ä"),
    ("ae", "ä"),
    ("OE", "Ö"),
    ("oe", "ö"),
]


def replace_inside_strings(content: str) -> str:
    """Replace aa/ae/oe only inside double-quoted string literals."""
    result = []
    i = 0
    n = len(content)
    in_string = False
    escape_next = False
    # For asm: .string "..."  For C: _("...") or "..."
    while i < n:
        c = content[i]
        if escape_next:
            result.append(c)
            escape_next = False
            i += 1
            continue
        if c == "\\" and in_string:
            result.append(c)
            escape_next = True
            i += 1
            continue
        if c == '"' and not escape_next:
            in_string = not in_string
            result.append(c)
            i += 1
            continue
        if in_string:
            # Check for 2-char sequences to replace
            replaced = False
            for old, new in SUBST:
                if content[i : i + len(old)] == old:
                    result.append(new)
                    i += len(old)
                    replaced = True
                    break
            if not replaced:
                result.append(c)
                i += 1
        else:
            result.append(c)
            i += 1
    return "".join(result)


def process_file(path: str, dry_run: bool = False) -> bool:
    """Return True if file was changed."""
    try:
        with open(path, "r", encoding="utf-8", errors="replace") as f:
            orig = f.read()
    except Exception as e:
        print(f"Read error {path}: {e}", file=sys.stderr)
        return False
    new_content = replace_inside_strings(orig)
    if new_content == orig:
        return False
    if not dry_run:
        with open(path, "w", encoding="utf-8", newline="") as f:
            f.write(new_content)
    return True


def process_json(path: str, dry_run: bool = False) -> bool:
    """Replace in JSON string values only (not keys)."""
    import json
    try:
        with open(path, "r", encoding="utf-8") as f:
            data = json.load(f)
    except Exception as e:
        print(f"JSON read error {path}: {e}", file=sys.stderr)
        return False

    def replace_in_obj(obj):
        changed = False
        if isinstance(obj, dict):
            for k, v in obj.items():
                if isinstance(v, str):
                    new_v = replace_inside_strings('"' + v.replace('\\', '\\\\').replace('"', '\\"') + '"')[1:-1]
                    # Unescape for the replacement we did inside the fake string
                    new_v = new_v.replace('\\"', '"').replace('\\\\', '\\')
                    for old, new in SUBST:
                        new_v = new_v.replace(old, new)
                    if new_v != v:
                        obj[k] = new_v
                        changed = True
                else:
                    changed |= replace_in_obj(v)
        elif isinstance(obj, list):
            for i, item in enumerate(obj):
                if isinstance(item, str):
                    for old, new in SUBST:
                        item = item.replace(old, new)
                    if item != obj[i]:
                        obj[i] = item
                        changed = True
                else:
                    changed |= replace_in_obj(item)
        return changed

    # Simpler: just do replace_inside_strings on the raw file content for JSON,
    # but JSON values are "...": "value" - so we need to only replace in value strings.
    # Actually replace_inside_strings already only replaces inside "...", so if we
    # run it on the whole file, it will replace inside every "..." including keys.
    # Keys are usually "english", "itemId" etc. - no aa/ae/oe. So running
    # replace_inside_strings on the whole JSON file is correct.
    with open(path, "r", encoding="utf-8") as f:
        orig = f.read()
    new_content = replace_inside_strings(orig)
    if new_content == orig:
        return False
    if not dry_run:
        with open(path, "w", encoding="utf-8", newline="") as f:
            f.write(new_content)
    return True


def main():
    base = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    dry_run = "--dry-run" in sys.argv
    if dry_run:
        sys.argv.remove("--dry-run")

    extensions = (".inc", ".s", ".c", ".h")
    json_files = []
    text_files = []

    for root, _dirs, files in os.walk(base):
        # Skip .git and build dirs
        if ".git" in root or "build" in root or root.endswith("build"):
            continue
        for f in files:
            path = os.path.join(root, f)
            rel = os.path.relpath(path, base)
            if rel.startswith("asm") and "macros" in rel:
                continue
            if f.endswith(".json") and "data" in rel and "items" in rel:
                json_files.append(path)
            elif f.endswith(extensions):
                # Only data/ and src/ for game text
                if rel.startswith("data/") or rel.startswith("src/"):
                    if "include" in rel and rel.startswith("include/"):
                        text_files.append(path)
                    elif rel.startswith("src/"):
                        text_files.append(path)
                    elif rel.startswith("data/"):
                        text_files.append(path)

    changed = 0
    for path in text_files:
        if process_file(path, dry_run=dry_run):
            changed += 1
            print(path)
    for path in json_files:
        if process_file(path, dry_run=dry_run):  # same string-inside-quotes logic works for JSON
            changed += 1
            print(path)

    print(f"\nTotal changed: {changed} files", file=sys.stderr)
    if dry_run:
        print("(dry run, no writes)", file=sys.stderr)


if __name__ == "__main__":
    main()
