#ifndef PRLIB_DATABASE_H
#define PRLIB_DATABASE_H

#include "common.h"

#include "objectset.h"
#include "animation.h"
#include "camera.h"
#include "scene.h"

#include <eetypes.h>
#include <libgraph.h>

class PrSceneObject;

class PrObjectDatabase {
public:
    PrObjectDatabase();
    ~PrObjectDatabase();

    void Initialize();
    void Cleanup();

    PrSceneObject* CreateScene(sceGsDrawEnv1 *draw_env, const char *name, u_int fbp);
    void DeleteScene(PrSceneObject *scene);

public:
    void InsertScene(PrSceneObject *scene) {
        m_scene_set.Insert(scene);
    }
    void RemoveScene(PrSceneObject *scene) {
        if (scene->m_obj_set != NULL) {
            m_scene_set.Remove(scene);
        }
    }

    void InsertAnimation(SpaFileHeader *animation) {
        m_animation_set.Insert(animation);
    }
    void RemoveAnimation(SpaFileHeader *animation) {
        if (animation->m_obj_set != NULL) {
            m_animation_set.Remove(animation);
        }
    }

public:
    PrObjectSet<PrSceneObject> m_scene_set;
    PrObjectSet<SpaFileHeader> m_animation_set;
    PrObjectSet<SpcFileHeader> m_camera_set;
};

extern PrObjectDatabase prObjectDatabase;

#endif /* PRLIB_DATABASE_H */
