#ifndef PRLIB_PRPRIV_H
#define PRLIB_PRPRIV_H

#include "common.h"

#include <nalib/navector.h>

class PrModelObject;
class SpaFileHeader;
class SpcFileHeader;
class PrSceneObject;

#define PR_DECACHE(addr) (void*)((u_int)(addr) & 0x0fffffff)
#define PR_DMA_SPR_ADDR(addr) (void*)((((u_int)addr) & 0x3fff) | 0x80000000)

typedef struct { // 0x40
    /* 0x00 */ NaVECTOR<float, 4> position;
    /* 0x10 */ NaVECTOR<float, 4> interest;
    /* 0x20 */ NaVECTOR<float, 4> up;
    /* 0x30 */ float aspect;
    /* 0x34 */ float field_of_view;
    /* 0x38 */ float near_clip;
    /* 0x3c */ float far_clip;
} PrPERSPECTIVE_CAMERA;

typedef struct { // 0x2c
    /* 0x00 */ unsigned int node_num;
    /* 0x04 */ unsigned int opaque_context1_node_num;
    /* 0x08 */ unsigned int transmit_context1_node_num;
    /* 0x0c */ unsigned int opaque_context2_node_num;
    /* 0x10 */ unsigned int transmit_context2_node_num;
    /* 0x14 */ unsigned short render_time0;
    /* 0x16 */ unsigned short render_time1;
    /* 0x18 */ unsigned short render_time2;
    /* 0x1a */ unsigned short render_time3;
    /* 0x1c */ unsigned short render_time4;
    /* 0x1e */ unsigned short render_time5;
    /* 0x20 */ unsigned short render_time6;
    /* 0x22 */ unsigned short render_time7;
    /* 0x24 */ unsigned short render_time8;
    /* 0x28 */ bool dynamic_append_transmit_node;
} PrRENDERING_STATISTICS;

typedef enum {
    PR_FLOAT_PARAM_DISTURBANCE,
    PR_DEBUG_PARAM_NUM,
} PrDEBUG_PARAM;

typedef union {
    int   d;
    float f;
} PrDebugParam;

extern int prCurrentStage;

PR_EXTERN {

void PrCleanupModel(PrModelObject *model);
void PrCleanupAnimation(SpaFileHeader *model);
void PrCleanupCamera(SpcFileHeader *camera);
void PrCleanupScene(PrSceneObject *scene);
void PrCleanupAllSceneModel(PrSceneObject *scene);

}

#endif /* PRLIB_PRPRIV_H */
