#include "spadata.h"

#include "animation.h"
#include "model.h"

#include <math.h>

template <>
const NaVECTOR<float, 4>* SpaTrack<NaVECTOR<float, 4> >::GetSprineValue(u_int seg, float arg1) const;

u_int SpaTrackBase::SearchSegment(float arg0) const {
    if (this->unk4 == 1) {
        return (u_int)-1;
    }

    if (arg0 <= this->unkC[0]) {
        return (u_int)-1;
    }

    if (arg0 >= this->unkC[this->unk4 - 1]) {
        return this->unk4;
    }

    if (arg0 >= this->unkC[this->unk8]) {
        if (arg0 < this->unkC[this->unk8 + 1]) {
            return this->unk8;
        }

        if ((this->unk8 + 2) < this->unk4) {
            if (arg0 < this->unkC[this->unk8 + 2]) {
                return ++this->unk8;
            }
        }
    } else if (this->unk8 != 0) {
        if (arg0 >= this->unkC[this->unk8 - 1]) {
            return --this->unk8;
        }
    }

    int right = this->unk4 - 2;
    int left = 0;
    int mid = 0;

    while (left <= right) {
        mid = (left + right) / 2;
        if (arg0 < this->unkC[mid]) {
            right = mid - 1;
        } else if (arg0 >= this->unkC[mid + 1]) {
            left = mid + 1;
        } else {
            break;
        }
    }

    this->unk8 = mid;
    return this->unk8;
}

template <>
const int* SpaTrack<int>::GetValue(float arg0) const {
    if (this->unk2 & 0x1) {
        float f13 = this->unkC[this->unk4 - 1];
        if (arg0 < 0.0f || arg0 >= f13) {
            arg0 = fmodf(arg0, f13);
        }
    }

    u_int seg = this->SearchSegment(arg0);
    if (seg == (u_int)-1) {
        return &this->unk10[0];
    }

    if (seg == this->unk4) {
        return &this->unk10[seg - 1];
    } else {
        return &this->unk10[seg];
    }
}

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", GetMatrix__C12SpaTransformf);

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", GetMatrix__C16SpaNodeAnimationf);

bool SpaNodeAnimation::IsVisible(float arg0) const {
    if (this->unk4 == NULL) {
        return true;
    }

    return *this->unk4->GetValue(arg0);
}

bool SpaFileHeader::IsNodeVisible(SpmNode *arg0, float arg1) const {
    SpaNodeAnimation *a0 = m_nodes[arg0->unk150];
    SpmNode *a2 = arg0->unk164;

    if (a0 != NULL && a0->unk4 == NULL) {
        a0 = NULL;
    }

    if (a2 != NULL) {
        if (!(a2->m_flags & 0x4000)) {
            return false;
        }
        if (a2->m_flags & 0x40000) {
            if (a0 == NULL) {
                arg0->m_flags |= 0x40000;
                if (a2->m_flags & 0x4000) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }

    if (a0 != NULL) {
        arg0->m_flags |= 0x40000;
        return a0->IsVisible(arg1);
    }

    arg0->m_flags &= ~0x40000;
    return (arg0->m_flags & 0x20000) ? false : true;
}

bool SpaTransform::IsEverIdentical() {
    switch (this->unk0) {
    case 0:
        if (this->unk14 == 1) {
            bool v0 = false;
            if (this->unk20[0][0] == 1.0f) {
                if (this->unk20[0][1] != 1.0f) {
                    return false;
                }
                if (this->unk20[0][2] == 1.0f) {
                    v0 = true;
                }
            }
            return v0;
        }

        return false;

    case 1:
        if (this->unk14 == 1) {
            if (this->unk20[0][3] == 0.0f) {
                return true;
            }
        }

        return false;

    case 2:
    case 3:
    case 4:
        if (this->unk14 == 1) {
            if (this->unk20[0][0] == 0.0f) {
                return true;
            }
        }

        return false;

    case 5:
        if (this->unk14 == 1) {
            bool v0 = false;
            if (this->unk20[0][0] == 0.0f) {
                if (this->unk20[0][1] != 0.0f) {
                    return false;
                }
                if (this->unk20[0][2] == 0.0f) {
                    v0 = true;
                }
            }
            return v0;
        }

        return false;

    case 6:
        if (this->unk14 == 1) {
            return this->unk20.inl0();
        }

        return false;
        
    case 7:
        if (this->unk14 == 1) {
            bool v0 = false;
            if (this->unk20[0][0] == 0.0f) {
                if (this->unk20[0][1] != 0.0f) {
                    return false;
                }
                if (this->unk20[0][2] == 0.0f) {
                    v0 = true;
                }
            }
            return v0;
        }

        return false;

    default:
        NaMATRIX<float, 4, 4>& a2 = NaMATRIX<float, 4, 4>::IDENT;
        return a2.inl1();
    }
}

int SpaNodeAnimation::Optimize() {
    int remove_count = 0;

    for (int i = 0; i < this->unk8; i++) {
        SpaTransform *transform = this->unkC[i];
        if (transform == NULL || transform->IsEverIdentical()) {
            remove_count++;
            continue;
        }
        this->unkC[i - remove_count] = this->unkC[i];
    }

    this->unk8 -= remove_count;
    return remove_count;
}

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", GetLinearValue__Ct8SpaTrack1Zt8NaVECTOR2Zfi4Uif);

template <>
const NaVECTOR<float, 4>* SpaTrack<NaVECTOR<float, 4> >::GetValue(float arg0) const {
    if (this->unk2 & 0x1) {
        float f13 = this->unkC[this->unk4 - 1];
        if (arg0 < 0.0f || arg0 >= f13) {
            arg0 = fmodf(arg0, f13);
        }
    }

    u_int seg = this->SearchSegment(arg0);

    if (seg == (u_int)-1) {
        return &this->unk10[0];
    }

    if (seg == this->unk4) {
        if (this->unk0 == 0) {
            return &this->unk10[(seg - 1) * 3];
        } else {
            return &this->unk10[seg - 1];
        }
    }

    switch (this->unk0) {
    case 0:
        return this->GetSprineValue(seg, arg0);
    case 1:
        return this->GetLinearValue(seg, arg0);
    case 2:
        return &this->unk10[seg];
    default:
        break;
    }

    return NULL;
}

/* nalib/navector.h */
INCLUDE_ASM("asm/nonmatchings/prlib/spadata", func_00149168);

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", func_001491C0);

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", func_00149270);

/* prlib/spadata.cpp */
INCLUDE_ASM("asm/nonmatchings/prlib/spadata", GetSprineValue__Ct8SpaTrack1ZfUif);

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", GetLinearValue__Ct8SpaTrack1ZfUif);

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", GetValue__Ct8SpaTrack1Zff);

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", GetSprineValue__Ct8SpaTrack1Zt8NaMATRIX3Zfi4i4Uif);

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", GetLinearValue__Ct8SpaTrack1Zt8NaMATRIX3Zfi4i4Uif);

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", GetValue__Ct8SpaTrack1Zt8NaMATRIX3Zfi4i4f);

/* nalib/navector.h */
INCLUDE_ASM("asm/nonmatchings/prlib/spadata", func_0014ABE0);

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", func_0014ACE8);

INCLUDE_ASM("asm/nonmatchings/prlib/spadata", func_0014AFE0);

template <>
const NaVECTOR<float, 4>* SpaTrack<NaVECTOR<float, 4> >::GetSprineValue(u_int seg, float arg1) const {
    float f2 = this->unkC[seg + 1] - this->unkC[seg];
    const NaVECTOR<float, 4> *a0 = &this->unk10[seg * 3];
    if (f2 == 0.0f) {
        return a0;
    }

    float f0 = (arg1 - this->unkC[seg]) / f2;

    /*
     * FIXME(poly): These `tmp_X` symbols aren't real
     * and are product of the static NaVECTOR instances.
     *
     * The solution would be to make these static
     * (when the TU's .bss matches, of course), and
     * the compiler should generate these temp. symbols.
     *
     * The symbols themselves are meant to call the
     * constructor once, though in this case there's
     * no actual call because it is inlined (empty constructor).
     */
    extern NaVECTOR<float, 4> return_buffer;
    extern int tmp_0_1744;
    if (tmp_0_1744 == 0) {
        tmp_0_1744 = 1;
    }

    #if 0
        vf04.xyzw = a0[0];
        vf05.xyzw = a0[3];
        vf01.xyzw = vf04.xyzw - vf05.xyzw;
        
        vf06.xyzw = a0[2];
        vf07.xyzw = a0[4];
        vf02.xyzw = vf06.xyzw + vf07.xyzw;
        
        vf08.x    = f2;
        ACC.xyzw  = vf01.xyzw + vf01.xyzw;
        vf03.xyzw = ACC.xyzw + (vf02.xyzw * vf08.x);
        
        vf09.x    = f0;
        ACC.xyzw  = vf06.xyzw + vf06.xyzw;
        vf02.xyzw = ACC.xyzw + (vf07.xyzw * vf00.w);
        ACC.w     = vf00.w + vf00.w;
        vf08.w    = ACC.w + (vf00.w * vf00.w);
        ACC.xyzw  = vf03.xyzw * vf09.x;
        ACC.xyzw  = ACC.xyzw - (vf02.xyzw * vf08.x);
        vf10.x    = vf09.x * vf08.x;
        vf02.x    = vf09.x * vf09.x;
        vf03.xyzw = ACC.xyzw - (vf01.xyzw * vf08.w);
        ACC.xyzw  = vf04.xyzw + vf00.x;
        ACC.xyzw  = ACC.xyzw + (vf06.xyzw * vf10.x);
        vf01.xyzw = ACC.xyzw + (vf03.xyzw * vf02.x);
        return_buffer = vf01.xyzw;
    #else
    asm volatile(
        "lqc2     $vf04,  0x00(%1)       \n\t"
        "lqc2     $vf05,  0x30(%1)       \n\t"
        "vsub     $vf01,  $vf04,  $vf05  \n\t"
        
        "lqc2     $vf06,  0x20(%1)       \n\t"
        "lqc2     $vf07,  0x40(%1)       \n\t"
        "vadd     $vf02,  $vf06,  $vf07  \n\t"
        
        "qmtc2    %2,     $vf08          \n\t"
        "vadda    ACC,    $vf01,  $vf01  \n\t"
        "vmaddx   $vf03,  $vf02,  $vf08  \n\t"
        
        "qmtc2    %3,     $vf09          \n\t"
        "vadda    ACC,    $vf06,  $vf06  \n\t"
        "vmaddw   $vf02,  $vf07,  $vf00  \n\t"
        "vadda.w  ACC,    $vf00,  $vf00  \n\t"
        "vmadd.w  $vf08,  $vf00,  $vf00  \n\t"
        "vmulax   ACC,    $vf03,  $vf09  \n\t"
        "vmsubax  ACC,    $vf02,  $vf08  \n\t"
        "vmul.x   $vf10,  $vf09,  $vf08  \n\t"
        "vmul.x   $vf02,  $vf09,  $vf09  \n\t"
        "vmsubw   $vf03,  $vf01,  $vf08  \n\t"
        "vaddax   ACC,    $vf04,  $vf00  \n\t"
        "vmaddax  ACC,    $vf06,  $vf10  \n\t"
        "vmaddx   $vf01,  $vf03,  $vf02  \n\t"
        "sqc2     $vf01,  0(%0)          \n\t"
    : : "r"(&return_buffer), "r"(a0), "r"(f2), "r"(f0));
    #endif

    return &return_buffer;
}
