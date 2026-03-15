.equ GAVE_PROFILE,  VAR_TEMP_1

MysteryEventClub_EventScript_Woman::
	lock
	faceplayer
	goto_if_eq GAVE_PROFILE, TRUE, EventScript_AlreadyGaveProfile
	goto_if_set FLAG_SYS_SET_TRAINER_CARD_PROFILE, EventScript_GivenProfileBefore
	msgbox Text_IdLoveToHearYourProfile
	goto EventScript_AskForProfile
	end

EventScript_AlreadyGaveProfile:
	msgbox Text_TellMoreNextTime
	release
	end

EventScript_AskForProfile:
	message Text_TellMeWhatsYourProfile
	waitmessage
	multichoice 18, 6, MULTICHOICE_YES_NO_INFO_2, FALSE
	switch VAR_RESULT
	case 0, EventScript_AcceptGiveProfile
	case 1, EventScript_DeclineGiveProfile
	case 2, EventScript_ProfileInfo
	case SCR_MENU_CANCEL, EventScript_DeclineGiveProfile
	end

EventScript_ProfileInfo:
	msgbox Text_ExplainProfile
	goto EventScript_AskForProfile
	end

EventScript_AcceptGiveProfile:
	msgbox Text_WhatsYourProfile
	closemessage
	goto EventScript_GiveProfile
	end

EventScript_CancelGiveProfile:
	msgbox Text_DecidedNotTo
	release
	end

EventScript_GaveProfile:
	setvar GAVE_PROFILE, TRUE
	setvar VAR_0x8004, 0
	special ShowEasyChatMessage
	waitmessage
	delay 80
	msgbox Text_ProfileSaysSomethingAboutYou
	release
	end

EventScript_DeclineGiveProfile:
	msgbox Text_DontBeLikeThat
	release
	end

EventScript_GivenProfileBefore:
	msgbox Text_HiWeMeetAgain
	goto EventScript_AskForNewProfile
	end

EventScript_AskForNewProfile:
	message Text_ChangeYourProfile
	waitmessage
	multichoice 18, 6, MULTICHOICE_YES_NO_INFO_2, FALSE
	switch VAR_RESULT
	case 0, EventScript_AcceptGiveNewProfile
	case 1, EventScript_DeclineGiveNewProfile
	case 2, EventScript_ProfileInfo2
	case SCR_MENU_CANCEL, EventScript_DeclineGiveNewProfile
	end

EventScript_ProfileInfo2:
	msgbox Text_ExplainProfile
	goto EventScript_AskForNewProfile
	end

EventScript_AcceptGiveNewProfile:
	msgbox Text_WhatAreYouLikeNow
	closemessage
	goto EventScript_GiveProfile
	end

EventScript_DeclineGiveNewProfile:
	msgbox Text_LikeProfileWayItIs
	release
	end

EventScript_GaveSpecialProfile:
	setvar GAVE_PROFILE, TRUE
	setvar VAR_0x8004, 0
	special ShowEasyChatMessage
	waitmessage
	delay 80
	msgbox Text_HeardThatBefore
	release
	end

EventScript_GiveProfile:
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_0x8004, 0, EventScript_GaveSpecialProfile
	goto_if_eq VAR_RESULT, FALSE, EventScript_CancelGiveProfile
	goto_if_eq VAR_RESULT, TRUE, EventScript_GaveProfile
	end

Text_IdLoveToHearYourProfile:
	.string "Hej, dejligt at møde dig!\p"
	.string "…Det er uvenligt af dig.\n"
	.string "Hvad med at sige hej tilbage?\p"
	.string "Kom nu, fortæl mig om\n"
	.string "dig selv.\p"
	.string "Jeg vil meget gerne høre din profil!$"

Text_TellMeWhatsYourProfile:
	.string "Fortæl mig noget godt om\n"
	.string "dig selv. Hvad er din profil?$"

Text_ExplainProfile:
	.string "En profil skrives med fire\n"
	.string "ord eller udtryk.\p"
	.string "Der er masser af ord at vælge\n"
	.string "mellem til din profil.\p"
	.string "Ordene og udtrykkene er placeret\n"
	.string "i flere praktiske grupper.\p"
	.string "Først vælg en gruppe, derefter\n"
	.string "et ord eller udtryk.\p"
	.string "…Det er nemmere end det lyder.\n"
	.string "Prøv det dog!$"

Text_WhatsYourProfile:
	.string "Hvad er din profil?$"

Text_DontBeLikeThat:
	.string "Av… Vær nu ikke sâ led.\n"
	.string "Du kan godt fortælle mig din profil.$"

Text_DecidedNotTo:
	.string "Aa, du har besluttet dig for ikke?\n"
	.string "Du er væglende, er du ikke?$"

Text_HiWeMeetAgain:
	.string "Hej!\n"
	.string "Vi mødes igen!$"

Text_ChangeYourProfile:
	.string "Vil du gerne ændre din\n"
	.string "profil?$"

Text_WhatAreYouLikeNow:
	.string "Hvordan er du nu?\n"
	.string "Det vil jeg virkelig gerne vide.$"

Text_LikeProfileWayItIs:
	.string "Ok, du kan lide din profil\n"
	.string "som den er.\p"
	.string "Det synes jeg ogsâ.$"

Text_ProfileSaysSomethingAboutYou:
	.string "Hmhm…\p"
	.string "Din profil siger virkelig noget\n"
	.string "om hvem du er.\p"
	.string "Nu hvor jeg kender dig bedre,\n"
	.string "bliver vi bedre venner end nogensinde!$"

Text_HeardThatBefore:
	.string "Aa, det har jeg hørt før…\p"
	.string "Min kusine, der bor langt væk,\n"
	.string "sagde altid det, tror jeg.$"

Text_TellMoreNextTime:
	.string "Fortæl mig venligst mere om\n"
	.string "dig selv næste gang!$"
