#include "libultra_internal.h"

#define OS_PI_MGR_MESG_BUFF_SIZE 1


OSMgrArgs __osPiDevMgr = { 0 };
OSThread piMgrThread;
u32 piMgrStack[0x400]; // stack bottom
OSMesgQueue __osPiMesgQueue;
OSMesg piMgrMesgBuff[OS_PI_MGR_MESG_BUFF_SIZE + 1];

extern u32 gOsPiAccessQueueCreated;
extern OSMesgQueue gOsPiMessageQueue;
void __osDevMgrMain(void *);

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt) {
    u32 int_disabled;
    OSPri newPri;
    OSPri currentPri;

    if (!__osPiDevMgr.initialized) {
        osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
        osCreateMesgQueue(&__osPiMesgQueue, &piMgrMesgBuff[0], OS_PI_MGR_MESG_BUFF_SIZE);
        if (!gOsPiAccessQueueCreated) {
            __osPiCreateAccessQueue();
        } // what is this constant geez
        osSetEventMesg(OS_EVENT_PI, &__osPiMesgQueue, (void *) 0x22222222);
        newPri = -1;
        currentPri = osGetThreadPri(NULL);
        if (currentPri < pri) {
            newPri = currentPri;
            osSetThreadPri(NULL, pri);
        }
        int_disabled = __osDisableInt();
        __osPiDevMgr.initialized = TRUE;
        __osPiDevMgr.mgrThread = &piMgrThread;
        __osPiDevMgr.cmdQueue = cmdQ;
        __osPiDevMgr.eventQueue = &__osPiMesgQueue;
        __osPiDevMgr.accessQueue = &gOsPiMessageQueue;
        __osPiDevMgr.dma_func = osPiRawStartDma;
        osCreateThread(&piMgrThread, 0, __osDevMgrMain, (void *) &__osPiDevMgr, &piMgrStack[0x400], pri);
        osStartThread(&piMgrThread);
        __osRestoreInt(int_disabled);
        if (newPri != -1) {
            osSetThreadPri(NULL, newPri);
        }
    }
}
