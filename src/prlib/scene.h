#ifndef PRLIB_SCENE_H
#define PRLIB_SCENE_H

#include "common.h"

#include "prpriv.h"
#include "objectset.h"

#include <eetypes.h>
#include <eestruct.h>
#include <libgraph.h>

class PrModelObject;
class SpcFileHeader;

class PrSceneObject {
public:
    PrSceneObject(sceGsDrawEnv1 *arg0, const char *name, u_int arg2);
    ~PrSceneObject();

    void SelectCamera(SpcFileHeader *camera);
    PrPERSPECTIVE_CAMERA* GetCurrentCamera();
    void SetAppropriateDefaultCamera();

    float GetFocalLength() const;
    float GetDefocusLength() const;
    u_int GetDepthLevel() const;
    void ApplyDepthOfField();

    void PreprocessModel();

    void Render();
    void InitializeVu1();
    void PrepareScreenModelRender();

public:
    PrLinkedList<PrSceneObject> m_list;
    PrObjectSet<PrSceneObject> *m_obj_set;
    PR_PADDING(unkC, 0x4);
    PrPERSPECTIVE_CAMERA m_default_camera;
    sceGsFrame unk50;
    sceGsXyoffset unk58;
    PrObjectSet<PrModelObject> m_model_set;
    SpcFileHeader *m_camera;
    sceGsDrawEnv1 *unk70;
    PR_PADDING(unk74, 0x8);
    float m_camera_time;
    char *m_name;
    float m_default_focal_len;
    float m_default_defocus_len;
    u_int m_default_depth_level;
    sceGsDBuffDc *unk90;
    PR_PADDING(unk94, 0x4);
    PrModelObject *unk98;
    PrModelObject *unk9C;
    PrModelObject *m_screen_model_list;
    PR_PADDING(unkA4, 0x8);
};

#endif /* PRLIB_SCENE_H */
