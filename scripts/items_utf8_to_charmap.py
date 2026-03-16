#!/usr/bin/env python3
"""Convert UTF-8 Danish chars to charmap bytes inside string literals; write file as Latin-1.
agbcc rejects \\x and \\3; using raw charmap bytes in Latin-1 source avoids escapes."""
import sys

# Charmap byte values (decimal): ä=F4=244, ö=F5=245, â=68, ø->ö=245, Ä=F1=241, Ö=F2=242, Â=3
MAP = {
    "ä": chr(0xF4),
    "ö": chr(0xF5),
    "â": chr(0x68),
    "ø": chr(0xF5),
    "Ä": chr(0xF1),
    "Ö": chr(0xF2),
    "Â": chr(0x03),
}

def convert(content: str) -> str:
    result = []
    i = 0
    in_string = False
    escape_next = False
    n = len(content)
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
        if c == '"':
            in_string = not in_string
            result.append(c)
            i += 1
            continue
        if in_string and c in MAP:
            result.append(MAP[c])
            i += 1
            continue
        result.append(c)
        i += 1
    return "".join(result)

def main():
    if len(sys.argv) != 2:
        sys.stderr.write("Usage: items_utf8_to_charmap.py <items.h>\n")
        sys.exit(1)
    path = sys.argv[1]
    with open(path, "r", encoding="utf-8") as f:
        content = f.read()
    out = convert(content)
    with open(path, "w", encoding="iso-8859-1", errors="replace") as f:
        f.write(out)

if __name__ == "__main__":
    main()
