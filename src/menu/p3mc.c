#include "menu/p3mc.h"

#include "main/cdctrl.h"

#include "menu/memc.h"
#include "menu/menu.h"
#include "menu/menudata.h"
#include "menu/menufont.h"

#include <libcdvd.h>

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* sdata 399830 */ extern char *HedderID; /* static */
/* sdata 399834 */ extern char *FooterID; /* static */
/* sdata 399838 */ extern GETUSER_WORK *pUChkWork; /* static */
/* bss 1c81100 */ extern P3MC_WORK P3MC_Work; /* static */
/* sbss 399b60 */ extern int FreeSizeFlg; /* static */
/* sbss 399b64 */ extern int portCheckFlg; /* static */
/* sbss 399b68 */ extern int NeedSize[2]; /* static */
/* sbss 399b70 */ extern int UChkSize[2]; /* static */
/* bss 1c81120 */ extern char filePath[64]; /* static */
/* bss 1c81160 */ extern MEMC_INFO mcmenu_info; /* static */
/* bss 1c81180 */ extern sceMcTblGetDir p3mcTblGetDir[8]; /* static */
/* sbss 399b78 */ extern int isFileFlgCash; /* static */
/* bss 1c81380 */ extern u_char McLogFileFlg[80]; /* static */
/* bss 1c813d0 */ extern u_char McReplayFileFlg[80]; /* static */

static int      P3MC_GetIconSize(int mode);
static void*    P3MC_GetIconPtr(int mode, int stageNo);
static void    _P3MC_SetUserDirName(int mode, int fileNo);
static char*   _P3MC_GetFilePath(int mode, int fileNo);
static void    _P3MC_EUC2SJIS(char *des, char *src);
static void    _P3MC_ASC2SJIS(char *des, char *src);
static void    _P3MC_UserName_ASC2SJIS(char *des, char *src);
static void    _P3MC_SetBrowsInfo(int mode, int fileNo, char *name, int stageNo, int roundNo, int isVs, int ParaCol);
static int     _P3MC_mainfile_chk(int no, int data_csize, int mode, int *need);
static int     _P3MC_file_chk(char *name, int size, int *need);
static int     _P3MC_freesize_chk(void);
static int     _P3MC_GetSaveDataSize(int dsize);
static int     _P3MCStrCmpLen(char *str, char *id, int len);
static int     _P3MCStrNum(char *nstr, int len);
static int     _P3MC_MemcCheck(int mode, sceMcTblGetDir *pDirTable);
static void    _P3MC_AddUserBroken(P3MC_USRLST *pUser, int mode, int fno);
static int     _P3MC_loadCheck(P3MC_WORK *pw, int skip);
static int     _P3MC_SaveCheck(P3MC_WORK *pw);
static u_short _P3MC_proc(u_short prg);
static void    _P3MC_dataCheckFunc(P3MC_WORK *pw, P3MCDataCheckFunc funcp);
static int     _P3MC_CheckUserData(P3MC_WORK *pw);
static int     _P3MC_CheckUserDataHead(P3MC_WORK *pw);

static int P3MC_GetIconSize(int mode) {
    int isize;

    switch (mode) {
    case 2:
        isize = 0x1e360;
        break;
    case 1:
    default:
        isize = 0x1ccb0;
        break;
    }

    return isize;
}

INCLUDE_RODATA("asm/nonmatchings/menu/p3mc", D_00396180);
INCLUDE_RODATA("asm/nonmatchings/menu/p3mc", D_00396190);

static void* P3MC_GetIconPtr(int mode, int stageNo) {
    int fn;

    if (mode == 1) {
        switch (stageNo) {
        case 1:
            fn = 0x161;
            break;
        case 2:
            fn = 0x162;
            break;
        case 3:
            fn = 0x163;
            break;
        default:
            fn = 0x164;
            break;
        }
    } else {
        switch (stageNo) {
        case 1:
            fn = 0x159;
            break;
        case 2:
            fn = 0x15a;
            break;
        case 3:
            fn = 0x15b;
            break;
        case 4:
            fn = 0x15c;
            break;
        case 5:
            fn = 0x15d;
            break;
        case 6:
            fn = 0x15e;
            break;
        case 7:
            fn = 0x15f;
            break;
        case 8:
        default:
            fn = 0x160;
            break;
        }
    }

    return GetIntAdrsCurrent(fn);
}

static void _P3MC_SetUserDirName(int mode, int fileNo) {
    memc_setDirName(_P3MC_GetFilePath(mode, fileNo));
}

extern char D_00399840[]; /* "LOG???"  */
extern char D_00399848[]; /* "LOG%03d" */
extern char D_00399850[]; /* "REP???"  */
extern char D_00399858[]; /* "REP%03d" */
extern char D_00399860[]; /* "??????"  */

#ifndef NON_MATCHING /* Requires sdata split to match */
INCLUDE_ASM("asm/nonmatchings/menu/p3mc", _P3MC_GetFilePath);
#else
static char* _P3MC_GetFilePath(int mode, int fileNo) {
    char *addName;

    strcpy(filePath, "BISCPS-15017"); /* D_003961C0 */
    addName = &filePath[12];

    switch (mode) {
    case 1:
        if (fileNo < 0) {
            strcpy(addName, "REP???");
        } else {
            sprintf(addName, "REP%03d", fileNo);
        }
        break;
    case 2:
        if (fileNo < 0) {
            strcpy(addName, "LOG???");
        } else {
            sprintf(addName, "LOG%03d", fileNo);
        }
        break;
    case 3:
    default:
        strcpy(addName, "??????");
        break;
    }

    return filePath;
}
#endif

static void _P3MC_EUC2SJIS(char *des, char *src) {
    u_char c1, c2;

    while ((c1 = *src++) != '\0') {
        c2 = *src++;
        if ((c1 % 2) == 0) {
            c2 -= 0x02;
        } else {
            c2 -= 0x61;
            if (c2 > 0x7e) {
                c2++;
            }
        }

        c1++;
        if (c1 < 0xe0) {
            c1 /= 2;
            c1 += 0x30;
        } else {
            c1 /= 2;
            c1 += 0x70;
        }

        *des++ = c1;
        *des++ = c2;
    }

    *des = '\0';
}

static void _P3MC_ASC2SJIS(char *des, char *src) {
    /* static */ extern char sjisASCII0[65]; // = "！”＃＄％＆’（）＊＋，−．／０１２３４５６７８９：；＜＝＞？＠";
    /* static */ extern char sjisASCII1[13]; // = "［￥］＾＿’";
    /* static */ extern char sjisASCII2[11]; // = "｛｜｝〜　";

    char    *des0;
    u_char   c;
    int      n;

    des0 = des;

    for (; (c = *src) != '\0'; src++, des += 2) {
        if (c <= ' ') {
            n = 0xa1a1; /* Space */
        } else if (c <= '@') {
            c = (c - '!');
            n = ((u_short*)sjisASCII0)[c];
        } else if (c <= 'Z') {
            c = (c - 'A');
            n = (c << 8) + 0xc1a3 /* A */;
        } else if (c <= '`') {
            c = (c - '[');
            n = ((u_short*)sjisASCII1)[c];
        } else if (c <= 'z') {
            c = (c - 'a');
            n = (c << 8) + 0xe1a3 /* a */;
        } else if (c <= '~') {
            c = (c - '{');
            n = ((u_short*)sjisASCII2)[c];
        } else {
            n = 0xa1a1; /* Space */
        }

        *(u_short*)des = n;
    }

    *des = '\0';
    _P3MC_EUC2SJIS(des0, des0);
}

static void _P3MC_UserName_ASC2SJIS(char *des, char *src) {
    MenuFont_ASC2EUC(des, src);
    _P3MC_EUC2SJIS(des, des);
}

static void _P3MC_SetBrowsInfo(int mode, int fileNo, char *name, int stageNo, int roundNo, int isVs, int ParaCol) {
    char  tname[256];
    int   s;
    char  tmps[30];
    int   r;
    int   size;
    void *ptr;
    int   iconNo;

    if (name == NULL) {
        return;
    }

    _P3MC_EUC2SJIS(tname, "ＰＡＲＡＰＰＡ２");

    if (mode == 1) {
        sprintf(tmps, "/SYS-%02d", fileNo + 1);
    } else {
        sprintf(tmps, "/REP-%02d", fileNo + 1);
    }

    s = strlen(tname);
    _P3MC_ASC2SJIS(tname + s, tmps);
    s = strlen(tname);

    switch (mode) {
    case 2:
        if (!isVs) {
            sprintf(tmps, "%s-ST%1d", name, stageNo);
        } else {
            sprintf(tmps, "%s-VS_ST%1d", name, stageNo);
        }
        break;

    default:
    case 1:
        if (roundNo == 0) {
            sprintf(tmps, "%s(ST%1d)", name, stageNo);
        } else {
            r = roundNo + 1;

            if (r > 99) {
                r = 99;
            }

            sprintf(tmps, "%s(C%2d)", name, r);
        }
        break;
    }

    _P3MC_UserName_ASC2SJIS(tname + s, tmps);

    memc_setSaveTitle(tname, s);

    if (mode == 1) {
        iconNo = ParaCol + 1;

        if (iconNo > 4) {
            iconNo = 4;
        }

        ptr = MenuDataGetIconSysHed(0, iconNo, &size);
    } else {
        iconNo = stageNo;
        ptr = MenuDataGetIconSysHed(1, iconNo, &size);
    }

    memc_setIconSysHed(ptr, size);

    memc_setSaveIcon(0, P3MC_GetIconPtr(mode, iconNo), P3MC_GetIconSize(mode));
    memc_setSaveIcon(1, NULL, 0);
    memc_setSaveIcon(2, NULL, 0);
}

INCLUDE_ASM("asm/nonmatchings/menu/p3mc", _P3MC_mainfile_chk);

static int _P3MC_file_chk(char *name, int size, int *need) {
    int             i, j;
    int             flg;
    int             closeFlagSw;
    sceMcTblGetDir *pTblDir;
    int             need0;

    pTblDir = mcmenu_info.dirfile;
    flg = FALSE;

    if (name == NULL) {
        return -1;
    }

    for (i = 0; pTblDir[i].EntryName[0] != '\0'; i++) {
        for (j = 0;; j++) {
            if (name[j] == '\0') {
                flg = TRUE;
                break;
            }

            if (name[j] != '?' && name[j] != pTblDir[i].EntryName[j]) {
                break;
            }
        }

        if (flg) {
            need0 = ((size + 1023) / 1024) - ((pTblDir[i].FileSizeByte + 1023) / 1024);
            if (need0 < 0) {
                need0 = 0;
            }

            if (need != NULL) {
                *need += need0;
            }

            closeFlagSw = (pTblDir[i].AttrFile >> 7) & 1;
            if (size == 0 || pTblDir[i].FileSizeByte == size) {
                if (!closeFlagSw || pTblDir[i].AttrFile & 0x80) {
                    break;
                }
            }

            return -2;
        }
    }

    if (!flg) {
        if (need != NULL) {
            *need += (size + 1023) / 1024;
        }
        return -1;
    }

    return 0;
}

int P3MC_InitReady(void) {
    int re;

    portCheckFlg = 0;
    FreeSizeFlg = 0;

    memset(&P3MC_Work, 0, sizeof(P3MC_WORK));
    memset(&mcmenu_info, 0, sizeof(MEMC_INFO));
    memset(p3mcTblGetDir, 0, sizeof(p3mcTblGetDir));

    isFileFlgCash = 0;

    memset(McLogFileFlg, 0, sizeof(McLogFileFlg));
    memset(McReplayFileFlg, 0, sizeof(McReplayFileFlg));
    memc_init();

    mcmenu_info.dirfile = p3mcTblGetDir;
    mcmenu_info.dirfileMax = 8;
    memc_port_info(0, &mcmenu_info);

    re = memc_manager(0);
    if (re == 0x10 || re == 0x6 || re == 0x30) {
        P3MC_CheckChangeClear();
        return -1;
    }

    return 0;
}

int P3MC_GetSaveSize(int size, int mode) {
    int dataAsize = _P3MC_GetSaveDataSize(size);
    int icsize = P3MC_GetIconSize(mode);

    size = ((icsize + 1023) / 1024) + ((dataAsize + 1023) / 1024);
    return size + 5;
}

void P3MC_SetCheckSaveSize(int mode, int fsize, int csize) {
    int asize = _P3MC_GetSaveDataSize(csize);

    switch (mode) {
    case 1:
        NeedSize[0] = fsize;
        UChkSize[0] = asize;
        break;
    case 2:
        NeedSize[1] = fsize;
        UChkSize[1] = asize;
        break;
    }
}

static int _P3MC_freesize_chk(void) {
    int free;
    int flg;

    free = mcmenu_info.free;

    if (!memc_checkFormat()) {
        flg = -1;
    } else {
        flg = (free >= NeedSize[0]);
        if (free >= NeedSize[1]) {
            flg |= 2;
        }
    }

    return flg;
}

int P3MC_CheckChange(void) {
    int re, err;

    err = 0;
    re = memc_manager(1);
    if (re == 0x10) {
        return -1;
    }

    switch (re) {
    case 1:
        portCheckFlg = 0;
        return -1;
    case 2:
        err = 3;
        P3MC_CheckChangeClear();
        break;
    case 6:
    case 48:
        err = 5;
        break;
    case 0:
    default:
        FreeSizeFlg = _P3MC_freesize_chk();
        break;
    }

    if (err != 0) {
        FreeSizeFlg = 0;
        portCheckFlg = 0;
        if (mcmenu_info.flag == 2) {
            return err;
        } else {
            return 3;
        }
    }

    if (portCheckFlg == 0) {
        portCheckFlg = 1;
        memc_port_check(0, &mcmenu_info.flag, &mcmenu_info.free);
        return -1;
    }

    portCheckFlg = 0;
    if (mcmenu_info.flag != 2) {
        FreeSizeFlg = 0;
        err = 3;
    } else {
        if (memc_getChangeState()) {
            err = 5;
        } else {
            err = 0;
        }
    }
 
    return err;
}

void P3MC_CheckChangeClear(void) {
    memc_setChangeState(0);
}

void P3MC_CheckChangeSet(void) {
    memc_setChangeState(1);
}

int P3MC_CheckIsNewSave(int mode) {
    return FreeSizeFlg & mode;
}

static int _P3MC_GetSaveDataSize(int dsize) {
    u_int dsize0 = (dsize + 0xf) >> 0x4 << 0x4;
    return sizeof(USER_HEADER) + dsize0 + sizeof(USER_FOOTER);
}

void P3MC_DeleteDataWork(MCRWDATA_HDL *phdl) {
    if (phdl == NULL) {
        return;
    }
    
    if (phdl->pMemTop != NULL) {
        free(phdl->pMemTop);
    }
    
    free(phdl);
}

MCRWDATA_HDL* P3MC_MakeDataWork(int dsize, USER_DATA *puser) {
    MCRWDATA_HDL *phdl;
    u_char       *pdata;
    int           asize, dsize0;
    u_char       *data;

    phdl = (MCRWDATA_HDL*)malloc(sizeof(MCRWDATA_HDL));
    memset(phdl, 0, sizeof(MCRWDATA_HDL));

    if (phdl != NULL) {
        dsize0 = ((dsize + 15) >> 4) << 4;
        asize = sizeof(USER_HEADER) + dsize0 + sizeof(USER_FOOTER);

        pdata = memalign(16, asize);
        memset(pdata, 0, asize);

        phdl->pMemTop = pdata;
        phdl->rwsize = asize;
        phdl->datasize = asize;
        phdl->srcsize = dsize;

        phdl->pHead = (USER_HEADER*)pdata;

        data = (u_char*)(((USER_HEADER*)pdata) + 1);
        phdl->pData = data;
        phdl->pFoot = (USER_FOOTER*)(data + dsize0);

        if (puser != NULL) {
            ((USER_HEADER*)pdata)->user = *puser;
        }

        return phdl;
    }

    P3MC_DeleteDataWork(NULL);
    return NULL;
}

static int _P3MCStrCmpLen(char *str, char *id, int len) {
    int i;

    for (i = 0; i < len; i++) {
        if (*str != *id) {
            return 1;
        }
        id++, str++;
    }

    return 0;
}

static int _P3MCStrNum(char *nstr, int len) {
    int    i;
    int    n;
    u_char c;

    n = 0;

    for (i = 0; i < len; i++, nstr++) {
        c = *nstr;
        if (c >= '0' && c <= '9') {
            n = (n * 10) + (c - '0');
        } else {
            printf("Error=%c\n", c);
        }
    }

    return n;
}

extern char D_00399868[]; /* .sdata - "LOG" */
extern char D_00399870[]; /* .sdata - "REP" */

static int _P3MC_MemcCheck(int mode, sceMcTblGetDir *pDirTable) {
    int re;
    int err;
    int i;
    int fileNo;

    re = memc_manager(1);
    if (re == 0x10) {
        return -1;
    }

    err = 0;

    switch (re) {
    case 0x01:
    case 0x06:
    case 0x30:
        err = -1;
        break;
    case 0x02:
        P3MC_CheckChangeClear();
        err = 3;
        break;
    case 0x03:
        err = 2;
        break;
    case 0x00:
        FreeSizeFlg = _P3MC_freesize_chk();
        break;
    default:
        break;
    }

    if (portCheckFlg != 0 && err != 0) {
        portCheckFlg = 0;
        return err;
    }

    if (portCheckFlg == 0) {
        if (memc_port_check(0, &mcmenu_info.flag, &mcmenu_info.free) == 0) {
            portCheckFlg = 1;
        }
        FreeSizeFlg = 0;
    } else if (portCheckFlg == 1) {
        int flag = mcmenu_info.flag; /* note: variable not in STABS. */

        if (mcmenu_info.flag != 2) {
            portCheckFlg = 0;
            return 3;
        }

        if (memc_getChangeState() != 0) {
            isFileFlgCash = 0;
        }

        if (isFileFlgCash != 0) {
            portCheckFlg = 0;
            return 0;
        }

        isFileFlgCash = 0;
        memset(McLogFileFlg, 0, sizeof(McLogFileFlg));
        memset(McReplayFileFlg, 0, sizeof(McReplayFileFlg));
        memset(pDirTable, 0, sizeof(sceMcTblGetDir) * 81);

        if (memc_get_dir(0, _P3MC_GetFilePath(3, -1), pDirTable, 80) == 0) {
            portCheckFlg = flag;
        }
    } else if (portCheckFlg == 2) {
        for (i = 0; i < 80; i++) {
            char *name = &pDirTable[i].EntryName[0];
            char *type = &pDirTable[i].EntryName[12];
            char *num = &pDirTable[i].EntryName[15];

            if (name[0] == '\0') {
                break;
            }

            fileNo = _P3MCStrNum(num, 3);
            if (fileNo < 80) {
                if (_P3MCStrCmpLen(type, D_00399868, 3) == 0) {
                    McLogFileFlg[fileNo] = 1;
                } else if (_P3MCStrCmpLen(type, D_00399870, 3) == 0) {
                    McReplayFileFlg[fileNo] = 1;
                }
            }
        }

        portCheckFlg = 0;
        return 0;
    }

    return -1;
}

int P3MC_GetUserStart(int mode, P3MC_USRLST *pUsrLst, int bFirst) {
    GETUSER_WORK *pWork;

    if (pUChkWork != NULL) {
        free(pUChkWork);
    }
    
    pWork = memalign(16, sizeof(*pWork));
    pUChkWork = pWork;

    portCheckFlg = 0;

    if (pWork != NULL) {
        pWork->bFirst = bFirst;
        pWork->curState = 0;

        if (mode & 1) {
            pWork->curMode = 1;
        } else if (mode & 2) {
            pWork->curMode = 2;
        } else {
            printf("P3MC_GetUser Error Mode is unknown!\n");
            pWork->curMode = 1;
        }

        pWork->curFno = 0;
        pWork->curUserMode = mode;
        pWork->pUserLst = pUsrLst;
    }

    return -1;
}

void P3MC_GetUserEnd(void) {
    if (pUChkWork != NULL) {
        free(pUChkWork);
    }

    pUChkWork = NULL;
}

INCLUDE_ASM("asm/nonmatchings/menu/p3mc", P3MC_GetUserCheck);

void P3MC_AddUser(P3MC_USRLST *pUser, int mode, USER_DATA *puser) {
    USER_DATA *newUser = &pUser->getUser[pUser->nGetUser];
    *newUser = *puser;

    pUser->nGetUser++;
    if (pUser->nGetUser > 0x4f) {
        printf(" AddUserWork Over All File Count...\n");
        pUser->nGetUser = 0x4f;
    }

    switch (mode) {
    case 1:
        pUser->plog_user[pUser->nLogGet] = newUser;
        pUser->nLogGet++;
        if (pUser->nLogGet > 0x4f) {
            printf(" AddUserWork Over Log File Count...\n");
            pUser->nLogGet = 0x4f;
        }
        break;
    case 2:
        pUser->prep_user[pUser->nRepGet] = newUser;
        pUser->nRepGet++;
        if (pUser->nRepGet > 0x4f) {
            printf(" AddUserWork Over Replay File Count...\n");
            pUser->nRepGet = 0x4f;
        }
        break;
    }
}

static void _P3MC_AddUserBroken(P3MC_USRLST *pUser, int mode, int fno) {
    USER_DATA *newUser = &pUser->getUser[pUser->nGetUser];

    memset(newUser, 0, sizeof(USER_DATA));
    strcpy(newUser->name, "(BROKEN)");
    strcpy(newUser->name1, "(BROKEN)");
    newUser->stageNo = 0;
    newUser->fileNo = fno;
    newUser->mode = mode;
    newUser->flg = 2;

    newUser->date_year = -0xfb0 - fno;

    pUser->nGetUser++;
    if (pUser->nGetUser > 0x4f) {
        printf(" AddUserWork Over All File Count...\n");
        pUser->nGetUser = 0x4f;
    }

    switch (mode) {
    case 1:
        pUser->plog_user[pUser->nLogGet] = newUser;
        pUser->nLogGet++;
        if (pUser->nLogGet > 0x4f) {
            printf(" AddUserWork Over Log File Count...\n");
            pUser->nLogGet = 0x4f;
        }
        break;
    case 2:
        pUser->prep_user[pUser->nRepGet] = newUser;
        pUser->nRepGet++;
        if (pUser->nRepGet > 0x4f) {
            printf(" AddUserWork Over Replay File Count...\n");
            pUser->nRepGet = 0x4f;
        }
        break;
    }
}

int P3MC_SortUser(P3MC_USRLST *pUser, int mode, int isSave) {
    USER_DATA  *newUser;
    USER_DATA **pSort;
    int         nSort;
    int         i, l;
    int         isNew;
    int         nmuser;
    USER_DATA **pmuser;
    u_char      map[80];

    if (mode == 1) {
        pmuser = pUser->plog_user;
        nmuser = pUser->nLogGet;
    } else {
        pmuser = pUser->prep_user;
        nmuser = pUser->nRepGet;
    }

    isNew = P3MC_CheckIsNewSave(mode);

    if (isSave) {
        newUser = &pUser->getUser[pUser->nGetUser];
        memset(newUser, 0, sizeof(USER_DATA));

        if (isNew) {
            memset(map, 0, PR_ARRAYSIZE(map));
            for (i = 0; i < nmuser; i++, pmuser++) {
                map[(*pmuser)->fileNo] = 1;
            }

            for (i = 0; i < PR_ARRAYSIZE(map); i++) {
                if (map[i] == 0) {
                    break;
                }
            }

            if (i < PR_ARRAYSIZE(map)) {
                newUser->fileNo = i;
            }
        } else {
            newUser->fileNo = -1;
        }

        pUser->nUserMax = 1;
        pUser->pUserTbl[0] = newUser;
        pSort = &pUser->pUserTbl[1];
    } else {
        pUser->nUserMax = 0;
        pSort = &pUser->pUserTbl[0];
    }

    if (mode == 1) {
        nSort = pUser->nLogGet;
        memcpy(pSort, pUser->plog_user, nSort * sizeof(USER_DATA*));
    } else {
        nSort = pUser->nRepGet;
        memcpy(pSort, pUser->prep_user, nSort * sizeof(USER_DATA*));
    }

    for (i = 0; i < (nSort - 1); i++) {
        USER_DATA **pSrc = &pSort[i];

        for (l = i + 1; l < nSort; l++) {
            u_int s = *(u_int*)&pSrc[0]->date_day;
            u_int d = *(u_int*)&pSort[l]->date_day;

            if (s <= d) {
                if (s != d || *(u_int*)&pSrc[0]->date_pad <= *(u_int*)&pSort[l]->date_pad) {
                    USER_DATA *tmp = pSrc[0];
                    pSrc[0] = pSort[l]; pSort[l] = tmp;
                }
            }
        }
    }

    pUser->nUserMax += nSort;
    return pUser->nUserMax;
}

int P3MC_CheckBrokenUser(P3MC_USRLST *pUser, int mode) {
    int         nmuser;
    USER_DATA **pmuser;

    int i;
    int nBrk = 0;

    if (mode & 1) {
        pmuser = pUser->plog_user;
        nmuser = pUser->nLogGet;

        for (i = 0; i < nmuser; i++, pmuser++) {
            if ((*pmuser)->flg == 2) {
                nBrk++;
            }
        }
    }

    if (mode & 2) {
        pmuser = pUser->prep_user;
        nmuser = pUser->nRepGet;

        for (i = 0; i < nmuser; i++, pmuser++) {
            if ((*pmuser)->flg == 2) {
                nBrk++;
            }
        }
    }

    return nBrk;
}

void P3MC_OpeningCheckStart(void) {
    GETUSER_WORK *pWork;

    if (pUChkWork != NULL) {
        free(pUChkWork);
    }

    pWork = memalign(16, sizeof(*pWork));
    pUChkWork = pWork;
    
    P3MC_CheckChangeSet();
    portCheckFlg = 0;

    if (pWork != NULL) {
        pWork->curState = 0;
    }
}

void P3MC_OpeningCheckEnd(void) {
    if (pUChkWork != NULL) {
        free(pUChkWork);
    }

    pUChkWork = NULL;
}

int P3MC_OpeningCheck(void) {
    int           re;
    int           flg;
    int           chk;
    int           i;
    GETUSER_WORK *pcw;

    pcw = pUChkWork;

    if (pcw == NULL) {
        return 1;
    }

    if (pcw->curState == 0) {
        re = _P3MC_MemcCheck(3, pcw->dirTable);
        if (re < 0) {
            return -1;
        }
        if (re == 2 || re == 3) {
            return -re;
        }

        P3MC_CheckChangeClear();
        pcw->curState = 1;
        return -1;
    }

    if (pcw->curState == 1) {
        chk = _P3MC_freesize_chk();

        for (flg = 0, i = 0; i < 80; i++) {
            if (McReplayFileFlg[i] != 0) {
                flg++;
            }
        }

        if (flg != 0) {
            chk |= 0x2;
        }

        if (chk & 0x1) {
            pcw->curState = 0;
            return chk;
        }

        for (flg = 0, i = 0; i < 80; i++) {
            if (McLogFileFlg[i] != 0) {
                flg++;
            }
        }

        if (flg == 0 || flg >= 4) {
            if (flg != 0) {
                chk |= 0x1;
            }

            pcw->curState = 0;
            return chk;
        }

        pcw->curState = 2;
        pcw->curFno = 0;
    }

    if (pcw->curState == 2) {
        int fno, n;

        n = pcw->curFno;

        for (fno = 0; fno < 80; fno++) {
            if (McLogFileFlg[fno] != 0) {
                if (n == 0) {
                    break;
                }

                n--;
            }
        }

        if (fno >= 80) {
            pcw->curState = 0;
            return 0;
        }

        _P3MC_SetUserDirName(1, fno);

        re = memc_port_info(0, &mcmenu_info);
        if (re != 0) {
            memc_manager(1);
            return -1;
        }

        pcw->curState = 3;
    }

    if (pcw->curState == 3) {
        int isErr;

        re = memc_manager(1);

        if (re == 0x10) {
            return -1;
        }

        switch (re) {
        case 0:
            isErr = FALSE;
            break;
        case 5:
        case 17:
            isErr = TRUE;
            break;
        case 16: /* note: random case to trigger use of jumptable */
        case 48:
        default:
            pcw->curState = 0;
            return -1;
        }

        if (!isErr) {
            int need = 0;

            if (_P3MC_mainfile_chk(-1, UChkSize[0], 1, &need) == -3) {
                isErr = TRUE;
            } else {
                isErr = (mcmenu_info.free < need);
            }

            if (!isErr) {
                pcw->curState = 0;
                return 1;
            }
        }

        pcw->curFno++;
        if (pcw->curFno >= 3) {
            pcw->curState = 0;
            return 0;
        }

        pcw->curState = 2;
    }

    return -1;
}

int P3MC_LoadUser(int mode, int fileNo, MCRWDATA_HDL *pdhdl, int flg) {
    P3MC_WORK *pw = &P3MC_Work;

    memset(pdhdl->pMemTop, 0, pdhdl->rwsize);

    _P3MC_SetUserDirName(mode, fileNo);
    _P3MC_dataCheckFunc(pw, _P3MC_CheckUserData);

    pw->prg = 0x1000;
    pw->dstat = 0;

    pw->data_mode = mode;
    pw->data_no = fileNo;
    pw->data_stage = 0;

    pw->dhdl = pdhdl;
    pw->prgflag = flg;
    return 0;
}

int P3MC_LoadCheck(void) {
    int        re;
    P3MC_WORK *pw = &P3MC_Work;

    re = _P3MC_loadCheck(pw, 0);
    if (re < 0) {
        if (pw->dstat == 0) {
            return -1;
        } else {
            return -2;
        }
    }

    if (re != 0) {
        if (re == 11) {
            re = 4;
        }

        memset(pw->dhdl->pMemTop, 0, pw->dhdl->rwsize);
    }

    return re;
}

static int _P3MC_loadCheck(P3MC_WORK *pw, int skip) {
    int ret;
    int re;

    ret = -1;

    switch (pw->prg) {
    case 0x1001:
        re = memc_loadFirst(0, 0, pw->dhdl->pMemTop, pw->dhdl->rwsize);
        if (re == 0) {
            pw->prg = 0x1400;
        } else {
            _P3MC_proc(pw->prg);
        }
        break;
    case 0x1002:
        re = memc_load_file(0, 0, pw->dhdl->pMemTop, pw->dhdl->rwsize);
        if (re == 0) {
            pw->prg = 0x1400;
        } else {
            _P3MC_proc(pw->prg);
        }
        break;
    case 0x1000:
        pw->prg = 0x1100;
        /* fallthrough */
    case 0x1100:
        if (skip == 0) {
            re = memc_port_info(0, &mcmenu_info);
        } else {
            re = memc_port_check(0, &mcmenu_info.flag, NULL);
        }

        if (re == 0) {
            pw->prg = 0x1200;
        } else {
            _P3MC_proc(pw->prg);
        }
        break;
    case 0x1200:
        pw->prg = _P3MC_proc(pw->prg);
        if (pw->prg == 0x1400) {
            memc_load_file(0, 0, pw->dhdl->pMemTop, pw->dhdl->rwsize);
        }
        break;
    case 0x1201:
        ret = 3;
        break;
    case 0x1202:
        ret = 4;
        break;
    case 0x1209:
        ret = 11;
        break;
    case 0x1203:
        ret = 2;
        break;
    case 0x1207:
    case 0x1211:
        ret = 1;
        break;
    case 0x1210:
        ret = 5;
        break;
    case 0x1231:
        ret = 6;
        break;
    case 0x1400:
        pw->dstat = 1;

        pw->prg = _P3MC_proc(pw->prg);
        if (pw->prg != 0x1401) {
            break;
        }

        if (pw->data_cfunc != NULL) {
            if (((P3MCDataCheckFunc)pw->data_cfunc)(pw) != 0) {
                pw->prg = 0x1231;
                ret = 6;
                break;
            }
        }

        /* fallthrough */
    case 0x1401:
        ret = 0;
        break;
    default:
        break;
    }

    return ret;
}

void P3MC_SetUserWorkTime(USER_DATA *puser) {
    int        err;
    sceCdCLOCK clock;

    err = sceCdReadClock(&clock);
    puser->date_pad = rand() % 200;

    if (err != 0 && clock.stat == 0) {
        puser->date_second = clock.second;
        puser->date_minute = clock.minute;
        puser->date_hour   = clock.hour;

        puser->date_day    = clock.day;
        puser->date_month  = clock.month;
        puser->date_year   = clock.year + 0x2000;
    } else {
        puser->date_second = 0;
        puser->date_minute = 0;
        puser->date_hour   = 12;

        puser->date_day    = 1;
        puser->date_month  = 1;
        puser->date_year   = 0x2000;
    }
}

int P3MC_SaveUser(MCRWDATA_HDL *pdhdl, int flg) {
    P3MC_WORK *pw = &P3MC_Work;
    u_char    *pData = pdhdl->pMemTop;
    u_char    *name;
    int        mode = ((USER_HEADER*)pData)->user.mode;
    int        stageNo = ((USER_HEADER*)pData)->user.stageNo;
    int        roundNo = ((USER_HEADER*)pData)->user.roundNo;
    int        fileNo = ((USER_HEADER*)pData)->user.fileNo;
    int        isVs = ((USER_HEADER*)pData)->user.isVs;
    int        ParaCol = 0;

    if (mode == 1) {
        name = ((USER_HEADER*)pData)->user.name;
    } else {
        name = ((USER_HEADER*)pData)->user.name1;
    }

    if (mode == 1) {
        P3LOG_VAL *pLog = pdhdl->pData;
        ParaCol = pLog->nRound;
        if (ParaCol < 0) {
            ParaCol = 0;
        }
        if (ParaCol > 4) {
            ParaCol = 4;
        }
    }

    _P3MC_SetUserDirName(mode, fileNo);
    _P3MC_SetBrowsInfo(mode, fileNo, name, stageNo, roundNo, isVs, ParaCol);

    isFileFlgCash = FALSE;

    P3MC_SetUserWorkTime(&pdhdl->pHead->user);

    memcpy(pdhdl->pHead->header, HedderID, 16);
    memcpy(pdhdl->pHead->footer, FooterID, 16);
    memcpy(pdhdl->pFoot->footer, FooterID, 16);

    pw->prg = 0;

    pw->data_no = fileNo;
    pw->data_mode = mode;
    pw->data_stage = (mode == 1) ? 0 : stageNo;

    pw->prgflag = flg;
    pw->dhdl = pdhdl;
    pw->dstat = 0;

    _P3MC_CheckUserDataHead(pw);
    return 0;
}

int P3MC_SaveCheck(void) {
    int        re;
    P3MC_WORK *pw = &P3MC_Work;

    re = _P3MC_SaveCheck(pw);
    if (re >= 0) {
        return re;
    }

    if (pw->dstat == 1) {
        return -2;
    }
    if (pw->dstat != 2) {
        return -1;
    }
    return -3;
}

static int _P3MC_SaveCheck(P3MC_WORK *pw) {
    int ret;
    int re;

    ret = -1;

    switch (pw->prg) {
    case 0:
        re = memc_port_info(0, &mcmenu_info);
        if (re == 0) {
            pw->prg = 0x200;
        } else {
            _P3MC_proc(pw->prg);
        }
        break;
    case 0x200:
        pw->prg = _P3MC_proc(pw->prg);
        if (pw->prg == 0x400) {
            pw->dstat = 1;
            if (pw->dhdl->pMemTop != NULL) {
                memc_save_file(0, 0, pw->dhdl->pMemTop, pw->dhdl->rwsize, pw->prgflag & 0x4);
            }
        }
        break;
    case 0x201:
        ret = 3;
        break;
    case 0x206:
        ret = 7;
        break;
    case 0x207:
    case 0x211:
        ret = 1;
        break;
    case 0x210:
        ret = 5;
        break;
    case 0x401:
        ret = 0;
        break;
    case 0x400:
        pw->prg = _P3MC_proc(pw->prg);

        if (pw->prg == 0x401) {
            break;
        }
        if (pw->prg == 0x400) {
            break;
        }

        if (pw->prg == 0x206) {
            ret = 7;
        } else {
            ret = 1;
        }

        break;
    case 0x402:
        pw->prg = _P3MC_proc(pw->prg);
        break;
    case 0x410:
        if (pw->prgflag & 0x1) {
            memc_port_info(0, &mcmenu_info);
            pw->prg = 0x411;
        } else {
            ret = 8;
        }
        break;
    case 0x411:
        pw->prg = _P3MC_proc(pw->prg);
        if (pw->prg == 0x400) {
            pw->dstat = 1;
            if (pw->dhdl->pMemTop != NULL) {
                memc_save_file(0, 0, pw->dhdl->pMemTop, pw->dhdl->rwsize, pw->prgflag & 0x4);
            }
        }
        break;
    case 0x510:
        if (pw->prgflag & 0x2) {
            memc_port_info(0, &mcmenu_info);
            pw->prg = 0x511;
        } else {
            ret = 9;
        }
        break;
    case 0x511:
        pw->prg = _P3MC_proc(pw->prg);
        break;
    case 0x520:
        pw->dstat = 2;
        pw->prg = _P3MC_proc(pw->prg);
        break;
    case 0x530:
        ret = 10;
        break;
    default:
        break;
    }

    return ret;
}

static u_short _P3MC_proc(u_short prg) {
    u_short    re;
    P3MC_WORK *pw = &P3MC_Work;
    int        need;

    re = memc_manager(1);

    switch (re) {
    case 6:
    case 48:
        switch (prg & 0xff00) {
        case 0x200:
        case 0x1200:
            if (pw->prgflag & 0x8) {
                memc_port_info(0, &mcmenu_info);
                re = prg;
                break;
            }
            /* fallthrough */
        default:
            if (prg & 0xf000) {
                re = 0x1210;
            } else {
                re = 0x210;
            }
            break;
        }
        break;
    case 0:
        switch (prg & 0xff00) {
        case 0x200:
            if (mcmenu_info.flag & 0x200) {
                if (!_P3MC_mainfile_chk(-1, pw->dhdl->datasize, pw->data_mode, &need)) {
                    re = 0x410;
                    break;
                }
                if (mcmenu_info.free < need) {
                    re = 0x206;
                } else {
                    re = 0x400;
                }
                break;
            }
            re = 0x201;
            break;
        case 0x400:
            if (prg == 0x411) {
                re = 0x400;
            } else {
                re = 0x401;
            }
            break;
        case 0x500:
            memc_port_info(0, &mcmenu_info);
            re = 0x200;
            break;
        case 0x1200:
            if (mcmenu_info.flag & 0x200) {
                /* note: variable not in STABS info. */
                int chk = _P3MC_mainfile_chk(-1, pw->dhdl->datasize, pw->data_mode, NULL);
                if (chk >= -1 && chk <= 0) {
                    re = 0x1400;
                } else {
                    re = 0x1231;
                }
                break;
            }
            re = 0x1201;
            break;
        case 0x1204:
            re = 0x1100;
            break;
        case 0x1400:
            re = 0x1401;
            break;
        default:
            re = prg & 0xf000;
            break;
        }
        break;
    case 16:
        re = prg;
        break;
    case 18:
        re = 0x400;
        memc_save_overwrite();
        break;
    case 2:
        switch (prg & 0xf000) {
        case 0:
            if (prg == 0x400) {
                re = 0x211;
            } else {
                re = 0x201;
            }
            break;
        case 0x1000:
            if ((prg & 0xff00) == 0x1400) {
                re = 0x1211;
            } else {
                re = 0x1201;
            }
            break;
        }
        break;
    case 5:
    case 17:
        switch (prg & 0xf000) {
        case 0:
            if (_P3MC_freesize_chk() & pw->data_mode) {
                re = 0x400;
            } else {
                re = 0x206;
            }
            break;
        case 0x1000:
            re = 0x1209;
            break;
        }
        break;
    case 4:
        if ((prg & 0xf000) == 0) {
            re = 0x206;
        } else {
            re = 0x1231;
        }
        break;
    case 3:
        switch (prg & 0xf000) {
        case 0:
            if ((prg & 0xff00) == 0x200) {
                re = 0x510;
            } else if (prg == 0x511) {
                re = 0x520;
                memc_format(0);
            } else {
                re = 0x210;
            }
            break;
        case 0x1000:
            re = 0x1203;
            break;
        }
        break;
    default:
        if ((prg & 0xff00) == 0x500) {
            re = 0x530;
        } else if (prg & 0x1000) {
            re = 0x1207;
        } else {
            re = 0x207;
        }
        break;
    }

    return re;
}

void _P3MC_dataCheckFunc(P3MC_WORK *pw, P3MCDataCheckFunc funcp) {
    pw->data_cfunc = funcp;
}

static int _P3MC_CheckUserData(P3MC_WORK *pw) {
    USER_FOOTER *pfoot = pw->dhdl->pFoot;

    if (_P3MC_CheckUserDataHead(pw)) {
        return 1;
    } else {
        return (strcmp(FooterID, pfoot->footer) != 0);
    }
}

/* There are no traces of such use of inlines on the
 * symbols, yet the function only matches this way. */
static inline int _P3MC_CheckHead(USER_HEADER *hed, P3MC_WORK *pw) {
    /* Checks done on a single line according to symbols */
    if (hed->user.fileNo != pw->data_no ||
        hed->user.mode != pw->data_mode || 
        hed->user.mode != pw->data_mode ||
        (pw->data_stage > 0 && hed->user.stageNo != pw->data_stage) ||
        (hed->user.name[0] == 0 && hed->user.name1[0] == 0)) {
        return 1;
    }
    return 0;
}

/* Without use of inlines you can have a decent
 * match with a minor difference on a likely branch:
 * https://decomp.me/scratch/QD9p8 */
static int _P3MC_CheckUserDataHead(P3MC_WORK *pw) {
    USER_HEADER *hed = (USER_HEADER*)pw->dhdl->pMemTop;

    if (strcmp(hed->header, HedderID) != 0 || strcmp(hed->footer, FooterID) != 0) {
        return 1;
    }

    if (hed->user.flg == 0) {
        return 0;
    }

    return _P3MC_CheckHead(hed, pw);
}
