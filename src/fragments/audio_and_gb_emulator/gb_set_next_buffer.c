/* Stadium Zero fragment000_80C00. */

#include "global.h"

/**
 * The fragment's private copy of libultra's osAiSetNextBuffer (same body, including the
 * hdwrBugFlag 8 KB-boundary workaround). GbAudio_UpdateFrame and GbAudio_RampToSilence use it
 * to hand the rendered GB audio buffers to the AI.
 * Seen in play (2026-11-12): GbAudio_UpdateFrame passed it the buffer GbApu_RenderBuffer filled
 * the frame before (0x801A64F0) with length 0xC40, that is 784 stereo 16-bit samples.
 */
s32 osGbSetNextBuffer(void* buf_ptr, u32 size) {
  static u8 hdwr_bug_flag = FALSE;
  char* bptr;
  s32 status;

#if BUILD_VERSION >= VERSION_J
  if (__osAiDeviceBusy()) {
      return -1;
  }
#endif


  bptr = buf_ptr;

  if (hdwr_bug_flag) {
      bptr = (u8*)buf_ptr - 0x2000;
  }

  if ((((u32)buf_ptr + size) & 0x1fff) == 0) {
      hdwr_bug_flag = TRUE;
  } else {
      hdwr_bug_flag = FALSE;
  }

#if BUILD_VERSION < VERSION_J
  status = IO_READ(AI_STATUS_REG);
  //! @bug The __osAiDeviceBusy call should be above the hardware bug workaround to ensure that it was only
  //! performed when a transfer was guaranteed to start. If this condition passes and this function returns without
  //! submitting a buffer for DMA, the code above will lose track of when to apply the workaround.
  if (status & AI_STATUS_FIFO_FULL) {
      return -1;
  }
#endif

  IO_WRITE(AI_DRAM_ADDR_REG, OS_PHYSICAL_TO_K0(bptr));
  IO_WRITE(AI_LEN_REG, size);
  return 0;
}
