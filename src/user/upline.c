/*
 * upline.c
 *
 * Copyright (C) 1997, Michael Goffioul
 * [goffioul@emic.ucl.ac.be]
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

#include <grx/pixmap.h>

#include "globals.h"
#include "libgrx.h"
#include "usercord.h"

/**
 * grx_user_draw_line_with_pixmap:
 * @x1: starting X coordinate
 * @y1: starting Y coordinate
 * @x2: ending X coordinate
 * @y2: ending Y coordinate
 * @o: the line options
 * @p: the pixmap
 *
 * Draws a line on the current context from the starting coordinates to the
 * ending coordinates using the specified line options and pixmap.
 */
void grx_user_draw_line_with_pixmap (int x1, int y1, int x2, int y2, GrxLineOptions *o, GrxPixmap *p)
{
    U2SX (x1 ,CURC);
    U2SX (x2, CURC);
    U2SY (y1, CURC);
    U2SY (y2, CURC);
    grx_draw_line_with_pixmap (x1, y1, x2, y2, o, p);
}
