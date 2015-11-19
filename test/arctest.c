/**
 ** arctest.c ---- test arc outline and filled arc drawing
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

#include <string.h>
#include "test.h"

TESTFUNC(arctest)
{
        char buff[300];
        int  xc,yc,xa,ya,start,end;
        FILE *fp;
        GrxColor red   = grx_color_info_alloc_color(255,0,0);
        GrxColor green = grx_color_info_alloc_color(0,255,0);
        GrxColor blue  = grx_color_info_alloc_color(0,0,255);

        fp = fopen("arctest.dat","r");
        if(fp == NULL) return;
        while(fgets(buff,299,fp) != NULL) {
            int len = strlen(buff);
            while(--len >= 0) {
                if(buff[len] == '\n') { buff[len] = '\0'; continue; }
                if(buff[len] == '\r') { buff[len] = '\0'; continue; }
                break;
            }
            if(sscanf(buff,
                      "arc xc=%d yc=%d xa=%d ya=%d start=%d end=%d",
                      &xc,&yc,&xa,&ya,&start,&end) == 6) {
                GrClearScreen(grx_color_info_get_black());
                GrEllipse(xc,yc,xa,ya,red);
                GrFilledEllipse(xc,yc,xa,ya,blue);
                GrEllipseArc(xc,yc,xa,ya,start,end,GR_ARC_STYLE_CLOSE2,grx_color_info_get_white());
                GrTextXY(0,0,buff,grx_color_info_get_white(),GRX_COLOR_NONE);
                GrTextXY(0,20,"press any key to continue",grx_color_info_get_white(),GRX_COLOR_NONE);
                GrKeyRead();
                GrClearScreen(grx_color_info_get_black());
                GrEllipseArc(xc,yc,xa,ya,start,end,GR_ARC_STYLE_CLOSE2,red);
                GrFilledEllipseArc(xc,yc,xa,ya,start,end,GR_ARC_STYLE_CLOSE2,green);
                GrTextXY(0,0,buff,grx_color_info_get_white(),GRX_COLOR_NONE);
                GrTextXY(0,20,"press any key to continue",grx_color_info_get_white(),GRX_COLOR_NONE);
                GrKeyRead();
            }
        }
        fclose(fp);
}

