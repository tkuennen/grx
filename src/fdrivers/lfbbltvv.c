/**
 ** LFBBLTVV.C ---- packed video->video blit operations for
 **                 8,16,24 and 32bpp Super VGA linear frame buffer modes
 **
 ** Copyright (c) 1995 Csaba Biegl, 820 Stirrup Dr, Nashville, TN 37221
 ** [e-mail: csaba@vuse.vanderbilt.edu] See "doc/copying.cb" for details.
 ** Contributions by: (See "doc/credits.doc" for details)
 ** Hartmut Schirmer (hsc@techfak.uni-kiel.de)
 ** Andrzej Lawa [FidoNet: Andrzej Lawa 2:480/19.77]
 **/

/* some systems map LFB in normal user space (eg. Linux/svgalib) */
/* near pointer stuff is equal to ram stuff :)                   */
/* in this is the far pointer code using %fs descriptor          */
#ifndef LBF_BY_NEAR_POINTER

#ifdef   __TURBOC__
#error This library will not work with as a 16-bit real-mode code
#endif

/* name of blit function to be created */
#define BLITFUNC _GrFrDrvPackedBitBltV2V_LFB

/* destination is video */
#define WRITE_FAR _f
/* source is video */
#define READ_FAR _f

/* need a selector before video access */
#define BLITSEL  dst->gf_selector

/* source and destination may overlap */
#define BLIT_CAN_OVERLAP

#include "fdrivers/pblit_nb.h"

#endif
