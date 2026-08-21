#include "common.h"

#include <eetypes.h>
#include <eestruct.h>

#include "camera.h"
#include "microprogram.h"
#include "model.h"
#include "animation.h"

void SpmFileHeader::ChangePointer() {
    if (m_flags & 0x1) {
        return;
    }

    this->unk64 = CalculatePointer<int>(this->unk64);
    m_nodes = CalculatePointer<SpmNode*>(m_nodes);

    for (int i = 0; i < m_node_num; i++) {
        m_nodes[i] = CalculatePointer<SpmNode>(m_nodes[i]);
    }

    /* Change node pointers starting from the root. */
    (*m_nodes)->ChangePointer(this, NULL);
    m_flags |= 0x1;
}

void SpmNode::ChangePointer(SpmFileHeader *model, SpmNode *arg1) {
    this->unk158 = model;
    this->unk164 = arg1;

    this->unk15C = model->CalculatePointer<SpmNode>(this->unk15C);
    this->unk160 = model->CalculatePointer<SpmNode>(this->unk160);

    this->unk16C[0] = model->CalculatePointer<PrVuNodeHeaderDmaPacket>(this->unk16C[0]);
    this->unk16C[1] = model->CalculatePointer<PrVuNodeHeaderDmaPacket>(this->unk16C[1]);

    this->unk17C = this->unk16C[0];
    if (this->unk16C[0] == NULL) {
        this->unk17C = this->unk16C[1];
    }

    for (u_int i = 0; i < 2; i++) {
        if (this->unk16C[i]) {
            this->unk16C[i]->unk194 = SCE_VIF1_SET_MSCAL(PrGetMicroProgramAddress(this->unk16C[i]->unk60), 0);
        }
    }

    if (m_flags & 0xff0) {
        this->unk198 = model->CalculatePointer<int>(this->unk198);
        if (m_flags & 0x10) {
            this->unk1B4 = model->CalculatePointer<int>(this->unk1B4);
            this->unk1B8 = model->CalculatePointer<int>(this->unk1B8);
        } else if (m_flags & 0x20) {
            this->unk1B4 = model->CalculatePointer<int>(this->unk1B4);
        }

        this->unk1A0 = model->CalculatePointer<int>(this->unk1A0);
        this->unk1A4 = model->CalculatePointer<PrVuNodeHeaderDmaPacket>(this->unk1A4);
        PrVuNodeHeaderDmaPacket *s0 = this->unk1A4;
        if (s0 != NULL) {
            s0->unk194 = SCE_VIF1_SET_MSCAL(PrGetMicroProgramAddress(PR_MICRO_PROGRAM_CONTOUR), 0);
        }
    }

    SpmNode *s0 = this->unk15C;
    while (s0 != 0) {
        s0->ChangePointer(model, this);
        s0 = s0->unk160;
    }
}

void SpaFileHeader::ChangePointer() {
    if (m_flags & 0x1) {
        return;
    }

    m_nodes = m_nodes_list;

    this->unk38 = CalculatePointer<int>(this->unk38);

    for (int i = 0; i < m_node_num; i++) {
        SpaNodeAnimation **node = &m_nodes[i];
        if ((*node) != NULL) {
            (*node) = CalculatePointerUnsafe<SpaNodeAnimation>(*node);
            (*node)->ChangePointer(this);
            (*node)->Optimize();
        }
    }

    m_flags |= 0x1;
}

INCLUDE_ASM("asm/nonmatchings/prlib/setpointer", ChangePointer__16SpaNodeAnimationP13SpaFileHeader);

void SpcFileHeader::ChangePointer() {
    if (m_flags & 0x1) {
        return;
    }

    this->unk74 = CalculatePointer<int>(this->unk74);
    
    this->unk88 = CalculatePointer<SpaTrack<NaVECTOR<float, 4> > >(this->unk88);
    if (this->unk88 != NULL) {
        this->unk88->ChangePointer();
    }

    this->unk8C = CalculatePointer<SpaTrack<NaVECTOR<float, 4> > >(this->unk8C);
    if (this->unk8C != NULL) {
        this->unk8C->ChangePointer();
    }

    this->unk90 = CalculatePointer<SpaTrack<float> >(this->unk90);
    if (this->unk90 != NULL) {
        this->unk90->ChangePointer();
    }

    this->unk94 = CalculatePointer<SpaTrack<float> >(this->unk94);
    if (this->unk94 != NULL) {
        this->unk94->ChangePointer();
    }

    if (m_flags & 0x8) {
        m_focal_len_track = CalculatePointer<SpaTrack<float> >(m_focal_len_track);
        if (m_focal_len_track != NULL) {
            m_focal_len_track->ChangePointer();
        }

        m_defocus_len_track = CalculatePointer<SpaTrack<float> >(m_defocus_len_track);
        if (m_defocus_len_track != NULL) {
            m_defocus_len_track->ChangePointer();
        }
    }

    m_flags |= 1;
}
