#include "libultra_internal.h"
#include "hardware.h"


extern u32 osTvType;

OSViContext sViContexts[2] = { 0 };
OSViContext *__osViCurr = &sViContexts[0];
OSViContext *__osViNext = &sViContexts[1];
u32 sTvType = TV_TYPE_NTSC;
u32 osViClock = 0x02E6D354;

extern OSViMode D_80334990;
extern OSViMode D_803349E0;

void __osViInit(void) {
//#ifdef VERSION_JP
    sTvType = osTvType;
    bzero(sViContexts, sizeof(sViContexts));
    __osViCurr = &sViContexts[0];
    __osViNext = &sViContexts[1];
    __osViNext->retraceCount = 1;
    __osViCurr->retraceCount = 1;


    if (sTvType == TV_TYPE_NTSC)
    {
        __osViNext->modep = &D_80334990;
        osViClock = 0x02E6D354;
    } else {
        __osViNext->modep = &D_803349E0;
        osViClock = 0x02E6025C;
    }

    __osViNext->unk00 = 0x20;
    __osViNext->features = __osViNext->modep->comRegs.ctrl;
    while (HW_REG(VI_CURRENT_REG, u32) > 0xa) {
        ;
    }
    HW_REG(VI_STATUS_REG, u32) = 0;
    __osViSwapContext();
}
