#include "database.h"
#include "prlib/prlib.h"

PrObjectDatabase prObjectDatabase;

static bool databaseInitialized = false;

PrObjectDatabase::PrObjectDatabase() {
    /* Empty */
}

PrObjectDatabase::~PrObjectDatabase() {
    /* Empty */
}

void PrObjectDatabase::Initialize() {
    databaseInitialized = true;
}

void PrObjectDatabase::Cleanup() {
    if (databaseInitialized) {
        databaseInitialized = false;
    }
}

PrSceneObject* PrObjectDatabase::CreateScene(sceGsDrawEnv1 *draw_env, const char *name, u_int fbp) {
    PrSceneObject *scene = new PrSceneObject(draw_env, name, fbp);
    m_scene_set.Insert(scene);
    return scene;
}

void PrObjectDatabase::DeleteScene(PrSceneObject *scene) {
    if (scene == NULL) {
        return;
    }
    PrCleanupAllSceneModel(scene);

    m_scene_set.Remove(scene);
    delete scene;
}
