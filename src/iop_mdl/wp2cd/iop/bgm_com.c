#include "../wp2cd.h"

#include <intrman.h>
#include <libcdvd.h>
#include <sifrpc.h>
#include <thread.h>

#include <stdio.h>

/* bgm_play.c */
extern void         BgmSetVolumeDirect(unsigned int vol);
extern void         BgmSetMasterVolume(unsigned int vol);
extern void         BgmCdInit(int mode);
extern void         BgmSdInit(int status);
extern int          BgmInit(int block_size);
extern void         BgmQuit(int status);
extern int          BgmOpen(char *filename);
extern int          BgmOpenFLoc(sceCdlFILE *fpLoc);
extern void         BgmClose(int status);
extern int          BgmPreLoad(void);
extern void         BgmPreLoadBack(void);
extern int          BgmReadBuffFull(void);
extern int          BgmStart(void);
extern void         BgmStop(unsigned int vol);
extern void         BgmSetVolume(unsigned int vol);
extern void         BgmSetMode(u_int maxChan);
extern unsigned int BgmGetMode(void);
extern int          BgmSeek(unsigned int ofs);
extern int          BgmSeekFLoc(sceCdlFILE *fpLoc);
extern void         BgmSetChannel(u_int chan);
extern void         BgmSetTrPoint(u_int trpos);
extern int          BgmGetTime(void);
extern int          BgmGetTSample(void);
extern int          BgmGetCdErrCode(void);

static void* bgmFunc(unsigned int command, void *data, int size);

extern int gRpcArg[16];

int sce_bgm_loop(void) {
    sceSifQueueData qd;
    sceSifServeData sd;

    CpuEnableIntr();
    EnableIntr(INUM_DMA_4);
    EnableIntr(INUM_DMA_7);
    EnableIntr(INUM_SPU);

    sceSifInitRpc(0);

    sceSifSetRpcQueue(&qd, GetThreadId());
    sceSifRegisterRpc(&sd, WP2CD_DEV, bgmFunc, gRpcArg, NULL, NULL, &qd);

    sceSifRpcLoop(&qd);
    return 0;
}

int ret = 0;

static void* bgmFunc(unsigned int command, void *data, int size) {
    switch (command) {
    case WP2_INIT:
        ret = BgmInit(*(int*)data);
        break;
    case WP2_QUIT:
        BgmQuit(*(int*)data);
        break;
    case WP2_OPEN:
        ret = BgmOpen(data);
        break;
    case WP2_CLOSE:
        BgmClose(*(int*)data);
        break;
    case WP2_PRELOAD:
        ret = BgmPreLoad();
        break;
    case WP2_START:
        ret = BgmStart();
        break;
    case WP2_STOP:
        BgmStop(*(int*)data);
        break;
    case WP2_SEEK:
        ret = BgmSeek(*(int*)data);
        break;
    case WP2_SETVOLUME:
        BgmSetVolume(*(int*)data);
        break;
    case WP2_SETVOLDIRECT:
        BgmSetVolumeDirect(*(int*)data);
        break;
    case WP2_SETMASTERVOL:
        BgmSetMasterVolume(*(int*)data);
        break;
    case WP2_SETMODE:
        BgmSetMode(*(int*)data);
        break;
    case WP2_GETMODE:
        ret = BgmGetMode();
        break;
    case WP2_SDINIT:
        BgmSdInit(*(int*)data);
        break;
    case WP2_SETCHANNEL:
        BgmSetChannel(*(int*)data);
        break;
    case WP2_CDINIT:
        BgmCdInit(*(int*)data);
        break;
    case WP2_GETTIME:
        ret = BgmGetTime();
        break;
    case WP2_GETTIMESAMPLE:
        ret = BgmGetTSample();
        break;
    case WP2_GETCDERRCODE:
        ret = BgmGetCdErrCode();
        break;
    case WP2_OPENFLOC:
        ret = BgmOpenFLoc(data);
        break;
    case WP2_SEEKFLOC:
        ret = BgmSeekFLoc(data);
        break;
    case WP2_PRELOADBACK:
        BgmPreLoadBack();
        break;
    case WP2_SETTRPOINT:
        BgmSetTrPoint(*(int*)data);
        break;
    case WP2_READBUFF:
        ret = BgmReadBuffFull();
        break;
    default:
        printf("EzBGM driver error: unknown command %d \n", *(int*)data);
        break;
    }

    return &ret;
}
