#!/usr/bin/env python3
"""Translate all English item names in items.json to Danish (max 14 chars, ä/ö/â)."""
import json
import os

MAX_LEN = 14

# Danish names (charmap: ä=F4, ö=F5, â=68 for å; ö used for ø). All ≤14 chars.
NAME_MAP = {
    # Balls
    "MASTER BALL": "MESTER BOLD",
    "ULTRA BALL": "ULTRA BOLD",
    "GREAT BALL": "STOR BOLD",
    "POKe BALL": "POKe BALL",
    "SAFARI BALL": "SAFARI BOLD",
    "NET BALL": "NET BOLD",
    "DIVE BALL": "DYK BOLD",
    "NEST BALL": "REDE BOLD",
    "REPEAT BALL": "GENTAG BOLD",
    "TIMER BALL": "STOPUR BOLD",
    "LUXURY BALL": "LUXUS BOLD",
    "PREMIER BALL": "PREMIER BOLD",
    # Medicine
    "POTION": "DRIK",
    "ANTIDOTE": "MODGIFT",
    "BURN HEAL": "BRÆNDHELING",
    "ICE HEAL": "ISHELING",
    "AWAKENING": "VÂGNING",
    "PARLYZ HEAL": "PARALYSE HEL",
    "FULL RESTORE": "FULD GENOPRET",
    "MAX POTION": "MAX DRIK",
    "HYPER POTION": "HYPER DRIK",
    "SUPER POTION": "SUPER DRIK",
    "FULL HEAL": "FULD HELING",
    "REVIVE": "GENOPLIV",
    "MAX REVIVE": "MAX GENOPLIV",
    # Drinks
    "FRESH WATER": "FERSKVAND",
    "SODA POP": "SODAVAND",
    "LEMONADE": "LIMONADE",
    "MOOMOO MILK": "MUMIEMÄLK",
    # Powders/roots
    "ENERGYPOWDER": "ENERGIPULVER",
    "ENERGY ROOT": "ENERGIROD",
    "HEAL POWDER": "HELINGSPULVER",
    "REVIVAL HERB": "GENOPLIV URTE",
    "ETHER": "ETER",
    "MAX ETHER": "MAX ETER",
    "ELIXIR": "ELIXIR",
    "MAX ELIXIR": "MAX ELIXIR",
    "LAVA COOKIE": "LAVA SMÅKAGE",
    # Flutes
    "BLUE FLUTE": "BLÂ FLÖJTE",
    "YELLOW FLUTE": "GUL FLÖJTE",
    "RED FLUTE": "RÖD FLÖJTE",
    "BLACK FLUTE": "SORT FLÖJTE",
    "WHITE FLUTE": "HVID FLÖJTE",
    # Other consumables
    "BERRY JUICE": "BÆR SAFT",
    "SACRED ASH": "HELLIG ASKE",
    "SHOAL SALT": "REVET SALT",
    "SHOAL SHELL": "REVSKAL",
    "RED SHARD": "RÖD SKÅRV",
    "BLUE SHARD": "BLÂ SKÅRV",
    "YELLOW SHARD": "GUL SKÅRV",
    "GREEN SHARD": "GRÖN SKÅRV",
    # Vitamins
    "HP UP": "HP OP",
    "PROTEIN": "PROTEIN",
    "IRON": "JERN",
    "CARBOS": "CARBOS",
    "CALCIUM": "KALCIUM",
    "RARE CANDY": "SJÄLDEN SLIK",
    "PP UP": "PP OP",
    "ZINC": "ZINK",
    "PP MAX": "PP MAX",
    # Battle
    "GUARD SPEC.": "FORSVAR SPEC",
    "DIRE HIT": "KRÆV TRÆF",
    "X ATTACK": "X ANGREB",
    "X DEFEND": "X FORSVAR",
    "X SPEED": "X HASTIGHED",
    "X ACCURACY": "X PRÆCISION",
    "X SPECIAL": "X SPECIAL",
    "POKe DOLL": "POKe DUKKE",
    "FLUFFY TAIL": "FLUFFY HALE",
    # Repels
    "SUPER REPEL": "SUPER FRÆST",
    "MAX REPEL": "MAX FRÆST",
    "ESCAPE ROPE": "FLUGTREB",
    "REPEL": "FRÆST",
    # Stones
    "SUN STONE": "SOLSTEN",
    # Pearls
    "BIG PEARL": "STOR PERLE",
    # Mail
    "ORANGE MAIL": "ORANGE BREV",
    "HARBOR MAIL": "HAVN BREV",
    "GLITTER MAIL": "GLITTER BREV",
    "MECH MAIL": "MECH BREV",
    "BEAD MAIL": "PERLE BREV",
    "TROPIC MAIL": "TROPISK BREV",
    "FAB MAIL": "FAB BREV",
    "RETRO MAIL": "RETRO BREV",
    # Berries
    "CHERI BERRY": "CHERI BÆR",
    "CHESTO BERRY": "CHESTO BÆR",
    "PECHA BERRY": "PECHA BÆR",
    "RAWST BERRY": "RAWST BÆR",
    "ASPEAR BERRY": "ASPEAR BÆR",
    "LEPPA BERRY": "LEPPA BÆR",
    "ORAN BERRY": "ORAN BÆR",
    "PERSIM BERRY": "PERSIM BÆR",
    "LUM BERRY": "LUM BÆR",
    "SITRUS BERRY": "SITRUS BÆR",
    "FIGY BERRY": "FIGY BÆR",
    "WIKI BERRY": "WIKI BÆR",
    "MAGO BERRY": "MAGO BÆR",
    "AGUAV BERRY": "AGUAV BÆR",
    "IAPAPA BERRY": "IAPAPA BÆR",
    "RAZZ BERRY": "RAZZ BÆR",
    "BLUK BERRY": "BLUK BÆR",
    "NANAB BERRY": "NANAB BÆR",
    "WEPEAR BERRY": "WEPEAR BÆR",
    "PINAP BERRY": "PINAP BÆR",
    "POMEG BERRY": "POMEG BÆR",
    "KELPSY BERRY": "KELPSY BÆR",
    "QUALOT BERRY": "QUALOT BÆR",
    "HONDEW BERRY": "HONDEW BÆR",
    "GREPA BERRY": "GREPA BÆR",
    "TAMATO BERRY": "TAMATO BÆR",
    "CORNN BERRY": "CORNN BÆR",
    "MAGOST BERRY": "MAGOST BÆR",
    "RABUTA BERRY": "RABUTA BÆR",
    "NOMEL BERRY": "NOMEL BÆR",
    "SPELON BERRY": "SPELON BÆR",
    "PAMTRE BERRY": "PAMTRE BÆR",
    "WATMEL BERRY": "WATMEL BÆR",
    "DURIN BERRY": "DURIN BÆR",
    "BELUE BERRY": "BELUE BÆR",
    "LIECHI BERRY": "LIECHI BÆR",
    "GANLON BERRY": "GANLON BÆR",
    "SALAC BERRY": "SALAC BÆR",
    "PETAYA BERRY": "PETAYA BÆR",
    "APICOT BERRY": "APICOT BÆR",
    "LANSAT BERRY": "LANSAT BÆR",
    "STARF BERRY": "STARF BÆR",
    "ENIGMA BERRY": "ENIGMA BÆR",
    # Hold items
    "MACHO BRACE": "MACHO ARM",
    "QUICK CLAW": "HURTIG KLO",
    "SOOTHE BELL": "BEDÂRINGS KL",
    "CHOICE BAND": "VALGBÂND",
    "LUCKY EGG": "HELDIG ÄG",
    "DEEPSEASCALE": "DYBHAVSKAL",
    "DRAGON FANG": "DRAGE TAND",
    "THICK CLUB": "TYK KÆP",
    "MAGNET": "MAGNET",
    # Scarves (English only)
    "PINK SCARF": "PINK TÖRKLÄDE",
    "GREEN SCARF": "GRÖN TÖRKLÄDE",
    # Key items
    "LETTER": "BREV",
    "EON TICKET": "EON BILLET",
    "BLUE ORB": "BLÂ KUGLE",
    "SCANNER": "SCANNER",
    "GO-GOGGLES": "GO-BRILLER",
    "METEORITE": "METEORIT",
    "ROD FOSSIL": "ROD FOSSIL",
    "SECRET KEY": "HEMMELIG NÖG",
    "S.S. TICKET": "S.S. BILLET",
    "WAILMER PAIL": "WAILMER SPAND",
    "DEVON GOODS": "DEVON VARER",
    "SOOT SACK": "SOT SÄK",
    "ACRO BIKE": "AKRO CYKEL",
    "TEACHY TV": "TEACHY TV",
    "TRI-PASS": "TRI-PAS",
    "RAINBOW PASS": "REGNBUE PAS",
    "MYSTICTICKET": "MYSTIK BILLET",
    "AURORATICKET": "AURORA BILLET",
    "TOWN MAP": "BYKORT",
    "VS SEEKER": "VS SÖGER",
    "OAK'S PARCEL": "OAKS PAKKE",
    "POKé FLUTE": "POKé FLÖJTE",
    "ITEMFINDER": "GENSTANDSFIND",
}

def main():
    base = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    path = os.path.join(base, "src", "data", "items.json")
    with open(path, "r", encoding="utf-8") as f:
        data = json.load(f)

    updated = 0
    for it in data["items"]:
        en = it["english"]
        if en in NAME_MAP:
            new_name = NAME_MAP[en]
            if len(new_name) > MAX_LEN:
                new_name = new_name[:MAX_LEN]
            it["english"] = new_name
            updated += 1

    with open(path, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2, ensure_ascii=False)

    print(f"Updated {updated} item names.")

if __name__ == "__main__":
    main()
