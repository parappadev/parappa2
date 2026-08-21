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

    void Remove(T *obj) {
        obj->m_obj_set = NULL;

        T *next = obj->m_list.next;
        T *prev = obj->m_list.prev;

        if (next != NULL) {
            next->m_list.prev = prev;
            obj->m_list.next = NULL;
        } else {
            m_tail = prev;
        }

        if (prev != NULL) {
            prev->m_list.next = next;
            obj->m_list.prev = NULL;
        } else {
            m_head = next;
        }

        m_num--;
    }

public:
    T *m_head;
    T *m_tail;
    int m_num;
};

#endif /* PRLIB_OBJECTSET_H */
