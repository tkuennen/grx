/**
 ** LFB8.C ---- the 256 color Super VGA linear frame buffer driver
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

/* -------------------------------------------------------------------- */

#define FAR_ACCESS
#include "fdrivers/driver8.h"

/* -------------------------------------------------------------------- */

GrFrameDriver _GrFrameDriverSVGA8_LFB = {
    GR_frameSVGA8_LFB,          /* frame mode */
    GR_frameRAM8,               /* compatible RAM frame mode */
    TRUE,                       /* onscreen */
    4,                          /* scan line width alignment */
    1,                          /* number of planes */
    8,                          /* bits per pixel */
    8*16*1024L*1024L,           /* max plane size the code can handle */
    NULL,
    readpixel,
    drawpixel,
    drawline,
    drawhline,
    drawvline,
    drawblock,
    drawbitmap,
    drawpattern,
    bitblit,
    bltv2r,
    bltr2v,
    getindexedscanline,
    putscanline
};

#endif
