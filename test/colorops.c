/**
 ** colorops.c ---- test WRITE, XOR, OR, and AND draw modes
 **
 ** Copyright (c) 1995 Csaba Biegl, 820 Stirrup Dr, Nashville, TN 37221
 ** [e-mail: csaba@vuse.vanderbilt.edu]
 **
 ** This is a test/demo file of the GRX graphics library.
 ** You can use GRX test/demo files as you want.
 **
 ** The GRX graphics library is free software; you can redistribute it
 ** and/or modify it under some conditions; see the "copying.grx" file
 ** for details.
 **
 ** This library is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 **
 **/

#include "test.h"
#include "rand.h"

TESTFUNC(colorops)
{
        GrFBoxColors bcolors,ocolors,icolors;
        GrxColor bg,c;
        int x = grx_get_size_x();
        int y = grx_get_size_y();
        int ww = (x * 2) / 3;
        int wh = (y * 2) / 3;
        int ii,jj;
        int wdt = ww / 150;
        int bw = x / 16;
        int bh = y / 16;
        int bx,by;

        /* This won't work very well under X11 in pseudocolor
        ** mode (256 colors or less) if not using a private
        ** color map. The missing colors break RGB mode      */
        grx_color_info_set_rgb_color_mode();

        bcolors.fbx_intcolor = grx_color_info_alloc_color(160,100,30);
        bcolors.fbx_topcolor = grx_color_info_alloc_color(240,150,45);
        bcolors.fbx_leftcolor = grx_color_info_alloc_color(240,150,45);
        bcolors.fbx_rightcolor = grx_color_info_alloc_color(80,50,15);
        bcolors.fbx_bottomcolor = grx_color_info_alloc_color(80,50,15);

        ocolors.fbx_intcolor = grx_color_info_alloc_color(0,120,100);
        ocolors.fbx_topcolor = grx_color_info_alloc_color(0,180,150);
        ocolors.fbx_leftcolor = grx_color_info_alloc_color(0,180,150);
        ocolors.fbx_rightcolor = grx_color_info_alloc_color(0,90,60);
        ocolors.fbx_bottomcolor = grx_color_info_alloc_color(0,90,60);

        icolors.fbx_intcolor = grx_color_info_alloc_color(30,30,30);
        icolors.fbx_bottomcolor = grx_color_info_alloc_color(0,180,150);
        icolors.fbx_rightcolor = grx_color_info_alloc_color(0,180,150);
        icolors.fbx_leftcolor = grx_color_info_alloc_color(0,90,60);
        icolors.fbx_topcolor = grx_color_info_alloc_color(0,90,60);

        c  = grx_color_info_alloc_color(250,250,0);
        bg = GRX_COLOR_NONE;

        for(ii = 0,by = -(bh / 3); ii < 17; ii++) {
            for(jj = 0,bx = (-bw / 2); jj < 17; jj++) {
                GrFramedBox(bx+2*wdt,by+2*wdt,bx+bw-2*wdt-1,by+bh-2*wdt-1,2*wdt,&bcolors);
                bx += bw;
            }
            by += bh;
        }

        GrFramedBox(ww/4-5*wdt-1,wh/4-5*wdt-1,ww/4+5*wdt+ww+1,wh/4+5*wdt+wh+1,wdt,&ocolors);
        GrFramedBox(ww/4-1,wh/4-1,ww/4+ww+1,wh/4+wh+1,wdt,&icolors);

        grx_set_clip_box(ww/4,wh/4,ww/4+ww,wh/4+wh);

        drawing(ww/4,wh/4,ww,wh,c,bg);
        while(!GrKeyPressed()) {
            drawing(ww/4+(RND()%100),
                wh/4+(RND()%100),
                ww,
                wh,
                ((RND() / 16) & (grx_color_info_n_colors() - 1)),
                bg
            );
        }
        GrKeyRead();
        GrFramedBox(ww/4-1,wh/4-1,ww/4+ww+1,wh/4+wh+1,wdt,&icolors);
        drawing(ww/4,wh/4,ww,wh,c,bg);
        while(!GrKeyPressed()) {
            drawing(ww/4+(RND()%100),
                wh/4+(RND()%100),
                ww,
                wh,
                ((RND() / 16) & (grx_color_info_n_colors() - 1)) | GRX_COLOR_MODE_XOR,
                bg
            );
        }
        GrKeyRead();
        GrFramedBox(ww/4-1,wh/4-1,ww/4+ww+1,wh/4+wh+1,wdt,&icolors);
        drawing(ww/4,wh/4,ww,wh,c,bg);
        while(!GrKeyPressed()) {
            drawing(ww/4+(RND()%100),
                wh/4+(RND()%100),
                ww,
                wh,
                ((RND() / 16) & (grx_color_info_n_colors() - 1)) | GRX_COLOR_MODE_OR,
                bg
            );
        }
        GrKeyRead();
        GrFramedBox(ww/4-1,wh/4-1,ww/4+ww+1,wh/4+wh+1,wdt,&icolors);
        drawing(ww/4,wh/4,ww,wh,c,bg);
        while(!GrKeyPressed()) {
            drawing(ww/4+(RND()%100),
                wh/4+(RND()%100),
                ww,
                wh,
                ((RND() / 16) & (grx_color_info_n_colors() - 1)) | GRX_COLOR_MODE_AND,
                bg
            );
        }
        GrKeyRead();
}

