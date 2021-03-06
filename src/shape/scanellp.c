/*
 * scanellp.c ---- draw the outline or scan fill an ellipse
 *
 * Copyright (c) 1995 Csaba Biegl, 820 Stirrup Dr, Nashville, TN 37221
 * [e-mail: csaba@vuse.vanderbilt.edu]
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
 */

#include <grx/draw.h>

#include "globals.h"
#include "libgrx.h"
#include "allocate.h"
#include "arith.h"
#include "clipping.h"
#include "mouse.h"
#include "shapes.h"

#define  MAXR   120             /* max radius for which Bresenham works */

void _GrScanEllipse(int xc,int yc,int rx,int ry,GrFiller *f,GrFillArg c,int filled)
{
        int x1,x2,y1,y2;
        if(rx < 0) rx = (-rx);
        if(ry < 0) ry = (-ry);
        x1 = xc - rx; y1 = yc - ry;
        x2 = xc + rx; y2 = yc + ry;
        clip_ordbox(CURC,x1,y1,x2,y2);
        mouse_block(CURC,x1,y1,x2,y2);
        setup_ALLOC();
        if((rx == 0) || (ry == 0)) (*f->line)(
            (x1 + CURC->x_offset),
            (y1 + CURC->y_offset),
            (x2 - x1),
            (y2 - y1),
            c
        );
        else if((rx > MAXR) || (ry > MAXR)) {   /* Bresenham would overflow !! */
            GArray *points;
            
            points = grx_generate_ellipse(xc, yc, rx, ry);
            if (filled) {
                _GrScanConvexPoly(points->len, (GrxPoint *)points->data, f, c);
            }
            else {
                _GrDrawPolygon(points->len, (GrxPoint *)points->data, f, c, TRUE);
            }
            g_array_unref(points);
        }
        else {
            int *scans = ALLOC(sizeof(int) * (ry + 1));
            int  row   = ry;
            int  col   = 0;
            if(scans != NULL) {
                long yasq  = umul32(ry,ry);
                long xasq  = umul32(rx,rx);
                long xasq2 = xasq + xasq;
                long yasq2 = yasq + yasq;
                long xasq4 = xasq2 + xasq2;
                long yasq4 = yasq2 + yasq2;
                long error = (xasq2 * (row - 1) * row) +
                             (yasq2 * (1 - xasq))      +
                             xasq;
                while((xasq * row) > (yasq * col)) {
                    if(error >= 0) {
                        scans[row] = col;
                        row--;
                        error -= xasq4 * row;
                    }
                    error += yasq2 * (3 + (col << 1));
                    col++;
                }
                error = (yasq2 * (col + 1) * col)         +
                        (xasq2 * ((row * (row - 2)) + 1)) +
                        (yasq  * (1 - xasq2));
                while(row >= 0) {
                    scans[row] = col;
                    if(error <= 0) {
                        col++;
                        error += yasq4 * col;
                    }
                    row--;
                    error += xasq2 * (2 - (row << 1));
                }
                for(row = y1; row <= y2; row++) {
                    col = iabs(yc - row);
                    if(!filled && (col < ry)) {
                        x1 = xc - scans[col];
                        x2 = xc - scans[col + 1];
                        if(x1 < x2) x2--;
                        do {
                            clip_ordxrange_(CURC,x1,x2,break,CLIP_EMPTY_MACRO_ARG);
                            (*f->scan)(
                                (x1  + CURC->x_offset),
                                (row + CURC->y_offset),
                                (x2  - x1 + 1),
                                c
                            );
                        } while (0);
                        x1 = xc + scans[col + 1];
                        x2 = xc + scans[col];
                        if(x1 < x2) x1++;
                    }
                    else {
                        x1 = xc - scans[col];
                        x2 = xc + scans[col];
                    }
                        clip_ordxrange_(CURC,x1,x2,continue,CLIP_EMPTY_MACRO_ARG);
                    (*f->scan)(
                        (x1  + CURC->x_offset),
                        (row + CURC->y_offset),
                        (x2  - x1 + 1),
                        c
                    );
                }
                FREE(scans);
            }
        }
        reset_ALLOC();
        mouse_unblock();
}
