#include "animation.h"

void SpaFileHeader::Initialize() {
    ChangePointer();
    if (m_obj_set == NULL) {
        if (m_list.next != NULL) {
            m_list.next = NULL;
        }
        if (m_list.prev != NULL) {
            m_list.prev = NULL;
        }
    }
}
