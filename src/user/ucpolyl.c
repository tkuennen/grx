/**
 **     UCPOLYL.C
 **
 **     Copyright (C) 1997, Michael Goffioul
 **
 **       goffioul@emic.ucl.ac.be
 **
 **/

#include "libgrx.h"
#include "allocate.h"
#include "usercord.h"

void GrUsrCustomPolyLine(int numpts,int points[][2],GrLineOption *lo)
{
        int pt;
        int (*tmp)[2];
        setup_ALLOC();
        tmp = ALLOC(sizeof(int) * 2 * numpts);

        if (tmp != NULL) {
          for ( pt = 0;pt < numpts;pt++) {
                tmp[pt][0] = points[pt][0];
                tmp[pt][1] = points[pt][1];
                U2SX(tmp[pt][0],CURC);
                U2SY(tmp[pt][1],CURC);
          }
          GrCustomPolyLine(numpts,tmp,lo);
          FREE(tmp);
        }
        reset_ALLOC();
}
