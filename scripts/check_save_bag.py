#!/usr/bin/env python3
"""
Check a Pokémon FireRed .sav file for basic validity and bag data.
Usage: python3 scripts/check_save_bag.py [path_to.sav]
Default: ~/Desktop/pokefirered.sav
"""
import struct
import sys
import os

SECTOR_SIZE = 4096
SECTOR_DATA_SIZE = 3968
SECTOR_FOOTER_SIZE = 128
SECTOR_SIGNATURE = 0x08012025
SAVEBLOCK2_SIZE = 0xF24
ENCRYPTION_KEY_OFFSET = 0xF20
# SaveBlock1: bagPocket_Items at 0x310, 42 slots * 4 bytes
BAG_ITEMS_OFFSET = 0x310
BAG_ITEMS_COUNT = 42
ITEMS_COUNT = 375  # max valid item id in FRLG

def main():
    path = sys.argv[1] if len(sys.argv) > 1 else os.path.expanduser("~/Desktop/pokefirered.sav")
    if not os.path.isfile(path):
        print(f"File not found: {path}")
        return 1
    data = open(path, "rb").read()
    # Use first 128KB (32 sectors)
    if len(data) < 32 * SECTOR_SIZE:
        print(f"File too small: {len(data)} bytes (expected at least {32 * SECTOR_SIZE})")
        return 1
    data = data[: 32 * SECTOR_SIZE]
    print(f"Checking: {path} ({len(data)} bytes)")
    print()

    # Sector footer: last 12 bytes used -> id (2), checksum (2), signature (4), counter (4)
    def read_footer(sector_idx):
        off = sector_idx * SECTOR_SIZE + SECTOR_DATA_SIZE
        sig_off = off + SECTOR_FOOTER_SIZE - 12 + 4  # signature at +4 in last 12
        sig = struct.unpack_from("<I", data, sig_off)[0]
        counter_off = sig_off + 4
        counter = struct.unpack_from("<I", data, counter_off)[0]
        return sig, counter

    # Which save slot is valid? Slot 1 = sectors 0-13, Slot 2 = sectors 14-27
    sig0, cnt0 = read_footer(0)
    sig14, cnt14 = read_footer(14)
    print("Save slot 1 (sector 0):  signature=0x%08X  counter=%u" % (sig0, cnt0))
    print("Save slot 2 (sector 14): signature=0x%08X  counter=%u" % (sig14, cnt14))
    if sig0 != SECTOR_SIGNATURE and sig14 != SECTOR_SIGNATURE:
        print("WARNING: No valid sector signature (0x08012025) found. Save may be empty or corrupted.")
    elif sig0 != SECTOR_SIGNATURE:
        print("Using save slot 2 (slot 1 invalid).")
        slot1_base = 14 * SECTOR_SIZE
    elif sig14 != SECTOR_SIGNATURE:
        print("Using save slot 1 (slot 2 invalid).")
        slot1_base = 0
    else:
        if cnt14 > cnt0:
            print("Using save slot 2 (newer counter).")
            slot1_base = 14 * SECTOR_SIZE
        else:
            print("Using save slot 1 (newer or equal counter).")
            slot1_base = 0
    print()

    # SaveBlock2 is sector 0 or 14
    sav2_data = data[slot1_base : slot1_base + SECTOR_DATA_SIZE]
    if len(sav2_data) < ENCRYPTION_KEY_OFFSET + 4:
        print("SaveBlock2 too small for encryption key.")
        return 1
    key = struct.unpack_from("<I", sav2_data, ENCRYPTION_KEY_OFFSET)[0]
    print("Encryption key (SaveBlock2): 0x%08X" % key)
    print()

    # SaveBlock1 chunk 0 is in sector 1 or 15
    sav1_sector = (1 if slot1_base == 0 else 15)
    sav1_chunk0 = data[sav1_sector * SECTOR_SIZE : sav1_sector * SECTOR_SIZE + SECTOR_DATA_SIZE]
    # bagPocket_Items at 0x310, all within first chunk (3968 bytes)
    bag_off = BAG_ITEMS_OFFSET
    if bag_off + BAG_ITEMS_COUNT * 4 > len(sav1_chunk0):
        print("SaveBlock1 chunk 0 too small for bag data.")
        return 1
    print("Bag (Items pocket) - 42 slots:")
    print("  (Only quantity is XOR'd with encryption key; itemId is stored plain.)")
    bad = []
    for i in range(BAG_ITEMS_COUNT):
        off = bag_off + i * 4
        item_id, enc_qty = struct.unpack_from("<HH", sav1_chunk0, off)
        qty = enc_qty ^ (key & 0xFFFF)
        if item_id > ITEMS_COUNT and item_id != 0:
            bad.append((i, item_id, qty))
        mark = " OK" if (item_id <= ITEMS_COUNT or item_id == 0) else " INVALID"
        if i < 12 or bad or (item_id != 0 and qty != 0):
            print("  [%2d] itemId=%5u  quantity=%3u%s" % (i, item_id, qty, mark))
    if len(bad) > 12:
        print("  ...")
        for i, (idx, item_id, qty) in enumerate(bad[:5]):
            print("  [%2d] itemId=%5u  quantity=%3u INVALID" % (idx, item_id, qty))
        if len(bad) > 5:
            print("  ... and %d more invalid slots" % (len(bad) - 5))
    print()
    if bad:
        print("WARNING: %d bag slot(s) have invalid itemId (max valid %u). This can cause")
        print("  crashes or freezes in the bag menu (e.g. bad pointer from ItemId_GetName).")
        print("  Try starting a new game or using a save that was never used with a different ROM.")
    else:
        print("All bag item IDs look valid.")
    return 0

if __name__ == "__main__":
    sys.exit(main())
