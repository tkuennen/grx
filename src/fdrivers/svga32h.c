/**
 ** SVGA32H.C ---- the 16M color padded Super VGA frame driver (high)
 **
 ** Copyright (c) 1995 Csaba Biegl, 820 Stirrup Dr, Nashville, TN 37221
 ** [e-mail: csaba@vuse.vanderbilt.edu] See "doc/copying.cb" for details.
 ** Contributions by: (See "doc/credits.doc" for details)
 ** Hartmut Schirmer (hsc@techfak.uni-kiel.de)
 ** Andrzej Lawa [FidoNet: Andrzej Lawa 2:480/19.77]
 **/

#define PIX2COL(col) ((col)>>8)
#define COL2PIX(col) ((col)<<8)

#include "fdrivers/banked32.h"

GrFrameDriver _GrFrameDriverSVGA32H = {
    GR_frameSVGA32H,            /* frame mode */
#ifdef GRX_USE_RAM3x8
    GR_frameRAM3x8,             /* compatible RAM frame mode */
#else
    GR_frameRAM32H,             /* compatible RAM frame mode */
#endif
    TRUE,                       /* onscreen */
    4,                          /* line width alignment */
    1,                          /* number of planes */
    32,                         /* bits per pixel */
    32*16*1024L*1024L,          /* max plane size the code can handle */
    NULL,
    readpixel,
    drawpixel,
    drawline,
    drawhline,
    drawvline,
    drawblock,
    drawbitmap,
    drawpattern,
    bitblt,
#ifdef GRX_USE_RAM3x8
    _GrFrDrvGenericBitBlt,
    _GrFrDrvGenericBitBlt,
#else
    bltv2r,
    bltr2v,
#endif
    _GrFrDrvGenericGetIndexedScanline,
    _GrFrDrvGenericPutScanline
};

