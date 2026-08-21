#ifndef PRLIB_SPADATA_H
#define PRLIB_SPADATA_H

#include "common.h"

#include <eetypes.h>

#include <nalib/namatrix.h>

class SpaFileHeader;

class SpaTrackBase {
public:
    u_int SearchSegment(float arg0) const;

public:
    void ChangePointer(u_int arg0, u_int arg1) {
        int ptr;
        if (this->unk0 == 0) {
            ptr = (int)(this + 1) + (this->unk4 * arg0);
            this->unkC = (float*)ptr;
        } else {
            ptr = (int)(this + 1) + (this->unk4 * arg1);
            this->unkC = (float*)ptr;
        }
    }

protected:
    u_char unk0;
    u_char unk1;
    u_short unk2;
    u_int unk4;
    mutable u_int unk8;
    float *unkC;
};

template <typename T>
class SpaTrack : public SpaTrackBase {
public:
    const T* GetValue(float arg0) const;

    const T* GetSprineValue(u_int seg, float arg1) const;
    const T* GetLinearValue(u_int seg, float arg1) const;

public:
    void ChangePointer() {
        SpaTrackBase::ChangePointer(sizeof(T)*3, sizeof(T));
    }

private:
    T unk10[0];
};

class SpaTransform {
public:
    bool IsEverIdentical();

private:
    u_char unk0;
    PR_PADDING(unk1, 0x13);
    int unk14;
    PR_PADDING(unk18, 0x8);
    NaMATRIX<float, 4, 4> unk20;
};
    
class SpaNodeAnimation {
public:
    NaMATRIX<float, 4, 4>* GetMatrix(float) const;
    bool IsVisible(float arg0) const;
    int Optimize();

    void ChangePointer(SpaFileHeader *animation);

public:
    PR_PADDING(unk0, 0x4);
    SpaTrack<int> *unk4;
    u_int unk8;
    SpaTransform **unkC;
};

#endif /* PRLIB_SPADATA_H */
