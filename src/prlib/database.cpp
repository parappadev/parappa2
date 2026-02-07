#include "database.h"
#include "prlib/prlib.h"

PrObjectDatabase prObjectDatabase;

static bool databaseInitialized = false;

PrObjectDatabase::PrObjectDatabase() {
}

PrObjectDatabase::~PrObjectDatabase() {
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
    if (scene == NULL) return;
    PrCleanupAllSceneModel(scene);

    if (scene->m_obj_set != NULL) {
        scene->m_obj_set = NULL;
        PrSceneObject *next = scene->m_list.next;
        PrSceneObject *prev = scene->m_list.prev;
        if (next != NULL) {
            next->m_list.prev = prev;
            scene->m_list.next = NULL;
        } else {
            m_scene_set.m_tail = prev;
        }
        if (prev != NULL) {
            prev->m_list.next = next;
            scene->m_list.prev = NULL;
        } else {
            m_scene_set.m_head = next;
        }
        m_scene_set.m_num--;
    }
    if (scene != NULL) {
        delete scene;
    }
}
