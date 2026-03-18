#!/usr/bin/env python3
"""Replace French å (0x68) with Danish å (0x0B) in all game text files."""
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DATA = os.path.join(ROOT, "data")

def main():
    count = 0
    for dirpath, _dirnames, filenames in os.walk(DATA):
        for name in filenames:
            if not (name.endswith(".inc") or (name.endswith(".s") and "event_scripts" in dirpath)):
                continue
            path = os.path.join(dirpath, name)
            rel = os.path.relpath(path, ROOT)
            try:
                with open(path, "r", encoding="utf-8") as f:
                    text = f.read()
            except (OSError, UnicodeDecodeError):
                continue
            if "å" not in text:
                continue
            new_text = text.replace("å", "å")
            with open(path, "w", encoding="utf-8") as f:
                f.write(new_text)
            n = text.count("å")
            count += n
            print(rel, n)
    print("Total replacements:", count)

if __name__ == "__main__":
    main()
