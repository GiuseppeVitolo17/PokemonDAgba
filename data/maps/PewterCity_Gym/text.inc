PewterCity_Gym_Text_BrockIntro::
    .string "Sâ du er her. Jeg er BROCK.\n"
    .string "Jeg er PEWTERs GYM LEDER.\p"
    .string "Min stenhârde viljekraft er tydelig\n"
    .string "selv i mine POKéMON.\p"
    .string "Mine POKéMON er alle stenhârde og\n"
    .string "har sand beslutsomhed.\p"
    .string "Det er rigtigt - mine POKéMON er alle\n"
    .string "ROCK typen!\p"
    .string "Fuhaha! Du vil udfordre mig\n"
    .string "selvom du ved du taber?\p"
    .string "Det er TRÆNERens ære der\n"
    .string "driver dig til at udfordre mig.\p"
    .string "Fint da!\n"
    .string "Vis mig dit bedste!{PLAY_BGM}{MUS_ENCOUNTER_GYM_LEADER}$"

@ NOTE: This defeat text actually causes a buffer overflow. It's too long for the gDisplayedStringBattle
@ buffer that it's put into, and it stomps all over the gBattleTextBuffs after, as well as the otherwise
@ unused array after that, sFlickerArray. Perhaps that's the reason why said array exists.
PewterCity_Gym_Text_BrockDefeat::
    .string "Jeg tog dig for givet, og sâ\n"
    .string "tabte jeg.\p"
    .string "Som bevis pâ din sejr giver jeg\n"
    .string "dig denne… den officielle POKéMON\l"
    .string "LEAGUE BOULDERBADGE.\p"
    .string "{FONT_NORMAL}{PLAYER} modtog BOULDERBADGE\n"
    .string "fra BROCK!{PAUSE_MUSIC}{PLAY_BGM}{MUS_OBTAIN_BADGE}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}\p"
    .string "{FONT_MALE}Bare at have BOULDERBADGE gør\n"
    .string "dine POKéMON stærkere.\p"
    .string "Det muliggør ogsâ brugen af\n"
    .string "trækket FLASH uden for kamp.\p"
    .string "Selvfølgelig skal en POKéMON kende\n"
    .string "trækket FLASH for at bruge det.$"

PewterCity_Gym_Text_TakeThisWithYou::
    .string "Vent!\n"
    .string "Tag dette med.$"

PewterCity_Gym_Text_ReceivedTM39FromBrock::
    .string "{PLAYER} modtog TM39\n"
    .string "fra BROCK.$"

PewterCity_Gym_Text_ExplainTM39::
    .string "En TM, Technical Machine, indeholder et\n"
    .string "træk til POKéMON.\p"
    .string "At bruge en TM lærer POKéMON\n"
    .string "trækket den indeholder.\p"
    .string "En TM kan kun bruges een gang.\p"
    .string "Sâ nâr du bruger een, væg\n"
    .string "POKéMON omhyggeligt.\p"
    .string "Anyway…\n"
    .string "TM39 indeholder ROCK TOMB.\p"
    .string "Den kaster sten mod fjenden og\n"
    .string "sænker dens HASTIGHED.$"

PewterCity_Gym_Text_BrockPostBattle::
    .string "Der er alle slags TRÆNERE i\n"
    .string "denne store verden.\p"
    .string "Du virker meget talentfuld som\n"
    .string "POKéMON TRÆNER.\p"
    .string "Sâ lad mig foreslâ noget.\p"
    .string "Ga til GYM i CERULEAN og test\n"
    .string "dine evner.$"

PewterCity_Gym_Text_DontHaveRoomForThis::
    .string "Du har ikke plads til dette.$"

PewterCity_Gym_Text_LiamIntro::
    .string "Stop lige der, unge!\p"
    .string "Du er ti tusind lysâr\n"
    .string "fra at møde BROCK!$"

PewterCity_Gym_Text_LiamDefeat::
    .string "Pokkers!\p"
    .string "Lysâr er ikke tid…\n"
    .string "Det mâler afstand!$"

PewterCity_Gym_Text_LiamPostBattle::
    .string "Du er ret varm.\n"
    .string "…Men ikke sâ varm som BROCK!$"

PewterCity_Gym_Text_LetMeTakeYouToTheTop::
    .string "Hej!\n"
    .string "Vil du dromme stort?\p"
    .string "Tør du dromme om at blive\n"
    .string "POKéMON mester?\p"
    .string "Jeg er ikke TRÆNER, men jeg kan\n"
    .string "râde dig til hvordan man vinder.\p"
    .string "Lad mig tage dig til toppen!$"

PewterCity_Gym_Text_LetsGetHappening::
    .string "Okay!\n"
    .string "Lad os komme i gang!$"

PewterCity_Gym_Text_TryDifferentPartyOrders::
    .string "Den første POKéMON ude i en kamp er\n"
    .string "til venstre pâ POKéMON LISTEN.\p"
    .string "Ved at ændre rækkefølgen af POKéMON\n"
    .string "kan du fâ en fordel.\p"
    .string "Prøv forskellige rækkefølger der\n"
    .string "passer til modstanderens hold.$"

PewterCity_Gym_Text_ItsFreeLetsGetHappening::
    .string "Det er gratis!\n"
    .string "Lad os komme i gang!$"

PewterCity_Gym_Text_YoureChampMaterial::
    .string "Som jeg tænkte!\n"
    .string "Du er POKéMON mestermateriale!$"

PewterCity_Gym_Text_GymStatue::
    .string "PEWTER POKéMON GYM\n"
    .string "LEDER: BROCK\p"
    .string "VINDENDE TRÆNERE:\n"
    .string "{RIVAL}$"

PewterCity_Gym_Text_GymStatuePlayerWon::
    .string "PEWTER POKéMON GYM\n"
    .string "LEDER: BROCK\p"
    .string "VINDENDE TRÆNERE:\n"
    .string "{RIVAL}, {PLAYER}$"
