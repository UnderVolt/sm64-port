#include <ultra64.h>

#include "buffers.h"
#include "config.h"

ALIGNED8 u8 gDecompressionHeap[0xD000];
ALIGNED16 u8 gAudioHeap[DOUBLE_SIZE_ON_64_BIT(0x31200)];

ALIGNED8 u8 gIdleThreadStack[0x800];
ALIGNED8 u8 gThread3Stack[0x2000];
ALIGNED8 u8 gThread4Stack[0x2000];
ALIGNED8 u8 gThread5Stack[0x2000];
ALIGNED8 u8 gThread6Stack[0x2000];
// 0x400 bytes
ALIGNED8 u8 gGfxSPTaskStack[SP_DRAM_STACK_SIZE8];
// 0xc00 bytes for f3dex, 0x900 otherwise
ALIGNED8 u8 gGfxSPTaskYieldBuffer[OS_YIELD_DATA_SIZE];
// 0x200 bytes
ALIGNED8 struct SaveBuffer gSaveBuffer;
// 0x190a0 bytes
struct GfxPool gGfxPools[GFX_NUM_POOLS];


// Yield buffer for audio, 0x400 bytes. Stubbed out post-JP since the audio
// task never yields.

// Probably Thread 2 stack space. Unreferenced, and stubbed out with f3dex to
// avoid an overflowing .buffers segment.
#if !defined(F3DEX_GBI_SHARED)
ALIGNED8 u8 gUnusedThread2Stack[0x1400];
#endif
