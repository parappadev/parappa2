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
    PrObjectSet<PrSceneObject> m_scene_set;
    PrObjectSet<SpaFileHeader> m_animation_set;
    PrObjectSet<SpcFileHeader> m_camera_set;
};

extern PrObjectDatabase prObjectDatabase;

#endif /* PRLIB_DATABASE_H */
