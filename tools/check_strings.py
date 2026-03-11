#!/usr/bin/env python3
"""
Check that lines containing _(" in C/H source files have balanced double-quotes.
Reports file:line for any line with an odd number of " characters (unclosed string).
Usage: python tools/check_strings.py [src/]
"""

import os
import sys

def check_file(path):
    errors = []
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        for i, line in enumerate(f, 1):
            if '_("' in line or "_('" in line:
                # Count double-quotes (only " counts for C strings)
                n = line.count('"')
                if n % 2 != 0:
                    errors.append((path, i, "unclosed string (odd number of \")"))
    return errors

def main():
    root = sys.argv[1] if len(sys.argv) > 1 else "src"
    if not os.path.isdir(root):
        print(f"Not a directory: {root}", file=sys.stderr)
        sys.exit(2)
    all_errors = []
    for dirpath, _, filenames in os.walk(root):
        for name in filenames:
            if name.endswith((".c", ".h")):
                path = os.path.join(dirpath, name)
                all_errors.extend(check_file(path))
    for path, line_no, msg in all_errors:
        print(f"{path}:{line_no}: {msg}")
    if all_errors:
        sys.exit(1)
    print("OK: all _(\"...\") lines have balanced quotes.")
    sys.exit(0)

if __name__ == "__main__":
    main()
