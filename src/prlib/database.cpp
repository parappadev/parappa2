#include "database.h"

#include "prpriv.h"

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
    InsertScene(scene);
    return scene;
}

void PrObjectDatabase::DeleteScene(PrSceneObject *scene) {
    if (scene == NULL) {
        return;
    }

    PrCleanupAllSceneModel(scene);
    RemoveScene(scene);
    delete scene;
}
