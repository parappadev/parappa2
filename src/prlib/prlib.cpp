#include "prpriv.h"

#include "animation.h"
#include "camera.h"
#include "database.h"
#include "model.h"
#include "random.h"
#include "renderstuff.h"
#include "scene.h"

#include <nalib/navector.h>

#include <eetypes.h>
#include <eestruct.h>
#include <libgraph.h>

#include <stdlib.h>

static float prFrameRate = 1.0f;
static float prInverseFrameRate = 1.0f;

/* sbss */
extern PrDebugParam debugParam[2];

static void InitializeDebugParam();

PR_EXTERN
void PrSetFrameRate(float frame_rate) {
    prFrameRate = frame_rate;
    prInverseFrameRate = 1.0f / frame_rate;
}

PR_EXTERN
float PrGetFrameRate() {
    return prFrameRate;
}

PR_EXTERN
void PrInitializeModule(sceGsZbuf zbuf) {
    InitializeDebugParam();
    PrInitializeRandomPool();

    prObjectDatabase.Initialize();
    prRenderStuff.Initialize(zbuf);
}

PR_EXTERN
void PrCleanupModule() {
    prRenderStuff.Cleanup();

    PrCleanupModel(NULL);
    PrCleanupAnimation(NULL);
    PrCleanupCamera(NULL);
    PrCleanupScene(NULL);

    prObjectDatabase.Cleanup();
}

PR_EXTERN
PrSceneObject* PrInitializeScene(sceGsDrawEnv1 *draw_env, const char *name, u_int fbp) {
    return prObjectDatabase.CreateScene(draw_env, name, fbp);
}

PR_EXTERN
PrSceneObject* PrInitializeSceneDBuff(sceGsDBuffDc *dbuff, const char *name, u_int fbp) {
    PrSceneObject *scene = prObjectDatabase.CreateScene(&dbuff->draw01, name, fbp);
    scene->unk90 = dbuff;
}

PR_EXTERN
void PrCleanupScene(PrSceneObject *scene) {
    if (scene == NULL) {
        scene = prObjectDatabase.m_scene_set.m_head;
        while (scene != NULL) {
            prObjectDatabase.DeleteScene(scene);
            scene = prObjectDatabase.m_scene_set.m_head;
        }
    } else {
        prObjectDatabase.DeleteScene(scene);
    }
}

PR_EXTERN
void PrSetSceneFrame() {
    /* Empty */
}

PR_EXTERN
void PrSetSceneEnv(PrSceneObject *scene, sceGsDrawEnv1 *draw_env) {
    scene->unk50 = draw_env->frame1;
    scene->unk58 = draw_env->xyoffset1;
}

PR_EXTERN
void PrPreprocessSceneModel(PrSceneObject *scene) {
    scene->PreprocessModel();
}

PR_EXTERN
PrModelObject* PrInitializeModel(SpmFileHeader *spm, PrSceneObject *scene) {
    if (spm->m_magic != SPM_MAGIC) {
    #if 0 /* (poly): Only present on McDonald's Demo build */
        printf("PRLIB(FATAL): not a SPM file (illegal magic number)\n");
    #endif
        exit(0);
    }
    if (spm->m_version != SPM_VERSION) {
    #if 0 /* (poly): Only present on McDonald's Demo build */
        printf("PRLIB(FATAL): not supported SPM file version %d:%d\n", spm->version, SPM_VERSION);
    #endif
        exit(0);
    }

    PrModelObject *model = new PrModelObject(spm);
    model->Initialize();
    scene->m_model_set.Insert(model);
    model->m_linked_scene = scene;
    return model;
}

PR_EXTERN
SpaFileHeader* PrInitializeAnimation(SpaFileHeader *spa) {
    if (spa->m_magic != SPA_MAGIC) {
        exit(0);
    }

    if (spa->m_version != SPA_VERSION) {
        exit(0);
    }

    spa->Initialize();
    if (spa->m_obj_set == NULL) {
        spa->m_user_data = NULL;
        prObjectDatabase.InsertAnimation(spa);
    }
    return spa;
}

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrInitializeCamera);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrCleanupModel);

PR_EXTERN
void PrCleanupAnimation(SpaFileHeader *animation) {
    if (animation == NULL) {
        animation = prObjectDatabase.m_animation_set.m_head;
        while (animation != NULL) {
            PrCleanupAnimation(animation);
            animation = prObjectDatabase.m_animation_set.m_head;
        }
    } else {
        if (animation->m_obj_set != NULL) {
            prObjectDatabase.RemoveAnimation(animation);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrCleanupCamera);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrCleanupAllSceneModel);

PR_EXTERN
float PrGetAnimationStartFrame(SpaFileHeader *animation) {
    return 0.0f;
}

PR_EXTERN
float PrGetAnimationEndFrame(SpaFileHeader *animation) {
    return animation->unk14 * prFrameRate;
}

PR_EXTERN
float PrGetCameraStartFrame(SpcFileHeader *camera) {
    return 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetCameraEndFrame);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSetModelUserData);

PR_EXTERN
void PrSetAnimationUserData(SpaFileHeader *animation, void *user_data) {
    animation->m_user_data = user_data;
}

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSetCameraUserData);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetModelUserData);

PR_EXTERN
void* PrGetAnimationUserData(SpaFileHeader *animation) {
    return animation->m_user_data;
}

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetCameraUserData);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrLinkAnimation);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrUnlinkAnimation);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetLinkedAnimation);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrLinkPositionAnimation);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrUnlinkPositionAnimation);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetLinkedPositionAnimation);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSelectCamera);

PR_EXTERN
SpcFileHeader* PrGetSelectedCamera(PrSceneObject *scene) {
    return scene->m_camera;
}

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetCurrentCamera);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSetDefaultCamera);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSetAppropriateDefaultCamera);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrShowModel);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetModelMatrix);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrHideModel);

PR_EXTERN
NaVECTOR<float, 4>* PrGetModelPrimitivePosition(PrModelObject *model) {
    static NaVECTOR<float, 4> vector;

    model->GetPrimitivePosition(&vector);
    return &vector;
}

PR_EXTERN
NaVECTOR<float, 4>* PrGetModelScreenPosition(PrModelObject *model) {
    static NaVECTOR<float, 4> vector;

    model->GetScreenPosition(&vector);
    return &vector;
}

int prCurrentStage = 0;

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrAnimateModel);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrAnimateModelPosition);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrAnimateSceneCamera);

PR_EXTERN
void PrRender(PrSceneObject *scene) {
    scene->Render();
}

PR_EXTERN
void PrWaitRender() {
    prRenderStuff.WaitRender();
}

PR_EXTERN
void PrSetStage(int stage) {
    prCurrentStage = stage;
}

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSetDepthOfField);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSetDepthOfFieldLevel);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetFocalLength);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetDefocusLength);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetDepthOfFieldLevel);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSaveContour);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrResetContour);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSavePosture);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrResetPosture);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSetContourBlurAlpha);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSetTransactionBlendRatio);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetContourBlurAlpha);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetContourBlurAlpha2);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetTransactionBlendRatio);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrSetModelDisturbance);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetModelDisturbance);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetVertexNum);

INCLUDE_ASM("asm/nonmatchings/prlib/prlib", PrGetModelName);

PR_EXTERN
char* PrGetAnimationName(SpaFileHeader *animation) {
    return animation->m_name;
}

PR_EXTERN
char* PrGetCameraName(SpcFileHeader *camera) {
    return camera->m_name;
}

PR_EXTERN
char* PrGetSceneName(PrSceneObject *scene) {
    return scene->m_name;
}

PR_EXTERN
PrRENDERING_STATISTICS* PrGetRenderingStatistics() {
    PrRenderStuff *renderStuff = &prRenderStuff;
    return &renderStuff->m_statistics;
}

PR_EXTERN
void PrSetModelVisibillity(PrModelObject *model, u_int node_idx, bool visible) {
    if (node_idx >= model->m_spm_image->m_node_num) {
        return;
    }

    SpmNode *node = model->m_spm_image->m_nodes[node_idx];
    if (visible) {
        node->m_flags &= ~0x20000;
    } else {
        node->m_flags |= 0x20000;
    }
}

PR_EXTERN
SpmFileHeader* PrGetModelImage(PrModelObject *model) {
    return model->m_spm_image;
}

PR_EXTERN
SpaFileHeader* PrGetAnimationImage(SpaFileHeader *animation) {
    return animation;
}

PR_EXTERN
SpcFileHeader* PrGetCameraImage(SpcFileHeader *camera) {
    return camera;
}

PR_EXTERN
void PrSetDebugParam(PrDEBUG_PARAM param, int value) {
    debugParam[param].d = value;
}

PR_EXTERN
void PrSetDebugParamFloat(PrDEBUG_PARAM param, float value) {
    debugParam[param].d = *(int*)&value;
}

PR_EXTERN
int PrGetDebugParam(PrDEBUG_PARAM param) {
    return debugParam[param].d;
}

PR_EXTERN
float PrGetDebugParamFloat(PrDEBUG_PARAM param) {
    return debugParam[param].f;
}

static void InitializeDebugParam() {
    PrSetDebugParamFloat(PR_FLOAT_PARAM_DISTURBANCE, 1.0f);
}
