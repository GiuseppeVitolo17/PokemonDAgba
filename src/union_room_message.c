#include "global.h"
#include "link_rfu.h"
#include "mystery_gift_server.h"
#include "mystery_gift_client.h"
#include "constants/union_room.h"

ALIGNED(4) const u8 gText_UR_EmptyString[] = _("");
ALIGNED(4) const u8 gText_UR_Colon[] = _(":");
ALIGNED(4) const u8 gText_UR_ID[] = _("{ID}");
ALIGNED(4) const u8 gText_UR_PleaseStartOver[] = _("Start forfra fra begyndelsen.");
ALIGNED(4) const u8 gText_UR_WirelessSearchCanceled[] = _("TRAADLOES KOMMUNIKATION\nsoegning er annulleret.");
ALIGNED(4) static const u8 sText_AwaitingCommunucation2[] = _("ともだちからの れんらくを\nまっています");
ALIGNED(4) const u8 gText_UR_AwaitingCommunication[] = _("{STR_VAR_1}! Venter paa\nkommunikation fra anden spiller.");
ALIGNED(4) const u8 gText_UR_AwaitingLinkPressStart[] = _("{STR_VAR_1}! Venter paa link!\nTryk START naar alle er klar.");

ALIGNED(4) static const u8 sText_SingleBattle[] = _("シングルバトルを かいさいする");
ALIGNED(4) static const u8 sText_DoubleBattle[] = _("ダブルバトルを かいさいする");
ALIGNED(4) static const u8 sText_MultiBattle[] = _("マルチバトルを かいさいする");
ALIGNED(4) static const u8 sText_TradePokemon[] = _("ポケモンこうかんを かいさいする");
ALIGNED(4) static const u8 sText_Chat[] = _("チャットを かいさいする");
ALIGNED(4) static const u8 sText_DistWonderCard[] = _("ふしぎなカードをくばる");
ALIGNED(4) static const u8 sText_DistWonderNews[] = _("ふしぎなニュースをくばる");
ALIGNED(4) static const u8 sText_DistMysteryEvent[] = _("ふしぎなできごとを かいさいする");
ALIGNED(4) static const u8 sText_HoldPokemonJump[] = _("なわとびを かいさいする");
ALIGNED(4) static const u8 sText_HoldBerryCrush[] = _("きのみマッシャーを かいさいする");
ALIGNED(4) static const u8 sText_HoldBerryPicking[] = _("きのみどりを かいさいする");
ALIGNED(4) static const u8 sText_HoldSpinTrade[] = _("ぐるぐるこうかんを かいさいする");
ALIGNED(4) static const u8 sText_HoldSpinShop[] = _("ぐるぐるショップを かいさいする");

// Unused
static const u8 *const sLinkGroupActionTexts[] = {
    sText_SingleBattle,
    sText_DoubleBattle,
    sText_MultiBattle,
    sText_TradePokemon,
    sText_Chat,
    sText_DistWonderCard,
    sText_DistWonderNews,
    sText_DistWonderCard,
    sText_HoldPokemonJump,
    sText_HoldBerryCrush,
    sText_HoldBerryPicking,
    sText_HoldBerryPicking,
    sText_HoldSpinTrade,
    sText_HoldSpinShop
};

static const u8 sText_1PlayerNeeded[] = _("1 spiller\nbehoeves.");
static const u8 sText_2PlayersNeeded[] = _("2 spillere\nbehoeves.");
static const u8 sText_3PlayersNeeded[] = _("3 spillere\nbehoeves.");
static const u8 sText_4PlayersNeeded[] = _("あと4にん\nひつよう");
static const u8 sText_2PlayerMode[] = _("2-PLAYER\nMODE");
static const u8 sText_3PlayerMode[] = _("3-PLAYER\nMODE");
static const u8 sText_4PlayerMode[] = _("4-PLAYER\nMODE");
static const u8 sText_5PlayerMode[] = _("5-PLAYER\nMODE");

const u8 *const gTexts_UR_PlayersNeededOrMode[][5] = {
    { // 2 players required
        sText_1PlayerNeeded,
        sText_2PlayerMode
    },
    { // 4 players required
        sText_3PlayersNeeded,
        sText_2PlayersNeeded,
        sText_1PlayerNeeded,
        sText_4PlayerMode
    },
    { // 2-5 players required
        sText_1PlayerNeeded,
        sText_2PlayerMode,
        sText_3PlayerMode,
        sText_4PlayerMode,
        sText_5PlayerMode
    },
    { // 3-5 players required
        sText_2PlayersNeeded,
        sText_1PlayerNeeded,
        sText_3PlayerMode,
        sText_4PlayerMode,
        sText_5PlayerMode
    }
};

ALIGNED(4) const u8 gText_UR_BButtonCancel[] = _("{B_BUTTON}ANNULLER");
ALIGNED(4) static const u8 sText_SearchingForParticipants[] = _("ため\nさんかしゃ ぼしゅうちゅう です！");
ALIGNED(4) const u8 gText_UR_PlayerContactedYouForXAccept[] = _("{STR_VAR_2} contacted you for\n{STR_VAR_1}. Accept?");
ALIGNED(4) const u8 gText_UR_PlayerContactedYouShareX[] = _("{STR_VAR_2} contacted you.\nWill you share {STR_VAR_1}?");
ALIGNED(4) const u8 gText_UR_PlayerContactedYouAddToMembers[] = _("{STR_VAR_2} kontaktede dig.\nTilfoej til medlemmerne?");
ALIGNED(4) const u8 gText_UR_AreTheseMembersOK[] = _("{STR_VAR_1}!\nEr disse medlemmer OK?");
ALIGNED(4) const u8 gText_UR_CancelModeWithTheseMembers[] = _("Annuller {STR_VAR_1} MODE\nmed disse medlemmer?");
ALIGNED(4) const u8 gText_UR_AnOKWasSentToPlayer[] = _("An “OK” was sent\nto {STR_VAR_1}.");

ALIGNED(4) static const u8 sText_OtherTrainerUnavailableNow[] = _("Den anden TRAENER ser ikke\nud til at vaere tilgaengelig…\p");
ALIGNED(4) static const u8 sText_CantTransmitTrainerTooFar[] = _("Du kan ikke sende til en TRAENER\nder er for langt vaek.\p");
ALIGNED(4) static const u8 sText_TrainersNotReadyYet[] = _("Den anden TRAENER er ikke\nklar endnu.\p");

const u8 *const gTexts_UR_CantTransmitToTrainer[] = {
    sText_CantTransmitTrainerTooFar,
    sText_TrainersNotReadyYet
};

ALIGNED(4) const u8 gText_UR_ModeWithTheseMembersWillBeCanceled[] = _("{STR_VAR_1} MODE med disse\nmedlemmer annulleres.{PAUSE 90}");
ALIGNED(4) static const u8 sText_MemberNoLongerAvailable[] = _("Et medlem kan ikke laengere\nvaere tilgaengelig.\p");

const u8 *const gTexts_UR_PlayerUnavailable[] = {
    sText_OtherTrainerUnavailableNow,
    sText_MemberNoLongerAvailable
};

ALIGNED(4) static const u8 sText_TrainerAppearsUnavailable[] = _("Den anden TRAENER ser ikke\nud til at vaere tilgaengelig…\p");
ALIGNED(4) const u8 gText_UR_PlayerSentBackOK[] = _("{STR_VAR_1} sent back an “OK”!");
ALIGNED(4) const u8 gText_UR_PlayerOKdRegistration[] = _("{STR_VAR_1} OK'd your registration as\na member.");
ALIGNED(4) static const u8 sText_PlayerRepliedNo[] = _("{STR_VAR_1} replied, “No…”\p");
ALIGNED(4) const u8 gText_UR_AwaitingOtherMembers[] = _("{STR_VAR_1}!\nVenter paa andre deltagere!");
ALIGNED(4) const u8 gText_UR_QuitBeingMember[] = _("Vil du slutte som medlem?");
ALIGNED(4) static const u8 sText_StoppedBeingMember[] = _("Du er ikke laengere medlem.\p");

const u8 *const gTexts_UR_PlayerDisconnected[] = {
    [RFU_STATUS_OK]                  = NULL,
    [RFU_STATUS_FATAL_ERROR]         = sText_MemberNoLongerAvailable,
    [RFU_STATUS_CONNECTION_ERROR]    = sText_TrainerAppearsUnavailable,
    [RFU_STATUS_CHILD_SEND_COMPLETE] = NULL,
    [RFU_STATUS_NEW_CHILD_DETECTED]  = NULL,
    [RFU_STATUS_JOIN_GROUP_OK]       = NULL,
    [RFU_STATUS_JOIN_GROUP_NO]       = sText_PlayerRepliedNo,
    [RFU_STATUS_WAIT_ACK_JOIN_GROUP] = NULL,
    [RFU_STATUS_LEAVE_GROUP_NOTICE]  = NULL,
    [RFU_STATUS_LEAVE_GROUP]         = sText_StoppedBeingMember
};

ALIGNED(4) const u8 gText_UR_WirelessLinkEstablished[] = _("TRAADLOES KOMMUNIKATION-\nSYSTEM forbindelsen er etableret.");
ALIGNED(4) const u8 gText_UR_WirelessLinkDropped[] = _("TRAADLOES KOMMUNIKATION-\nSYSTEM forbindelsen er afbrudt…");
ALIGNED(4) const u8 gText_UR_LinkWithFriendDropped[] = _("Forbindelsen med din ven\nblev afbrudt…");
ALIGNED(4) static const u8 sText_PlayerRepliedNo2[] = _("{STR_VAR_1} replied, “No…”");

const u8 *const gTexts_UR_LinkDropped[] = {
    [RFU_STATUS_OK]                  = NULL,
    [RFU_STATUS_FATAL_ERROR]         = gText_UR_LinkWithFriendDropped,
    [RFU_STATUS_CONNECTION_ERROR]    = gText_UR_LinkWithFriendDropped,
    [RFU_STATUS_CHILD_SEND_COMPLETE] = NULL,
    [RFU_STATUS_NEW_CHILD_DETECTED]  = NULL,
    [RFU_STATUS_JOIN_GROUP_OK]       = NULL,
    [RFU_STATUS_JOIN_GROUP_NO]       = sText_PlayerRepliedNo2,
    [RFU_STATUS_WAIT_ACK_JOIN_GROUP] = NULL,
    [RFU_STATUS_LEAVE_GROUP_NOTICE]  = NULL,
    [RFU_STATUS_LEAVE_GROUP]         = NULL
};

ALIGNED(4) static const u8 sText_DoYouWantXMode[] = _("Vil du have {STR_VAR_2}\nMODE?");
ALIGNED(4) static const u8 sText_DoYouWantXMode2[] = _("Vil du have {STR_VAR_2}\nMODE?");

// Unused
static const u8 *const sDoYouWantModeTexts[] = {
    sText_DoYouWantXMode,
    sText_DoYouWantXMode2
};

ALIGNED(4) static const u8 sText_CommunicatingPleaseWait[] = _("はなしかけています…\nしょうしょう おまちください"); // Unused
ALIGNED(4) const u8 gText_UR_AwaitingPlayersResponseAboutTrade[] = _("Venter paa {STR_VAR_1}s svar om\nbyttet…");

ALIGNED(4) static const u8 sText_Communicating[] = _("Kommunikerer{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\n{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.");
ALIGNED(4) static const u8 sText_CommunicatingWithPlayer[] = _("Kommunikerer med {STR_VAR_1}{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\n{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.");
ALIGNED(4) static const u8 sText_PleaseWaitAWhile[] = _("Vent venligst{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.\n{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.{PAUSE 15}.");

const u8 *const gTexts_UR_CommunicatingWait[] = {
    sText_Communicating,
    sText_CommunicatingWithPlayer,
    sText_PleaseWaitAWhile
};

ALIGNED(4) static const u8 sText_HiDoSomethingMale[] = _("Hej! Er der noget du\nville goere?");
ALIGNED(4) static const u8 sText_HiDoSomethingFemale[] = _("Hej!\nVil du goere noget?");
ALIGNED(4) static const u8 sText_HiDoSomethingAgainMale[] = _("{STR_VAR_1}: Hiya, we meet again!\nWhat are you up for this time?");
ALIGNED(4) static const u8 sText_HiDoSomethingAgainFemale[] = _("{STR_VAR_1}: Oh! {PLAYER}, hello!\nWould you like to do something?");

const u8 *const gTexts_UR_HiDoSomething[][GENDER_COUNT] = {
    {
        sText_HiDoSomethingMale,
        sText_HiDoSomethingFemale
    }, {
        sText_HiDoSomethingAgainMale,
        sText_HiDoSomethingAgainFemale
    }
};

ALIGNED(4) static const u8 sText_DoSomethingMale[] = _("Want to do something?");
ALIGNED(4) static const u8 sText_DoSomethingFemale[] = _("Vil du goere noget?");
ALIGNED(4) static const u8 sText_DoSomethingAgainMale[] = _("{STR_VAR_1}: What would you like to\ndo now?");
ALIGNED(4) static const u8 sText_DoSomethingAgainFemale[] = _("{STR_VAR_1}‘また なにかする？");

// Unused
static const u8 *const sDoSomethingTexts[][GENDER_COUNT] = {
    {
        sText_DoSomethingMale,
        sText_DoSomethingFemale
    }, {
        sText_DoSomethingAgainMale,
        sText_DoSomethingAgainMale // was probably supposed to be sText_DoSomethingAgainFemale
    }
};

ALIGNED(4) static const u8 sText_SomebodyHasContactedYou[] = _("Nogen har kontaktet dig.{PAUSE 60}");
ALIGNED(4) static const u8 sText_PlayerHasContactedYou[] = _("{STR_VAR_1} has contacted you.{PAUSE 60}");

const u8 *const gTexts_UR_PlayerContactedYou[] = {
    sText_SomebodyHasContactedYou,
    sText_PlayerHasContactedYou
};

ALIGNED(4) static const u8 sText_AwaitingResponseFromTrainer[] = _("Venter paa svar fra\nden anden TRAENER…");
ALIGNED(4) static const u8 sText_AwaitingResponseFromPlayer[] = _("Venter paa svar fra\n{STR_VAR_1}…");

const u8 *const gTexts_UR_AwaitingResponse[] = {
    sText_AwaitingResponseFromTrainer,
    sText_AwaitingResponseFromPlayer
};

ALIGNED(4) static const u8 sText_AwaitingResponseCancelBButton[] = _("あいての ていあんを まっています\nビーボタンで キャンセル");

ALIGNED(4) const u8 gText_UR_ShowTrainerCard[] = _("Den anden TRAENER viste\ndig sit TRAENERKORT.\pVil du vise dit\nTRAENERKORT?");
ALIGNED(4) const u8 gText_UR_BattleChallenge[] = _("Den anden TRAENER udfordrer\ndig til kamp.\pAccepterer du kamp-\nudfordringen?");
ALIGNED(4) const u8 gText_UR_ChatInvitation[] = _("Den anden TRAENER inviterer\ndig til chat.\pAccepterer du chat-\ninvitationen?");
ALIGNED(4) const u8 gText_UR_OfferToTradeMon[] = _("Der er et tilbud om at bytte din\nregistrerede Niv. {DYNAMIC 0} {DYNAMIC 1}\pmod en Niv. {DYNAMIC 2} {DYNAMIC 3}.\pAccepterer du dette bytte-\ntilbud?");
ALIGNED(4) const u8 gText_UR_OfferToTradeEgg[] = _("Der er et tilbud om at bytte dit\nregistrerede AEG.\lAccepterer du dette bytte-tilbud?");
ALIGNED(4) const u8 gText_UR_ChatDropped[] = _("Chatten er afbrudt.\p");
ALIGNED(4) const u8 gText_UR_OfferDeclined1[] = _("Du afslog tilbuddet.\p");
ALIGNED(4) const u8 gText_UR_OfferDeclined2[] = _("Du afslog tilbuddet.\p");
ALIGNED(4) const u8 gText_UR_ChatEnded[] = _("Chatten blev afsluttet.\p");

// Unused
static const u8 *const sInvitationTexts[] = {
    gText_UR_ShowTrainerCard,
    gText_UR_BattleChallenge,
    gText_UR_ChatInvitation,
    gText_UR_OfferToTradeMon
};

ALIGNED(4) static const u8 sText_JoinChatMale[] = _("Hey! Vi chatter lige nu.\nVil du vaere med?");
ALIGNED(4) static const u8 sText_PlayerJoinChatMale[] = _("{STR_VAR_1}: Hej, {PLAYER}!\nVi chatter lige nu.\lVil du vaere med?");
ALIGNED(4) static const u8 sText_JoinChatFemale[] = _("Hej! Vi chatter nu.\nVil du vaere med?");
ALIGNED(4) static const u8 sText_PlayerJoinChatFemale[] = _("{STR_VAR_1}: Hej, {PLAYER}!\nVi chatter nu.\lVil du vaere med?");

const u8 *const gTexts_UR_JoinChat[][GENDER_COUNT] = {
    {
        sText_JoinChatMale,
        sText_JoinChatFemale
    }, {
        sText_PlayerJoinChatMale,
        sText_PlayerJoinChatFemale
    }
};

ALIGNED(4) const u8 gText_UR_TrainerAppearsBusy[] = _("……\nTRAENERen ser travl ud…\p");
ALIGNED(4) static const u8 sText_WaitForBattleMale[] = _("En kamp? Okay,\ngiv mig lidt tid.");
ALIGNED(4) static const u8 sText_WaitForChatMale[] = _("Vil du chatte? Okay,\nvent lidt.");
ALIGNED(4) static const u8 sText_ShowTrainerCardMale[] = _("Selvfoelgelig! Her er mit “Greetings,” TRAENERKORT.");
ALIGNED(4) static const u8 sText_WaitForBattleFemale[] = _("En kamp? Selvfoelgelig, men jeg\nskal lige goere mig klar.");
ALIGNED(4) static const u8 sText_WaitForChatFemale[] = _("Ville du chatte?\nOkay, vent et ojeblik.");
ALIGNED(4) static const u8 sText_ShowTrainerCardFemale[] = _("Som introduktion viser jeg\ndig mit TRAENERKORT.");

const u8 *const gTexts_UR_WaitOrShowCard[GENDER_COUNT][4] = {
    {
        sText_WaitForBattleMale,
        sText_WaitForChatMale,
        NULL,
        sText_ShowTrainerCardMale
    }, {
        sText_WaitForBattleFemale,
        sText_WaitForChatFemale,
        NULL,
        sText_ShowTrainerCardFemale
    }
};

ALIGNED(4) static const u8 sText_WaitForChatMale2[] = _("チャットだね！\nわかった ちょっと まってて！");
ALIGNED(4) static const u8 sText_DoneWaitingBattleMale[] = _("Tak for taalmodigheden!\nLad os starte kampen!{PAUSE 60}");
ALIGNED(4) static const u8 sText_DoneWaitingChatMale[] = _("Okay!\nLad os chatte!{PAUSE 60}");
ALIGNED(4) static const u8 sText_DoneWaitingBattleFemale[] = _("Undskyld ventetiden!\nLad os starte!{PAUSE 60}");
ALIGNED(4) static const u8 sText_DoneWaitingChatFemale[] = _("Undskyld ventetiden!\nLad os chatte.{PAUSE 60}");
ALIGNED(4) static const u8 sText_TradeWillBeStarted[] = _("Bytte startes.{PAUSE 60}");
ALIGNED(4) static const u8 sText_BattleWillBeStarted[] = _("Kampen startes.{PAUSE 60}");
ALIGNED(4) static const u8 sText_EnteringChat[] = _("Gaar ind i chatten…{PAUSE 60}");

const u8 *const gTexts_UR_StartActivity[][GENDER_COUNT][3] = {
    {
        {
            sText_BattleWillBeStarted,
            sText_EnteringChat,
            sText_TradeWillBeStarted
        }, {
            sText_BattleWillBeStarted,
            sText_EnteringChat,
            sText_TradeWillBeStarted
        }
    }, {
        {
            sText_DoneWaitingBattleMale,
            sText_DoneWaitingChatMale,
            sText_TradeWillBeStarted
        }, {
            sText_DoneWaitingBattleFemale,
            sText_DoneWaitingChatFemale,
            sText_TradeWillBeStarted
        }
    }
};

ALIGNED(4) static const u8 sText_BattleDeclinedMale[] = _("Undskyld! Mine POKeMON har det ikke\nsaerlig godt lige nu.\lVi kaemper en anden gang.\p");
ALIGNED(4) static const u8 sText_BattleDeclinedFemale[] = _("Jeg er meget ked af det, mine POKeMON\nhar det ikke godt…\pLad os kaempe en anden gang.\p");

const u8 *const gTexts_UR_BattleDeclined[GENDER_COUNT] = {
    sText_BattleDeclinedMale,
    sText_BattleDeclinedFemale
};

ALIGNED(4) static const u8 sText_ShowTrainerCardDeclinedMale[] = _("Hvad? Mit TRAENERKORT…\nHvor blev det af?\lUndskyld! Jeg viser det en anden gang!\p");
ALIGNED(4) static const u8 sText_ShowTrainerCardDeclinedFemale[] = _("Hvor har jeg lagt mit\nTRAENERKORT?…\lUndskyld! Jeg viser det senere!\p");

const u8 *const gTexts_UR_ShowTrainerCardDeclined[GENDER_COUNT] = {
    sText_ShowTrainerCardDeclinedMale,
    sText_ShowTrainerCardDeclinedFemale
};

ALIGNED(4) static const u8 sText_IfYouWantToDoSomethingMale[] = _("Hvis du vil goere noget med mig,\nsaa sig til!\p");
ALIGNED(4) static const u8 sText_IfYouWantToDoSomethingFemale[] = _("Hvis du vil goere noget med mig,\nvaer ikke genert.\p");

const u8 *const gTexts_UR_IfYouWantToDoSomething[GENDER_COUNT] = {
    sText_IfYouWantToDoSomethingMale,
    sText_IfYouWantToDoSomethingFemale
};

ALIGNED(4) const u8 gText_UR_TrainerBattleBusy[] = _("Ups! Undskyld, jeg skal\ngoere noget andet.\lEn anden gang, okay?\p");
ALIGNED(4) const u8 gText_UR_NeedTwoMonsOfLevel30OrLower1[] = _("Til kamp skal du have\nto POKeMON under Niv. 30.\p");
ALIGNED(4) const u8 gText_UR_NeedTwoMonsOfLevel30OrLower2[] = _("Til kamp skal du have to\nPOKeMON under Niv. 30.\p");

ALIGNED(4) static const u8 sText_DeclineChatMale[] = _("Oh, all right.\nCome see me anytime, okay?\p");
ALIGNED(4) static const u8 stext_DeclineChatFemale[] = _("Oh…\nKom forbi naar som helst.\p");

// Response from partner when player declines chat
const u8 *const gTexts_UR_DeclineChat[GENDER_COUNT] = {
    sText_DeclineChatMale,
    stext_DeclineChatFemale
};

ALIGNED(4) static const u8 sText_ChatDeclinedMale[] = _("Oh, sorry!\nI just can't right this instant.\lLet's chat another time.\p");
ALIGNED(4) static const u8 sText_ChatDeclinedFemale[] = _("Oh, I'm sorry.\nI have too much to do right now.\lLet's chat some other time.\p");

// Response from partner when they decline chat
const u8 *const gTexts_UR_ChatDeclined[GENDER_COUNT] = {
    sText_ChatDeclinedMale,
    sText_ChatDeclinedFemale
};

ALIGNED(4) static const u8 sText_YoureToughMale[] = _("Wow!\nDu er da haard!\p");
ALIGNED(4) static const u8 sText_UsedGoodMoveMale[] = _("Brugte du det angreb?\nGod strategi!\p");
ALIGNED(4) static const u8 sText_BattleSurpriseMale[] = _("Fedt!\nDet var en oejenabner!\p");
ALIGNED(4) static const u8 sText_SwitchedMonsMale[] = _("Oh! Hvordan kunne du bruge den\nPOKeMON i den situation?\p");
ALIGNED(4) static const u8 sText_YoureToughFemale[] = _("Den POKeMON…\nDen er opdraget rigtig godt!\p");
ALIGNED(4) static const u8 sText_UsedGoodMoveFemale[] = _("Praecis!\nDet er det rigtige angreb nu!\p");
ALIGNED(4) static const u8 sText_BattleSurpriseFemale[] = _("Fantastisk!\nKan man kaempe saadan?\p");
ALIGNED(4) static const u8 sText_SwitchedMonsFemale[] = _("Perfekt timing med at\nskifte POKeMON!\p");

const u8 *const gTexts_UR_BattleReaction[GENDER_COUNT][4] = {
    {
        sText_YoureToughMale,
        sText_UsedGoodMoveMale,
        sText_BattleSurpriseMale,
        sText_SwitchedMonsMale
    }, {
        sText_YoureToughFemale,
        sText_UsedGoodMoveFemale,
        sText_BattleSurpriseFemale,
        sText_SwitchedMonsFemale
    }
};

ALIGNED(4) static const u8 sText_LearnedSomethingMale[] = _("Aa, jeg forstaar!\nLaererigt!\p");
ALIGNED(4) static const u8 sText_ThatsFunnyMale[] = _("Sig ikke mere sjovt!\nJeg har ondt af at grine!\p");
ALIGNED(4) static const u8 sText_RandomChatMale1[] = _("Oh?\nNoget lignende skete.\p");
ALIGNED(4) static const u8 sText_RandomChatMale2[] = _("Hmhm… Hvad?\nEr det det du siger?\p");
ALIGNED(4) static const u8 sText_LearnedSomethingFemale[] = _("Er det rigtigt?\nDet vidste jeg ikke.\p");
ALIGNED(4) static const u8 sText_ThatsFunnyFemale[] = _("Ahaha!\nHvad handler det om?\p");
ALIGNED(4) static const u8 sText_RandomChatFemale1[] = _("Ja, praecis!\nDet var det jeg mente.\p");
ALIGNED(4) static const u8 sText_RandomChatFemale2[] = _("Med andre ord…\nJa! Det er rigtigt!\p");

const u8 *const gTexts_UR_ChatReaction[GENDER_COUNT][4] = {
    {
        sText_LearnedSomethingMale,
        sText_ThatsFunnyMale,
        sText_RandomChatMale1,
        sText_RandomChatMale2
    }, {
        sText_LearnedSomethingFemale,
        sText_ThatsFunnyFemale,
        sText_RandomChatFemale1,
        sText_RandomChatFemale2
    }
};

ALIGNED(4) static const u8 sText_ShowedTrainerCardMale1[] = _("Jeg viser bare mit TRAENERKORT\nsom haelsening.\p");
ALIGNED(4) static const u8 sText_ShowedTrainerCardMale2[] = _("Haaber vi laerer hinanden at kende!\p");
ALIGNED(4) static const u8 sText_ShowedTrainerCardFemale1[] = _("Vi viser hinanden vores\nTRAENERKORT for at laere hinanden at kende.\p");
ALIGNED(4) static const u8 sText_ShowedTrainerCardFemale2[] = _("Dejligt at moede dig.\nKom igen!\p");

const u8 *const gTexts_UR_TrainerCardReaction[GENDER_COUNT][2] = {
    {
        sText_ShowedTrainerCardMale1,
        sText_ShowedTrainerCardMale2
    }, {
        sText_ShowedTrainerCardFemale1,
        sText_ShowedTrainerCardFemale2
    }
};

ALIGNED(4) static const u8 sText_MaleTraded1[] = _("Ja!\nJeg ville virkelig have denne POKeMON!\p");
ALIGNED(4) static const u8 sText_MaleTraded2[] = _("Endelig fik jeg den POKeMON\njeg havde oensket mig i et bytte.\p");
ALIGNED(4) static const u8 sText_FemaleTraded1[] = _("Jeg bytter POKeMON lige nu.\p");
ALIGNED(4) static const u8 sText_FemaleTraded2[] = _("Endelig fik jeg den POKeMON\njeg ville have i et bytte!\p");

const u8 *const gTexts_UR_TradeReaction[GENDER_COUNT][4] = {
    {
        sText_MaleTraded1,
        sText_MaleTraded2
    }, {
        sText_FemaleTraded1,
        sText_FemaleTraded2
    }
};

const u8 gText_UR_XCheckedTradingBoard[] = _("{STR_VAR_1} tjekkede\nBYTTETAVLEN.\p");
ALIGNED(4) const u8 gText_UR_RegisterMonAtTradingBoard[] = _("Velkommen til BYTTETAVLEN.\pDu kan registrere din POKeMON\nog tilbyde den til bytte.\pVil du registrere en af\ndine POKeMON?");
ALIGNED(4) const u8 gText_UR_TradingBoardInfo[] = _("BYTTETAVLEN bruges til at\n"
                                                    "tilbyde en POKeMON til bytte.\p"
                                                    "Du skal bare registrere en\n"
                                                    "POKeMON til bytte.\p"
                                                    "En anden TRAENER kan tilbyde en\n"
                                                    "POKeMON til gengaeld.\p"
                                                    "Vi haaber du registrerer POKeMON\n"
                                                    "og bytter med mange andre\l"
                                                    "TRAENERe.\p"
                                                    "Vil du registrere en af\n"
                                                    "dine POKeMON?");
ALIGNED(4) static const u8 sText_ThankYouForRegistering[] = _("こうかんけいじばん の とうろくが\nかんりょう しました\pごりよう ありがとう\nございました！\p");
ALIGNED(4) static const u8 sText_NobodyHasRegistered[] = _("けいじばんに だれも ポケモンを\nとうろく していません\p\n");
ALIGNED(4) const u8 gText_UR_ChooseRequestedMonType[] = _("Vaelg den type POKeMON\ndu vil have i byttet.\n");
ALIGNED(4) const u8 gText_UR_WhichMonWillYouOffer[] = _("Hvilken af dine POKeMON vil\ndu tilbyde i bytte?\p");
ALIGNED(4) const u8 gText_UR_RegistrationCanceled[] = _("Registreringen er annulleret.\p");
ALIGNED(4) const u8 gText_UR_RegistraionCompleted[] = _("Registrering er gennemfoert.\p");
ALIGNED(4) const u8 gText_UR_TradeCanceled[] = _("Bytte er annulleret.\p");
ALIGNED(4) const u8 gText_UR_CancelRegistrationOfMon[] = _("Annuller registrering af din\nNiv. {STR_VAR_2} {STR_VAR_1}?");
ALIGNED(4) const u8 gText_UR_CancelRegistrationOfEgg[] = _("Annuller registrering af dit\nAEG?");
ALIGNED(4) const u8 gText_UR_RegistrationCanceled2[] = _("Registreringen er annulleret.\p");
ALIGNED(4) static const u8 sText_TradeTrainersWillBeListed[] = _("こうかんを きぼうしているひとを\nひょうじします");
ALIGNED(4) static const u8 sText_ChooseTrainerToTradeWith2[] = _("こうかん したい トレーナーを\nえらんで ください");
ALIGNED(4) const u8 gText_UR_AskTrainerToMakeTrade[] = _("Vil du bede {STR_VAR_1} om\nat bytte?");
ALIGNED(4) static const u8 sText_AwaitingResponseFromTrainer2[] = _("……\nあいての へんじを まっています");
ALIGNED(4) static const u8 sText_NotRegisteredAMonForTrade[] = _("あなたが こうかんにだす\nポケモンが とうろくされていません\p");
ALIGNED(4) const u8 gText_UR_DontHaveTypeTrainerWants[] = _("Du har ikke et {STR_VAR_2}-type\nPOKeMON som {STR_VAR_1} vil have.\p");
ALIGNED(4) const u8 gText_UR_DontHaveEggTrainerWants[] = _("Du har ikke et AEG som\n{STR_VAR_1} vil have.\p");

ALIGNED(4) static const u8 sText_PlayerCantTradeForYourMon[] = _("{STR_VAR_1} kan ikke bytte med\ndine POKeMON lige nu.\p");
ALIGNED(4) static const u8 sText_CantTradeForPartnersMon[] = _("Du kan ikke bytte med\n{STR_VAR_1}s POKeMON lige nu.\p");

// Unused
static const u8 *const sCantTradeMonTexts[] = {
    sText_PlayerCantTradeForYourMon,
    sText_CantTradeForPartnersMon
};

ALIGNED(4) const u8 gText_UR_TradeOfferRejected[] = _("Dit bytte-tilbud blev afvist.\p");
ALIGNED(4) const u8 gText_UR_EggTrade[] = _("AEG BYTTE");
ALIGNED(4) const u8 gText_UR_ChooseJoinCancel[] = _("{DPAD_UPDOWN}VALG  {A_BUTTON}DELTAG  {B_BUTTON}ANNULLER");
ALIGNED(4) const u8 gText_UR_ChooseTrainer[] = _("Vaelg en TRAENER.");
ALIGNED(4) static const u8 sText_ChooseTrainerSingleBattle[] = _("Vaelg en TRAENER til\neen ENKELTKAMP.");
ALIGNED(4) static const u8 sText_ChooseTrainerDoubleBattle[] = _("Vaelg en TRAENER til\neen Dobbeltkamp.");
ALIGNED(4) static const u8 sText_ChooseLeaderMultiBattle[] = _("Vaelg LEDEREN til\neen MULTIKAMP.");
ALIGNED(4) static const u8 sText_ChooseTrainerToTradeWith[] = _("Vaelg TRAENEREN du vil\nbytte med.");
ALIGNED(4) static const u8 sText_ChooseTrainerToShareWonderCards[] = _("Vaelg TRAENEREN der deler\nWONDER CARDS.");
ALIGNED(4) static const u8 sText_ChooseTrainerToShareWonderNews[] = _("Vaelg TRAENEREN der deler\nWONDER NEWS.");
ALIGNED(4) static const u8 sText_ChooseLeaderPokemonJump[] = _("Hop med mini POKeMON!\nVaelg LEDEREN.");
ALIGNED(4) static const u8 sText_ChooseLeaderBerryCrush[] = _("BERRY CRUSH!\nVaelg LEDEREN.");
ALIGNED(4) static const u8 sText_ChooseLeaderBerryPicking[] = _("DODRIO BERRY-PICKING!\nVaelg LEDEREN.");

const u8 *const gTexts_UR_ChooseTrainer[] = {
    [LINK_GROUP_SINGLE_BATTLE] = sText_ChooseTrainerSingleBattle,
    [LINK_GROUP_DOUBLE_BATTLE] = sText_ChooseTrainerDoubleBattle,
    [LINK_GROUP_MULTI_BATTLE]  = sText_ChooseLeaderMultiBattle,
    [LINK_GROUP_TRADE]         = sText_ChooseTrainerToTradeWith,
    [LINK_GROUP_POKEMON_JUMP]  = sText_ChooseLeaderPokemonJump,
    [LINK_GROUP_BERRY_CRUSH]   = sText_ChooseLeaderBerryCrush,
    [LINK_GROUP_BERRY_PICKING] = sText_ChooseLeaderBerryPicking,
    [LINK_GROUP_WONDER_CARD]   = sText_ChooseTrainerToShareWonderCards,
    [LINK_GROUP_WONDER_NEWS]   = sText_ChooseTrainerToShareWonderNews
};

ALIGNED(4) const u8 gText_UR_SearchingForWirelessSystemWait[] = _("Searching for a WIRELESS\nCOMMUNICATION SYSTEM. Wait...");
ALIGNED(4) static const u8 sText_MustHaveTwoMonsForDoubleBattle[] = _("ダブルバトルでは 2ひき いじょうの\nポケモンが ひつようです\p");
ALIGNED(4) const u8 gText_UR_AwaitingPlayersResponse[] = _("Awaiting {STR_VAR_1}'s response…");
ALIGNED(4) const u8 gText_UR_PlayerHasBeenAskedToRegisterYouPleaseWait[] = _("{STR_VAR_1} has been asked to register\nyou as a member. Please wait.");
ALIGNED(4) const u8 gText_UR_AwaitingResponseFromWirelessSystem[] = _("Venter paa svar fra\nTRAADLOES KOMMUNIKATION.");
ALIGNED(4) static const u8 sText_PleaseWaitForOtherTrainersToGather[] = _("ほかの さんかしゃが そろうまで\nしょうしょう おまちください");

ALIGNED(4) static const u8 sText_NoCardsSharedRightNow[] = _("Ingen KORT deles lige nu.");
ALIGNED(4) static const u8 sText_NoNewsSharedRightNow[] = _("Ingen NYHEDER deles lige nu.");

const u8 *const gTexts_UR_NoWonderShared[] = {
    sText_NoCardsSharedRightNow,
    sText_NoNewsSharedRightNow
};

ALIGNED(4) const u8 gText_UR_Battle[] = _("BATTLE");
ALIGNED(4) const u8 gText_UR_Chat2[] = _("CHAT");
ALIGNED(4) const u8 gText_UR_Greetings[] = _("GREETINGS");
ALIGNED(4) const u8 gText_UR_Exit[] = _("EXIT");

ALIGNED(4) const u8 gText_UR_Exit2[] = _("EXIT");
ALIGNED(4) const u8 gText_UR_Info[] = _("INFO");
ALIGNED(4) const u8 gText_UR_NameWantedOfferLv[] = _("NAME{CLEAR_TO 0x3C}WANTED{CLEAR_TO 0x6E}OFFER{CLEAR_TO 0xC6}LV.");

ALIGNED(4) const u8 gText_UR_SingleBattle[] = _("SINGLE BATTLE");
ALIGNED(4) const u8 gText_UR_DoubleBattle[] = _("DOUBLE BATTLE");
ALIGNED(4) const u8 gText_UR_MultiBattle[] = _("MULTI BATTLE");
ALIGNED(4) const u8 gText_UR_PokemonTrades[] = _("POKeMON TRADES");
ALIGNED(4) const u8 gText_UR_Chat[] = _("CHAT");
ALIGNED(4) const u8 gText_UR_Cards[] = _("CARDS");
ALIGNED(4) const u8 gText_UR_WonderCards[] = _("WONDER CARDS");
ALIGNED(4) const u8 gText_UR_WonderNews[] = _("WONDER NEWS");
ALIGNED(4) const u8 gText_UR_PokemonJump[] = _("POKeMON JUMP");
ALIGNED(4) const u8 gText_UR_BerryCrush[] = _("BERRY CRUSH");
ALIGNED(4) const u8 gText_UR_BerryPicking[] = _("BERRY-PICKING");
ALIGNED(4) const u8 gText_UR_Search[] = _("SEARCH");
ALIGNED(4) const u8 gText_UR_SpinTrade[] = _("ぐるぐるこうかん");
ALIGNED(4) const u8 gText_UR_ItemTrade[] = _("アイテムトレード");

ALIGNED(4) static const u8 sText_ItsNormalCard[] = _("It's a NORMAL CARD.");
ALIGNED(4) static const u8 sText_ItsBronzeCard[] = _("It's a BRONZE CARD!");
ALIGNED(4) static const u8 sText_ItsCopperCard[] = _("It's a COPPER CARD!");
ALIGNED(4) static const u8 sText_ItsSilverCard[] = _("It's a SILVER CARD!");
ALIGNED(4) static const u8 sText_ItsGoldCard[] = _("It's a GOLD CARD!");

const u8 *const gTexts_UR_CardColor[] = {
    sText_ItsNormalCard,
    sText_ItsBronzeCard,
    sText_ItsCopperCard,
    sText_ItsSilverCard,
    sText_ItsGoldCard
};

ALIGNED(4) const u8 gText_UR_TrainerCardInfoPage1[] = _("Dette er {DYNAMIC 0} {DYNAMIC 1}s\nTRAENERKORT…\l{DYNAMIC 2}\pPOKeDEX: {DYNAMIC 3}\nTID:     {DYNAMIC 4}:{DYNAMIC 5}\p");
ALIGNED(4) const u8 gText_UR_TrainerCardInfoPage2[] = _("BATTLES: {DYNAMIC 0} WINS  {DYNAMIC 2} LOSSES\nTRADES:  {DYNAMIC 3} TIMES\p“{DYNAMIC 4} {DYNAMIC 5}\n{DYNAMIC 6} {DYNAMIC 7}”\p");
ALIGNED(4) static const u8 sText_GladToMeetYouMale[] = _("{DYNAMIC 1}: Glad to have met you!{PAUSE 60}");
ALIGNED(4) static const u8 sText_GladToMeetYouFemale[] = _("{DYNAMIC 1}: Glad to meet you!{PAUSE 60}");

const u8 *const gTexts_UR_GladToMeetYou[GENDER_COUNT] = {
    sText_GladToMeetYouMale,
    sText_GladToMeetYouFemale
};

ALIGNED(4) const u8 gText_UR_FinishedCheckingPlayersTrainerCard[] = _("Finished checking {DYNAMIC 1}'s\nTRAINER CARD.{PAUSE 60}");
ALIGNED(4) static const u8 sText_CanceledReadingCard[] = _("Canceled reading the Card.");

static const struct MysteryGiftClientCmd sClientScript_DynamicError[] = {
    {CLI_RECV, MG_LINKID_DYNAMIC_MSG},
    {CLI_COPY_MSG},
    {CLI_SEND_READY_END},
    {CLI_RETURN, CLI_MSG_BUFFER_FAILURE}
};

const struct MysteryGiftServerCmd gServerScript_ClientCanceledCard[] = {
    {SVR_LOAD_CLIENT_SCRIPT, PTR_ARG(sClientScript_DynamicError)},
    {SVR_SEND},
    {SVR_LOAD_MSG, PTR_ARG(sText_CanceledReadingCard)},
    {SVR_SEND},
    {SVR_RECV, MG_LINKID_READY_END},
    {SVR_RETURN, SVR_MSG_CLIENT_CANCELED}
};
