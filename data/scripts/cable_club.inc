CableClub_OnTransition::
	call CableClub_EventScript_HideOrShowMysteryGiftMan
	end

CableClub_EventScript_HideOrShowMysteryGiftMan::
	specialvar VAR_RESULT, ValidateSavedWonderCard
	goto_if_eq VAR_RESULT, FALSE, EventScript_HideMysteryGiftMan
	clearflag FLAG_HIDE_MG_DELIVERYMEN
	return

EventScript_HideMysteryGiftMan::
	setflag FLAG_HIDE_MG_DELIVERYMEN
	return

CableClub_EventScript_MysteryGiftMan::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	trywondercardscript

@ Unused
EventScript_MysteryGiftThankYou::
	msgbox Text_ThankYouForAccessingMysteryGift, MSGBOX_NPC
	end

CableClub_OnWarp::
	map_script_2 VAR_CABLE_CLUB_STATE, USING_SINGLE_BATTLE, EventScript_CheckTurnAttendant
	map_script_2 VAR_CABLE_CLUB_STATE, USING_DOUBLE_BATTLE, EventScript_CheckTurnAttendant
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MULTI_BATTLE, EventScript_CheckTurnAttendant
	map_script_2 VAR_CABLE_CLUB_STATE, USING_TRADE_CENTER, EventScript_CheckTurnAttendant
	map_script_2 VAR_CABLE_CLUB_STATE, USING_UNION_ROOM, EventScript_CheckTurnAttendant
	map_script_2 VAR_CABLE_CLUB_STATE, USING_BERRY_CRUSH, EventScript_CheckTurnAttendant
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, EventScript_CheckTurnAttendant
	.2byte 0

EventScript_CheckTurnAttendant::
	goto_if_eq VAR_0x8007, 0, EventScript_CheckTurnAttendantEnd
	turnobject VAR_0x8007, DIR_WEST
EventScript_CheckTurnAttendantEnd:
	end

CableClub_OnLoad::
	goto_if_eq VAR_CABLE_CLUB_STATE, USING_SINGLE_BATTLE, EventScript_OnLoadFromColosseum
	goto_if_eq VAR_CABLE_CLUB_STATE, USING_DOUBLE_BATTLE, EventScript_OnLoadFromColosseum
	goto_if_eq VAR_CABLE_CLUB_STATE, USING_MULTI_BATTLE, EventScript_OnLoadFromColosseum
	goto_if_eq VAR_CABLE_CLUB_STATE, USING_TRADE_CENTER, EventScript_OnLoadFromTradeCenter
	goto_if_eq VAR_CABLE_CLUB_STATE, USING_UNION_ROOM, EventScript_OnLoadFromUnionRoom
	goto_if_eq VAR_CABLE_CLUB_STATE, USING_BERRY_CRUSH, EventScript_OnLoadFromBerryCrush
	goto_if_eq VAR_CABLE_CLUB_STATE, USING_MINIGAME, EventScript_OnLoadFromGameCorner
	end

EventScript_OnLoadFromColosseum::
	call CableClub_EventScript_OpenDirectCornerBarrier
	end

EventScript_OnLoadFromTradeCenter::
	call CableClub_EventScript_OpenDirectCornerBarrier
	end

EventScript_OnLoadFromUnionRoom::
	call CableClub_EventScript_OpenUnionRoomBarrier
	end

EventScript_OnLoadFromBerryCrush::
	call CableClub_EventScript_OpenDirectCornerBarrier
	end

EventScript_OnLoadFromGameCorner::
	call CableClub_EventScript_OpenGameCornerBarrier
	end

CableClub_OnFrame::
	map_script_2 VAR_MAP_SCENE_POKEMON_CENTER_TEALA, 1, CableClub_EventScript_Tutorial
	map_script_2 VAR_CABLE_CLUB_STATE, USING_SINGLE_BATTLE, CableClub_EventScript_ExitLinkRoom
	map_script_2 VAR_CABLE_CLUB_STATE, USING_DOUBLE_BATTLE, CableClub_EventScript_ExitLinkRoom
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MULTI_BATTLE, CableClub_EventScript_ExitLinkRoom
	map_script_2 VAR_CABLE_CLUB_STATE, USING_TRADE_CENTER, CableClub_EventScript_ExitTradeCenter
	map_script_2 VAR_CABLE_CLUB_STATE, USING_UNION_ROOM, CableClub_EventScript_ExitUnionRoom
	map_script_2 VAR_CABLE_CLUB_STATE, USING_BERRY_CRUSH, CableClub_EventScript_ExitLinkRoom
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_ExitMinigameRoom
	.2byte 0

CableClub_EventScript_ExitLinkRoom::
	lockall
	call CableClub_EventScript_CloseLinkAndExitLinkRoom
	call CableClub_EventScript_CloseDirectCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	erasebox 0, 0, 29, 19
	releaseall
	end

CableClub_EventScript_ExitMinigameRoom::
	lockall
	call CableClub_EventScript_CloseLinkAndExitLinkRoom
	call CableClub_EventScript_CloseGameCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	erasebox 0, 0, 29, 19
	releaseall
	end

CableClub_EventScript_CloseLinkAndExitLinkRoom::
	special CloseLink
	special HelpSystem_Enable
	special QuestLog_StartRecordingInputsAfterDeferredEvent
	setvar VAR_CABLE_CLUB_STATE, 0
	textcolor NPC_TEXT_COLOR_FEMALE
	goto_if_eq VAR_0x8007, 0, CableClub_EventScript_PlayerExitLinkRoom
	applymovement VAR_0x8007, Movement_AttendantFaceLeft
	waitmovement 0
	applymovement LOCALID_PLAYER, Movement_PlayerExitLinkRoom
	waitmovement 0
	applymovement VAR_0x8007, Movement_AttendantFaceDown
	waitmovement 0
	return

CableClub_EventScript_ExitTradeCenter::
	lockall
	call CableClub_EventScript_PlayerExitTradeCenter
	call CableClub_EventScript_CloseDirectCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	erasebox 0, 0, 29, 19
	releaseall
	end

CableClub_EventScript_PlayerExitTradeCenter::
	special CloseLink
	special HelpSystem_Enable
	special QuestLog_StartRecordingInputsAfterDeferredEvent
	setvar VAR_CABLE_CLUB_STATE, 0
	textcolor NPC_TEXT_COLOR_FEMALE
	goto_if_eq VAR_0x8007, 0, CableClub_EventScript_PlayerExitLinkRoom
	applymovement LOCALID_PLAYER, Movement_PlayerFaceAttendantRight
	waitmovement 0
	applymovement VAR_0x8007, Movement_AttendantFaceLeft
	waitmovement 0
	call CableClub_EventScript_TrainerCardDataOverwritten
	return

CableClub_EventScript_ExitUnionRoom::
	lockall
	call CableClub_EventScript_PlayerExitUnionRoom
	call CableClub_EventScript_CloseUnionRoomBarrier
	special DrawWholeMapView
	playse SE_CLICK
	erasebox 0, 0, 29, 19
	releaseall
	end

CableClub_EventScript_PlayerExitUnionRoom::
	special HelpSystem_Enable
	special QuestLog_StartRecordingInputsAfterDeferredEvent
	setvar VAR_CABLE_CLUB_STATE, 0
	textcolor NPC_TEXT_COLOR_FEMALE
	goto_if_eq VAR_0x8007, 0, CableClub_EventScript_PlayerExitLinkRoom
	applymovement LOCALID_PLAYER, Movement_PlayerFaceAttendantRight
	waitmovement 0
	applymovement VAR_0x8007, Movement_AttendantFaceLeft
	waitmovement 0
	call CableClub_EventScript_TrainerCardDataOverwritten
	return

CableClub_EventScript_TrainerCardDataOverwritten::
	message CableClub_Text_TrainerCardDataOverwritten
	waitmessage
	playse SE_PIN
	message CableClub_Text_HopeToSeeYouAgain
	waitmessage
	applymovement LOCALID_PLAYER, Movement_PlayerExitLinkRoom
	waitmovement 0
	applymovement VAR_0x8007, Movement_AttendantFaceDown
	waitmovement 0
	return

CableClub_EventScript_PlayerExitLinkRoom::
	applymovement LOCALID_PLAYER, Movement_PlayerExitLinkRoom
	waitmovement 0
	return

CableClub_EventScript_Tutorial::
	lockall
	textcolor NPC_TEXT_COLOR_FEMALE
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox CableClub_Text_FirstTimeRightThisWay
	closemessage
	applymovement LOCALID_PLAYER, Movement_PlayerApproachCounter
	waitmovement 0
	delay 30
	msgbox CableClub_Text_ExplainWirelessClubFirstTime
	setvar VAR_MAP_SCENE_POKEMON_CENTER_TEALA, 2
	releaseall
	end

Movement_PlayerApproachCounter:
	walk_up
	walk_up
	step_end

CableClub_EventScript_WelcomeToCableClub::
	message CableClub_Text_WelcomeWhichCableClubService
	waitmessage
	delay 15
	goto CableClub_EventScript_SelectCableClubRoom
	end

CableClub_EventScript_UnusedWelcomeToCableClub::
	msgbox CableClub_Text_WhichService
	goto CableClub_EventScript_SelectCableClubRoom
	end

CableClub_EventScript_SelectCableClubRoom::
	setvar VAR_0x8004, 0
	multichoice 0, 0, MULTICHOICE_TRADE_CENTER_COLOSSEUM, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_TradeCenter
	case 1, CableClub_EventScript_Colosseum
	case 2, CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortLink
	end

CableClub_EventScript_Colosseum::
	copyvar VAR_0x8007, VAR_LAST_TALKED
	goto CableClub_EventScript_SelectBattleMode
	end

CableClub_EventScript_SelectBattleMode::
	message CableClub_Text_PlayWhichBattleMode
	waitmessage
	multichoice 0, 0, MULTICHOICE_SINGLE_DOUBLE_MULTI_INFO_EXIT, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_SingleBattleMode
	case 1, CableClub_EventScript_DoubleBattleMode
	case 2, CableClub_EventScript_MultiBattleMode
	case 3, CableClub_EventScript_BattleModeInfo
	case 4, CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortLink
	end

CableClub_EventScript_BattleModeInfo::
	msgbox CableClub_Text_ExplainBattleModes
	goto CableClub_EventScript_SelectBattleMode
	end

CableClub_EventScript_SingleBattleMode::
	setvar VAR_0x8004, USING_SINGLE_BATTLE
	goto CableClub_EventScript_TryEnterColosseum
	end

CableClub_EventScript_DoubleBattleMode::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, CableClub_EventScript_NeedTwoMonsForDoubleBattle
	setvar VAR_0x8004, USING_DOUBLE_BATTLE
	goto CableClub_EventScript_TryEnterColosseum
	end

CableClub_EventScript_NeedTwoMonsForDoubleBattle::
	msgbox CableClub_Text_NeedTwoMonsForDoubleBattle
	goto CableClub_EventScript_SelectBattleMode
	end

CableClub_EventScript_MultiBattleMode::
	setvar VAR_0x8004, USING_MULTI_BATTLE
	goto CableClub_EventScript_TryEnterColosseum
	end

CableClub_EventScript_TryEnterColosseum::
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_AbortLink
	message CableClub_Text_PleaseWaitBCancel
	waitmessage
	special HelpSystem_Disable
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special TryBattleLinkup
	waitstate
	call EventScript_RestorePrevTextColor
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterColosseum
	goto_if_eq VAR_RESULT, LINKUP_SOMEONE_NOT_READY, CableClub_EventScript_AbortLinkSomeoneNotReady
	goto_if_eq VAR_RESULT, LINKUP_DIFF_SELECTIONS, CableClub_EventScript_AbortLinkDifferentSelections
	goto_if_eq VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS, CableClub_EventScript_AbortLinkIncorrectNumberOfBattlers
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_AbortLink
	goto_if_eq VAR_RESULT, LINKUP_CONNECTION_ERROR, CableClub_EventScript_AbortLinkConnectionError
	end

CableClub_EventScript_EnterColosseum::
	special HealPlayerParty
	special SavePlayerParty
	special LoadPlayerBag
	copyvar VAR_CABLE_CLUB_STATE, VAR_0x8004
	messageautoscroll CableClub_Text_PleaseEnter
	waitmessage
	call CableClub_EventScript_OpenDirectCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement LOCALID_PLAYER, Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 9, 1
	waitdooranim
	applymovement LOCALID_PLAYER, Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideobjectat LOCALID_PLAYER, 0
	closedoor 9, 1
	waitdooranim
	release
	goto_if_eq VAR_0x8004, USING_MULTI_BATTLE, CableClub_EventScript_WarpTo4PColosseum
	special SetCableClubWarp
	warp MAP_BATTLE_COLOSSEUM_2P, 6, 8
	special DoCableClubWarp
	waitstate
	end

@ Unused
CableClub_EventScript_PlayerApproachLinkRoomRight::
	applymovement LOCALID_PLAYER, Movement_PlayerApproachLinkRoomRight
	waitmovement 0
	return

CableClub_EventScript_WarpTo4PColosseum::
	special SetCableClubWarp
	warp MAP_BATTLE_COLOSSEUM_4P, 5, 8
	special DoCableClubWarp
	waitstate
	end

CableClub_EventScript_AbortLinkIncorrectNumberOfBattlers::
	switch VAR_0x8004
	case USING_SINGLE_BATTLE, CableClub_EventScript_AbortLinkWrongNumberForSingleBattle
	case USING_DOUBLE_BATTLE, CableClub_EventScript_AbortLinkWrongNumberForDoubleBattle
	case USING_MULTI_BATTLE, CableClub_EventScript_AbortLinkNeedFourPlayers
	goto CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants
	end

CableClub_EventScript_AbortLinkNeedFourPlayers::
	special CloseLink
	msgbox CableClub_Text_NeedFourPlayers
	goto CableClub_EventScript_ConfirmNumberAndRestart
	end

CableClub_EventScript_AbortLinkWrongNumberForDoubleBattle::
	special CloseLink
	msgbox CableClub_Text_CantDoubleBattleWithXPlayers
	goto CableClub_EventScript_ConfirmNumberAndRestart
	end

CableClub_EventScript_AbortLinkWrongNumberForSingleBattle::
	special CloseLink
	msgbox CableClub_Text_CantSingleBattleWithXPlayers
	goto CableClub_EventScript_ConfirmNumberAndRestart
	end

CableClub_EventScript_ConfirmNumberAndRestart::
	special CloseLink  @ Redundant
	special HelpSystem_Enable
	msgbox CableClub_Text_PleaseConfirmNumberAndRestart
	release
	end

CableClub_EventScript_TradeCenter::
	copyvar VAR_0x8007, VAR_LAST_TALKED
	call CableClub_EventScript_CheckPartyTradeRequirements
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_AbortLink
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_AbortLink
	message CableClub_Text_PleaseWaitBCancel
	waitmessage
	special HelpSystem_Disable
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special TryTradeLinkup
	waitstate
	call EventScript_RestorePrevTextColor
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterTradeCenter
	goto_if_eq VAR_RESULT, LINKUP_SOMEONE_NOT_READY, CableClub_EventScript_AbortLinkSomeoneNotReady
	goto_if_eq VAR_RESULT, LINKUP_DIFF_SELECTIONS, CableClub_EventScript_AbortLinkDifferentSelections
	goto_if_eq VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS, CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_AbortLink
	goto_if_eq VAR_RESULT, LINKUP_CONNECTION_ERROR, CableClub_EventScript_AbortLinkConnectionError
	goto_if_eq VAR_RESULT, LINKUP_PLAYER_NOT_READY, CableClub_EventScript_AbortLinkPlayerNotReady
	goto_if_eq VAR_RESULT, LINKUP_PARTNER_NOT_READY, CableClub_EventScript_AbortLinkOtherTrainerNotReady
	end

CableClub_EventScript_EnterTradeCenter::
	setvar VAR_0x8004, USING_TRADE_CENTER
	copyvar VAR_CABLE_CLUB_STATE, VAR_0x8004
	messageautoscroll CableClub_Text_PleaseEnter
	waitmessage
	call CableClub_EventScript_OpenDirectCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement LOCALID_PLAYER, Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 9, 1
	waitdooranim
	applymovement LOCALID_PLAYER, Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideobjectat LOCALID_PLAYER, 0
	closedoor 9, 1
	waitdooranim
	release
	special SetCableClubWarp
	setwarp MAP_TRADE_CENTER, 5, 8
	special DoCableClubWarp
	waitstate
	end

CableClub_EventScript_CheckPartyTradeRequirements::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_lt VAR_RESULT, 2, CableClub_EventScript_NeedTwoMonsToTrade
	specialvar VAR_RESULT, DoesPartyHaveEnigmaBerry
	goto_if_eq VAR_RESULT, TRUE, CableClub_EventScript_CantTradeEnigmaBerry
	setvar VAR_RESULT, TRUE
	return

CableClub_EventScript_NeedTwoMonsToTrade::
	msgbox CableClub_Text_NeedTwoMonsToTrade
	setvar VAR_RESULT, FALSE
	return

CableClub_EventScript_CantTradeEnigmaBerry::
	msgbox CableClub_Text_CantTradeEnigmaBerry
	setvar VAR_RESULT, FALSE
	return

@ Record Corner is nopped in FRLG
CableClub_EventScript_RecordCorner::
	end

CableClub_EventScript_AbortLinkPlayerNotReady::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_NotSetUpForFarAwayRegion
	release
	end

CableClub_EventScript_AbortLinkOtherTrainerNotReady::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_OtherTrainerNotReady
	release
	end

CableClub_EventScript_AbortLinkConnectionError::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_LinkErrorPleaseReset
	release
	end

CableClub_EventScript_AbortLinkSomeoneNotReady::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_SomeoneIsNotReadyToLink
	release
	end

CableClub_EventScript_AbortLinkDifferentSelections::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_PlayersMadeDifferentSelections
	release
	end

CableClub_EventScript_AbortLink::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_PleaseVisitAgain
	release
	end

CableClub_EventScript_AbortMinigame::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_ComeAgain
	release
	end

@ Unused
CableClub_EventScript_CableClubWarp::
	special SetCableClubWarp
	special DoCableClubWarp
	waitstate
	end

CableClub_EventScript_AbortLinkIncorrectNumberOfParticipants::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_IncorrectNumberOfParticipants
	release
	end

CableClub_EventScript_AbortLinkPlayerHasBadEgg::
	special CloseLink
	special HelpSystem_Enable
	msgbox CableClub_Text_YouHaveAMonThatCantBeTaken
	release
	end

CableClub_EventScript_WirelessClubAdjustements::
	msgbox Text_WirelessClubUndergoingAdjustments
	release
	end

CableClub_EventScript_NotReadyYet::
	msgbox Text_AppearsToBeUndergoingAdjustments
	releaseall
	end

Movement_AttendantFaceDown::
	face_down
	step_end

@ Unused
Movement_AttendantFaceRight::
	face_right
	step_end

Movement_AttendantFaceLeft::
	face_left
	step_end

Movement_PlayerExitLinkRoom::
	walk_down
	walk_down
	step_end

Movement_PlayerApproachLinkRoomRight::
	walk_right
	walk_up
	walk_up
	step_end

Movement_PlayerApproachLinkRoomLeft::
	walk_left
	walk_up
	walk_up
	step_end

Movement_PlayerEnterLinkRoom::
	walk_up
	step_end

@ Unused
Movement_PlayerFaceAttendantLeft::
	face_left
	step_end

Movement_PlayerFaceAttendantRight::
	face_right
	step_end

Movement_PlayerEnterMinigameRoom::
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

CableClub_EventScript_ShowBattleRecords::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	fadescreen FADE_TO_BLACK
	setvar VAR_0x8004, 0
	special ShowBattleRecords
	waitstate
	releaseall
	end

BattleColosseum_2P_EventScript_PlayerSpot0::
	setvar VAR_0x8005, 0
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_2P_EventScript_PlayerSpot1::
	setvar VAR_0x8005, 1
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_4P_EventScript_PlayerSpot0::
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleColosseum_4P_EventScript_CancelSpotTrigger
	setvar VAR_0x8005, 0
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_4P_EventScript_PlayerSpot1::
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleColosseum_4P_EventScript_CancelSpotTrigger
	setvar VAR_0x8005, 1
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_4P_EventScript_PlayerSpot2::
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleColosseum_4P_EventScript_CancelSpotTrigger
	setvar VAR_0x8005, 2
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_4P_EventScript_PlayerSpot3::
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleColosseum_4P_EventScript_CancelSpotTrigger
	setvar VAR_0x8005, 3
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterColosseumPlayerSpot
	waitstate
	end

BattleColosseum_4P_EventScript_CancelSpotTrigger::
	end

TradeCenter_EventScript_Chair0::
	setvar VAR_0x8005, 0
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterTradeSeat
	waitstate
	end

TradeCenter_EventScript_Chair1::
	setvar VAR_0x8005, 1
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterTradeSeat
	waitstate
	end

@ Unused
TradeCenter_EventScript_Chair2::
	setvar VAR_0x8005, 2
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterTradeSeat
	waitstate
	end

@ Unused
TradeCenter_EventScript_Chair3::
	setvar VAR_0x8005, 3
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special EnterTradeSeat
	waitstate
	end

@ Nop in FRLG
@ Separate labels to match GetDirectionForEventScript
RecordCorner_EventScript_Spot0::
RecordCorner_EventScript_Spot1::
RecordCorner_EventScript_Spot2::
RecordCorner_EventScript_Spot3::
	end

CableClub_EventScript_ReadTrainerCard::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox Text_LookedAtPlayersTrainerCard
	fadescreen FADE_TO_BLACK
	special Script_ShowLinkTrainerCard
	waitstate
	end

CableClub_EventScript_ReadTrainerCardColored::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox Text_LookedAtPlayersTrainerCardColored
	fadescreen FADE_TO_BLACK
	special Script_ShowLinkTrainerCard
	waitstate
	end

CableClub_EventScript_TooBusyToNotice::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox Text_TrainerTooBusyToNotice
	closemessage
	end

BattleColosseum_2P_EventScript_Attendant::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special Script_FacePlayer
	msgbox Text_TakeSeatStartBattle
	special Script_ClearHeldMovement
	closemessage
	end

TradeCenter_EventScript_Attendant::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	special Script_FacePlayer
	msgbox Text_TakeSeatStartTrade
	special Script_ClearHeldMovement
	closemessage
	end

@ Nop in FRLG
RecordCorner_EventScript_Attendant::
	end

TradeCenter_ConfirmLeaveRoom::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox Text_TerminateLinkIfYouLeaveRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, TradeCenter_TerminateLink
	erasebox 0, 0, 29, 19
	releaseall
	end

TradeCenter_TerminateLink::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	messageautoscroll Text_TerminateLinkConfirmation
	waitmessage
	special ExitLinkRoom
	end

CableClub_EventScript_DoLinkRoomExit::
	special CleanupLinkRoomState
	special ReturnFromLinkRoom
	waitstate
	end

CableClub_EventScript_UnionRoomAttendant::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	faceplayer
	goto_if_unset FLAG_SYS_POKEDEX_GET, CableClub_EventScript_WirelessClubAdjustements
	specialvar VAR_RESULT, IsBadEggInParty
	goto_if_eq VAR_RESULT, TRUE, CableClub_EventScript_AbortLinkPlayerHasBadEgg
	copyvar VAR_0x8007, VAR_LAST_TALKED
	specialvar VAR_RESULT, IsWirelessAdapterConnected
	goto_if_eq VAR_RESULT, FALSE, CableClub_EventScript_UnionRoomAdapterNotConnected
	message CableClub_Text_WelcomeUnionRoomEnter
	waitmessage
	goto CableClub_EventScript_AskEnterUnionRoom
	end

CableClub_EventScript_AskEnterUnionRoom::
	multichoice 18, 6, MULTICHOICE_YES_NO_INFO, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_EnterUnionRoom
	case 1, CableClub_EventScript_AbortLink
	case 2, CableClub_EventScript_UnionRoomInfo
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortLink
	end

CableClub_EventScript_UnionRoomInfo::
	message CableClub_Text_UnionRoomInfo
	waitmessage
	goto CableClub_EventScript_AskEnterUnionRoom
	end

CableClub_EventScript_EnterUnionRoom::
	call CableClub_EventScript_CheckPartyUnionRoomRequirements
	goto_if_eq VAR_RESULT, FALSE, CableClub_EventScript_AbortLink
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_AbortLink
	msgbox CableClub_Text_EnjoyUnionRoom
	closemessage
	special HealPlayerParty
	setvar VAR_0x8004, USING_UNION_ROOM
	copyvar VAR_CABLE_CLUB_STATE, VAR_0x8004
	special HelpSystem_Disable
	call CableClub_EventScript_OpenUnionRoomBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Movement_AttendantFaceLeft
	waitmovement 0
	applymovement LOCALID_PLAYER, Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 5, 1
	waitdooranim
	applymovement LOCALID_PLAYER, Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideobjectat LOCALID_PLAYER, 0
	closedoor 5, 1
	waitdooranim
	special Script_ResetUnionRoomTrade
	special SetCableClubWarp
	warpspinenter MAP_UNION_ROOM, 7, 11
	waitstate
	special RunUnionRoom
	waitstate
	end

CableClub_EventScript_CheckPartyUnionRoomRequirements::
	specialvar VAR_RESULT, CountPartyNonEggMons
	goto_if_lt VAR_RESULT, 2, CableClub_EventScript_NeedTwoMonsForUnionRoom
	specialvar VAR_RESULT, DoesPartyHaveEnigmaBerry
	goto_if_eq VAR_RESULT, TRUE, CableClub_EventScript_NoEnigmaBerryInUnionRoom
	setvar VAR_RESULT, TRUE
	return

CableClub_EventScript_NeedTwoMonsForUnionRoom::
	msgbox CableClub_Text_NeedTwoMonsForUnionRoom
	goto EventScript_SetResultFalse
	end

CableClub_EventScript_NoEnigmaBerryInUnionRoom::
	msgbox CableClub_Text_NoEnigmaBerryInUnionRoom
	goto EventScript_SetResultFalse
	end

CableClub_EventScript_UnionRoomAdapterNotConnected::
	msgbox CableClub_Text_UnionRoomAdapterNotConnected
	release
	return

CableClub_EventScript_WirelessClubAttendant::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_POKEDEX_GET, CableClub_EventScript_WirelessClubAdjustements
	msgbox CableClub_Text_AskAboutLinking, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CableClub_EventScript_DontAskAboutLinking
	msgbox CableClub_Text_ExplainWirelessClub
	release
	return

CableClub_EventScript_DontAskAboutLinking::
	msgbox CableClub_Text_HopeYouEnjoyWirelessSystem
	release
	return

CableClub_EventScript_DirectCornerAttendant::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	faceplayer
	goto_if_unset FLAG_SYS_POKEDEX_GET, CableClub_EventScript_WirelessClubAdjustements
	specialvar VAR_RESULT, IsBadEggInParty
	goto_if_eq VAR_RESULT, TRUE, CableClub_EventScript_AbortLinkPlayerHasBadEgg
	specialvar VAR_RESULT, IsWirelessAdapterConnected
	goto_if_eq VAR_RESULT, FALSE, CableClub_EventScript_WelcomeToCableClub
	message CableClub_Text_WelcomeWhichDirectCornerRoom
	waitmessage
	delay 15
	goto CableClub_EventScript_DirectCornerSelectService
	end

CableClub_EventScript_DirectCornerSelectService::
	goto_if_unset FLAG_GOT_POWDER_JAR, CableClub_EventScript_DirectCornerNoBerry
	multichoice 0, 0, MULTICHOICE_TRADE_COLOSSEUM_CRUSH, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_WirelessTrade
	case 1, CableClub_EventScript_WirelessBattleSelect
	case 2, CableClub_EventScript_WirelessBerryCrush
	case 3, CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortLink
	end

CableClub_EventScript_DirectCornerNoBerry::
	multichoice 0, 0, MULTICHOICE_TRADE_COLOSSEUM_2, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_WirelessTrade
	case 1, CableClub_EventScript_WirelessBattleSelect
	case 2, CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortLink
	end

CableClub_EventScript_WirelessTrade::
	msgbox CableClub_Text_TradePokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CableClub_EventScript_AbortLink
	call CableClub_EventScript_CheckPartyTradeRequirements
	goto_if_eq VAR_RESULT, FALSE, CableClub_EventScript_AbortLink
	setvar VAR_0x8004, LINK_GROUP_TRADE
	goto CableClub_EventScript_SaveAndChooseLinkLeader
	end

CableClub_EventScript_WirelessBattleSelect::
	message CableClub_Text_PlayWhichBattleMode
	waitmessage
	multichoice 0, 0, MULTICHOICE_SINGLE_DOUBLE_MULTI_INFO_EXIT, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_WirelessSingleBattle
	case 1, CableClub_EventScript_WirelessDoubleBattle
	case 2, CableClub_EventScript_WirelessMultiBattle
	case 3, CableClub_EventScript_WirelessBattleInfo
	case 4, CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortLink
	end

CableClub_EventScript_WirelessSingleBattle::
	setvar VAR_0x8004, LINK_GROUP_SINGLE_BATTLE
	goto CableClub_EventScript_SaveAndChooseLinkLeader
	end

CableClub_EventScript_WirelessDoubleBattle::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, CableClub_EventScript_TwoMonsNeededForWirelessDoubleBattle
	setvar VAR_0x8004, LINK_GROUP_DOUBLE_BATTLE
	goto CableClub_EventScript_SaveAndChooseLinkLeader
	end

CableClub_EventScript_TwoMonsNeededForWirelessDoubleBattle::
	msgbox CableClub_Text_NeedTwoMonsForDoubleBattle
	goto CableClub_EventScript_WirelessBattleSelect
	end

CableClub_EventScript_WirelessMultiBattle::
	setvar VAR_0x8004, LINK_GROUP_MULTI_BATTLE
	goto CableClub_EventScript_SaveAndChooseLinkLeader
	end

CableClub_EventScript_WirelessBattleInfo::
	msgbox CableClub_Text_ExplainBattleModes
	goto CableClub_EventScript_WirelessBattleSelect
	end

CableClub_EventScript_WirelessBerryCrush::
	msgbox CableClub_Text_UseBerryCrush, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CableClub_EventScript_AbortLink
	special HasAtLeastOneBerry
	goto_if_eq VAR_RESULT, FALSE, CableClub_EventScript_NeedBerryForBerryCrush
	setvar VAR_0x8004, LINK_GROUP_BERRY_CRUSH
	goto CableClub_EventScript_SaveAndChooseLinkLeader
	end

CableClub_EventScript_NeedBerryForBerryCrush::
	msgbox CableClub_Text_NeedBerryForBerryCrush
	goto CableClub_EventScript_DirectCornerSelectService
	end

CableClub_EventScript_SaveAndChooseLinkLeader::
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_AbortLink
	switch VAR_0x8004
	case LINK_GROUP_TRADE, CableClub_EventScript_ChooseLinkLeaderFrom2
	case LINK_GROUP_SINGLE_BATTLE, CableClub_EventScript_ChooseLinkLeaderFrom2
	case LINK_GROUP_DOUBLE_BATTLE, CableClub_EventScript_ChooseLinkLeaderFrom2
	case LINK_GROUP_MULTI_BATTLE, CableClub_EventScript_ChooseLinkLeaderFrom4
	case LINK_GROUP_BERRY_CRUSH, CableClub_EventScript_ChooseLinkLeader
	end

CableClub_EventScript_ChooseLinkLeaderFrom2::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message CableClub_Text_ChooseGroupLeaderOfTwo
	waitmessage
	call EventScript_RestorePrevTextColor
	multichoice 13, 6, MULTICHOICE_JOIN_OR_LEAD, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_TryJoinGroup2Players
	case 1, CableClub_EventScript_TryLeadGroup2Players
	case 2, CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortLink
	end

CableClub_EventScript_TryLeadGroup2Players::
	call CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_ChooseLinkLeaderFrom2
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, CableClub_EventScript_TryLeadGroup2Players
	release
	return

CableClub_EventScript_TryJoinGroup2Players::
	call CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_ChooseLinkLeaderFrom2
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, CableClub_EventScript_TryJoinGroup2Players
	release
	return

CableClub_EventScript_ChooseLinkLeaderFrom4::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message CableClub_Text_ChooseGroupLeaderOfFour
	waitmessage
	call EventScript_RestorePrevTextColor
	multichoice 13, 6, MULTICHOICE_JOIN_OR_LEAD, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_TryJoinGroup4Players
	case 1, CableClub_EventScript_TryLeadGroup4Players
	case 2, CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortLink
	end

CableClub_EventScript_TryLeadGroup4Players::
	call CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_ChooseLinkLeaderFrom4
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, CableClub_EventScript_TryLeadGroup4Players
	release
	return

CableClub_EventScript_TryJoinGroup4Players::
	call CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_ChooseLinkLeaderFrom4
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, CableClub_EventScript_TryJoinGroup4Players
	release
	return

CableClub_EventScript_ChooseLinkLeader::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message CableClub_Text_ChooseGroupLeader
	waitmessage
	call EventScript_RestorePrevTextColor
	multichoice 13, 6, MULTICHOICE_JOIN_OR_LEAD, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_TryJoinGroupXPlayers
	case 1, CableClub_EventScript_TryLeadGroupXPlayers
	case 2, CableClub_EventScript_AbortLink
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortLink
	end

CableClub_EventScript_TryLeadGroupXPlayers::
	call CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_ChooseLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, CableClub_EventScript_TryLeadGroupXPlayers
	release
	return

CableClub_EventScript_TryJoinGroupXPlayers::
	call CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterWirelessLinkRoom
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_ChooseLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, CableClub_EventScript_TryJoinGroupXPlayers
	release
	return

CableClub_EventScript_TryBecomeLinkLeader::
	special HelpSystem_Disable
	special TryBecomeLinkLeader
	waitstate
	return

CableClub_EventScript_TryJoinLinkGroup::
	special HelpSystem_Disable
	special TryJoinLinkGroup
	waitstate
	return

CableClub_EventScript_EnterWirelessLinkRoom::
	messageautoscroll CableClub_Text_DirectYouToYourRoom
	waitmessage
	delay 60
	closemessage
	copyvar VAR_0x8007, VAR_LAST_TALKED
	call CableClub_EventScript_OpenDirectCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement LOCALID_PLAYER, Movement_PlayerApproachLinkRoomLeft
	waitmovement 0
	opendoor 9, 1
	waitdooranim
	applymovement LOCALID_PLAYER, Movement_PlayerEnterLinkRoom
	waitmovement 0
	hideobjectat LOCALID_PLAYER, 0
	closedoor 9, 1
	waitdooranim
	release
	waitstate
	end

CableClub_EventScript_ShowWirelessCommunicationScreen::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_unset FLAG_SYS_POKEDEX_GET, CableClub_EventScript_NotReadyYet
	specialvar VAR_RESULT, IsWirelessAdapterConnected
	goto_if_eq VAR_RESULT, FALSE, CableClub_EventScript_AdapterNotConnected
	special HelpSystem_Disable
	fadescreen FADE_TO_BLACK
	special ShowWirelessCommunicationScreen
	waitstate
	msgbox CableClub_Text_ParticipantsStepUpToCounter
	special HelpSystem_Enable
	releaseall
	end

CableClub_EventScript_AdapterNotConnected::
	msgbox CableClub_Text_AdapterNotConnected
	releaseall
	end

CableClub_EventScript_OpenUnionRoomBarrier::
	setmetatile 5, 3, METATILE_PokemonCenter_Floor_ShadeLeft, 0
	return

CableClub_EventScript_CloseUnionRoomBarrier::
	setmetatile 5, 3, METATILE_PokemonCenter_CounterBarrier, 1
	return

CableClub_EventScript_OpenDirectCornerBarrier::
	setmetatile 9, 3, METATILE_PokemonCenter_Floor_ShadeLeft, 0
	return

CableClub_EventScript_CloseDirectCornerBarrier::
	setmetatile 9, 3, METATILE_PokemonCenter_CounterBarrier, 1
	return

CableClub_EventScript_OpenGameCornerBarrier::
	setmetatile 5, 3, METATILE_GameCorner_CheckeredFloor_ShadeLeft, 0
	return

CableClub_EventScript_CloseGameCornerBarrier::
	setmetatile 5, 3, METATILE_GameCorner_CounterBarrier, 1
	return

CableClub_OnResume::
	special InitUnionRoom
	end

JoyfulGameCorner_EventScript_InfoMan2::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	faceplayer
	message Text_DescribeWhichGame
	waitmessage
	multichoice 0, 0, MULTICHOICE_POKEJUMP_DODRIO, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_PokemonJumpInfo
	case 1, CableClub_EventScript_DodrioBerryPickingInfo
	case 2, CableClub_EventScript_MinigameInfoExit
	case SCR_MENU_CANCEL, CableClub_EventScript_MinigameInfoExit
	end

CableClub_EventScript_PokemonJumpInfo::
	msgbox Text_PokemonJumpInfo
	release
	end

CableClub_EventScript_DodrioBerryPickingInfo::
	msgbox Text_DodrioBerryPickingInfo
	release
	end

CableClub_EventScript_MinigameInfoExit::
	msgbox Text_TalkToManToPlay
	release
	end

JoyfulGameCorner_EventScript_MinigameAttendant::
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lock
	faceplayer
	message Text_WelcomeCanYouWait
	waitmessage
	specialvar VAR_RESULT, IsWirelessAdapterConnected
	goto_if_eq VAR_RESULT, FALSE, CableClub_EventScript_AdapterNotConnectedMinigame
	delay 60
	special HelpSystem_Disable
	message Text_PlayWhichGame
	waitmessage
	multichoice 0, 0, MULTICHOICE_POKEJUMP_DODRIO, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_PlayPokemonJump
	case 1, CableClub_EventScript_PlayDodrioBerryPicking
	case 2, CableClub_EventScript_AbortMinigame
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortMinigame
	end

CableClub_EventScript_PlayPokemonJump::
	setvar VAR_0x8005, 0
	special IsPokemonJumpSpeciesInParty
	goto_if_eq VAR_RESULT, FALSE, CableClub_EventScript_NoEligiblePkmn
	msgbox Text_EnterWhichPokemon
	setvar VAR_0x8005, 0
	special ChooseMonForWirelessMinigame
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, CableClub_EventScript_AbortMinigame
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_AbortMinigame
	setvar VAR_0x8004, LINK_GROUP_POKEMON_JUMP
	goto CableClub_EventScript_ChooseLinkLeaderMinigame
	end

CableClub_EventScript_PlayDodrioBerryPicking::
	setvar VAR_0x8005, 1
	special IsDodrioInParty
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_NoEligiblePkmn
	msgbox Text_EnterWhichPokemon
	setvar VAR_0x8005, 1
	special ChooseMonForWirelessMinigame
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, CableClub_EventScript_AbortMinigame
	call EventScript_AskSaveGame
	goto_if_eq VAR_RESULT, 0, CableClub_EventScript_AbortMinigame
	setvar VAR_0x8004, LINK_GROUP_BERRY_PICKING
	goto CableClub_EventScript_ChooseLinkLeaderMinigame
	end

CableClub_EventScript_ChooseLinkLeaderMinigame::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	message CableClub_Text_ChooseGroupLeader
	waitmessage
	call EventScript_RestorePrevTextColor
	multichoice 13, 6, MULTICHOICE_JOIN_OR_LEAD, FALSE
	switch VAR_RESULT
	case 0, CableClub_EventScript_TryJoinMinigameLinkGroup
	case 1, CableClub_EventScript_TryBecomeMinigameLinkLeader
	case 2, CableClub_EventScript_AbortMinigame
	case SCR_MENU_CANCEL, CableClub_EventScript_AbortMinigame
	end

CableClub_EventScript_TryBecomeMinigameLinkLeader::
	call CableClub_EventScript_TryBecomeLinkLeader
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterMinigame
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_ChooseLinkLeaderMinigame
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, CableClub_EventScript_TryBecomeMinigameLinkLeader
	release
	return

CableClub_EventScript_TryJoinMinigameLinkGroup::
	call CableClub_EventScript_TryJoinLinkGroup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, CableClub_EventScript_EnterMinigame
	goto_if_eq VAR_RESULT, LINKUP_FAILED, CableClub_EventScript_ChooseLinkLeaderMinigame
	goto_if_eq VAR_RESULT, LINKUP_RETRY_ROLE_ASSIGN, CableClub_EventScript_TryJoinMinigameLinkGroup
	release
	return

CableClub_EventScript_EnterMinigame::
	messageautoscroll Text_AllGoodToGo
	waitmessage
	delay 120
	closemessage
	copyvar VAR_0x8007, VAR_LAST_TALKED
	call CableClub_EventScript_OpenGameCornerBarrier
	special DrawWholeMapView
	playse SE_CLICK
	delay 60
	applymovement VAR_LAST_TALKED, Movement_AttendantFaceLeft
	waitmovement 0
	closemessage
	applymovement LOCALID_PLAYER, Movement_PlayerEnterMinigameRoom
	waitmovement 0
	hideobjectat LOCALID_PLAYER, 0
	release
	waitstate
	end

CableClub_EventScript_AdapterNotConnectedMinigame::
	msgbox Text_AdapterNotConnectedMinigame
	release
	end

CableClub_EventScript_NoEligiblePkmn::
	msgbox EventScript_ExplainPokemonJumpRequirements, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CableClub_EventScript_AbortMinigame
	call_if_eq VAR_0x8005, 0, CableClub_EventScript_ExplainPokemonJumpRequirements
	call_if_eq VAR_0x8005, 1, CableClub_EventScript_ExplainDodrioBerryPickingRequirements
	goto CableClub_EventScript_AbortMinigame
	end

CableClub_EventScript_ExplainPokemonJumpRequirements::
	msgbox Text_ShortJumpingPokemonAllowed
	return

CableClub_EventScript_ExplainDodrioBerryPickingRequirements::
	msgbox Text_OnlyDodrioAllowed
	return

TwoIsland_JoyfulGameCorner_EventScript_ShowPokemonJumpRecords::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	special ShowPokemonJumpRecords
	waitstate
	releaseall
	end

TwoIsland_JoyfulGameCorner_EventScript_ShowDodrioBerryPickingRecords::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	special ShowDodrioBerryPickingRecords
	waitstate
	releaseall
	end

CableClub_Text_WelcomeWhichCableClubService::
	.string "Velkommen til POKéMON CABLE\n"
	.string "CLUBBEN.\p"
	.string "Hvilken af vores tjenester vil du\n"
	.string "bruge?$"

CableClub_Text_WhichService::
	.string "Hvilken af vores tjenester vil du\n"
	.string "bruge?$"

CableClub_Text_TradeMonsUsingLinkCable::
	.string "Byt POKéMON med en anden spiller\n"
	.string "med et GBA Game Link-kabel.$"

CableClub_Text_BattleUsingLinkCable::
	.string "Du kan kæmpe mod en anden TRÆNER\n"
	.string "med et GBA Game Link-kabel.$"

@ Unused, translated in Emerald
CableClub_Text_CloseThisMenu::
	.string "おわります$"

CableClub_Text_NeedTwoMonsForDoubleBattle::
	.string "Til en DOBBELTKAMP skal du\n"
	.string "have mindst to POKéMON.$"

CableClub_Text_NeedTwoMonsToTrade::
	.string "For at bytte skal du have\n"
	.string "mindst to POKéMON med dig.$"

CableClub_Text_CantTradeEnigmaBerry::
	.string "En POKéMON der holder {STR_VAR_1}\n"
	.string "BÆR kan ikke byttes.$"

CableClub_Text_PleaseWaitBCancel::
	.string "Vent venligst.\n"
	.string "… … B-knap: Annuller$"

CableClub_Text_WhenAllPlayersReadyAConfirmBCancel::
	.string "Når alle spillere er klar…\n"
	.string "A-knap: Bekræft\l"
	.string "B-knap: Annuller$"

CableClub_Text_StartLinkWithXPlayersAConfirmBCancel::
	.string "Start link med {STR_VAR_1} spillere.\n"
	.string "A-knap: Bekræft\l"
	.string "B-knap: Annuller$"

CableClub_Text_AwaitingLinkupBCancel::
	.string "Afventer forbindelse…\n"
	.string "… … B-knap: Annuller$"

@ Unused, translated in Emerald
CableClub_Text_OkayToSaveProgress::
	.string "はじめる　まえに　レポートを\n"
	.string "かきますが　よろしいですか？$"

CableClub_Text_PleaseEnter::
	.string "Kom venligst ind.$"

CableClub_Text_DirectYouToYourRoom::
	.string "Jeg viser dig til dit rum nu.$"

CableClub_Text_SomeoneIsNotReadyToLink::
	.string "Nogen er ikke klar til link.\p"
	.string "Kom tilbage når alle\n"
	.string "har gjort sig klar.$"

CableClub_Text_LinkErrorPleaseReset::
	.string "Beklager, der opstod en link-fejl…\n"
	.string "Nulstil og prøv igen.$"

CableClub_Text_PlayersMadeDifferentSelections::
	.string "Det ser ud til at link-partnerne har\n"
	.string "valgt forskelligt.$"

CableClub_Text_PleaseVisitAgain::
	.string "Kom gerne igen.$"

CableClub_Text_IncorrectNumberOfParticipants::
	.string "Antallet af deltagere er\n"
	.string "forkert.$"

CableClub_Text_CantSingleBattleWithXPlayers::
	.string "SINGLE BATTLE-tilstand kan ikke\n"
	.string "spilles af {STR_VAR_1} spillere.$"

CableClub_Text_CantDoubleBattleWithXPlayers::
	.string "DOUBLE BATTLE-tilstand kan ikke\n"
	.string "spilles af {STR_VAR_1} spillere.$"

CableClub_Text_NeedFourPlayers::
	.string "Der skal være fire spillere for at spille\n"
	.string "denne kamptilstand.$"

CableClub_Text_PleaseConfirmNumberAndRestart::
	.string "Bekræft venligst antallet af\n"
	.string "spillere og start igen.$"

Text_TerminateLinkIfYouLeaveRoom::
	.string "Linket afbrydes hvis du\n"
	.string "forlader rummet. Er det okay?$"

Text_TerminateLinkConfirmation::
	.string "Afbryder link…\n"
	.string "Du bliver fulgt ud af\l"
	.string "rummet. Vent venligst.$"

Text_TrainerTooBusyToNotice::
	.string "Denne TRÆNER har for travlt til\n"
	.string "at bemærke det…$"

Text_LookedAtPlayersTrainerCard::
	.string "Yes! Fik set {STR_VAR_1}s\n"
	.string "TRÆNERKORT!$"

Text_LookedAtPlayersTrainerCardColored::
	.string "Yes! Fik set {STR_VAR_1}s\n"
	.string "TRÆNERKORT!\p"
	.string "Det er et {STR_VAR_2}-kort!$"

Text_TakeSeatStartBattle::
	.string "Tag venligst plads og start\n"
	.string "din kamp.$"

Text_TakeSeatStartTrade::
	.string "Tag venligst plads og start\n"
	.string "dit bytte.$"

@ Unused, leftover from RS
RecordCorner_Text_ThanksForComing::
	.string "ごりよう　ありがとう　ございました$"

CableClub_Text_TrainerCardDataOverwritten::
	.string "TRÆNERKORT-dataene bliver\n"
	.string "overskrevet.$"

CableClub_Text_HopeToSeeYouAgain::
	.string "Jeg håber vi ses igen!$"

CableClub_Text_NotSetUpForFarAwayRegion::
	.string "Jeg er meget ked af det.\p"
	.string "Vi er endnu ikke sat op til at bytte\n"
	.string "med TRÆNERE langt væk i en anden\l"
	.string "region endnu…$"

CableClub_Text_OtherTrainerNotReady::
	.string "Den anden TRÆNER er ikke klar.$"

CableClub_Text_YouHaveAMonThatCantBeTaken::
	.string "Du har mindst én POKéMON\n"
	.string "som ikke kan medbringes.$"

CableClub_Text_AdapterNotConnected::
	.string "Den trådløse adapter er ikke\n"
	.string "forbundet korrekt.$"

CableClub_Text_ParticipantsStepUpToCounter::
	.string "Deltagere bedes gå frem til\n"
	.string "receptionsskranken.$"

@ Unused, translated in Emerald
CableClub_Text_Hello::
	.string "こんにちは！$"

@ Unused, translated in Emerald
CableClub_Text_PleaseWait::
	.string "しょうしょう　おまちください$"

CableClub_Text_YouMayTradeHere::
	.string "Du kan bytte dine POKéMON her\n"
	.string "med en anden TRÆNER.$"

CableClub_Text_YouMayBattleHere::
	.string "Du kan kæmpe mod dine venner\n"
	.string "her.$"

CableClub_Text_CanMakeBerryPowder::
	.string "To til fem TRÆNERE kan lave\n"
	.string "BÆR-PULVER sammen.$"

@ Unused, Record Mix nopped
CableClub_Text_CanMixRecords::
	.string "ワイヤレス　クラブでの\n"
	.string "あそびかたを　せつめいします$"

CableClub_Text_CancelSelectedItem::
	.string "Annullerer det valgte MENU-punkt.$"

@ Unused, translated in Emerald
CableClub_Text_WhichBattleMode::
	.string "どちらの　しょうぶに　しますか？$"

@ Unused, translated in Emerald
CableClub_Text_ReturnsToPreviousStep::
	.string "ひとつ　まえに　もどります$"

CableClub_Text_NeedBerryForBerryCrush::
	.string "For at bruge BERRY CRUSH-tjenesten\n"
	.string "skal du have mindst ét BÆR.$"

CableClub_Text_NeedTwoMonsForUnionRoom::
	.string "For at gå ind i UNION ROOM skal du\n"
	.string "have mindst to POKéMON.$"

CableClub_Text_NoEnigmaBerryInUnionRoom::
	.string "Ingen POKéMON der holder {STR_VAR_1}\n"
	.string "BÆR må gå ind i UNION ROOM.$"

CableClub_Text_UnionRoomAdapterNotConnected::
	.string "Dette er POKéMON WIRELESS CLUB\n"
	.string "UNION ROOM.\p"
	.string "Desværre er din trådløse\n"
	.string "Adapter is not forbundet korrekt.\p"
	.string "Kom venligst igen.$"

@ Unused, translated in Emerald
CableClub_Text_OhExcuseMe::
	.string "あ‥‥\n"
	.string "おきゃくさま！$"

Text_PlayerIsPlayingRightNowGoForIt::
	.string "Det ser ud til at {STR_VAR_1} spiller\n"
	.string "lige nu.\l"
	.string "Giv den gas!$"

Text_DescribeWhichGame::
	.string "Jeg kan forklare spillereglerne,\n"
	.string "hvis du vil.\p"
	.string "Hvilket spil skal jeg forklare?$"

Text_PokemonJumpInfo::
	.string "“POKéMON JUMP”\p"
	.string "Få dine POKéMON til at hoppe over\n"
	.string "VINE WHIP-rebet med A-knappen.\p"
	.string "Kun små POKéMON omkring 28 tommer\n"
	.string "eller mindre kan deltage.\p"
	.string "POKéMON der kun svømmer, graver eller\n"
	.string "flyver, er ikke gode til at hoppe.\p"
	.string "Derfor kan de POKéMON ikke\n"
	.string "deltage.\p"
	.string "Der sker gode ting hvis alle\n"
	.string "hopper i takt.$"

Text_DodrioBerryPickingInfo::
	.string "“DODRIO BERRY-PICKING”\p"
	.string "Styr DODRIOs tre hoveder til at\n"
	.string "fange faldende BÆR.\p"
	.string "Tryk højre, op eller venstre på\n"
	.string "{PLUS}-styrepuden for at flytte hovederne.\p"
	.string "For at spille dette spil skal du have\n"
	.string "en DODRIO.$"

Text_TalkToManToPlay::
	.string "Hvis du vil spille et spil,\n"
	.string "så sig det til manden ved siden af mig.$"

Text_WelcomeCanYouWait::
	.string "Hej, velkommen!\n"
	.string "Du kan spille spil via\l"
	.string "det trådløse kommunikationssystem.\p"
	.string "Kan du vente lidt?$"

CableClub_Text_ComeAgain::
	.string "Okay, kom igen!$"

Text_AdapterNotConnectedMinigame::
	.string "Den trådløse adapter er ikke\n"
	.string "forbundet.\p"
	.string "Kom tilbage når den er tilsluttet!$"

Text_PlayWhichGame::
	.string "Okay, hvilket spil ville du\n"
	.string "spille?$"

Text_EnterWhichPokemon::
	.string "Hvilken POKéMON vil du\n"
	.string "gå ind i?$"

Text_AllGoodToGo::
	.string "Okay, I er klar til at gå i gang.\n"
	.string "Lad ikke de andre slå dig!$"

@ Unused, translated in Emerald
Text_LeavingDoComeAgain::
	.string "きょうは　けえるのか？\n"
	.string "またこいよ！$"

EventScript_ExplainPokemonJumpRequirements::
	.string "Det ser ikke ud til at du har nogen\n"
	.string "POKéMON du kan tilmelde…\p"
	.string "Vil du have mig til at forklare hvilke\n"
	.string "kinds of POKéMON can gå ind i?$"

Text_ShortJumpingPokemonAllowed::
	.string "“POKéMON JUMP” er åbent for POKéMON\n"
	.string "omkring 28 tommer eller mindre.\p"
	.string "Du kan ikke tilmelde dem der\n"
	.string "ikke kan hoppe.\p"
	.string "Altså POKéMON der kun\n"
	.string "svømmer, graver eller flyver.\p"
	.string "Det er alt du behøver at vide.$"

Text_OnlyDodrioAllowed::
	.string "“DODRIO BERRY-PICKING”…\n"
	.string "Tja, navnet siger det hele.\p"
	.string "Du skal have en DODRIO for at spille\n"
	.string "dette spil.$"

@ Unused, translated in Emerald
Text_RetryFromStartPlease::
	.string "もういちど　はじめから\n"
	.string "やりなおして　みて　くれ$"

CableClub_Text_WelcomeWhichDirectCornerRoom::
	.string "Velkommen til POKéMON WIRELESS\n"
	.string "CLUB DIRECT CORNER.\p"
	.string "Du kan interagere direkte med\n"
	.string "your friends her.\p"
	.string "Hvilket rum vil du\n"
	.string "gå ind i?$"

CableClub_Text_TradePokemon::
	.string "Vil du bytte POKéMON?$"

CableClub_Text_PlayWhichBattleMode::
	.string "Hvilken kamptilstand vil du\n"
	.string "spille?$"

CableClub_Text_UseBerryCrush::
	.string "Vil du bruge\n"
	.string "BERRY CRUSH-systemet?$"

CableClub_Text_ExplainBattleModes::
	.string "Der er tre kamptilstande.\p"
	.string "SINGLE BATTLE er for to TRÆNERE\n"
	.string "med én eller flere POKéMON hver.\p"
	.string "Hver TRÆNER kan have én POKéMON\n"
	.string "i kamp ad gangen.\p"
	.string "DOUBLE BATTLE er for to TRÆNERE\n"
	.string "med to eller flere POKéMON hver.\p"
	.string "Hver TRÆNER sender to\n"
	.string "POKéMON i kamp ad gangen.\p"
	.string "MULTI BATTLE er for fire TRÆNERE\n"
	.string "med én eller flere POKéMON hver.\p"
	.string "Hver TRÆNER kan have én POKéMON\n"
	.string "in battle at a time.$"

CableClub_Text_ChooseGroupLeaderOfTwo::
	.string "Afgør hvem af jer to der\n"
	.string "bliver LEDEREN.\p"
	.string "Den anden spiller skal derefter vælge\n"
	.string "“TILMELD GRUPPE.”$"

CableClub_Text_ChooseGroupLeaderOfFour::
	.string "Afgør hvem af jer fire der\n"
	.string "bliver GRUPPELEDER.\p"
	.string "De andre spillere skal derefter vælge\n"
	.string "“TILMELD GRUPPE.”$"

CableClub_Text_ChooseGroupLeader::
	.string "Afgør hvem af jer der\n"
	.string "bliver GRUPPELEDER.\p"
	.string "De andre spillere skal derefter vælge\n"
	.string "“TILMELD GRUPPE.”$"

CableClub_Text_WelcomeUnionRoomEnter::
	.string "Velkommen til POKéMON WIRELESS\n"
	.string "CLUB UNION ROOM.\p"
	.string "Du kan interagere direkte med\n"
	.string "andre TRÆNERE her, nogle af\l"
	.string "dem kender du måske ikke engang.\p"
	.string "Vil du gå ind i RUMMET?$"

CableClub_Text_UnionRoomInfo::
	.string "TRÆNERNE i UNION ROOM\n"
	.string "er de spillere omkring dig\l"
	.string "som også er gået ind i RUMMET.\p"
	.string "Du kan gøre mange forskellige ting\n"
	.string "her, fx udveksle hilsner.\p"
	.string "Du kan tilmelde to POKéMON op til\n"
	.string "Lv. 30 til en en-mod-en kamp.\p"
	.string "Du kan deltage i en chat med\n"
	.string "to til fem personer.\p"
	.string "Eller du kan registrere en POKéMON til\n"
	.string "bytte.\p"
	.string "Vil du gå ind i RUMMET?$"

CableClub_Text_EnjoyUnionRoom::
	.string "Jeg håber du hygger dig i\n"
	.string "UNION ROOM.$"

CableClub_Text_FirstTimeRightThisWay::
	.string "Hej!\n"
	.string "Jeg hedder TEALA.\p"
	.string "Det må være din første gang\n"
	.string "up her.\p"
	.string "Jeg viser dig hvordan det trådløse\n"
	.string "kommunikationssystem virker.\p"
	.string "Først skal jeg vise dig denne\n"
	.string "etage i vores POKéMON CENTER.\p"
	.string "Denne vej, tak.$"

CableClub_Text_ExplainWirelessClubFirstTime::
	.string "På øverste etage er der to\n"
	.string "rum.\p"
	.string "Først rummet til venstre.\n"
	.string "It's UNION ROOM.\p"
	.string "Du kan linke med TRÆNERE\n"
	.string "omkring dig som også er gået ind i\l"
	.string "UNION ROOM.\p"
	.string "Med dem kan du fx\n"
	.string "chat, battle, and bytte.\p"
	.string "Dernæst er rummet til højre\n"
	.string "DIRECT CORNER.\p"
	.string "Du kan bytte eller kæmpe med POKéMON\n"
	.string "med dine venner i dette rum.\p"
	.string "Hvis den trådløse adapter ikke er\n"
	.string "forbundet, kan du stadig linke\l"
	.string "med et GBA Game Link-kabel.\p"
	.string "I så fald skal du gå\n"
	.string "to DIRECT CORNER.\p"
	.string "Jeg håber du nyder det trådløse\n"
	.string "kommunikationssystem.$"

CableClub_Text_AskAboutLinking::
	.string "Hej, {PLAYER}!\p"
	.string "Det er mig, TEALA, POKéMON\n"
	.string "CENTER 2F-medarbejder.\p"
	.string "Er der noget du ville\n"
	.string "spørge mig om vedr. link?$"

CableClub_Text_ExplainWirelessClub::
	.string "Lad mig forklare hvordan POKéMON\n"
	.string "WIRELESS CLUB fungerer.\p"
	.string "Her på øverste etage er der\n"
	.string "two rum.\p"
	.string "Først rummet til venstre.\n"
	.string "It's UNION ROOM.\p"
	.string "Du kan linke med TRÆNERE\n"
	.string "omkring dig som også er gået ind i\l"
	.string "UNION ROOM.\p"
	.string "Med dem kan du fx\n"
	.string "chat, battle, and bytte.\p"
	.string "Dernæst er rummet til højre\n"
	.string "DIRECT CORNER.\p"
	.string "Du kan bytte eller kæmpe med POKéMON\n"
	.string "med dine venner i dette rum.\p"
	.string "Nogle gange kan du ikke\n"
	.string "finde dine venner i UNION ROOM\l"
	.string "or DIRECT CORNER.\p"
	.string "I så fald, gå venligst tættere\n"
	.string "på dine venner.\p"
	.string "Hvis den trådløse adapter ikke er\n"
	.string "forbundet, kan du stadig linke\l"
	.string "med et GBA Game Link-kabel.\p"
	.string "I så fald skal du gå\n"
	.string "to DIRECT CORNER.\p"
	.string "Jeg håber du nyder det trådløse\n"
	.string "kommunikationssystem.$"

CableClub_Text_HopeYouEnjoyWirelessSystem::
	.string "Jeg håber du nyder det trådløse\n"
	.string "kommunikationssystem.$"
