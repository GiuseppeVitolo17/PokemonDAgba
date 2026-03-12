PewterCity_Gym_Text_BrockIntro::
    .string "Saa du er her. Jeg er BROCK.\n"
    .string "Jeg er PEWTERs GYM LEDER.\p"
    .string "Min stenhaarde viljekraft er tydelig\n"
    .string "selv i mine POKeMON.\p"
    .string "Mine POKeMON er alle stenhaarde og\n"
    .string "har sand beslutsomhed.\p"
    .string "Det er rigtigt - mine POKeMON er alle\n"
    .string "ROCK typen!\p"
    .string "Fuhaha! Du vil udfordre mig\n"
    .string "selvom du ved du taber?\p"
    .string "Det er TRAeNERens aere der\n"
    .string "driver dig til at udfordre mig.\p"
    .string "Fint da!\n"
    .string "Vis mig dit bedste!{PLAY_BGM}{MUS_ENCOUNTER_GYM_LEADER}$"

@ NOTE: This defeat text actually causes a buffer overflow. It's too long for the gDisplayedStringBattle
@ buffer that it's put into, and it stomps all over the gBattleTextBuffs after, as well as the otherwise
@ unused array after that, sFlickerArray. Perhaps that's the reason why said array exists.
PewterCity_Gym_Text_BrockDefeat::
    .string "Jeg tog dig for givet, og saa\n"
    .string "tabte jeg.\p"
    .string "Som bevis paa din sejr giver jeg\n"
    .string "dig denne… den officielle POKeMON\l"
    .string "LEAGUE BOULDERBADGE.\p"
    .string "{FONT_NORMAL}{PLAYER} modtog BOULDERBADGE\n"
    .string "fra BROCK!{PAUSE_MUSIC}{PLAY_BGM}{MUS_OBTAIN_BADGE}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}\p"
    .string "{FONT_MALE}Bare at have BOULDERBADGE goer\n"
    .string "dine POKeMON staerkere.\p"
    .string "Det muliggoer ogsaa brugen af\n"
    .string "traekket FLASH uden for kamp.\p"
    .string "Selvfoelgelig skal en POKeMON kende\n"
    .string "traekket FLASH for at bruge det.$"

PewterCity_Gym_Text_TakeThisWithYou::
    .string "Vent!\n"
    .string "Tag dette med.$"

PewterCity_Gym_Text_ReceivedTM39FromBrock::
    .string "{PLAYER} modtog TM39\n"
    .string "fra BROCK.$"

PewterCity_Gym_Text_ExplainTM39::
    .string "En TM, Technical Machine, indeholder et\n"
    .string "traek til POKeMON.\p"
    .string "At bruge en TM laerer POKeMON\n"
    .string "traekket den indeholder.\p"
    .string "En TM kan kun bruges een gang.\p"
    .string "Saa naar du bruger een, vaeg\n"
    .string "POKeMON omhyggeligt.\p"
    .string "Anyway…\n"
    .string "TM39 indeholder ROCK TOMB.\p"
    .string "Den kaster sten mod fjenden og\n"
    .string "saenker dens HASTIGHED.$"

PewterCity_Gym_Text_BrockPostBattle::
    .string "Der er alle slags TRAeNERE i\n"
    .string "denne store verden.\p"
    .string "Du virker meget talentfuld som\n"
    .string "POKeMON TRAeNER.\p"
    .string "Saa lad mig foreslaa noget.\p"
    .string "Ga til GYM i CERULEAN og test\n"
    .string "dine evner.$"

PewterCity_Gym_Text_DontHaveRoomForThis::
    .string "Du har ikke plads til dette.$"

PewterCity_Gym_Text_LiamIntro::
    .string "Stop lige der, unge!\p"
    .string "Du er ti tusind lysaar\n"
    .string "fra at moede BROCK!$"

PewterCity_Gym_Text_LiamDefeat::
    .string "Pokkers!\p"
    .string "Lysaar er ikke tid…\n"
    .string "Det maaler afstand!$"

PewterCity_Gym_Text_LiamPostBattle::
    .string "Du er ret varm.\n"
    .string "…Men ikke saa varm som BROCK!$"

PewterCity_Gym_Text_LetMeTakeYouToTheTop::
    .string "Hej!\n"
    .string "Vil du dromme stort?\p"
    .string "Toer du dromme om at blive\n"
    .string "POKeMON mester?\p"
    .string "Jeg er ikke TRAeNER, men jeg kan\n"
    .string "raade dig til hvordan man vinder.\p"
    .string "Lad mig tage dig til toppen!$"

PewterCity_Gym_Text_LetsGetHappening::
    .string "Okay!\n"
    .string "Lad os komme i gang!$"

PewterCity_Gym_Text_TryDifferentPartyOrders::
    .string "Den foerste POKeMON ude i en kamp er\n"
    .string "til venstre paa POKeMON LISTEN.\p"
    .string "Ved at aendre raekkefoelgen af POKeMON\n"
    .string "kan du faa en fordel.\p"
    .string "Proev forskellige raekkefoelger der\n"
    .string "passer til modstanderens hold.$"

PewterCity_Gym_Text_ItsFreeLetsGetHappening::
    .string "Det er gratis!\n"
    .string "Lad os komme i gang!$"

PewterCity_Gym_Text_YoureChampMaterial::
    .string "Som jeg taenkte!\n"
    .string "Du er POKeMON mestermateriale!$"

PewterCity_Gym_Text_GymStatue::
    .string "PEWTER POKeMON GYM\n"
    .string "LEDER: BROCK\p"
    .string "VINDENDE TRAeNERE:\n"
    .string "{RIVAL}$"

PewterCity_Gym_Text_GymStatuePlayerWon::
    .string "PEWTER POKeMON GYM\n"
    .string "LEDER: BROCK\p"
    .string "VINDENDE TRAeNERE:\n"
    .string "{RIVAL}, {PLAYER}$"
