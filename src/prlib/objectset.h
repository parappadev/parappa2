#ifndef PRLIB_OBJECTSET_H
#define PRLIB_OBJECTSET_H

#include "common.h"

#include "linkedlist.h"

template <typename T>
class PrObjectSet {
public:
    PrObjectSet() {
        m_head = NULL;
        m_tail = NULL;
        m_num  = 0;
    }
    ~PrObjectSet() {}

    void Insert(T *obj) {
        if (m_tail == NULL) {
            m_head = obj;
        } else {
            m_tail->m_list.next = obj;
            obj->m_list.prev = m_tail;
        }

        m_tail = obj;
        m_tail->m_obj_set = this;
        m_num++;
    }

public:
    T *m_head;
    T *m_tail;
    int m_num;
};

#endif /* PRLIB_OBJECTSET_H */
