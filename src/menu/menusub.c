#include "menu/menusub.h"

#include "main/cdctrl.h"
#include "main/etc.h"

#include "menu/menudata.h"
#include "menu/menufont.h"
#include "menu/menu_mdl.h"
#include "menu/p3mc.h"

#include "os/syssub.h"
#include "os/system.h"
#include "os/tim2.h"

#include <prlib/prlib.h>

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/* data 18b0e0 */ extern MNMAPPOS mnmapMap1[]; /* static */
/* data 18b160 */ extern MNMAPPOS mnmapMap[]; /* static */
/* data 18b3a0 */ extern MNMAPPOS mnmapMap2[]; /* static */
// /* data 18b620 */ static short RShopRute0[0];
// /* data 18b630 */ static short RShopRute1[0];
// /* data 18b638 */ static short RShopRute2[0];
// /* data 18b648 */ static short *RecordShopRute[10];
/* data 18b670 */ extern MNMAPPOS mnmapCityHall[]; /* static */
// /* data 18b730 */ short AnmCHallPara_OptRet[0];
// /* data 18b738 */ short AnmCHallPara_Opt[0];
// /* data 18b740 */ short AnmCHallPara_RepRet[0];
// /* data 18b748 */ short AnmCHallPara_Rep[0];
// /* data 18b750 */ short AnmCHallFphs_OptRet[0];
// /* data 18b758 */ short AnmCHallFphs_Opt[0];
// /* data 18b760 */ short AnmCHallFphs_RepRet[0];
// /* data 18b768 */ short AnmCHallFphs_Rep[0];
// /* data 18b770 */ short AnmCHallChar_Log[0];
// /* data 18b780 */ short AnmCHallChar_Opt[0];
// /* data 18b790 */ short AnmCHallChar_Rep[0];
// /* sdata 399748 */ static u_char *UserName_InitialStr;
// /* sdata 39974c */ static u_char *UserName_InitialStr2;
// /* data 18b7a0 */ static u_char UserName_AsciiSetB[41];
// /* data 18b7d0 */ static u_char UserName_AsciiSetS[41];
/* data 18b800 */ extern USERNAME_CSET UserName_CharSet[];
// /* data 18b810 */ static u_char *TeachersName_Tbl[0];
// /* sdata 39975c */ static u_char *UserName_RankingNoSave;
// /* data 18b830 */ static char *_MONTH_STR[0];
/* data 18b880 */ extern MAPBGM MapBgmTbl[]; /* static */
/* data 18b908 */ extern TSVOICE_TBL TsVoiceTbl[]; /* static */
// /* data 18bac8 */ static u_short FussenWAIT0[0];
// /* data 18bad8 */ static u_short FussenWAIT1[0];
// /* data 18bae8 */ static u_short LoadConfLst[0];
/* data 18baf8 */ extern TSVSNDSEQ VSNDSEQ_Tbl[]; /* static */
/* data 18bb10 */ extern TSTEX_TBL TexTable[]; /* static */
// /* data 18bcb0 */ static PATPOS PAT_ALERT_WIN_ABOVE;
// /* data 18bcc0 */ static PATPOS PAT_ALERT_WIN_CENTER;
// /* data 18bcd0 */ static PATPOS PAT_ALERT_WIN_BELOW;
// /* data 18bce0 */ static PATPOS PAT_ALERT_WIN_FFACE[0];
// /* data 18bd10 */ static PATPOS SAVE_MENU_SELPAT[0];
// /* data 18bd28 */ static PTPOS SAVEWZoom_CXY[0];
// /* data 18bd30 */ static PATPOS LG_SCROLL_MARK[0];
// /* data 18bd48 */ static PATPOS RP_SCROLL_MARK[0];
// /* data 18bd60 */ static PATPOS LLG_SCROLL_MARK[0];
// /* data 18bd78 */ static PATPOS CSSLASH_MARK;
// /* data 18bd88 */ static STRPOS PAGENO_StrCOD[0];
// /* data 18bd98 */ static PTPOS CellCusPos[0];
// /* data 18bdb8 */ static STRPOS LOGS_StrCOD[0];
// /* data 18bde0 */ static STRPOS LOGL_StrCOD[0];
// /* data 18be08 */ static STRPOS REPLAY_StrCOD[0];
// /* data 18be38 */ static STRPOS VSREPLAY_StrCOD[0];
// /* data 18be78 */ static PATPOS VS_MARK;
// /* data 18be88 */ static PATPOS VS_WINMARK1;
// /* data 18be98 */ static PATPOS VS_WINMARK2;
// /* data 18bea8 */ static PATPOS LG_NEWDATA_MARK;
// /* data 18beb8 */ static PATPOS RP_NEWDATA_MARK;
// /* data 18bec8 */ static PATPOS STGCNameBox[0];
// /* data 18bf08 */ static PATPOS STGCNameBoxOK;
// /* data 18bf18 */ static PATPOS VS1PNameBox[0];
// /* data 18bf58 */ static PATPOS VS1PNameBoxOK;
// /* data 18bf68 */ static PATPOS VS2PNameBox[0];
// /* data 18bfa8 */ static PATPOS VS2PNameBoxOK;
// /* data 18bfb8 */ static MNOPT_OBJ MNOptObj_Lang[0];
// /* data 18bfd8 */ static MNOPT_OBJ MNOptObj_Subt[0];
// /* data 18bff8 */ static MNOPT_OBJ MNOptObj_Vibr[0];
// /* data 18c018 */ static MNOPT_OBJ MNOptObj_Oneb[0];
// /* data 18c038 */ static PATPOS MNOptMiniFrm[0];
// /* data 18c068 */ static PATPOS MNOptLRBtn[0];
// /* data 18c0c8 */ static PATPOS PopMenuSel_Pat[0];
// /* data 18c108 */ static PATPOS VSComMenuSel_Pat[0];
// /* data 18c138 */ static PATPOS VSComMenuSelH_Pat[0];
// /* data 18c168 */ static PATPOS SIRanking_Pat[0];
// /* data 18c180 */ static PATPOS Ranking_PatScroll[0];
// /* data 18c198 */ static PATPOS RankSISTNo_PAT[0];
// /* data 18c208 */ static PATPOS VSL1Ranking_Pat[0];
// /* data 18c248 */ static PATPOS VSL2Ranking_Pat[0];
// /* data 18c288 */ static PATPOS VSL3Ranking_Pat[0];
// /* data 18c2c8 */ static PATPOS VSL4Ranking_Pat[0];
// /* data 18c308 */ static PATPOS *VSRanking_PatTbl[0];
// /* data 18c318 */ static PATPOS RankVSSTNo_PAT[0];
// /* data 18c388 */ static STRPOS SRanking_Str[0];
// /* data 18c3a0 */ static STRPOS VRanking_Str[0];
// /* data 18c3b8 */ static PTPOS PopMenu_Pos[0];
// /* data 18c3c0 */ static PTPOS Ranking_Pos[0];
// /* data 18c3c8 */ static POPRNK_PPOS PopRnk_pPos[0];
// /* data 18c420 */ static int PopRnkPos_No[0][9];
// /* data 18c4b0 */ static int PopBubblePat_No[0][9];
// /* data 18c540 */ static PTPOS POPWZoom_CXY[0];
// /* data 18c588 */ static PTPOS JUKEBOX_Pos[0];
// /* data 18c5b0 */ static PATPOS JUKEJKT_Pat[0];
// /* data 18c628 */ static float JUKEWAV_INITBL[0];
// /* data 18c650 */ static PATPOS JUKEJKT_PatS[0];
// /* data 18c660 */ static PATPOS JUKEREC_Pat[0];
// /* data 18c6d8 */ static PATPOS JUKEREC_PatS[0];
/* data 18c6e8 */ extern u_int HosiColor[][8]; /* static */
/* data 18c748 */ extern HOSI_TYPE hTypeTable[17];
/* sdata 3997bc */ extern TSTEX_INF *tblTex; /* static */
/* data 18c8e0 */ extern u_int RPPadBit[]; /* static */
/* data 18c8f0 */ extern MCDATA_TBL McVoiceTbl[23]; /* static */
/* data 18c9a8 */ extern MCDATA_TBL McFaceTbl[23]; /* static */
/* sdata 3997c0 */ extern int UserList_Sw; /* static */
/* sdata 3997c4 */ extern int OptionList_Sw; /* static */
/* sdata 3997c8 */ extern int PopMenu_Sw; /* static */
/* sdata 3997cc */ extern int SaveMenu_Sw; /* static */
/* sdata 3997d0 */ extern int JukeMenu_Sw; /* static */
/* data 18ca60 */ extern USERLISTTYPE_TABLE ULTypeT_CITY_STGCLR; /* static */
/* data 18ca70 */ extern USERLISTTYPE_TABLE ULTypeT_CITY_REPLAY; /* static */
// /* data 18ca80 */ static USERLISTTYPE_TABLE ULTypeT_SAVE_LOG;
// /* data 18ca90 */ static USERLISTTYPE_TABLE ULTypeT_SAVE_REPLAY;
/* data 18caa0 */ extern int POPBtn2Sel[]; /* static */
// /* data 18cab8 */ static int POPSel2Btn[0];
// /* data 18cad0 */ static int Pop_CmpMesNo[0];
// /* data 18cae8 */ static int POPSel2BtnDir[0];
// /* data 18cb00 */ static int SaveMenu_CmpMesNo[0];
// /* data 18cb08 */ static BGM_TABLE JukeBgmTbl[0];
// /* data 18cb58 */ static int JukeMenu_CmpMesNo[0];
// /* data 18cb80 */ static MNOPT_SELINF OptionSelTbl[0];
/* data 18cbc0 */ extern USERLIST_TYPE UserListTbl[]; /* static */
/* sdata 399820 */ extern int _TexFunc; /* static */
/* sdata 399824 */ extern HOSI_OBJ *HOSIObj; /* static */
/* bss 1c77ac0 */ extern TSREPPAD menuPadState[2][4]; /* static */
/* bss 1c77ae0 */ extern TSSND_CHAN TsSndChan[15]; /* static */
/* bss 1c77c10 */ extern BGMSTATE TsBGMState; /* static */
/* sbss 399b18 */ extern P3GAMESTATE *pP3GameState; /* static */
/* sbss 399b1c */ extern int _bMapCaptureReq; /* static */
/* sbss 399b20 */ extern int _MNwaitTime; /* static */
/* data 18cc38 */ extern MN_SCENE MNS_StageMap;
/* bss 1c77cb0 */ extern MN_SCENE MNS_StageMap2; /* static */
/* bss 1c78e08 */ extern MN_SCENE MNS_CityHall; /* static */
/* bss 1c79f60 */ extern MN_SCENE MNS_OptCounter; /* static */
/* bss 1c7b0b8 */ extern MN_SCENE MNS_RepCounter; /* static */
/* bss 1c7c210 */ extern MN_SCENE MNS_StgCounter[2]; /* static */
/* bss 1c7e4b8 */ extern MN_SCENE MNS_JimakuBak; /* static */
/* sbss 399b24 */ extern int CurMapOldFlg; /* static */
// /* sbss 399b28 */ static int CurMapNo;
/* sbss 399b2c */ extern int CurMapBakFlg; /* static */
// /* sbss 399b30 */ static int CurMapState;
/* sbss 399b34 */ extern USER_DATA *UserWork; /* static */
/* sbss 399b38 */ extern P3MC_STAGERANK *pCStageRank; /* static */
// /* bss 1c7f610 */ static P3MC_RANKSCORE CurRankScore;
/* sbss 399b3c */ extern P3MC_USRLST *UserLst; /* static */
/* sbss 399b40 */ extern MN_USERLST_WORK *UserDispWork; /* static */
/* bss 1c7f628 */ extern CURFILEINFO CurFileInfo; /* static */
/* bss 1c7f640 */ extern TsUSERPKT MnPkt; /* static */
/* bss 1c7f6e0 */ extern TsUSERPKT MnLPkt; /* static */
/* bss 1c7f780 */ extern sceGifPacket FPacket; /* static */
/* sdata 399828 */ extern MAP_TIME MapTime;
/* sbss 399b44 */ extern int UCheckLoadError; /* static */
/* sbss 399b48 */ extern int UCheckSaveError; /* static */
/* sbss 399b4c */ extern int subStatus; /* static */
/* sbss 399b50 */ extern int ret; /* static */
/* sbss 399b54 */ extern int errorNo; /* static */
/* sbss 399b58 */ extern int waitTime; /* static */
// /* sbss 399b5c */ static MCRWDATA_HDL *pGameData;
/* bss 1c7f790 */ extern MCMES_WORK MCMesWork; /* static */
/* bss 1c7f7c8 */ extern CMPMES_WORK CmpMesWork; /* static */
// /* bss 1c7f7e0 */ static RANKLIST RankLst[20];
// /* bss 1c7f970 */ static POPUP_MENU PopupMenu;
// /* bss 1c7fa88 */ static SAVE_MENU SaveMenu;
// /* bss 1c7fb48 */ static JUKE_MENU JukeMenu;
// /* bss 1c80f60 */ static OPTION_MENU OptionMenu;
/* bss 1c80fb0 */ extern USERLIST_MENU UserListMenu; /* static */
/* bss 1c810c8 */ extern SCFADE ScFade; /* static */

static int   TsGetMenuPadIsRepeat(int no, int npad);
static void  TSSNDPLAY(int n);
static void  TSSNDSTOP(int chan);
static void  TSSNDMASK_CHAN(int chan, int mskflag);
static void  TSSND_SKIPSTOP(int n);
static void  TSSND_SKIPPLAY(int n);
static int   TSSND_CHANISSTOP(int chan);
static void  tsBGMONEPlay(int no);
static void  tsBGMONEStop(int no);
static void  tsBGMONEVol(int no, int vol);
static void  tsBGMONETop(int no, int vol);
/* static */ void  tsBGMONEflow(void);
static void  tsBGMONEPause(int flg);
/* static */ void  TsBGMInit(void);
/* static */ void  TsBGMPlay(int no, int time);
static void  TsBGMStop(int time);
/* static */ void  TsBGMMute(int time);
static int   TsBGMLoadCheck(void);
/* static */ void  TsBGMPause(int flg);
/* static */ void  TsBGMPoll(void);
/* static */ void* TsCmnPkOpen(sceGifPacket *pgifpk);
/* static */ void  TsCmnPkClose(sceGifPacket *pgifpk, void *pk, int pri);
static void  TsClearMenuPad(int no);
static void  TsGetMenuPad(int no, u_int *getpad);
static void  TsSndFlow(int flg);
/* static */ int   TSNumMov(int cn, int dn, int scale);
static int   TSLOOP(int no, int max);
static int   TSLIMIT(int no, int min, int max);
/* static */ int   TsMENU_GetMapNo(int *psize);
static void  TsMENU_GetMapTimeState(int flg);
/* static */ void  TsSetScene_Map(MN_SCENE *pScene, int mapNo, int tflg, int bFocus);
static void  TsSet_ParappaCapColor(void);
/* static */ void  TsClearSet(P3GAMESTATE *pstate);
/* static */ void  TsCheckEnding(P3GAMESTATE *pstate);
/* static */ void  TsSetRankingName(P3MC_STAGERANK *pRankTop, u_char *name);
/* static */ void  TsSetRanking2UData(USER_DATA *puser, P3MC_STAGERANK *wkRank);
/* static */ void  TsSetSaveData(MCRWDATA_HDL *pDataW, int mode, USER_DATA *puser);
/* static */ void  TsRestoreSaveData(MCRWDATA_HDL *pDataW, int mode);
/* static */ int   TsRanking_Set(void);
/* static */ int   TsCheckTimeMapChange(void);
static int   TsMemCardCheck_Flow(int flg, u_int tpad);
static int   TsMap_Flow(int flg, u_int tpad, u_int tpad2);
/* static */ void  TsMakeUserWork(int mode);
/* static */ void  TsSaveSuccessProc(void);
/* static */ int   MpSave_Flow(int flg, u_int tpad, u_int tpad2);
static int   MpCityHall_Flow(int flg, u_int tpad, u_int tpad2);
/* static */ void  MpCityHallParaStart(int pos);
static void  MpCityHallFPHSSoundMask(int flg);
/* static */ int   MpCityHallFPHSMove(int pos, int fpos);
/* static */ void  MpCityHallFPHOK(int flg);
/* static */ void  MpCityHallCharPosSet(int pos);
/* static */ int   MpPopMenu_Flow(int flg, u_int tpad);
/* static */ int   MpMapMenu_Flow(int flg, MAPPOS *mpw, u_int tpad);
static int   _MapGetMovableDir(MAPPOS *mpw);
/* static */ int   McErrorMess(int err);
static void  McInitFlow(void);
/* static */ int   McStartCheckFlow(int flg);
/* static */ int   McUserCheckFlow(int type, int mode, int *bError);
/* static */ int   McUserSaveFlow(USER_DATA *puser);
/* static */ int   McUserLoadFlow(int fileNo, int mode, int bBroken);
static void  TsMCAMes_Init(void);
static int   TsMCAMes_GetSelect(void);
static int   TsMCAMes_IsON(void);
/* static */ void  TsMCAMes_Flow(u_int tpad);
/* static */ void  TsMCAMes_Draw(SPR_PKT pk, SPR_PRM *spr);
/* static */ void  TsCMPMes_Draw(SPR_PKT pk, SPR_PRM *spr);
static void  TsANIME_Init(ANIME_WK *wk);
/* static */ int   TsANIME_Poll(ANIME_WK *wk);
static void  TsANIME_Start(ANIME_WK *wk, int state, int tim);
static int   TsANIME_GetRate(ANIME_WK *wk, float *rt0, float *rt1, float *rt2);
/* static */ void  _TsSortSetRanking(P3MC_RANKSCORE **ptRank, int n, P3MC_RANKSCORE *pRank, int bNameCmp);
/* static */ RANKLIST* TsGetRankingList(int flag, int vsLev, int stageNo, int *nrank);
/* static */ int   TsPopMenu_Flow(int flg, u_int tpad);
/* static */ void  TsPopMenu_Draw(SPR_PKT pk, SPR_PRM *spr);
/* static */ int   TsSaveMenu_Flow(int flg, u_int tpad);
/* static */ void  TsSaveMenu_Draw(SPR_PKT pk, SPR_PRM *spr);
/* static */ void  TSJukeCDObj_Init(JUKECDOBJ *pw, int pno);
/* static */ void  _TsJkJacketPut(SPR_PKT pk, SPR_PRM *spr, JUKECDOBJ *pw, int px, int py, float zx, float rot, u_int abgr, u_int abgrs);
/* static */ void  _TsJkRecordPut(SPR_PKT pk, SPR_PRM *spr, JUKECDOBJ *pw, int px, int py, float zr, float rrot, u_int abgr, u_int abgrs);
/* static */ void  TSJukeCDObj_Draw(SPR_PKT pk, SPR_PRM *spr, JUKECDOBJ *pw, int px, int py, int anmtime);
/* static */ int   TsJukeIsObjAnime(int isComp);
/* static */ int   TsJukeObjAnime(int isOut);
/* static */ int   TsJukeObjAnime2(int isOut);
/* static */ int   _TsJKMoveCus(int *cx, int *cy, int mx, int my, JUKECDOBJ *cobj);
/* static */ void  _TsJKSetPadArrow(int sel, JUKECDOBJ *cobj);
/* static */ int   TsJukeMenu_Flow(int flg, u_int tpad);
/* static */ void  TsJukeMenu_Draw(SPR_PKT pk, SPR_PRM *spr);
static void  TsCmnCell_CusorSET(CELLOBJ *obj);
static void  TsCmnCell_CusorON(CELLOBJ *obj);
static void  TsCmnCell_CusorOFF(CELLOBJ *obj);
static void  TsCmnCell_CusorSEL(CELLOBJ *obj);
static void  TsCmnCell_CusorMASK(CELLOBJ *obj);
/* static */ void  TsCmnCell_CusorDraw(SPR_PKT pk, SPR_PRM *spr, int n, CELLOBJ *obj, int ox, int oy, int CurColor);
/* static */ int   TsOption_Flow(int flg, u_int tpad);
/* static */ void  TsOption_Draw(SPR_PKT pk, SPR_PRM *spr);
static int   TsUserList_GetCurFileNo(int *isBroken);
static int   TsUserList_IsGetFileSave(void);
static int   TsUserList_SortUser(void);
static void  TsUserList_SetCurUserData(USER_DATA *psrc);
static void  TsUserList_SetCurDispUserData(USER_DATA *psrc);
/* static */ void  TsUserList_SetCurFileNoCusor(int fileNo, u_int *fDate);
static void  TsUserList_SetType(USERLISTTYPE_TABLE *ptbl, int mode, int curTag);
static int   TsUserList_TagChangeAble(USERLIST_MENU *pfw, int *pno);
/* static */ int   TsUserList_SetCurTag(USERLIST_MENU *pfw, int no);
/* static */ int   TsUserList_Flow(int flg, u_int tpad, u_int tpad2);
/* static */ void  TsUserList_Draw(SPR_PKT pk, SPR_PRM *spr);
/* static */ void  NameSpaceCut(u_char *dst, u_char *src);
/* static */ void  TsUser_PanelDraw(SPR_PKT pk, SPR_PRM *spr, USER_DATA *user, int px, int py, int pflg, int isLog);
/* static */ void  TsNAMEINBox_SetName(NAMEINW *pfw, u_char *name);
static void  TsNAMEINBox_GetName(NAMEINW *pfw, u_char *name);
/* static */ int   TsNAMEINBox_Flow(int flg, NAMEINW *pfw, u_int tpad);
/* static */ void  TsNAMEINBox_Draw(SPR_PKT pk, SPR_PRM *spr, int px, int py, int isLog, NAMEINW *pfw, int side);
static void  TsSCFADE_Flow(int flg, int prm);
/* static */ void  TsSCFADE_Draw(SPR_PKT pk, SPR_PRM *spr, int prio);
static void  TsPatTexFnc(int flg);
/* static */ void  _TsPatSetPrm(SPR_PKT pk, SPR_PRM *spr, PATPOS *ppos, int ox, int oy);
static void  TsPatPut(SPR_PKT pk, SPR_PRM *spr, PATPOS *ppos, int ox, int oy);
static void  TsPatGetSize(PATPOS *ppos, int *x, int *y, int *w, int *h);
/* static */ void  TsPatPutRZoom(SPR_PKT pk, SPR_PRM *spr, PATPOS *ppos, int ox, int oy, float zrate, float rot);
/* static */ void  TsPatPutMZoom(SPR_PKT pk, SPR_PRM *spr, PATPOS *ppos, int ox, int oy, float Zrx, float Zry, int mx, int my, float Crx, float Cry);
static void  TsPatPutSwing(SPR_PKT pk, SPR_PRM *spr, PATPOS *ppos, int ox, int oy, int mx, int my, float Crx);
static void  TsPatPutUneri(SPR_PKT pk, SPR_PRM *spr, PATPOS *ppos, int ox, int oy, int mx, int my, float Crx, float Drt);
static void  TsCELBackInit(void);
/* static */ void  _TsCELBackObjDraw(SPR_PKT pk, SPR_PRM *spr, int sw, int sh, u_int *colTbl);
/* static */ void  TsHosiPut(SPR_PKT pk, SPR_PRM *spr, TSTEX_INF *ptex, float px, float py, float zrate, float rot);

static int TsGetMenuPadIsRepeat(int no, int npad) {
    return (menuPadState[no][npad].state >= 2);
}

static void TSSNDPLAY(int n) {
    TSVOICE_TBL *ptap;
    TSSND_CHAN  *pchan;
    int          bMsk;
    TSVSNDSEQ   *pSeq;

    if (n >= 0) {
        if (n & 0x8000) {
            pSeq  = &VSNDSEQ_Tbl[n & ~0x8000];
            pchan = &TsSndChan[pSeq->chanNo];

            bMsk = pchan->bMsk;

            memset(pchan, 0, sizeof(*pchan));

            pchan->isSeq = TRUE;

            pchan->pSeq = pSeq->pSeqTop;
            pchan->bMsk = bMsk;
        } else if (n < 0x38) {
            ptap  = &TsVoiceTbl[n];
            pchan = &TsSndChan[ptap->chanNo];

            bMsk = pchan->bMsk;

            memset(pchan, 0, sizeof(*pchan));

            pchan->pTap = ptap;
            pchan->bMsk = bMsk;
        }
    }
}

static void TSSNDSTOP(int chan) {
    memset(&TsSndChan[chan], 0, sizeof(TSSND_CHAN));
    MenuVoiceStop(chan);
}

static void TSSNDMASK_CHAN(int chan, int mskflag) {
    TSSND_CHAN *pchan = &TsSndChan[chan];

    pchan->bMsk = mskflag;
    if (pchan->pTap != NULL || pchan->pSeq != NULL) {
        MenuVoiceStop(chan);
    }
}

static void TSSND_SKIPSTOP(int n) {
    TSVOICE_TBL *ptap;
    TSSND_CHAN  *pchan;

    if (n >= 0x38) {
        return;
    }

    ptap  = &TsVoiceTbl[n];
    pchan = &TsSndChan[ptap->chanNo];

    if (pchan->pTap == ptap) {
        memset(pchan, 0, sizeof(*pchan));
        MenuVoiceStop(ptap->chanNo);
    }
}

static void TSSND_SKIPPLAY(int n) {
    TSVOICE_TBL *ptap;
    TSSND_CHAN  *pchan;

    if (n >= 0x38) {
        return;
    }

    ptap  = &TsVoiceTbl[n];
    pchan = &TsSndChan[ptap->chanNo];

    if (pchan->pTap == ptap && !pchan->isOn) {
        pchan->tim = ptap->ontim;
    }
}

static int TSSND_CHANISSTOP(int chan) {
    TSSND_CHAN *pchan = &TsSndChan[chan];
    int         ret   = FALSE;

    if (pchan->pTap == NULL) {
        ret = (pchan->pSeq == NULL);
    }

    return ret;
}

static void tsBGMONEPlay(int no) {
    BGMONE *wbgm  = &TsBGMState.wbgm[no];
    MAPBGM *mpbgm = &MapBgmTbl[no];

    wbgm->pbgm = mpbgm;
    wbgm->vol  = 0;
    
    if (mpbgm->lpTimeF != 0) {
        wbgm->tim = mpbgm->lpTimeF;
        MenuVoicePlayVol(mpbgm->chan, mpbgm->tapNo, 0);
    }
}

static void tsBGMONEStop(int no) {
    BGMONE *wbgm = &TsBGMState.wbgm[no];

    wbgm->pbgm = &MapBgmTbl[no];
    wbgm->vol  = 0;
    wbgm->tim  = 0;
    MenuVoiceStop(MapBgmTbl[no].chan);

    wbgm->pbgm = NULL;
}

static void tsBGMONEVol(int no, int vol) {
    BGMONE *wbgm = &TsBGMState.wbgm[no];

    if (wbgm->vol != vol) {
        wbgm->vol = vol;
        MenuVoiceSetVol(wbgm->pbgm->chan, wbgm->pbgm->tapNo, vol);
    }
}

static void tsBGMONETop(int no, int vol) {
    BGMONE *wbgm = &TsBGMState.wbgm[no];
    MAPBGM *mpbgm = &MapBgmTbl[no];

    wbgm->pbgm = mpbgm;
    wbgm->vol  = vol;
    wbgm->tim  = mpbgm->lpTimeF;
    MenuVoicePlayVol(mpbgm->chan, mpbgm->tapNo, vol);
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", tsBGMONEflow);

static void tsBGMONEPause(int flg) {
    BGMONE *wbgm = TsBGMState.wbgm;
    int     i;

    for (i = 0; i < PR_ARRAYSIZE(TsBGMState.wbgm); i++, wbgm++) {
        wbgm->bPause = (flg != 0);
    }
}

void TsBGMInit(void) {
    memset(&TsBGMState, 0, sizeof(TsBGMState));
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsBGMPlay);

static void TsBGMStop(int time) {
    BGMSTATE *pbgm = &TsBGMState;
    int       i;

    if (pbgm->state != 0) {
        pbgm->ttim0 = 0;
        pbgm->ttim = 0;

        if (time >= 1) {
            pbgm->state = 3;
            pbgm->vol = 0x100;

            if (pbgm->ctim == 0) {
                tsBGMONEVol(pbgm->sndno, 0x100);
            }

            do {} while (0); /* TODO: Get rid of this? */
        } else {
            pbgm->chgReq = 0;
            pbgm->cstate = 0;
            pbgm->ctim = 0;

            pbgm->state = 0;
            pbgm->vol = 0;

            for (i = 0; i < 11; i++) {
                tsBGMONEStop(i);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsBGMMute);

static int TsBGMLoadCheck(void) {
    return MenuVoiceBankSet(-1);
}

void TsBGMPause(int flg) {
    if (TsBGMState.state != 0) {
        TsBGMState.chgReq = 0;
        TsBGMState.cstate = 0;
        TsBGMState.ctim = 0;
        tsBGMONEPause(flg);
    }
}

void TsBGMChangePos(int no) {
    BGMSTATE *pbgm = &TsBGMState;

    if (no >= 11) {
        return;
    }

    pbgm->vol    = 256;
    pbgm->state  = 1;
    pbgm->ttim0  = 0;
    pbgm->ttim   = 0;
    pbgm->chgReq = no + 1;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsBGMPoll);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsCmnPkOpen);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsCmnPkClose);

int _P3DATA_SIZE(int mode) {
    u_int size;

    switch (mode) {
    case 1:
        size = 0x188;
        break;
    case 2:
        size = 0x4528;
        break;
    default:
        size = 0;
        break;
    }

    return size;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsGetTm2Tex);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsGetTm2HedTex);

static void TsClearMenuPad(int no) {
    if (no >= 2) {
        return;
    }

    memset(&menuPadState[no][0], 0, sizeof(TSREPPAD) * 4);
}

static void TsGetMenuPad(int no, u_int *getpad) {
    PADD     *pPad;
    u_int     one, shot;
    TSREPPAD *pRpPad;
    u_int    *pPadBit;
    u_int     padMsk;
    u_int     i;

    pPadBit = RPPadBit;
    if (no >= 2) {
        return;
    }

    *getpad = 0;

    pRpPad = &menuPadState[no][0];
    padMsk = 0;
    pPad = &pad[no];

    one = pPad->mone;
    shot = pPad->mshot;

    for (i = 0; i < 4; i++, pRpPad++, pPadBit++) {
        padMsk |= *pPadBit;
        if (one & *pPadBit) {
            pRpPad->time = 0;
            pRpPad->state = 1;
            *getpad |= *pPadBit;
        } else if (shot & *pPadBit) {
            pRpPad->time++;
            if (pRpPad->time >= 19) {
                if (pRpPad->time % 5) {
                    pRpPad->state = 2;
                } else {
                    pRpPad->state = 3;
                    *getpad |= *pPadBit;
                }
            }
        } else {
            pRpPad->state = 0;
            pRpPad->time = 0;
        }
    }

    *getpad |= (one & ~padMsk);
}

static void TsSndFlow(int flg) {
    int          i;
    TSVOICE_TBL *ptap;
    TSSND_CHAN  *pchan;
    u_short     *pSeq, *pCur;

    if (flg == 1) {
        memset(&TsSndChan, 0, sizeof(TsSndChan));
        return;
    }

    pchan = TsSndChan;

    for (i = 0; i < 15; i++, pchan++) {
        ptap = pchan->pTap;
        if (ptap != NULL) {
            pchan->tim++;

            if (!pchan->isOn) {
                if (ptap->ontim < pchan->tim) {
                    if (!pchan->bMsk) {
                        MenuVoicePlay(i, ptap->vsetNo);
                    }

                    pchan->isOn = 1;
                    if (ptap->offtim == 0) {
                        memset(pchan, 0, sizeof(*pchan));
                    }
                }

                if (!pchan->isOn) {
                    continue;
                }
            }

            if (ptap->offtim != 0 && pchan->tim >= ptap->offtim) {
                MenuVoiceStop(i);
                memset(pchan, 0, sizeof(*pchan));
            }
        } else {
            pSeq = pchan->pSeq;
            if (pSeq != NULL) {
                pchan->tim++;
                pCur = &pSeq[pchan->sqIdx * 2];
    
                if (!pchan->isOn) {
                    pchan->isOn = 1;
                } else {
                    if (pchan->tim < pCur[1]) {
                        continue;
                    }
                    pchan->tim -= pCur[1];
                    pchan->sqIdx++;
                    pCur = &pSeq[pchan->sqIdx * 2];
                }
    
                switch (pCur[0]) {
                case 0xffff:
                    break;
                case 0xfffe:
                    pchan->sqIdx = 0;
                    pCur = pSeq;
                    break;
                case 0xfffd:
                    pchan->sqIdx = 0;
                    MenuVoiceStop(i);
                    memset(pchan, 0, sizeof(*pchan));
                    continue;
                }
                
                if (!pchan->bMsk && !(pCur[0] & 0xf000)) {
                    MenuVoicePlay(i, pCur[0]);
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TSNumMov);

float TSNumRBack(float rt, float bkrt) {
    float limit = bkrt + 1.0f;
    
    rt *= (bkrt * 2.0f) + 1.0f;
    if (limit < rt) {
        rt = (limit * 2.0f) - rt;
    }
    
    return rt;
}

static int TSLOOP(int no, int max) {
    return (no + max) % max;
}

static int TSLIMIT(int no, int min, int max) {
    if (no < min) {
        return min;
    }
    if (no >= max) {
        return max - 1;
    }
    return no;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsMENU_GetMapNo);

static inline int PrBcdInt(u_int n) {
    return (((n / 16) * 10) + (n % 16));
}

static void TsMENU_GetMapTimeState(int flg) {
    /* sdata 3997d4 */ extern int nTim;
    int         err;
    short       hour;
    short       state;
    MAP_TIME   *mptim;
    sceCdCLOCK  clock;

    mptim = &MapTime;

    if (flg == 1) {
        CurMapOldFlg = -1;
        CurMapBakFlg = -1;
        memset(mptim, 0, sizeof(*mptim));
        nTim = flg;
    } else if (flg == 3) {
        nTim = 30;
        return;
    }

    nTim--;
    if (nTim > 0) {
        return;
    }
    nTim = 30;

    err = sceCdReadClock(&clock);
    mptim->date_pad = rand() % 200;
    if (err != 0 && clock.stat == 0) {
        mptim->date_second = clock.second;
        mptim->date_minute = clock.minute;
        mptim->date_hour = clock.hour;
        mptim->date_day = clock.day;
        mptim->date_month = clock.month;
        mptim->date_year = clock.year + 0x2000;
        flg = 0;
    } else {
        mptim->date_second = 0x0;
        mptim->date_minute = 0x0;
        mptim->date_hour = 12; /* BUG: Value isn't valid BCD, */
        mptim->date_day = 0x1; /*      though it still works. */
        mptim->date_month = 0x1;
        mptim->date_year = 0x2000;
        flg = 1;
    }

    state = CurMapBakFlg;

    if (!flg) {
        hour = PrBcdInt(mptim->date_hour);

        /* Dumb nested ifs but required to match. */
        if (hour < 4) {
            state = 2;
        } else {
            state = 0;
            if (hour >= 7) {
                state = 1;
                if (hour >= 16) {
                    if (hour <= 18) {
                        state = 0;
                    } else {
                        state = 2;
                    }
                }
            }
        }
    } else {
        if (state <= -1) {
            state = 1;
        }
    }

    CurMapBakFlg = state;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSetScene_Map);

static void TsSet_ParappaCapColor(void) {
    P3LOG_VAL      *pLog = pP3GameState->pLog;
    TAP_ROUND_ENUM  n;

    switch (pLog->nRound) {
    case 0:
        n = TRND_R1;
        break;
    case 1:
        n = TRND_R2;
        break;
    case 2:
        n = TRND_R3;
        break;
    default:
        n = TRND_R4;
        break;
    }

    MenuRoundTim2Trans(n);
}

INCLUDE_RODATA("asm/nonmatchings/menu/menusub", D_00395F10);
INCLUDE_RODATA("asm/nonmatchings/menu/menusub", D_00395F20);
INCLUDE_RODATA("asm/nonmatchings/menu/menusub", D_00395F30);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsClearSet);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsCheckEnding);

void TsMENU_InitSystem(void) {
    int i;

    P3MC_InitReady();
    P3MC_CheckChangeSet();

    memset(&MNS_JimakuBak, 0, sizeof(MNS_JimakuBak));
    memset(&MNS_RepCounter, 0, sizeof(MNS_RepCounter));
    memset(&MNS_OptCounter, 0, sizeof(MNS_OptCounter));
    memset(&MNS_CityHall, 0, sizeof(MNS_CityHall));
    memset(&MNS_StageMap, 0, sizeof(MNS_StageMap));
    memset(&MNS_StageMap2, 0, sizeof(MNS_StageMap2));

    for (i = 0; i < 2; i++) {
        memset(&MNS_StgCounter[i], 0, sizeof(MNS_StgCounter[i]));
    }

    tblTex = NULL;
    UserLst = NULL;
    UserDispWork = NULL;

    UserWork = (USER_DATA*)memalign(16, sizeof(USER_DATA));
    memset(UserWork, 0, sizeof(*UserWork));

    pCStageRank = (P3MC_STAGERANK*)memalign(16, sizeof(P3MC_STAGERANK[8]));
    memset(pCStageRank, 0, sizeof(P3MC_STAGERANK[8]));

    memset(&CurFileInfo, 0, sizeof(CurFileInfo));
    CurFileInfo.logFileNo = -1;
    CurFileInfo.repFileNo = -1;
}

void TsMENU_EndSystem(void) {
    if (pCStageRank != 0) {
        free(pCStageRank);
    }
    if (UserWork != 0) {
        free(UserWork);
    }
}

void TsMenu_RankingClear(void) {
    int             i;
    P3MC_STAGERANK *pRank = pCStageRank;

    for (i = 0; i < 8; i++, pRank++) {
        memset(pRank, 0, sizeof(*pRank));
    }
}

void TsMenu_Init(int iniflg, P3GAMESTATE *pstate) {
    int   i;
    void *ptim2;

    pP3GameState = pstate;

    PrSetStage(0);

    P3MC_SetCheckSaveSize(1, 0x8c, 0x188);
    P3MC_SetCheckSaveSize(2, 0xa0, 0x4528);

    if (!iniflg) {
        MENUSubt_PadFontSw(0);
        TsMemCardCheck_Flow(1, 0);
    } else {
        MENUSubt_PadFontSw(1);

        MNScene_Init(&MNS_CityHall, &Scene_CityHall, 1);
        MNScene_Init(&MNS_StageMap, &Scene_StageMap, 1);

        MNScene_Init(&MNS_OptCounter, &Scene_OptCounter, 0);
        MNScene_Init(&MNS_RepCounter, &Scene_RepCounter, 0);
        MNScene_Init(&MNS_JimakuBak, &Scene_JimakuBak, 0);

        MNScene_Init(&MNS_StgCounter[0], &Scene_StgCounterLoad, 0);
        MNScene_Init(&MNS_StgCounter[1], &Scene_StgCounterSave, 0);

        MNScene_DispSw(&MNS_OptCounter, 0);
        MNScene_DispSw(&MNS_RepCounter, 0);
        MNScene_DispSw(&MNS_JimakuBak, 0);

        for (i = 0; i < 2; i++) {
            MNScene_DispSw(&MNS_StgCounter[i], 0);
        }

        tblTex = (TSTEX_INF*)malloc(sizeof(TSTEX_INF) * 104);

        for (i = 0; i < 104; i++) {
            switch (TexTable[i].flg) {
            case 0:
                TsGetTm2HedTex(TexTable[i].fno, &tblTex[i]);
                break;
            case 1:
                ptim2 = GetIntAdrsCurrent(TexTable[i].fno);
                Tim2Trans(ptim2);
                TsGetTm2Tex(ptim2, &tblTex[i]);
                break;
            case 2:
                ptim2 = GetIntAdrsCurrent(TexTable[i].fno);
                TsGetTm2Tex(ptim2, &tblTex[i]);
                break;
            }
        }
    }

    UserLst = (P3MC_USRLST*)memalign(16, sizeof(P3MC_USRLST));
    memset(UserLst, 0, sizeof(*UserLst));
    P3MC_CheckChangeSet();

    UserDispWork = (MN_USERLST_WORK*)memalign(16, sizeof(MN_USERLST_WORK));
    memset(UserDispWork, 0, sizeof(*UserDispWork));

    TsInitUPacket(&MnPkt, NULL, 0x20000);
    TsInitUPacket(&MnLPkt, NULL, 0x2000);

    TsMCAMes_Init();
    TsMCAMes_SetMes(-1);
    TsCMPMes_SetMes(-1);

    TsClearMenuPad(0);
    TsClearMenuPad(1);

    TsSCFADE_Flow(1, 0);
    TsBGMInit();

    _bMapCaptureReq = FALSE;
    UserList_Sw     = FALSE;
    OptionList_Sw   = FALSE;
    PopMenu_Sw      = FALSE;
    SaveMenu_Sw     = FALSE;
    JukeMenu_Sw     = FALSE;

    TsSndFlow(1);

    TsMENU_GetMapTimeState(1);
}

void TsMenu_End(void) {
    int i;

    TsBGMStop(0);

    TsCELBackEnd();
    TsEndUPacket(&MnLPkt);
    TsEndUPacket(&MnPkt);

    MNScene_End(&MNS_JimakuBak);
    MNScene_End(&MNS_RepCounter);
    MNScene_End(&MNS_OptCounter);

    for (i = 0; i < 2; i++) {
        MNScene_End(&MNS_StgCounter[i]);
    }

    MNScene_End(&MNS_StageMap2);
    MNScene_End(&MNS_StageMap);
    MNScene_End(&MNS_CityHall);

    if (tblTex != NULL) {
        free(tblTex);
    }

    if (UserDispWork != NULL) {
        free(UserDispWork);
    }

    if (UserLst != NULL) {
        free(UserLst);
    }
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsMenu_InitFlow);

int TsMenuMemcChk_Flow(void) {
    u_int tpad, tpad2;
    int   ret;

    TsGetMenuPad(0, &tpad);
    TsGetMenuPad(1, &tpad2);

    TsMCAMes_Flow(tpad);
    ret = TsMemCardCheck_Flow(0, tpad);

    TsSCFADE_Flow(0, 0);
    TsBGMPoll();

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsMenu_Flow);

void TsMenu_Draw(void) {
    SPR_PRM    SprPrm;
    u_long128 *pkt;
    SPR_PRM   *spr;
    SPR_PKT    pk;
    int        flg;
    int        i;

    pk  = &pkt;
    spr = &SprPrm;

    MNScene_Draw(&MNS_StageMap);
    MNScene_Draw(&MNS_StageMap2);
    MNScene_Draw(&MNS_CityHall);

    flg = TsCELBackDraw(&MnPkt, spr, MNS_OptCounter.isDisp, 0);
    MNScene_Draw(&MNS_OptCounter);
    flg |= TsCELBackDraw(&MnPkt, spr, MNS_RepCounter.isDisp, 1);
    MNScene_Draw(&MNS_RepCounter);

    for (i = 0; i < PR_ARRAYSIZE(MNS_StgCounter); i++) {
        flg |= TsCELBackDraw(&MnPkt, spr, MNS_StgCounter[i].isDisp, 2);
        MNScene_Draw(&MNS_StgCounter[i]);
    }

    if (!flg) {
        TsCELBackEnd();
    }

    TsPatTexFnc(0);

    MnPkt.ptop = PR_UNCACHED(MnPkt.pkt[MnPkt.idx].PaketTop);
    pkt = (u_long128*)MnPkt.ptop;

    PkSprPkt_SetDefault(pk, spr, DrawGetDrawEnvP(DNUM_DRAW));

    if (_bMapCaptureReq) {
        TsMenu_CaptureVram(pk, spr);
        _bMapCaptureReq = FALSE;
    }
    if (UserList_Sw) {
        TsUserList_Draw(pk, spr);
    }
    if (OptionList_Sw) {
        TsOption_Draw(pk, spr);
    }

    TsSCFADE_Draw(pk, spr, 2);

    if (PopMenu_Sw) {
        TsPopMenu_Draw(pk, spr);
    }
    if (SaveMenu_Sw) {
        TsSaveMenu_Draw(pk, spr);
    }
    if (JukeMenu_Sw) {
        TsJukeMenu_Draw(pk, spr);
    }

    MnPkt.ptop = (u_int)pkt;
    sceGsSyncPath(0, 0);

    TsDrawUPacket(&MnPkt);
    sceGsSyncPath(0, 0);

    MnPkt.ptop = PR_UNCACHED(MnPkt.pkt[MnPkt.idx].PaketTop);
    pkt = (u_long128*)MnPkt.ptop;

    PkSprPkt_SetDefault(pk, spr, DrawGetDrawEnvP(DNUM_DRAW));
    TsCMPMes_SetPos(0x140, 0xba);
    TsCMPMes_Draw(pk, spr);
    TsSCFADE_Draw(pk, spr, 1);
    TsMCAMes_SetPos(0x140, 0x65);

    TsMCAMes_Draw(pk, spr);
    MnPkt.ptop = (u_int)pkt;
    sceGsSyncPath(0, 0);

    TsDrawUPacket(&MnPkt);
    sceGsSyncPath(0, 0);

    pkt = TsCmnPkOpen(&FPacket);

    PkSprPkt_SetDefault(pk, spr, DrawGetDrawEnvP(DNUM_DRAW));
    TsSCFADE_Draw(pk, spr, 0);

    TsCmnPkClose(&FPacket, pkt, 0xf);
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSetRankingName);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSetRanking2UData);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSetSaveData);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsRestoreSaveData);

int DateChgInt(u_int n) {
    /* Convert BCD to decimal */
    return 
    (
        ((n & 0xf0) >> 4) * 10 +
         (n & 0xf)
    );
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", GetRankScoreID);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsRanking_Set);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsMENU_SetMapScreen);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsCheckTimeMapChange);

int TsAnimeWait_withKeySkip(u_int tpad, MN_SCENE *scene, int ltim, u_int bnk) {
    if (bnk == -1) {
        return MNScene_isAnime(scene, ltim);
    } else {
        return MNScene_isAnimeBank(scene, ltim, bnk);
    }
}

static int TsMemCardCheck_Flow(int flg, u_int tpad) {
    extern int state;
    extern int mesNo;
    int ret;

    if (flg == 1) {
        McInitFlow();
        state = 0;
        mesNo = -1;
        McStartCheckFlow(1);
        TsMCAMes_SetMes(-1);
        return 0;
    }

    switch (state) {
    case 0:
        ret = McStartCheckFlow(0);
        if (ret == 0) {
            state = 0x1000;
            return 0;
        }

        if (ret >= 0) {
            if (mesNo != ret) {
                mesNo = ret;

                switch (ret) {
                case 1:
                    TsMCAMes_SetMes(0x1030001);
                    break;
                case 2:
                    TsMCAMes_SetMes(0x1030000);
                    break;
                }
            }

            if (TsMCAMes_GetSelect()) {
                state = 0x1000;
            }
        }

        break;
    case 0x1000:
        if (TsSCFADE_Set(2, 0xf, 0)) {
            return 0;
        }
        TsMCAMes_SetMes(-1);
        McStartCheckFlow(2);
        P3MC_CheckChangeSet();
        _MNwaitTime = 30;
        state = 0x1010;
    /* fallthrough */
    case 0x1010:
        if (--_MNwaitTime <= 0) {
            return 1;
        }
        break;
    }

    return 0;
}

static int TsMap_Flow(int flg, u_int tpad, u_int tpad2) {
    /* TODO: Fix names once made static. */
    /* sbss 399ad0 */ extern int state_tmp_253;
    /* bss 1c77a50 */ extern MAPPOS MapCity_tmp_254;
    int ret;
    int mn;

    if (flg == 1) {
        switch (tpad) {
        case 0:
            pP3GameState->nStage = 0;
            MenuVoiceBankSet(0);
            state_tmp_253 = 0;
            break;
        case 1:
            MenuVoiceBankSet(0);
            state_tmp_253 = 0x6500;
            break;
        case 2:
            MenuVoiceBankSet(0);
            TsBGMPlay(1, 0x14);
            state_tmp_253 = 0x2000;
            break;
        case 3:
            MenuVoiceBankSet(0);
            state_tmp_253 = 0;
            break;
        }

        TsMENU_GetMapTimeState(1);
        return 0;
    }

    switch (state_tmp_253) {
    case 0:
        CurMapOldFlg = -1;
        mn = TsMENU_GetMapNo(NULL);
        TsMENU_SetMapScreen(mn);
        MapCity_tmp_254.pscene = &MNS_StageMap;
        MapCity_tmp_254.panime = StageMapAnimePA;
        MapCity_tmp_254.lmtPos = mn + 1;

        if (mn < 2) {
            MapCity_tmp_254.mnmap = mnmapMap1;
        } else if (pP3GameState->pLog->nRound >= 4) {
            MapCity_tmp_254.mnmap = mnmapMap2;
        } else {
            MapCity_tmp_254.mnmap = mnmapMap;
        }

        MpMapMenu_Flow(1, &MapCity_tmp_254, 0);

        switch (pP3GameState->nStage) {
        case 1:
            mn = 1;
            break;
        case 2:
            mn = 2;
            break;
        case 3:
            mn = 3;
            break;
        case 4:
            mn = 4;
            break;
        case 5:
            mn = 5;
            break;
        case 6:
            mn = 6;
            break;
        case 7:
            mn = 7;
            break;
        case 8:
            mn = 8;
            break;
        case 9:
            mn = 9;
            break;
        case 0:
        default:
            mn = 0;
            break;
        }

        MpMapMenu_Flow(3, &MapCity_tmp_254, mn);
        TsCMPMes_SetMes(-1);
        TsSet_ParappaCapColor();
        if (pP3GameState->pAutoMove == NULL) {
            TsBGMPlay(MapCity_tmp_254.curPos + 1, 0xa);
        }
        state_tmp_253 = 0x1000;
        /* fallthrough */
    case 0x1000:
        MNScene_DispSw(&MNS_CityHall, 0);
        MNScene_DispSw(&MNS_StageMap, 1);
        state_tmp_253 = 0x1010;
        break;
    case 0x1010:
        if (!pP3GameState->isWipeEnd || TsBGMLoadCheck()) {
            return 0;
        }
        if (TsAnimeWait_withKeySkip(tpad, &MNS_StageMap, 0, -1)) {
            return 0;
        }
        /* fallthrough */
    case 0x1018:
        mn = 0;

        if (pP3GameState->pAutoMove != NULL) {
            switch (*pP3GameState->pAutoMove) {
            case 1:
                mn = 1;
                break;
            case 2:
                mn = 2;
                break;
            case 3:
                mn = 3;
                break;
            case 4:
                mn = 4;
                break;
            case 5:
                mn = 5;
                break;
            case 6:
                mn = 6;
                break;
            case 7:
                mn = 7;
                break;
            case 8:
                mn = 8;
                break;
            case 9:
                mn = 9;
                break;
            case 0:
                mn = 0;
                break;
            case -2:
                mn = -2;
                pP3GameState->pAutoMove = NULL;
                break;
            case -1:
            default:
                pP3GameState->pAutoMove = NULL;
                mn = 0;
                break;            
            }

            if (pP3GameState->pAutoMove != NULL) {
                MpMapMenu_Flow(4, &MapCity_tmp_254, mn);

                if (MapCity_tmp_254.sndtrg == 1) {
                    TsBGMChangePos(MapCity_tmp_254.curPos + 1);
                }

                pP3GameState->pAutoMove++;
                if (*pP3GameState->pAutoMove == -1) {
                    pP3GameState->pAutoMove = NULL;
                }
            }
        } 

        if (mn == -2) {
            state_tmp_253 = 0x5010;
            break;
        }

        state_tmp_253 = 0x1020;
        /* fallthrough */
    case 0x1020:
        if (!MapCity_tmp_254.bMove) {
            if (TsCheckTimeMapChange()) {
                break;
            }
        }

        ret = MpMapMenu_Flow(0, &MapCity_tmp_254, tpad);
        if (MapCity_tmp_254.anmStop != 0) {
            if (pP3GameState->pAutoMove != NULL) {
                state_tmp_253 = 0x1018;
                break;
            }
        }

        switch (MapCity_tmp_254.sndtrg) {
        case 1:
            TsBGMChangePos(MapCity_tmp_254.curPos + 1);
            break;
        case 3:
            TSSNDPLAY(VSND_CANCEL);
            break;
        case 2:
            break;
        }

        if (ret == 0) {
            break;
        } else if (ret == 1) {
            state_tmp_253 = 0x1100;
        } else if (ret == -1) {
            state_tmp_253 = 0x1200;
            break;
        } else {
            break;
        }

        /* fallthrough */
    case 0x1100:
        if (MapCity_tmp_254.curPos == 0) {
            MNScene_StartAnime(&MNS_StageMap, -1, &StageMapAnimePA[3]);
            TSSNDPLAY(VSND_SELMODE);
            state_tmp_253 = 0x6000;
            break;
        } else if (MapCity_tmp_254.curPos == 9) {
            MNScene_StartAnime(&MNS_StageMap, -1, &StageMapAnimePA[3]);
            TSSNDPLAY(VSND_SELMODE);
            state_tmp_253 = 0x5000;
            break;
        }

        TSSNDPLAY(VSND_SELMODE);
        pP3GameState->nStage = MapCity_tmp_254.curPos;
        state_tmp_253 = 0x3000;
        break;
    case 0x1200:
        TsBGMStop(0x26);
        _MNwaitTime = 40;
        TsCMPMes_SetMes(-1);
        pP3GameState->nStage = MapCity_tmp_254.curPos;
        state_tmp_253 = 0x1210;
        /* fallthrough */
    case 0x1210:
        if (--_MNwaitTime <= 0) {
            return P3MRET_TOTITLE;
        }
        break;
    case 0x2000:
        if (pP3GameState->nStage < 1 || pP3GameState->nStage > 8) {
            state_tmp_253 = 0;
            return 0;
        }
        TsRanking_Set();
        MpSave_Flow(1, 0, 0);
        state_tmp_253 = 0x2010;
        /* fallthrough */
    case 0x2010:
        if (!pP3GameState->isWipeEnd) {
            break;
        }
        _MNwaitTime = 30;
        state_tmp_253 = 0x2020;
        /* fallthrough */
    case 0x2020:
        if (--_MNwaitTime <= 0) {
            state_tmp_253 = 0x2100;
        } else {
            break;
        }        
        /* fallthrough */
    case 0x2100:
        if (!MpSave_Flow(0, tpad, tpad2)) {
            return 0;
        }
        state_tmp_253 = 0x2200;
        /* fallthrough */
    case 0x2200:
        if (TsSCFADE_Set(2, 0x1e, 0)) {
            return 0;
        }
        TsSet_ParappaCapColor();
        state_tmp_253 = 0x2400;
        /* fallthrough */
    case 0x2400:
        TsSCFADE_Set(1, 0x1e, 0);
        state_tmp_253 = 0;
        break;
    case 0x3000:
        MNScene_StartAnime(&MNS_StageMap, -1, &StageMapAnimePA[3]);
        MpPopMenu_Flow(1, 0);
        state_tmp_253 = 0x3010;
        /* fallthrough */
    case 0x3010:
        ret = MpPopMenu_Flow(0, tpad);

        if (ret == 0) {
            break;
        } else if (ret == -1) {
            MNScene_StartAnime(&MNS_StageMap, -1, &StageMapAnimePA[0]);
            state_tmp_253 = 0x1000;
            break;
        }

        switch (ret & 0xff) {
        case 1:
            pP3GameState->nMode = 0;
            pP3GameState->vsLev = 0;
            break;
        case 2:
            pP3GameState->nMode = 1;
            pP3GameState->vsLev = 0;
            break;
        case 3:
            pP3GameState->nMode = 2;
            pP3GameState->vsLev = ret >> 0x8;
            break;
        }

        state_tmp_253 = 0x4000;
        break;
    case 0x4000:
        TsCheckEnding(pP3GameState);
        TsBGMStop(0x20);
        _MNwaitTime = 32;
        TsCMPMes_SetMes(-1);
        state_tmp_253 = 0x4010;
        /* fallthrough */
    case 0x4010:
        if (--_MNwaitTime <= 0) {
            return P3MRET_PLAYGAME;
        }
        break;
    case 0x5000:
        pP3GameState->curRecJacket = 0;
        state_tmp_253 = 0x5100;
        break;
    case 0x5010:
        MNScene_StartAnime(&MNS_StageMap, -1, &StageMapAnimePA[0]);
        state_tmp_253 = 0x5018;
        _MNwaitTime = 40;
        /* fallthrough */
    case 0x5018:
        if (--_MNwaitTime <= 0) {
            TSSNDPLAY(VSND_SELMODE);
            state_tmp_253 = 0x5100;
        }
        break;
    case 0x5100:
        pP3GameState->nStage = MapCity_tmp_254.curPos;
        MNScene_StartAnime(&MNS_StageMap, -1, &StageMapAnimePA[3]);
        TsJukeMenu_Flow(1, pP3GameState->curRecJacket);
        state_tmp_253 = 0x5200;
        /* fallthrough */
    case 0x5200:
        if (!TsJukeMenu_Flow(0, tpad)) {
            return 0;
        }
        TsJukeMenu_Flow(2, 0);
        MNScene_StartAnime(&MNS_StageMap, -1, &StageMapAnimePA[0]);
        state_tmp_253 = 0x1000;
        break;
    case 0x6000:
        MenuVoiceBankSet(0);
        state_tmp_253 = 0x6001;
        /* fallthrough */
    case 0x6001:
        if (TsSCFADE_Set(2, 0x14, 0)) {
            return 0;
        }
        state_tmp_253 = 0x6010;
        /* fallthrough */
    case 0x6010:
        TsBGMPlay(1, 0x14);
        TsSCFADE_Set(1, 0x14, 0);
        MpCityHall_Flow(1, 0, 0);
        state_tmp_253 = 0x7000;
        break;
    case 0x6500:
        TsBGMPlay(1, 0x14);
        MpCityHall_Flow(1, 1, 0);
        state_tmp_253 = 0x6510;
        /* fallthrough */
    case 0x6510:
        if (!pP3GameState->isWipeEnd) {
            break;
        }
        state_tmp_253 = 0x7000;
        /* fallthrough */
    case 0x7000:
        ret = MpCityHall_Flow(0, tpad, tpad2);
        if (ret == 0) {
            break;
        } else if (ret == 2) {
            state_tmp_253 = 0xff00;
        } else if (ret == 3) {
            state_tmp_253 = 0x7020;
        } else {
            state_tmp_253 = 0x7010;
        }
        break;
    case 0x7010:
        MenuVoiceBankSet(0);
        state_tmp_253 = 0x7011;
        /* fallthrough */
    case 0x7011:
        if (TsSCFADE_Set(2, 0x1e, 0)) {
            return 0;
        }
        state_tmp_253 = 0x7020;
        /* fallthrough */
    case 0x7020:
        if (TsBGMLoadCheck()) {
            return 0;
        }
        TsMap_Flow(1, 0, 0);
        TsSCFADE_Set(1, 0xf, 0);
        break;
    case 0xff00:
        return P3MRET_REPLAY;
    }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsMakeUserWork);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSaveSuccessProc);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", MpSave_Flow);

static int MpCityHall_Flow(int flg, u_int tpad, u_int tpad2) {
    /* TODO: Fix names once made static. */
    /* sbss 399ae0 */ extern int state_tmp_270;
    /* sbss 399ae4 */ extern int waitTime_tmp_271;
    /* bss 1c77a88 */ extern MAPPOS MapCHall_tmp_272;
    /* sbss 399ae8 */ extern int scstate_tmp_273;
    /* sbss 399aec */ extern int scstPos_tmp_274;
    /* sbss 399af0 */ extern int curTag_tmp_275;
    /* sbss 399af4 */ extern int fphs_pos_tmp_276;
    /* sbss 399af8 */ extern u_int AnmBit_tmp_277;
    int chkType, chkMode;
    int bBroken;
    int ret;
    int anmno;
    int cmpmesNo;
    int isError;
    int ntag;

    if (flg == 1) {
        switch (tpad) {
        case 0:
            MNScene_DispSw(&MNS_StageMap, 0);
            MNScene_DispSw(&MNS_CityHall, 1);
            AnmBit_tmp_277 = MNScene_StartAnime(&MNS_CityHall, -1, CityHallAnime);
            TsCMPMes_SetMes(-1);
            MapCHall_tmp_272.pscene = &MNS_CityHall;
            MapCHall_tmp_272.panime = CityHallAnime;
            MapCHall_tmp_272.mnmap = mnmapCityHall;
            MpMapMenu_Flow(1, &MapCHall_tmp_272, 0);
            MapCHall_tmp_272.curPos = 0;
            waitTime_tmp_271 = 0;
            state_tmp_270 = 0;
            scstate_tmp_273 = 0;
            scstPos_tmp_274 = 0;
            MpCityHallCharPosSet(0);
            fphs_pos_tmp_276 = 0;
            MpCityHallFPHSSoundMask(0);
            TSSNDPLAY(0x8001);
            return 0;
        case 1:
            MNScene_DispSw(&MNS_StageMap, 0);
            MNScene_DispSw(&MNS_CityHall, 1);
            MapCHall_tmp_272.pscene = &MNS_CityHall;
            MapCHall_tmp_272.panime = CityHallAnime;
            MapCHall_tmp_272.mnmap = mnmapCityHall;
            MpMapMenu_Flow(1, &MapCHall_tmp_272, 0);
            MpMapMenu_Flow(3, &MapCHall_tmp_272, 2);
            TsCMPMes_SetMes(-1);
            scstate_tmp_273 = 0;
            state_tmp_270 = 0x100;
            scstPos_tmp_274 = 0;
            MpCityHallCharPosSet(2);
            fphs_pos_tmp_276 = 2;
            return 0;
        }
    }

    switch (scstate_tmp_273) {
    case 0:
        if (scstPos_tmp_274 != 0) {
            scstate_tmp_273 = 0x2100;
        }
        break;
    case 0x100:
        if (TsSCFADE_Set(2, 0xa, 1)) {
            break;
        }
        TsUserList_Flow(2, 0, 0);
        UserList_Sw = 0;
        MNScene_DispSw(&MNS_OptCounter, 0);
        OptionList_Sw = 0;
        scstate_tmp_273 = 0x110;
        /* fallthrough */
    case 0x110:
        MNScene_DispSw(&MNS_CityHall, 1);
        MpMapMenu_Flow(3, &MapCHall_tmp_272, MapCHall_tmp_272.curPos);
        MpCityHallCharPosSet(MapCHall_tmp_272.curPos);
        fphs_pos_tmp_276 = MapCHall_tmp_272.curPos;
        MpCityHallFPHSSoundMask(0);
        scstate_tmp_273 = 0x120;
        /* fallthrough */
    case 0x120:
        if (!TsSCFADE_Set(1, 0x14, 1)) {
            scstate_tmp_273 = 0;
        }
        break;
    case 0x2000:
        if (scstPos_tmp_274 == 0) {
            scstate_tmp_273 = 0x100;
        }
        break;
    case 0x2100:
        anmno = -1;
        cmpmesNo = -1;

        switch (MapCHall_tmp_272.curPos) {
        case 0:
            anmno = 3;
            cmpmesNo = MENU_LOGLOAD_CAM;
            MpCityHallFPHOK(0);
            break;
        case 2:
            anmno = 9;
            cmpmesNo = MENU_REPLOAD_CAM;
            MpCityHallFPHOK(1);
            break;
        case 1:
            anmno = 6;
            cmpmesNo = MENU_OPT_CAM;
            MpCityHallFPHOK(2);
            break;
        }

        AnmBit_tmp_277 = 0x80000000;
        if (anmno >= 0) {
            AnmBit_tmp_277 |= MNScene_StartAnime(&MNS_CityHall, -1, &CityHallAnime[anmno]);
        }

        MpCityHallFPHSSoundMask(1);
        TsCMPMes_SetMes(cmpmesNo);
        scstate_tmp_273 = 0x2200;
        /* fallthrough */
    case 0x2200:
        if (scstPos_tmp_274 == 0) {
            scstate_tmp_273 = 0x100;
        }
        if (!TsAnimeWait_withKeySkip(tpad, &MNS_CityHall, 0xa, AnmBit_tmp_277)) {
            scstate_tmp_273 = 0x2000;
        }
        break;
    }

    
    fphs_pos_tmp_276 = MpCityHallFPHSMove(MapCHall_tmp_272.curPos, fphs_pos_tmp_276);

    switch (state_tmp_270) {
    case 0:
        if (++waitTime_tmp_271 == 70) {
            TsCMPMes_SetMes(MENU_HALL_INSIDE);
            TSSNDPLAY(VSND_MENU1);
        }
        if (TsAnimeWait_withKeySkip(tpad, &MNS_CityHall, 0, -1)) {
            return 0;
        }
        TSSND_SKIPPLAY(VSND_MENU1);
        TsCMPMes_SetMes(MENU_HALL_INSIDE);
        MpMapMenu_Flow(3, &MapCHall_tmp_272, 0);
        state_tmp_270 = 0x100;
        /* fallthrough */
    case 0x100:
        ret = MpMapMenu_Flow(0, &MapCHall_tmp_272, tpad);
        if (MapCHall_tmp_272.anmStop != 0) {
            TSSND_SKIPSTOP(2);
        }
        if (MapCHall_tmp_272.anmtrg != 0) {
            MpCityHallParaStart(MapCHall_tmp_272.anmtrg);
        }
    
        switch (MapCHall_tmp_272.sndtrg) {
        case 1:
            TSSNDPLAY(VSND_MVCUS_LR);
            break;
        case 2:
            TSSNDPLAY(VSND_SELPOPUP);
            break;
        case 3:
            TSSNDPLAY(VSND_CANCEL);
            break;
        }
    
        if (ret != 0) {
            if (ret == 1) {
                switch (MapCHall_tmp_272.curPos) {
                case 0:
                    TSSNDSTOP(3);
                    TSSNDPLAY(VSND_MENU2);
                    break;
                case 2:
                    TSSNDSTOP(3);
                    TSSNDPLAY(VSND_MENU3);
                    break;
                case 1:
                    TSSNDSTOP(3);
                    TSSNDPLAY(VSND_MENU4);
                    break;
                }

                state_tmp_270 = 0x1000;
            }

            if (ret == -1) {
                state_tmp_270 = 0xf000;
            }

            return 0;
        }

        break;
    case 0x1000:
        if (MapCHall_tmp_272.curPos == 1) {
            state_tmp_270 = 0x1500;
            break;
        }
        McInitFlow();
        state_tmp_270 = 0x1010;
        /* fallthrough */
    case 0x1010:
        if (MapCHall_tmp_272.curPos == 0) {
            curTag_tmp_275 = 0;
            chkMode = 1;
            chkType = 3;
        } else {
            curTag_tmp_275 = 0;
            chkType = 1;
            chkMode = 2;
        }

        ret = McUserCheckFlow(chkType, chkMode, 0);
        if (ret == -2) {
            break;
        }
        if (ret > 0 && ret < 3) {
            state_tmp_270 = 0x5000;
            break;
        }
        state_tmp_270 = 0x1500;
        /* fallthrough */
    case 0x1500:
        scstPos_tmp_274 = 1;
    
        switch (MapCHall_tmp_272.curPos) {
        case 0:
        case 2:
            state_tmp_270 = 0x2000;
            break;
        case 1:
            state_tmp_270 = 0x3000;
            break;
        }
    
        break;
    case 0x2000:
        if (MapCHall_tmp_272.curPos == 0) {
            chkMode = 1;
            chkType = 3;
        } else {
            chkMode = 2;
            chkType = 1;
        }

        isError = 0;
        ret = McUserCheckFlow(chkType, chkMode, &isError);
        if (ret < 0) {
            if (isError == 1) {
                scstPos_tmp_274 = 0;
            }
            if (isError == 2) {
                scstPos_tmp_274 = 1;
                break;
            }
            return 0;
        }
        if (ret > 0 && ret < 3) {
            state_tmp_270 = 0x5000;
            break;
        }
        TsMCAMes_SetMes(-1);
        state_tmp_270 = 0x2020;
        break;
    case 0x2020:
        if (scstate_tmp_273 & 0xfff) {
            return 0;
        }
        state_tmp_270 = 0x2021;
        /* fallthrough */
    case 0x2021:
        if (UserList_Sw) {
            if (TsSCFADE_Set(2, 0x14, 0)) {
                return 0;
            }
        }
        TsMakeUserWork(1);
        state_tmp_270 = 0x2022;
        /* fallthrough */
    case 0x2022:
        if (MapCHall_tmp_272.curPos == 0) {
            if (UCheckLoadError != 0) {
                ntag = 1;
                curTag_tmp_275 = 1;
            } else {
                ntag = curTag_tmp_275;
            }
            TsUserList_SetType(&ULTypeT_CITY_STGCLR, pP3GameState->nMode, ntag);
        } else {
            TsUserList_SetType(&ULTypeT_CITY_REPLAY, pP3GameState->nMode, 0);
        }

        MNScene_End(&MNS_StageMap2);
        MNScene_Init(&MNS_StageMap2, &Scene_CityHall, 0);
        MNScene_CopyState(&MNS_StageMap2, &MNS_CityHall);
        MNScene_DispSw(&MNS_CityHall, 0);
        MNScene_DispSw(&MNS_StageMap2, 2);
        state_tmp_270 = 0x2024;
        /* fallthrough */
    case 0x2024:
        if (!UserList_Sw) {
            chkType = 5;
            TsSCFADE_Set(chkType, 0x14, 2);
        } else {
            chkType = 1;
            TsSCFADE_Set(chkType, 0x14, 0);
        }
        UserList_Sw = 1;
        state_tmp_270 = 0x2026;
        /* fallthrough */
    case 0x2026:
        if (TsSCFADE_Set(0, 0, 0) >= 9) {
            break;
        }
        MNScene_DispSw(&MNS_CityHall, 0);
        MNScene_DispSw(&MNS_StageMap2, 0);
        MNScene_End(&MNS_StageMap2);
        state_tmp_270 = 0x2028;
        /* fallthrough */
    case 0x2028:
        ret = TsUserList_Flow(0, tpad, tpad2);

        if (ret != 0) {
            switch (ret) {
            case -1:
                state_tmp_270 = 0x5000;
                break;
            case 1:
                if (TsUserList_IsGetFileSave()) {
                    state_tmp_270 = 0x2830;
                } else {
                    state_tmp_270 = 0x2030;
                }
                break;
            case -3:
                if (TsUserList_IsGetFileSave()) {
                    curTag_tmp_275 = 1;
                } else {
                    curTag_tmp_275 = 0;
                }

                McInitFlow();
                state_tmp_270 = 0x2000;
                break;
            }

            McInitFlow();
            return 0;
        }

        break;
    case 0x2030:
        if (MapCHall_tmp_272.curPos == 0) {
            chkMode = 1;
        } else {
            chkMode = 2;
        }

        ret = McUserLoadFlow(TsUserList_GetCurFileNo(&bBroken), chkMode, bBroken);
        if (ret < 0) {
            return 0;
        }

        waitTime_tmp_271 = 0;
        if (ret != 0) {
            if (ret == 1) {
                state_tmp_270 = 0x2028;
            }
            if (ret == 2) {
                state_tmp_270 = 0x2050;
            }
            if (ret != 4) {
                return 0;
            }
            McInitFlow();
            state_tmp_270 = 0x2000;
            break;
        }

        TsCMPMes_SetMes(-1);
        state_tmp_270 = 0x2040;
        /* fallthrough */
    case 0x2040:
        if (++waitTime_tmp_271 >= 35) {
            waitTime_tmp_271 = 0;
            TsSet_ParappaCapColor();
            if (MapCHall_tmp_272.curPos == 2) {
                state_tmp_270 = 0xf010;
            } else {
                state_tmp_270 = 0xef00;
            }
        }
        break;
    case 0x2830:
        UserWork->fileNo = TsUserList_GetCurFileNo(NULL);
        state_tmp_270 = 0x2840;
        /* fallthrough */
    case 0x2840:
        ret = McUserSaveFlow(UserWork);
        if (ret < 0) {
            TsUserList_SetCurDispUserData(UserWork);
            return 0;
        }
        if (ret != 0) {
            if (ret == 1) {
                state_tmp_270 = 0x2020;
            }
            if (ret == 2) {
                state_tmp_270 = 0x2900;
            }
            if (ret == 4) {
                McInitFlow();
                state_tmp_270 = 0x2000;
                break;
            }
            return 0;
        }
        /* fallthrough */
    case 0x2850:
        TsSaveSuccessProc();
        waitTime_tmp_271 = 0;
        state_tmp_270 = 0x2860;
        /* fallthrough */
    case 0x2860:
        TsCMPMes_SetMes(-1);
        if (++waitTime_tmp_271 >= 35) {
            waitTime_tmp_271 = 0;
            state_tmp_270 = 0x2900;
        } else {
            break;
        }
        /* fallthrough */
    case 0x2050:
    case 0x2900:
        state_tmp_270 = 0x5000;
        break;
    case 0x3000:
        if (scstate_tmp_273 & 0xfff) {
            return 0;
        }
        OptionList_Sw = 1;
        TsOption_Flow(1, tpad);
        MNScene_End(&MNS_StageMap2);
        MNScene_Init(&MNS_StageMap2, &Scene_CityHall, 0);
        MNScene_CopyState(&MNS_StageMap2, &MNS_CityHall);
        MNScene_DispSw(&MNS_CityHall, 0);
        MNScene_DispSw(&MNS_StageMap2, 2);
        MNScene_DispSw(&MNS_OptCounter, 1);
        state_tmp_270 = 0x3005;
        /* fallthrough */
    case 0x3005:
        if (TsSCFADE_Set(5, 0x14, 2)) {
            return 0;
        }
        MNScene_DispSw(&MNS_CityHall, 0);
        MNScene_DispSw(&MNS_StageMap2, 0);
        MNScene_End(&MNS_StageMap2);
        state_tmp_270 = 0x3010;
        /* fallthrough */
    case 0x3010:
        ret = TsOption_Flow(0, tpad);
        if (ret != 0) {
            if (ret == -1) {
                state_tmp_270 = 0x3f00;
            }
            if (ret == 1) {
                state_tmp_270 = 0x3f00;
            }
            return 0;
        }
        break;
    case 0x3f00:
        state_tmp_270 = 0x5000;
        /* fallthrough */
    case 0x5000:
        scstPos_tmp_274 = 0;
        state_tmp_270 = 0x5008;
        break;
    case 0x5008:
        if (scstate_tmp_273 & 0xfff) {
            return 0;
        }
        state_tmp_270 = 0x100;
        break;
    case 0xef00:
        TSSNDSTOP(3);
        MenuVoiceBankSet(0);
        state_tmp_270 = 0xef10;
        /* fallthrough */
    case 0xef10:
        if (TsSCFADE_Set(2, 0x14, 1)) {
            return 0;
        }
        TsUserList_Flow(2, 0, 0);
        UserList_Sw = 0;
        MNScene_DispSw(&MNS_OptCounter, 0);
        OptionList_Sw = 0;
        TSSNDSTOP(3);
        return 3;
    case 0xf000:
        TSSNDSTOP(3);
        return 1;
    case 0xf010:
        TSSNDSTOP(3);
        scstPos_tmp_274 = 0;
        state_tmp_270 = 0xf014;
        break;
    case 0xf014:
        TsCMPMes_SetMes(-1);
        if (scstate_tmp_273 & 0xfff) {
            return 0;
        }
        TsBGMStop(12);
        _MNwaitTime = 10;
        state_tmp_270 = 0xf018;
        /* fallthrough */
    case 0xf018:
        if (--_MNwaitTime <= 0) {
            TSSNDSTOP(3);
            return 2;
        }
        break;
    }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", MpCityHallParaStart);

static void MpCityHallFPHSSoundMask(int flg) {
    TSSNDMASK_CHAN(3, flg);
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", MpCityHallFPHSMove);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", MpCityHallFPHOK);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", MpCityHallCharPosSet);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", MpPopMenu_Flow);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", MpMapMenu_Flow);

static int _MapGetMovableDir(MAPPOS *mpw) {
    int       posNo, ret, DirMask;
    MNMAPPOS *mpos;
    int       flg, i;

    DirMask = 1;
    mpos = &mpw->mnmap[mpw->curPos];

    ret = 0;

    for (i = 0; i < PR_ARRAYSIZE(mpos->mapdir); i++, DirMask <<= 1) {
        flg = TRUE;
        posNo = mpos->mapdir[i].mapNo;

        if (posNo == -1) {
            flg = FALSE;
        } else {
            posNo &= ~0x8000;
            if (mpw->lmtPos != 0) {
                if (posNo >= mpw->lmtPos) {
                    flg = FALSE;
                } else {
                    if (mpos->mapdir[i].mapNo & 0x8000) {
                        if (mpw->curPos == (mpw->lmtPos - 1) || posNo == (mpw->lmtPos - 1)) {
                            flg = FALSE;
                        }
                    }
                }
            }
        }

        if (flg) {
            ret |= DirMask;
        }
    }

    return ret;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", McErrorMess);

static void McInitFlow(void) {
    subStatus = 0;
    ret       = 0;
    errorNo   = 0;
    waitTime  = 0;
}

#ifndef NON_MATCHING /* .rodata JPT */
INCLUDE_ASM("asm/nonmatchings/menu/menusub", McStartCheckFlow);
#else
static int McStartCheckFlow(/* a0 4 */ int flg) {
    /* v1 3 */ int ret;

    if (flg == 1) {
        McInitFlow();
        P3MC_OpeningCheckStart();
        return 0;
    }

    if (flg == 2) {
        P3MC_OpeningCheckEnd();
        return 0;
    }

    switch (subStatus) {
    case 0:
        subStatus = 1;
        break;
    case 1:
        ret = P3MC_OpeningCheck();
        if (ret >= 0) {
            if (ret & 1) {
                ret = 0;
            } else {
                ret = 1;
            }
        }

        switch (ret) {
        case -2:
            subStatus = 0x100;
            break;
        case 0:
            subStatus = 0x100;
            break;
        case 1:
            subStatus = 0x10;
            break;
        case -3:
            subStatus = 0x20;
            break;
        }
    
        break;
    case 0x10:
        ret = P3MC_OpeningCheck();
        if (ret >= 0) {
            ret = (ret & 0x1) ^ 0x1;
        }

        switch (ret) {
        case -3:
            subStatus = 0x20;
            break;
        case -2:
        case 0:
            subStatus = 0x100;
            break;
        case -1:
        case 1:
        default:
            break;
        }

        break;
    case 0x20:
        ret = P3MC_OpeningCheck();
        if (ret >= 0) {
            ret = (ret & 0x1) ^ 0x1;
        }

        switch (ret) {
        case -2:
        case 0:
            subStatus = 0x100;
            break;
        case 1:
            subStatus = 0x10;
            break;
        case -3:
        case -1:
        default:
            break;
        }

        break;
    case 0x100:
        return 0;
    }

    switch (subStatus) {
    case 0x10:
        return 1;
    case 0x20:
        return 2;
    }

    return -1;
}
#endif

INCLUDE_ASM("asm/nonmatchings/menu/menusub", McUserCheckFlow);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", McUserSaveFlow);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", McUserLoadFlow);

static void TsMCAMes_Init(void) {
    memset(&MCMesWork, 0, sizeof(MCMesWork));
    MCMesWork.mesflg = -1;
}

static int TsMCAMes_GetSelect(void) {
    MCMES_WORK *pmesw = &MCMesWork;

    if (pmesw->mesflg < 0) {
        return 1;
    } else if (pmesw->mesflg & 0xff000000) {
        return pmesw->selflg;
    }

    return 1;
}

static int TsMCAMes_IsON(void) {
    MCMES_WORK *pmesw = &MCMesWork;
    return (u_int)~pmesw->mesflg >> 0x1f;
}

void TsMCAMes_SetPos(int x, int y) {
    MCMES_WORK *pmesw = &MCMesWork;

    pmesw->px = x;
    pmesw->py = y;
}

void TsMCAMes_SetMes(int no) {
    MCMES_WORK *pmesw;
    int         i;

    pmesw = &MCMesWork;

    if (no < 0) {
        pmesw->mesflg = -1;
        pmesw->selflg = 0;
        pmesw->seltim = 0;
        pmesw->line = 0;
        pmesw->btflg = 0;
        pmesw->backSw = 0;
        pmesw->faceNo = 0;
        return;
    }

    if (pmesw->mesflg != no) {
        if (TSSND_CHANISSTOP(2)) {
            for (i = 0; i < PR_ARRAYSIZEU(McVoiceTbl); i++) {
                if (McVoiceTbl[i].mesNo == no) {
                    TSSNDPLAY(McVoiceTbl[i].dataNo);
                    break;
                }
            }
        }
    }

    pmesw->mesflg = no;
    pmesw->faceNo = 0;

    for (i = 0; i < PR_ARRAYSIZEU(McFaceTbl); i++) {
        if (McFaceTbl[i].mesNo == no) {
            pmesw->faceNo = McFaceTbl[i].dataNo;
            break;
        }
    }

    if (no & 0x10000) {
        pmesw->backSw = 0;
        pmesw->btflg = 0;
    } else {
        pmesw->backSw = 1;
        pmesw->btflg = 1;
    }

    if (no & 0x20000) {
        pmesw->color = 1;
    } else {
        pmesw->color = 0;
    }

    pmesw->selflg = 0;
    pmesw->seltim = 0;
    pmesw->line = _PkMCMsgGetLine(pmesw->mesflg & 0xffff);
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsMCAMes_Flow);
#else /* Needs .sdata match */
static void TsMCAMes_Flow(u_int tpad) {
    MCMES_WORK *pmesw;
    int         cLine;
    float       fRate;
    int         isOK, isCAN;

    pmesw = &MCMesWork;
    if (pmesw->backSw && pmesw->mesflg >= 0) {
        cLine = pmesw->line;
        if (cLine == 1) {
            cLine = 2;
        }

        cLine *= 4096;
        if (pmesw->D0line == 0) {
            pmesw->Dline = pmesw->D0line = cLine;
        } else {
            pmesw->Dline = pmesw->D0line = TSNumMov(pmesw->D0line, cLine, 4);
        }

        fRate = (MNSceneGetMusicFitTimer() % 72) / 72.0f;
        fRate *= 6.2831855f;
        fRate = cosf(fRate);
        fRate = ((fRate * fRate) * 1228.8f);
        pmesw->Dline += (int)fRate;
    } else {
        pmesw->D0line = 0;
        pmesw->Dline = 0;
    }

    if (pmesw->btflg != 0) {
        if (pmesw->btton < 0x40) {
            pmesw->btton += 7;
            if (pmesw->btton > 0x40) {
                pmesw->btton = 0x40;
            }
        }
    } else {
        if (pmesw->btton > 0) {
            pmesw->btton -= 7;
            if (pmesw->btton < 0) {
                pmesw->btton = 0;
            }
        }
    }

    if (pmesw->mesflg >= 0 && (pmesw->mesflg & 0xff000000)) {
        if (pmesw->mesflg & 0xc000000) {
            if (!TSSND_CHANISSTOP(1)) {
                pmesw->seltim++;
                return;
            }
        }

        if (pmesw->mesflg & 0x2000000) {
            isCAN = TRUE;
        } else {
            isCAN = FALSE;
        }
    
        if (pmesw->mesflg & 0x1000000) {
            isOK = TRUE;
        } else {
            isOK = FALSE;
        }
        
        if (pmesw->mesflg & 0x14000000) {
            isOK = TRUE;
            isCAN = TRUE;
        }
    
        if (isOK && (tpad & 0x20)) {
            pmesw->selflg = 1;
            TSSNDPLAY(6);
        }
    
        if (isCAN && (tpad & 0x40)) {
            pmesw->selflg = 2;
            if (pmesw->mesflg & 0x4000000) {
                TSSNDPLAY(6);
            } else {
                TSSNDPLAY(9);
            }
        }
    
        if (pmesw->mesflg & 0xc000000) {
            pmesw->seltim++;
            if (pmesw->seltim >= 0x79) {
                pmesw->selflg = 1;
            }
        }
    }
}
#endif

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsMCAMes_Draw);

void TsCMPMes_SetPos(int x, int y) {
    CMPMES_WORK *pmesw = &CmpMesWork;
    pmesw->px = x;
    pmesw->py = y;
}

void TsCMPMes_SetMes(int no) {
    CMPMES_WORK *pmesw = &CmpMesWork;

    if (no < 0) {
        pmesw->mesflg = -1;
        pmesw->backSw = 0;

        pmesw->wh = 0;
        pmesw->ww = 0;
    } else {
        pmesw->mesflg = no;
        pmesw->backSw = 1;

        pmesw->ww = 600;
        pmesw->wh = 26;
    }
}

void TsCMPMes_Draw(SPR_PKT pk, SPR_PRM *spr) {
    CMPMES_WORK *pmesw = &CmpMesWork;

    if (pmesw->backSw) {
        MNScene_DispSw(&MNS_JimakuBak, 1);
        MNScene_Draw(&MNS_JimakuBak);
    } else {
        MNScene_DispSw(&MNS_JimakuBak, 0);
    }

    if ((u_int)pmesw->mesflg >= 0x1000) {
        return;
    }

    _PkSubMsgPut(pk, spr, pmesw->mesflg & 0xffff, pmesw->px, pmesw->py, 0x807f7f7f);
}

void TsANIME_Init(ANIME_WK *wk) {
    memset(wk, 0, sizeof(*wk));
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsANIME_Poll);

static void TsANIME_Start(ANIME_WK *wk, int state, int tim) {
    wk->atrn2 = 0x200;
    wk->atrn  = 0x200;
    wk->atrn3 = 0x200;

    wk->atim = tim;
    wk->aflg = state;
}

static int TsANIME_GetRate(ANIME_WK *wk, float *rt0, float *rt1, float *rt2) {
    float p0, p1, p2;

    if (wk->aflg) {
        p0 = wk->atrn  * 0.001953125f;
        p1 = wk->atrn2 * 0.001953125f;
        p2 = wk->atrn3 * 0.001953125f;

        if (!(wk->aflg & 1)) {
            p0 = 1.0f - p0;
            p1 = 1.0f - p1;
        } else {
            p2 = 1.0f - p2;
        }

        if (rt0 != NULL) {
            *rt0 = p0;
        }
        if (rt1 != NULL) {
            *rt1 = p1;
        }
        if (rt2 != NULL) {
            *rt2 = p2;
        }

        return 1;
    } else {
        if (rt0 != NULL) {
            *rt0 = 1.0f;
        }
        if (rt1 != NULL) {
            *rt1 = 1.0f;
        }
        if (rt2 != NULL) {
            *rt2 = 1.0f;
        }

        return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", _TsSortSetRanking);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsGetRankingList);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsPopCusAOff);

void TsPopCusDim(POPCTIM *pfw, int n, int flg) {
    if ((u_int)n < 16) {
        pfw->bDim[n] = (u_short)flg;
    }
}

void TsPopCusInit(POPCTIM *pfw,  int curIdx) {
    memset(pfw, 0, sizeof(*pfw));
    pfw->onTNo = curIdx;
}

void TsPopCusFlow(POPCTIM *pfw) {
    int i;

    if (pfw->okTim != 0) {
        pfw->okTim--;
    }
    if (pfw->onTim != 0) {
        pfw->onTim--;
    }
    if (pfw->srTim != 0) {
        pfw->srTim--;
    }

    for (i = 0; i < PR_ARRAYSIZE(pfw->offinf); i++) {
        if (pfw->offinf[i].time) {
            pfw->offinf[i].time--;
        }
        if (pfw->offinf[i].cltm) {
            pfw->offinf[i].cltm--;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsPopCusPut);

int TsPUPCheckMove(int nbtn, int bank, POPCTIM *pfw) {
    return (pfw->bDim[POPBtn2Sel[(bank != 0) ? (nbtn + 3) : (nbtn + 0)]] == FALSE);
}

INCLUDE_RODATA("asm/nonmatchings/menu/menusub", D_00396068);

INCLUDE_RODATA("asm/nonmatchings/menu/menusub", D_00396070);

INCLUDE_RODATA("asm/nonmatchings/menu/menusub", D_00396078);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsPopMenu_Flow);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsPopMenu_Draw);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsPopMenCus_Draw);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSaveMenu_Flow);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSaveMenu_Draw);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TSJukeCDObj_Init);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", _TsJkJacketPut);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", _TsJkRecordPut);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TSJukeCDObj_Draw);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsJukeIsObjAnime);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsJukeObjAnime);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsJukeObjAnime2);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", _TsJKMoveCus);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", _TsJKSetPadArrow);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsJukeMenu_Flow);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsJukeMenu_Draw);

static void TsCmnCell_CusorSET(CELLOBJ *obj) {
    obj->state = 0;
    obj->flg = 1;
    obj->ton = 0x80;
}

static void TsCmnCell_CusorON(CELLOBJ *obj) {
    obj->state = 1;
    obj->flg = 0;
    obj->tim = 0x10;
}

static void TsCmnCell_CusorOFF(CELLOBJ *obj) {
    obj->state = 2;
    obj->flg = 1;
    obj->tim = 0x10;
}

static void TsCmnCell_CusorSEL(CELLOBJ *obj) {
    obj->state = 3;
    obj->flg = 1;
    obj->tim = 0x18;
}

static void TsCmnCell_CusorMASK(CELLOBJ *obj) {
    obj->state = 0;
    obj->flg = 0xffff;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsCmnCell_CusorDraw);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsOption_Flow);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsOption_Draw);

static int TsUserList_GetCurFileNo(int *isBroken) {
    USERLIST_MENU *pfw   = &UserListMenu;
    USER_DATA     *puser = pfw->pusrlst->pUserTbl[pfw->curuser + pfw->curPageTop];

    if (isBroken != NULL) {
        *isBroken = (puser->flg == 2);
    }

    return puser->fileNo;
}

static int TsUserList_IsGetFileSave(void) {
    USERLIST_MENU *pfw = &UserListMenu;
    return pfw->isSave;
}

static int TsUserList_SortUser(void) {
    USERLIST_MENU *pfw;
    int            i, maxn;

    pfw = &UserListMenu;
    pfw->pusrdspWk = UserDispWork;
    memset(pfw->pusrdspWk, 0, sizeof(*pfw->pusrdspWk));

    if (pfw->pusrlst == NULL) {
        return 0;
    }

    maxn = P3MC_SortUser(pfw->pusrlst, pfw->dataMode, pfw->isSave);
    for (i = 0; i < maxn; i++) {
        *(pfw->pusrdspWk->pUserDisp + i) = *pfw->pusrlst->pUserTbl[i];
    }

    return maxn;
}

static void TsUserList_SetCurUserData(USER_DATA *psrc) {
    USERLIST_MENU *pfw = &UserListMenu;
    USER_DATA     *puser;

    if (pfw->pusrlst == NULL) {
        return;
    }

    puser = pfw->pusrlst->pUserTbl[pfw->curuser + pfw->curPageTop];
    if (puser->flg == 0) {
        P3MC_AddUser(pfw->pusrlst, pfw->dataMode, psrc);
    } else {
        *puser = *psrc;
    }
}

static void TsUserList_SetCurDispUserData(USER_DATA *psrc) {
    USERLIST_MENU *pfw = &UserListMenu;

    *(pfw->pusrdspWk->pUserDisp + (pfw->curuser + pfw->curPageTop)) = *psrc;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsUserList_SetCurFileNoCusor);

static void TsUserList_SetType(USERLISTTYPE_TABLE *ptbl, int mode, int curTag) {
    USERLIST_MENU *pfw = &UserListMenu;

    TsUserList_Flow(1, 0, 0);

    pfw->ptypttbl = ptbl;
    pfw->gameMode = mode;

    TsUserList_Flow(3, curTag, 0);
}

static int TsUserList_TagChangeAble(USERLIST_MENU *pfw, int *pno) {
    int flg, no;

    no = *pno;
    if (no < 0) {
        no = 0;
    }
    if (no >= pfw->ptypttbl->nType) {
        no = (pfw->ptypttbl->nType - 1);
    }

    if (UserListTbl[pfw->ptypttbl->typeNo[no]].isSave) {
        flg = UCheckSaveError;
    } else {
        flg = UCheckLoadError;
    }

    if (flg != 0) {
        *pno = no;
    }

    return flg;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsUserList_SetCurTag);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsUserList_Flow);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsUserList_Draw);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", NameSpaceCut);

INCLUDE_RODATA("asm/nonmatchings/menu/menusub", D_00396120);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsUser_PanelDraw);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsNAMEINBox_SetName);

static void TsNAMEINBox_GetName(NAMEINW *pfw, u_char *name) {
    u_short *pcode = pfw->curnchr;
    int      i;

    for (i = 0; i < PR_ARRAYSIZE(pfw->curnchr); i++, pcode++) {
        *name++ = UserName_CharSet[(*pcode / 4096)].ptbl[*pcode & 0xfff];
    }

    *name = '\0';
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsNAMEINBox_Flow);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsNAMEINBox_Draw);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSCFADE_Set);

static void TsSCFADE_Flow(int flg, int prm) {
    SCFADE *pfw = &ScFade;

    if (flg == 1 || flg == 3) {
        memset(pfw, 0, sizeof(*pfw));
        if (flg == 3) {
            pfw->ton = prm;
        }
        return;
    }

    if (pfw->ttim0 != 0) {
        pfw->ttim++;
    }

    switch (pfw->state) {
    case 1:
    case 5:
        pfw->ton = 256 - ((pfw->ttim * 256) / pfw->ttim0);
        if (pfw->ton <= 0) {
            TsSCFADE_Flow(1, 0);
        }
        break;
    case 2:
    case 6:
        pfw->ton = (pfw->ttim * 256) / pfw->ttim0;
        if (pfw->ton >= 256) {
            TsSCFADE_Flow(3, 256);
        }
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSCFADE_Draw);

void _PkMCMsgPut(SPR_PKT pk, SPR_PRM *spr, int id, int x, int y, u_int abgr) {
    int flg;

    if (pP3GameState != NULL) {
        flg = pP3GameState->pGameStatus->language_type;
    } else {
        flg = LANG_JAPANESE;
    }

    MENUSubtPut(pk, spr, x, y, abgr, 1, MenuMsgGetMessageMc(id, flg), flg);
}

int _PkMCMsgGetLine(int id) {
    int flg;

    if (pP3GameState != NULL) {
        flg = pP3GameState->pGameStatus->language_type;
    } else {
        flg = LANG_JAPANESE;
    }

    return MENUSubtGetLine(MenuMsgGetMessageMc(id, flg), flg);
}

void _PkSubMsgPut(SPR_PKT pk, SPR_PRM *spr, int id, int x, int y, u_int abgr) {
    int flg;

    if (pP3GameState != NULL) {
        flg = pP3GameState->pGameStatus->language_type;
    } else {
        flg = LANG_JAPANESE;
    }

    MENUSubtPut(pk, spr, x, y, abgr, 1, MenuMsgGetMessageSub(id, flg), flg);
}

void TsMenu_CleanVram(int nFrm) {
    SPR_PRM        SprPrm;
    u_long128     *pkt;
    SPR_PKT        pk;
    sceGsDrawEnv1 *pdenv;

    pk = &pkt;

    pdenv = DrawGetDrawEnvP(nFrm);
    if (pdenv != NULL) {
        MnLPkt.ptop = PR_UNCACHED(MnLPkt.pkt[MnLPkt.idx].PaketTop);
        pkt = (u_long128*)MnLPkt.ptop;

        PkSprPkt_SetDefault(pk, &SprPrm, pdenv);
        PkSprPkt_SetDrawEnv(pk, &SprPrm, pdenv);
        PkZBUFMask_Add(pk, FALSE);

        SprPrm.zdepth = 0;
        SprPrm.rgba0 = 0x80000000;
    
        SetSprScreenXYWH(&SprPrm);
        PkCRect_Add(pk, &SprPrm, 0);

        PkSprPkt_SetDrawEnv(pk, &SprPrm, DrawGetDrawEnvP(DNUM_DRAW));
        PkZBUFMask_Add(pk, TRUE);

        MnLPkt.ptop = (u_int)pkt;
        sceGsSyncPath(0, 0);

        TsDrawUPacket(&MnLPkt);
        sceGsSyncPath(0, 0);
    }
}

void TsMenu_CaptureVram(SPR_PKT pk, SPR_PRM *spr) {
    PkSprPkt_SetDrawEnv(pk, spr, DrawGetDrawEnvP(DNUM_VRAM2));
    PkSprPkt_SetTexVram(pk, spr, DrawGetDrawEnvP(DNUM_DRAW));

    PkTEX1_Add(pk, SCE_GS_SET_TEX1(0, 0, 0, 0, 0, 0, 0));
    PkALPHA_Add(pk, SCE_GS_SET_ALPHA(2, 2, 0, 0, 0));

    spr->zy = 1.0f;
    spr->zx = 1.0f;
    spr->zdepth = 0;
    spr->rgba0 = SCE_GS_SET_RGBAQ(128, 128, 128, 128, 0);

    SetSprScreenXYWH(spr);
    spr->ux = spr->px;
    spr->uy = spr->py;
    spr->uw = spr->sw;
    spr->uh = spr->sh;

    PkNSprite_AddAdj(pk, spr, 1);
    PkTEX1_Add(pk, 0x2020);

    PkSprPkt_SetDrawEnv(pk, spr, DrawGetDrawEnvP(DNUM_DRAW));
    PkSprPkt_SetTexVram(pk, spr, DrawGetDrawEnvP(DNUM_VRAM2));

    PkALPHA_Add(pk, SCE_GS_SET_ALPHA(0, 1, 0, 1, 0));
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSetCTransSpr);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSetSLTransSpr);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsSetPNTransSpr);

static void TsPatTexFnc(int flg) {
    _TexFunc = flg;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", _TsPatSetPrm);

static void TsPatPut(SPR_PKT pk, SPR_PRM *spr, PATPOS *ppos, int ox, int oy) {
    _TsPatSetPrm(pk, spr, ppos, ox, oy);
    PkNSprite_Add(pk, spr, 3);
}

static void TsPatGetSize(PATPOS *ppos, int *x, int *y, int *w, int *h) {
    TSTEX_INF *ptex = &tblTex[ppos->texNo];

    if (w != NULL) {
        *w = ptex->w;
    }
    if (h != NULL) {
        *h = ptex->h;
    }
    if (x != NULL) {
        *x = ppos->x + (ptex->w / 2);
    }
    if (y != NULL) {
        *y = ppos->y + (ptex->h / 2);
    }
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsPatPutRZoom);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsPatPutMZoom);

static void TsPatPutSwing(SPR_PKT pk, SPR_PRM *spr, PATPOS *ppos, int ox, int oy, int mx, int my, float Crx) {
    _TsPatSetPrm(pk, spr, ppos, ox, oy);
    TsSetSLTransSpr(pk, spr, mx,my, Crx);
}

static void TsPatPutUneri(SPR_PKT pk, SPR_PRM *spr, PATPOS *ppos, int ox, int oy, int mx, int my, float Crx, float Drt) {
    _TsPatSetPrm(pk, spr, ppos, ox, oy);
    TsSetPNTransSpr(pk, spr, mx, my, Crx, Drt);
}

static void TsCELBackInit(void) {
    int        i, l;
    HOSI_TYPE *type;
    int        num;

    type = hTypeTable;
    num  = 0;
    for (l = 0; l < PR_ARRAYSIZEU(hTypeTable); l++, type++) {
        num += type->num;
    }

    if (HOSIObj != NULL) {
        free(HOSIObj);
        HOSIObj = NULL;
    }

    if (num != 0) {
        HOSIObj = malloc(num * sizeof(HOSI_TYPE));
    } else {
        HOSIObj = NULL;
    }

    if (HOSIObj != NULL) {
        HOSI_OBJ *obj;
        memset(HOSIObj, 0, num * sizeof(HOSI_TYPE));

        type = hTypeTable;
        obj  = HOSIObj;

        for (l = 0; l < PR_ARRAYSIZEU(hTypeTable); l++, type++) {
            for (i = 0; i < type->num; i++, obj++) {
                obj->wtim = (rand() % (type->dispTime >> 3)) * 2;
            }
        }
    }
}

void TsCELBackEnd(void) {
    if (HOSIObj != NULL) {
        free(HOSIObj);
        HOSIObj = NULL;
    }
}

int TsCELBackDraw(TsUSERPKT *UPacket, SPR_PRM *spr, int dispSw, int colNo) {
    u_int      bkabgr;
    u_int     *colTbl;
    u_long128 *pkt;
    SPR_PKT    pk;
    int        bDrawVram;

    pk = &pkt;

    if (dispSw != 0 && (colNo >= 0 && colNo < 3)) {
        if (HOSIObj == NULL) {
            TsCELBackInit();
            if (HOSIObj == NULL) {
                return 0;
            }
        }
    } else {
        return 0;
    }

    bDrawVram = (dispSw ^ 0x1);
    bDrawVram &= 1;

    (u_int)pkt = UPacket->ptop = PR_UNCACHED(UPacket->pkt[UPacket->idx].PaketTop);
    PkSprPkt_SetDefault(pk, spr, DrawGetDrawEnvP((bDrawVram) ? DNUM_VRAM2 : DNUM_DRAW));

    if (bDrawVram) {
        PkSprPkt_SetDrawEnv(pk, spr, DrawGetDrawEnvP(DNUM_VRAM2));
    }

    colTbl = HosiColor[colNo];
    bkabgr = colTbl[0];
    PkALPHA_Add(pk, 0x44);

    spr->zx = spr->zy = 1.0f;
    SetSprScreenXYWH(spr);
    spr->rgba0 = bkabgr;

    PkCRect_Add(pk, spr, 0);
    _TsCELBackObjDraw(pk, spr, spr->sw, spr->sh, colTbl);

    if (bDrawVram) {
        PkSprPkt_SetDrawEnv(pk, spr, DrawGetDrawEnvP(DNUM_DRAW));
    }

    UPacket->ptop = (u_int)pkt;
    sceGsSyncPath(0, 0);
    TsDrawUPacket(UPacket);
    sceGsSyncPath(0, 0);

    return 1;
}

INCLUDE_ASM("asm/nonmatchings/menu/menusub", _TsCELBackObjDraw);

INCLUDE_ASM("asm/nonmatchings/menu/menusub", TsHosiPut);

INCLUDE_RODATA("asm/nonmatchings/menu/menusub", D_00396168);

INCLUDE_RODATA("asm/nonmatchings/menu/menusub", D_00396170);
