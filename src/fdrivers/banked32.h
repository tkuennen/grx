/*
 * banked32.h ---- the 16M color padded SVGA banked frame buffer driver
 *                 standard routines for 32H and 32L support
 *
 * Copyright (c) 1995 Csaba Biegl, 820 Stirrup Dr, Nashville, TN 37221
 * [e-mail: csaba@vuse.vanderbilt.edu].
 *
 * This file is part of the GRX graphics library.
 *
 * The GRX graphics library is free software; you can redistribute it
 * and/or modify it under some conditions; see the "copying.grx" file
 * for details.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contributions by: (See "doc/credits.doc" for details)
 * Hartmut Schirmer (hsc@techfak.uni-kiel.de)
 */

#include "banking.h"
#include "globals.h"
#include "colors.h"
#include "libgrx.h"
#include "grdriver.h"
#include "arith.h"
#include "mempeek.h"
#include "memfill.h"

/* frame offset address calculation */
#define FOFS(x,y,lo) umuladd32((y),(lo),((x)<<2))

static INLINE
GrxColor readpixel(GrxFrame *c,int x,int y)
{
        GR_int32u offs;
        char *pp;
        GRX_ENTER();
        offs = FOFS(x,y,SCRN->gc_line_offset);
        CHKBANK(BANKNUM(offs));
        pp = &SCRN->gc_base_address.plane0[BANKPOS(offs)];
        setup_far_selector(SCRN->gc_selector);
        GRX_RETURN(PIX2COL(peek_l_f(pp)));
}

static INLINE
void drawpixel(int x,int y,GrxColor color)
{
        GR_int32u offs;
        char *ptr;
        int op;
        GRX_ENTER();
        offs = FOFS(x,y,SCRN->gc_line_offset);
        CHKBANK(BANKNUM(offs));
        ptr = &SCRN->gc_base_address.plane0[BANKPOS(offs)];
        op = C_OPER(color);
        color = COL2PIX(color);
        setup_far_selector(CURC->gc_selector);
        switch(op) {
            case C_XOR: poke_l_f_xor(ptr,color); break;
            case C_OR:  poke_l_f_or( ptr,color); break;
            case C_AND: poke_l_f_and(ptr,color); break;
            default:    poke_l_f(    ptr,color); break;
        }
        GRX_LEAVE();
}

#ifdef freplicate_l
static void drawhline(int x,int y,int w,GrxColor color)
{
        GR_int32u offs;
        GR_repl cval;
        int oper;
        unsigned int w1, w2;
        GRX_ENTER();
        offs = FOFS(x,y,SCRN->gc_line_offset);
        w2 = BANKLFT(offs) >> 2;
        w2 = w - (w1 = umin(w,w2));
        oper = C_OPER(color);
        color = COL2PIX(color);
        cval = freplicate_l(color);
        setup_far_selector(CURC->gc_selector);
        do {
            char *pp = &CURC->gc_base_address.plane0[BANKPOS(offs)];
            CHKBANK(BANKNUM(offs));
            offs += (w1 << 2);
            switch(oper) {
                case C_XOR: repfill_l_f_xor(pp,cval,w1); break;
                case C_OR:  repfill_l_f_or( pp,cval,w1); break;
                case C_AND: repfill_l_f_and(pp,cval,w1); break;
                default:    repfill_l_f(    pp,cval,w1); break;
            }
            w1 = w2;
            w2 = 0;
        } while(w1 != 0);
        GRX_LEAVE();
}
#else
static
#include "generic/hline.c"
#endif

static
#include "generic/vline.c"

static
#include "generic/block.c"

static
#include "generic/line.c"

static
#include "generic/bitmap.c"

static
#include "generic/pattern.c"

static void bitblt(GrxFrame *dst,int dx,int dy,GrxFrame *src,int sx,int sy,int w,int h,GrxColor op)
{
        GRX_ENTER();
        if(grx_color_get_mode(op) == GRX_COLOR_MODE_IMAGE) _GrFrDrvGenericBitBlt(
            dst,dx,dy,
            src,sx,sy,
            w,h,
            op
        );
        else _GrFrDrvPackedBitBltV2V(
            dst,(dx << 2),dy,
            src,(sx << 2),sy,
            (w << 2),h,
            op
        );
        GRX_LEAVE();
}

#ifndef GRX_USE_RAM3x8

static void bltv2r(GrxFrame *dst,int dx,int dy,GrxFrame *src,int sx,int sy,int w,int h,GrxColor op)
{
        GRX_ENTER();
        if(grx_color_get_mode(op) == GRX_COLOR_MODE_IMAGE) _GrFrDrvGenericBitBlt(
            dst,dx,dy,
            src,sx,sy,
            w,h,
            op
        );
        else _GrFrDrvPackedBitBltV2R(
            dst,(dx << 2),dy,
            src,(sx << 2),sy,
            (w << 2),h,
            op
        );
        GRX_LEAVE();
}

static void bltr2v(GrxFrame *dst,int dx,int dy,GrxFrame *src,int sx,int sy,int w,int h,GrxColor op)
{
        GRX_ENTER();
        if(grx_color_get_mode(op) == GRX_COLOR_MODE_IMAGE) _GrFrDrvGenericBitBlt(
            dst,dx,dy,
            src,sx,sy,
            w,h,
            op
        );
        else _GrFrDrvPackedBitBltR2V(
            dst,(dx << 2),dy,
            src,(sx << 2),sy,
            (w << 2),h,
            op
        );
        GRX_LEAVE();
}

#endif /* !GRX_USE_RAM3x8 */
