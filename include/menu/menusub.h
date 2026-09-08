#ifndef MENUSUB_H
#define MENUSUB_H

#include "common.h"

#include "menu/menu.h"
#include "menu/menu_mdl.h"
#include "menu/p3mc.h"
#include "menu/pksprite.h"

#include <eetypes.h>

typedef struct { // 0x18
    /* 0x00 */ int wtim;
    /* 0x04 */ short tim;
    /* 0x06 */ short dir;
    /* 0x08 */ float px;
    /* 0x0c */ float py;
    /* 0x10 */ float vx;
    /* 0x14 */ float vy;
} HOSI_OBJ;

typedef struct { // 0x18
    /* 0x00 */ int num;
    /* 0x04 */ u_int patNo;
    /* 0x08 */ int patW;
    /* 0x0c */ int dispTime;
    /* 0x10 */ u_int colIdx;
    /* 0x14 */ u_int rate;
} HOSI_TYPE;

typedef struct { // 0x4
    /* 0x0 */ u_short state;
    /* 0x2 */ u_short time;
} TSREPPAD;

typedef struct { // 0x4
    /* 0x0 */ short x;
    /* 0x2 */ short y;
} PTPOS;

typedef struct { // 0xc
    /* 0x0 */ int texNo;
    /* 0x4 */ short x;
    /* 0x6 */ short y;
    /* 0x8 */ short w;
    /* 0xa */ short h;
} PATPOS;

typedef struct { // 0x4
    /* 0x0 */ u_short fno;
    /* 0x2 */ u_short flg;
} TSTEX_TBL;

typedef struct { // 0x18
    /* 0x00 */ u_long tex0;
    /* 0x08 */ float rUsize;
    /* 0x0c */ float rVsize;
    /* 0x10 */ u_int w;
    /* 0x14 */ u_int h;
} TSTEX_INF;

typedef struct { // 0x8
    /* 0x0 */ u_char *ptbl;
    /* 0x4 */ int len;
} USERNAME_CSET;

typedef struct { // 0xc
    /* 0x0 */ u_short chan;
    /* 0x2 */ u_short tapNo;
    /* 0x4 */ int lpTimeF;
    /* 0x8 */ int lpTime;
} MAPBGM;

typedef struct { // 0x8
    /* 0x0 */ u_short chanNo;
    /* 0x2 */ u_short vsetNo;
    /* 0x4 */ u_short ontim;
    /* 0x6 */ u_short offtim;
} TSVOICE_TBL;

enum {
    VSND_MVCUS_L = 0,
    VSND_MVCUS_R = 1,
    VSND_MVCUS_LR = 2,
    VSND_MVCUS_U = 3,
    VSND_MVCUS_D = 4,
    VSND_MVCUS_UD = 5,
    VSND_SELPOPUP = 6,
    VSND_SELMODE = 7,
    VSND_GO_GAME = 8,
    VSND_CANCEL = 9,
    VSND_CHALL_MOVE = 10,
    VSND_CHALL_PHFSMOVE = 11,
    VSND_PARAMOVE = 12,
    VSND_MC_FORMAT1 = 13,
    VSND_MC_FORMAT2 = 14,
    VSND_MC_FORMAT3 = 15,
    VSND_MC_SAVE1 = 16,
    VSND_MC_SAVE2 = 17,
    VSND_MC_SAVE3 = 18,
    VSND_MC_SAVE4 = 19,
    VSND_MC_ALERT1 = 20,
    VSND_MC_ALERT2 = 21,
    VSND_MC_CHECK1 = 22,
    VSND_MC_CHECK2 = 23,
    VSND_BGM_MOVEEND = 24,
    VSND_BGM_MOVE = 25,
    VSND_BGM_CHALL = 26,
    VSND_BGM_ST1 = 27,
    VSND_BGM_ST2 = 28,
    VSND_BGM_ST3 = 29,
    VSND_BGM_ST4 = 30,
    VSND_BGM_ST5 = 31,
    VSND_BGM_ST6 = 32,
    VSND_BGM_ST7 = 33,
    VSND_BGM_ST8 = 34,
    VSND_MC_LOAD1 = 35,
    VSND_MC_LOAD2 = 36,
    VSND_MC_LOAD3A = 37,
    VSND_MC_LOAD3B = 38,
    VSND_MC_LOAD4 = 39,
    VSND_MC_LOAD5 = 40,
    VSND_MC_LOAD6 = 41,
    VSND_MENU1 = 42,
    VSND_MENU2 = 43,
    VSND_MENU3 = 44,
    VSND_MENU4 = 45,
    VSND_MENU5 = 46,
    VSND_MENU6 = 47,
    VSND_OPTION1 = 48,
    VSND_OPTION2 = 49,
    VSND_OPTION3 = 50,
    VSND_OPTION4 = 51,
    VSND_WAIT1 = 52,
    VSND_WAIT2 = 53,
    VSND_MC_LOAD7 = 54,
    VSND_MC_CHECK2_B = 55,
    VSND_MAXNUM = 56
};

typedef struct { // 0x14
    /* 0x00 */ TSVOICE_TBL *pTap;
    /* 0x04 */ u_short isOn;
    /* 0x06 */ u_short tim;
    /* 0x08 */ u_short bMsk;
    /* 0x0a */ u_short isSeq;
    /* 0x0c */ u_short sqIdx;
    /* 0x0e */ u_short pad;
    /* 0x10 */ u_short *pSeq;
} TSSND_CHAN;

typedef struct { // 0x8
    /* 0x0 */ int mesNo;
    /* 0x4 */ int dataNo;
} MCDATA_TBL;

typedef struct { // 0xc
    /* 0x0 */ u_short vol;
    /* 0x2 */ short bPause;
    /* 0x4 */ int tim;
    /* 0x8 */ MAPBGM *pbgm;
} BGMONE;

typedef struct { // 0xa0
    /* 0x00 */ u_short vol;
    /* 0x02 */ u_short state;
    /* 0x04 */ u_short ttim;
    /* 0x06 */ u_short ttim0;
    /* 0x08 */ u_short wtLoad;
    /* 0x0a */ u_short wtNo;
    /* 0x0c */ u_short wtTim;
    /* 0x0e */ u_short pad;
    /* 0x10 */ u_short chgReq;
    /* 0x12 */ u_short sndno;
    /* 0x14 */ u_short oldno;
    /* 0x16 */ u_short cstate;
    /* 0x18 */ u_short ctim;
    /* 0x1c */ BGMONE wbgm[11];
} BGMSTATE;

typedef struct { // 0xc25a4
    /* 0x00000 */ USER_DATA pUserDisp[81];
} MN_USERLST_WORK;

typedef struct { // 0x18
    /* 0x00 */ int logFileNo;
    /* 0x04 */ u_int logDate[2];
    /* 0x0c */ int repFileNo;
    /* 0x10 */ u_int repDate[2];
} CURFILEINFO;

typedef struct { // 0x8
    /* 0x0 */ u_char date_day;
    /* 0x1 */ u_char date_month;
    /* 0x2 */ u_short date_year;
    /* 0x4 */ u_char date_pad;
    /* 0x5 */ u_char date_second;
    /* 0x6 */ u_char date_minute;
    /* 0x7 */ u_char date_hour;
} MAP_TIME;

typedef struct { // 0x14
    /* 0x00 */ u_int score;
    /* 0x04 */ u_char name[16];
} RANKLIST;

typedef struct { // 0x6
    /* 0x0 */ short bCur;
    /* 0x2 */ short time;
    /* 0x4 */ short cltm;
} POPCOFF;

typedef struct { // 0xa0
    /* 0x00 */ int onTNo;
    /* 0x04 */ int okTim;
    /* 0x08 */ int onTim;
    /* 0x0c */ int srTim;
    /* 0x10 */ int srTNo;
    /* 0x14 */ POPCOFF offinf[16];
    /* 0x74 */ u_short bDim[16];
    /* 0x94 */ float fswing;
    /* 0x98 */ u_int habgr;
    /* 0x9c */ u_int nabgr;
} POPCTIM;

typedef struct { // 0x14
    /* 0x00 */ int atim;
    /* 0x04 */ int aflg;
    /* 0x08 */ int atrn;
    /* 0x0c */ int atrn2;
    /* 0x10 */ int atrn3;
} ANIME_WK;

typedef struct { // 0x118
    /* 0x000 */ int state;
    /* 0x004 */ int exitflg;
    /* 0x008 */ int selno;
    /* 0x00c */ int btnNo;
    /* 0x010 */ int bSelRank;
    /* 0x014 */ int selLev;
    /* 0x018 */ int levMax;
    /* 0x01c */ int isSelLev;
    /* 0x020 */ ANIME_WK awork;
    /* 0x034 */ int isRnkWAnime;
    /* 0x038 */ float bpTim;
    /* 0x03c */ POPCTIM cani;
    /* 0x0dc */ int urTim;
    /* 0x0e0 */ int await;
    /* 0x0e4 */ int selrnkpg;
    /* 0x0e8 */ int isRankOn;
    /* 0x0ec */ int rankFlg;
    /* 0x0f0 */ int rStageNo;
    /* 0x0f4 */ int rVsLev;
    /* 0x0f8 */ int nRanking;
    /* 0x0fc */ RANKLIST *pRanking;
    /* 0x100 */ int nPPosSet;
    /* 0x104 */ int nPBubPat;
    /* 0x108 */ int nPageMax;
    /* 0x10c */ int nTagMax;
    /* 0x110 */ int nRankMax;
    /* 0x114 */ int rsline;
} POPUP_MENU;

typedef struct { // 0x44
    /* 0x00 */ short patNo;
    /* 0x02 */ short bMsk;
    /* 0x04 */ PTPOS *patPos;
    /* 0x08 */ int state;
    /* 0x0c */ int time;
    /* 0x10 */ int anime;
    /* 0x14 */ int atime;
    /* 0x18 */ int innm;
    /* 0x1c */ int innm2;
    /* 0x20 */ int dir;
    /* 0x24 */ int dir2;
    /* 0x28 */ float ox;
    /* 0x2c */ float oy;
    /* 0x30 */ float rot;
    /* 0x34 */ float rox;
    /* 0x38 */ float roy;
    /* 0x3c */ float rrot;
    /* 0x40 */ float vrate;
} JUKECDOBJ;

enum {
    TSJKCUS_MSK = 0,
    TSJKCUS_DEF = 1,
    TSJKCUS_CUR = 2,
    TSJKCUS_ON = 3,
    TSJKCUS_OFF = 4,
    TSJKCUS_SELOK = 5
};

enum {
    TSJKANM_OFF = 0,
    TSJKANM_IN = 1,
    TSJKANM_OUT = 2,
    TSJKANM_PLAY1 = 3,
    TSJKANM_RETURN1 = 4,
    TSJKANM_PLAY2 = 5,
    TSJKANM_RETURN2 = 6,
    TSJKANM_ROTATE = 7,
    TSJKANM_ROTSTOP = 8
};

typedef struct { // 0x1414
    /* 0x0000 */ int state;
    /* 0x0004 */ int exitflg;
    /* 0x0008 */ int selno;
    /* 0x000c */ MN_SCENE MNS_StageMapW;
    /* 0x1160 */ JUKECDOBJ cusObj[10];
    /* 0x1408 */ int anmTime;
    /* 0x140c */ int timeV;
    /* 0x1410 */ int bgmFadeVol;
} JUKE_MENU;

typedef struct { // 0xc
    /* 0x0 */ int mapNo;
    /* 0x4 */ short anmNo;
    /* 0x6 */ short anmLtim;
    /* 0x8 */ int exflg;
} MNMAP_DIR;

typedef struct { // 0x40
    /* 0x00 */ int cmpmes;
    /* 0x04 */ int posanm0;
    /* 0x08 */ int posanm1;
    /* 0x0c */ int movanm1;
    /* 0x10 */ MNMAP_DIR mapdir[4];
} MNMAPPOS;

typedef struct { // 0x34
    /* 0x00 */ int state;
    /* 0x04 */ int curPos;
    /* 0x08 */ int lmtPos;
    /* 0x0c */ int anmLtim;
    /* 0x10 */ int bMove;
    /* 0x14 */ int anmBit;
    /* 0x18 */ int anmtrg;
    /* 0x1c */ int sndtrg;
    /* 0x20 */ int anmStop;
    /* 0x24 */ int mvFlag;
    /* 0x28 */ MNMAPPOS *mnmap;
    /* 0x2c */ MN_SCENE *pscene;
    /* 0x30 */ MNANM_TBL *panime;
} MAPPOS;

typedef struct { // 0x8
    /* 0x0 */ u_short state;
    /* 0x2 */ short flg;
    /* 0x4 */ u_short tim;
    /* 0x6 */ u_short ton;
} CELLOBJ;

typedef struct { // 0xc
    /* 0x0 */ int nType;
    /* 0x4 */ int typeNo[2];
} USERLISTTYPE_TABLE;

typedef struct { // 0x18
    /* 0x00 */ MN_SCENE *pScene;
    /* 0x04 */ int isSave;
    /* 0x08 */ int dataMode;
    /* 0x0c */ int dispColor;
    /* 0x10 */ int cmpMesTbl[2];
} USERLIST_TYPE;

typedef struct { // 0x44
    /* 0x00 */ int state;
    /* 0x04 */ int isOn;
    /* 0x08 */ short dispType;
    /* 0x0a */ short isCan;
    /* 0x0c */ int curnpos;
    /* 0x10 */ int curchrmode;
    /* 0x14 */ ANIME_WK awork;
    /* 0x28 */ int nameMsk;
    /* 0x2c */ int onTime;
    /* 0x30 */ char *desname;
    /* 0x34 */ u_short curnchr[8];
} NAMEINW;

typedef struct { // 0x118
    /* 0x000 */ int state;
    /* 0x004 */ int exitflg;
    /* 0x008 */ USERLISTTYPE_TABLE *ptypttbl;
    /* 0x00c */ MN_SCENE *scene;
    /* 0x010 */ int nTag;
    /* 0x014 */ int dataMode;
    /* 0x018 */ int dispColor;
    /* 0x01c */ int isSave;
    /* 0x020 */ int *cmpMesTbl;
    /* 0x024 */ int gameMode;
    /* 0x028 */ int isNameIn;
    /* 0x02c */ int mcerrNo;
    /* 0x030 */ int mcRetTag;
    /* 0x034 */ int curuser;
    /* 0x038 */ int curPageTop;
    /* 0x03c */ int wtim;
    /* 0x040 */ int userMax;
    /* 0x044 */ int curFileNo;
    /* 0x048 */ u_int curFileDate[2];
    /* 0x050 */ NAMEINW nameinw[2];
    /* 0x0d8 */ CELLOBJ cellcs[6];
    /* 0x108 */ float sline;
    /* 0x10c */ USER_DATA *wuser;
    /* 0x110 */ P3MC_USRLST *pusrlst;
    /* 0x114 */ MN_USERLST_WORK *pusrdspWk;
} USERLIST_MENU;

typedef struct { // 0x14
    /* 0x00 */ int state;
    /* 0x04 */ int ton;
    /* 0x08 */ int prio;
    /* 0x0c */ int ttim;
    /* 0x10 */ int ttim0;
} SCFADE;

typedef struct { // 0x34
    /* 0x00 */ int px;
    /* 0x04 */ int py;
    /* 0x08 */ int mesflg;
    /* 0x0c */ int line;
    /* 0x10 */ int backSw;
    /* 0x14 */ int color;
    /* 0x18 */ int faceNo;
    /* 0x1c */ int Dline;
    /* 0x20 */ int D0line;
    /* 0x24 */ int selflg;
    /* 0x28 */ int seltim;
    /* 0x2c */ int btton;
    /* 0x30 */ int btflg;
} MCMES_WORK;

typedef struct { // 0x18
    /* 0x00 */ int px;
    /* 0x04 */ int py;
    /* 0x08 */ int mesflg;
    /* 0x0c */ int backSw;
    /* 0x10 */ int ww;
    /* 0x14 */ int wh;
} CMPMES_WORK;

typedef struct { // 0x8
    /* 0x0 */ int chanNo;
    /* 0x4 */ u_short *pSeqTop;
} TSVSNDSEQ;

enum {
    VSNDSEQNO_LOAD3 = 0,
    VSNDSEQNO_WAIT0 = 1,
    VSNDSEQNO_WAIT1 = 2,
    VSNDSEQNO_MAX = 3
};

void TsBGMChangePos(int no);

int _P3DATA_SIZE(int mode);

void TsGetTm2Tex(void *ptim2, TSTEX_INF *tex);
void TsGetTm2HedTex(int no, TSTEX_INF *tex);

float TSNumRBack(float rt, float bkrt);

void TsMENU_InitSystem(void);
void TsMENU_EndSystem(void);
void TsMenu_RankingClear(void);

void TsMenu_Init(int iniflg, P3GAMESTATE *pstate);
void TsMenu_End(void);

void TsMenu_InitFlow(P3GAMESTATE *pstate);
int  TsMenuMemcChk_Flow(void);
int  TsMenu_Flow(void);
void TsMenu_Draw(void);

int DateChgInt(u_int n);
void GetRankScoreID(MAP_TIME *mptim, u_int *dat);

void TsMENU_SetMapScreen(int mapNo);
int TsAnimeWait_withKeySkip(u_int tpad, MN_SCENE *scene, int ltim, u_int bnk);

void TsMCAMes_SetPos(int x, int y);
void TsMCAMes_SetMes(int no);

void TsCMPMes_SetPos(int x, int y);
void TsCMPMes_SetMes(int no);

void TsPopCusAOff(POPCTIM *pfw);
void TsPopCusDim(POPCTIM *pfw, int n, int flg);
void TsPopCusInit(POPCTIM *pfw, int curIdx);
void TsPopCusFlow(POPCTIM *pfw);
void TsPopCusPut(SPR_PKT pk, SPR_PRM *spr, int dflg, POPCTIM *pfw, int bPut, int idx, PATPOS *ppat, int px, int py);
int TsPUPCheckMove(int nbtn, int bank, POPCTIM *pfw);

void TsPopMenCus_Draw(SPR_PKT pk, SPR_PRM *spr, POPUP_MENU *pfw,int px, int py, u_int hicol, u_int nmcol, int dflg);

int TsSCFADE_Set(int flg, int num, int prio);

void _PkMCMsgPut(SPR_PKT pk, SPR_PRM *spr, int id, int x, int y, u_int abgr);
int _PkMCMsgGetLine(int id);

void _PkSubMsgPut(SPR_PKT pk, SPR_PRM *spr, int id, int x, int y, u_int abgr);

void TsMenu_CleanVram(int nFrm);
void TsMenu_CaptureVram(SPR_PKT pk, SPR_PRM *spr);

void TsSetCTransSpr(SPR_PKT pk, SPR_PRM *spr, int mx, int my, float zx, float zy);
void TsSetSLTransSpr(SPR_PKT pk, SPR_PRM *spr, int mx, int my, float zx);
void TsSetPNTransSpr(SPR_PKT pk, SPR_PRM *spr, int mx, int my, float wr, float dr);

void TsCELBackEnd(void);
int TsCELBackDraw(TsUSERPKT *UPacket, SPR_PRM *spr, int dispSw, int colNo);

#endif /* MENUSUB_H */
