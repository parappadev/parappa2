#ifndef PRLIB_C_H
#define PRLIB_C_H

#include <eetypes.h>
#include <libgraph.h>
#include <libvu0.h>

typedef void* PR_MODELHANDLE;
typedef void* PR_ANIMATIONHANDLE;
typedef void* PR_CAMERAHANDLE;
typedef void* PR_SCENEHANDLE;
typedef float PR_FRAME;

/* model.cpp */
void PrSetPostureWorkArea(u_int areaTop, int areaSize);

/* prlib.cpp */
void  PrSetFrameRate(float frameRate);
float PrGetFrameRate(void);

void PrInitializeModule(sceGsZbuf zbuf);
void PrCleanupModule(void);

PR_SCENEHANDLE PrInitializeScene(sceGsDrawEnv1 *drawEnv, char *name, u_int fbp);
void PrInitializeSceneDBuff(sceGsDBuff *buff, char *name, u_int fbp);

void PrCleanupScene(PR_SCENEHANDLE scene);

void PrSetSceneFrame(PR_SCENEHANDLE scene, sceGsFrame frame);
void PrSetSceneEnv(PR_SCENEHANDLE scene, sceGsDrawEnv1 *drawEnv);

void PrPreprocessSceneModel(PR_SCENEHANDLE scene);

PR_MODELHANDLE PrInitializeModel(void* modelImage, PR_SCENEHANDLE scene);
PR_ANIMATIONHANDLE PrInitializeAnimation(PR_ANIMATIONHANDLE animImage);
PR_CAMERAHANDLE PrInitializeCamera(PR_CAMERAHANDLE cameraImage);

void PrCleanupModel(PR_MODELHANDLE model);
void PrCleanupAnimation(PR_ANIMATIONHANDLE animation);
void PrCleanupCamera(PR_CAMERAHANDLE camera);
void PrCleanupAllSceneModel(PR_SCENEHANDLE scene);

float PrGetAnimationStartFrame(PR_ANIMATIONHANDLE animation);
float PrGetAnimationEndFrame(PR_ANIMATIONHANDLE animation);

float PrGetCameraStartFrame(PR_CAMERAHANDLE camera);
float PrGetCameraEndFrame(PR_CAMERAHANDLE camera);

void PrSetModelUserData(PR_MODELHANDLE model, int userData);
void PrSetAnimationUserData(PR_ANIMATIONHANDLE animation, int userData);
void PrSetCameraUserData(PR_CAMERAHANDLE camera, int userData);

int PrGetModelUserData(PR_MODELHANDLE model);
int PrGetAnimationUserData(PR_ANIMATIONHANDLE animation);
int PrGetCameraUserData(PR_CAMERAHANDLE camera);

void PrLinkAnimation(PR_MODELHANDLE model, PR_ANIMATIONHANDLE animation);
void PrUnlinkAnimation(PR_MODELHANDLE model);

PR_ANIMATIONHANDLE PrGetLinkedAnimation(PR_MODELHANDLE model);

void PrLinkPositionAnimation(PR_MODELHANDLE model, PR_ANIMATIONHANDLE animation);
void PrUnlinkPositionAnimation(PR_MODELHANDLE model);

PR_ANIMATIONHANDLE PrGetLinkedPositionAnimation(PR_MODELHANDLE model);

void PrSelectCamera(PR_CAMERAHANDLE camera, PR_SCENEHANDLE scene);
PR_CAMERAHANDLE PrGetSelectedCamera(PR_SCENEHANDLE scene);

void* PrGetCurrentCamera(PR_SCENEHANDLE scene);

void PrSetDefaultCamera(PR_SCENEHANDLE scene, PR_CAMERAHANDLE camera);
void PrSetAppropriateDefaultCamera(PR_SCENEHANDLE scene);

void PrShowModel(PR_MODELHANDLE model, sceVu0FMATRIX *matrix);

float* PrGetModelMatrix(PR_MODELHANDLE model);

void PrHideModel(PR_MODELHANDLE model);

float* PrGetModelPrimitivePosition(PR_MODELHANDLE model);
float* PrGetModelScreenPosition(PR_MODELHANDLE model);

void PrAnimateModel(PR_MODELHANDLE model, float time);
void PrAnimateModelPosition(PR_MODELHANDLE model, float time);
void PrAnimateSceneCamera(PR_SCENEHANDLE scene, float time);

void PrRender(PR_SCENEHANDLE scene);
void PrWaitRender(void);

void PrSetStage(int stage);

void PrSetDepthOfField(PR_MODELHANDLE scene, float focalLen, float defocusLen);
void PrSetDepthOfFieldLevel(PR_SCENEHANDLE scene, u_int depthLevel);

float PrGetFocalLength(PR_SCENEHANDLE scene);
float PrGetDefocusLength(PR_SCENEHANDLE scene);

u_int PrGetDepthOfFieldLevel(PR_SCENEHANDLE scene);

void PrSaveContour(PR_MODELHANDLE model);
void PrResetContour(PR_MODELHANDLE model);

void PrSavePosture(PR_MODELHANDLE model);
void PrResetPosture(PR_MODELHANDLE model);

void PrSetContourBlurAlpha(PR_MODELHANDLE model, float blurAlpha, float blurAlpha2);

void PrSetTransactionBlendRatio(PR_MODELHANDLE model, float blendRatio);

float PrGetContourBlurAlpha(PR_MODELHANDLE model);
float PrGetContourBlurAlpha2(PR_MODELHANDLE model);

float PrGetTransactionBlendRatio(PR_MODELHANDLE model);

void  PrSetModelDisturbance(PR_MODELHANDLE model, float disturbance);
float PrGetModelDisturbance(PR_MODELHANDLE model);

u_int PrGetVertexNum(PR_MODELHANDLE model);

char* PrGetModelName(PR_MODELHANDLE model);
char* PrGetAnimationName(PR_ANIMATIONHANDLE animation);
char* PrGetCameraName(PR_CAMERAHANDLE camera);
char* PrGetSceneName(PR_SCENEHANDLE scene);

void* PrGetRenderingStatistics(void);

void PrSetModelVisibillity(PR_MODELHANDLE model, u_int nodeIndex, u_int visible);

PR_MODELHANDLE     PrGetModelImage(PR_MODELHANDLE model);
PR_ANIMATIONHANDLE PrGetAnimationImage(PR_ANIMATIONHANDLE animation);
PR_CAMERAHANDLE    PrGetCameraImage(PR_CAMERAHANDLE camera);

void  PrSetDebugParam(int param, int value);
void  PrSetDebugParamFloat(int param, float value);
int   PrGetDebugParam(int param);
float PrGetDebugParamFloat(int param);

/* menderer.cpp */
void  PrDecelerateMenderer(int speed);
void  PrRestartMenderer(void);

void  PrSetMendererRatio(float ratio);
float PrGetMendererRatio(void);

void  PrSetMendererDirection(int direction);
int   PrGetMendererDirection(void);

void  PrSetMendererColorModulation(int color);
int   PrIsMendererColorModulation(void);

void  PrInitializeMenderer(u_int tbp, void *noodlePicture, u_int fbp);
void  PrRenderMenderer(void);

/* menderercreate.cpp */
void PrCreateMendererTexture(void);

#endif /* PRLIB_C_H */
