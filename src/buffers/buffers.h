#ifndef BUFFERS_H
#define BUFFERS_H

#include <PR/ultratypes.h>

#include "game/save_file.h"
#include "game/game_init.h"
#include "config.h"

extern u8 gDecompressionHeap[];

extern u8 gAudioHeap[];

extern u8 gAudioSPTaskYieldBuffer[];

extern u8 gUnusedThread2Stack[];

extern u8 gIdleThreadStack[];
extern u8 gThread3Stack[];
extern u8 gThread4Stack[];
extern u8 gThread5Stack[];
extern u8 gThread6Stack[];

extern u8 gGfxSPTaskYieldBuffer[];

extern struct SaveBuffer gSaveBuffer;

extern u8 gGfxSPTaskStack[];

#define GFX_NUM_POOLS 1
extern struct GfxPool gGfxPools[GFX_NUM_POOLS];

#endif // BUFFERS_H
