#ifndef PRLIB_PRPRIV_H
#define PRLIB_PRPRIV_H

#include "common.h"

#include <nalib/navector.h>
#include <nalib/namatrix.h>

#include <libgraph.h>

class SpmFileHeader;
class SpaFileHeader;
class SpcFileHeader;
class PrModelObject;
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

void PrSetFrameRate(float frame_rate);
float PrGetFrameRate();
void PrInitializeModule(sceGsZbuf zbuf);
void PrCleanupModule();
PrSceneObject* PrInitializeScene(sceGsDrawEnv1 *draw_env, const char *name, u_int fbp);
PrSceneObject* PrInitializeSceneDBuff(sceGsDBuffDc *dbuff, const char *name, u_int fbp);
void PrCleanupScene(PrSceneObject *scene);
void PrSetSceneFrame();
void PrSetSceneEnv(PrSceneObject *scene, sceGsDrawEnv1 *draw_env);
void PrPreprocessSceneModel(PrSceneObject *scene);
PrModelObject* PrInitializeModel(SpmFileHeader *spm, PrSceneObject *scene);
SpaFileHeader* PrInitializeAnimation(SpaFileHeader *spa);
SpcFileHeader* PrInitializeCamera(SpcFileHeader *spc);
void PrCleanupModel(PrModelObject *model);
void PrCleanupAnimation(SpaFileHeader *animation);
void PrCleanupCamera(SpcFileHeader *camera);
void PrCleanupAllSceneModel(PrSceneObject *scene);
float PrGetAnimationStartFrame(SpaFileHeader *animation);
float PrGetAnimationEndFrame(SpaFileHeader *animation);
float PrGetCameraStartFrame(SpcFileHeader *camera);
float PrGetCameraEndFrame(SpcFileHeader *camera);
void PrSetModelUserData(PrModelObject *model, void *user_data);
void PrSetAnimationUserData(SpaFileHeader *animation, void *user_data);
void PrSetCameraUserData(SpcFileHeader *camera, void *user_data);
void* PrGetModelUserData(PrModelObject *model);
void* PrGetAnimationUserData(SpaFileHeader *animation);
void* PrGetCameraUserData(SpcFileHeader *camera);
void PrLinkAnimation(PrModelObject *model, SpaFileHeader *animation);
void PrUnlinkAnimation(PrModelObject *model);
SpaFileHeader* PrGetLinkedAnimation(PrModelObject *model);
void PrLinkPositionAnimation(PrModelObject *model, SpaFileHeader *animation);
void PrUnlinkPositionAnimation(PrModelObject *model);
SpaFileHeader* PrGetLinkedPositionAnimation(PrModelObject *model);
void PrSelectCamera(SpcFileHeader *camera, PrSceneObject *scene);
SpcFileHeader* PrGetSelectedCamera(PrSceneObject *scene);
PrPERSPECTIVE_CAMERA* PrGetCurrentCamera(PrSceneObject *scene);
void PrSetDefaultCamera(NaMATRIX<float, 4, 4> *arg0, NaMATRIX<float, 4, 4> *arg1);
void PrSetAppropriateDefaultCamera(PrSceneObject *scene);
void PrShowModel(PrModelObject *model, NaMATRIX<float, 4, 4> *position);
NaMATRIX<float, 4, 4>* PrGetModelMatrix(PrModelObject *model);
void PrHideModel(PrModelObject *model);
NaVECTOR<float, 4>* PrGetModelPrimitivePosition(PrModelObject *model);
NaVECTOR<float, 4>* PrGetModelScreenPosition(PrModelObject *model);
void PrAnimateModel(PrModelObject *model, float time);
void PrAnimateModelPosition(PrModelObject *model, float time);
void PrAnimateSceneCamera(PrSceneObject *scene, float time);
void PrRender(PrSceneObject *scene);
void PrWaitRender();
void PrSetStage(int stage);
void PrSetDepthOfField(PrSceneObject *scene, float focal_lng, float defocus_lng);
void PrSetDepthOfFieldLevel(PrSceneObject *scene, u_int level);
float PrGetFocalLength(PrSceneObject *scene);
float PrGetDefocusLength(PrSceneObject *scene);
u_int PrGetDepthOfFieldLevel(PrSceneObject *scene);
void PrSaveContour(PrModelObject *model);
void PrResetContour(PrModelObject *model);
void PrSavePosture(PrModelObject *model);
void PrResetPosture(PrModelObject *model);
void PrSetContourBlurAlpha(PrModelObject *model, float alpha, float alpha2);
void PrSetTransactionBlendRatio(PrModelObject *model, float ratio);
float PrGetContourBlurAlpha(PrModelObject *model);
float PrGetContourBlurAlpha2(PrModelObject *model);
float PrGetTransactionBlendRatio(PrModelObject *model);
void PrSetModelDisturbance(PrModelObject *model, float disturbance);
float PrGetModelDisturbance(PrModelObject *model);
int PrGetVertexNum(PrModelObject *model);
char* PrGetModelName(PrModelObject *model);
char* PrGetAnimationName(SpaFileHeader *animation);
char* PrGetCameraName(SpcFileHeader *camera);
char* PrGetSceneName(PrSceneObject *scene);
PrRENDERING_STATISTICS* PrGetRenderingStatistics();
void PrSetModelVisibillity(PrModelObject *model, u_int node_idx, bool visible);
SpmFileHeader* PrGetModelImage(PrModelObject *model);
SpaFileHeader* PrGetAnimationImage(SpaFileHeader *animation);
SpcFileHeader* PrGetCameraImage(SpcFileHeader *camera);
void PrSetDebugParam(PrDEBUG_PARAM param, int value);
void PrSetDebugParamFloat(PrDEBUG_PARAM param, float value);
int PrGetDebugParam(PrDEBUG_PARAM param);
float PrGetDebugParamFloat(PrDEBUG_PARAM param);

}

#endif /* PRLIB_PRPRIV_H */
