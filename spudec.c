/* SPUdec.c
   Skeleton of function spudec_process_controll() was written by Apri.
   Further works:
   LGB,... (yeah, try to improve it and insert your name here! ;-) */


#include <stdio.h>
#include "spudec.h"




void spudec_process_control(unsigned char *control, int size, int* d1, int* d2)
{
  int off = 2;
  int a,b; /* Temporary vars */

  do {
    int type = control[off];
    off++;
    printf("cmd=%d  ",type);

    switch(type) {
    case 0x00:
      /* Menu ID, 1 byte */
      printf("Menu ID\n");
      break;
    case 0x01:
      /* Start display */
      printf("Start display!\n");
//      gSpudec.geom.bIsVisible = 1;
      break;
    case 0x03:
      /* Palette */
      printf("Palette\n");
//      palette[3] = &(gSpudec.clut[(control[off] >> 4)]);
//      palette[2] = &(gSpudec.clut[control[off] & 0xf]);
//      palette[1] = &(gSpudec.clut[(control[off+1] >> 4)]);
//      palette[0] = &(gSpudec.clut[control[off+1] & 0xf]);
      off+=2;
      break;
    case 0x04:
      /* Alpha */
      printf("Alpha\n");
//      alpha[3] = control[off] & 0xf0;
//      alpha[2] = (control[off] & 0xf) << 4;
//      alpha[1] = control[off+1] & 0xf0;
//      alpha[0] = (control[off+1] & 0xf) << 4;
      off+=2;
      break;
    case 0x05:
      /* Co-ords */
      a = (control[off] << 16) + (control[off+1] << 8) + control[off+2];
      b = (control[off+3] << 16) + (control[off+4] << 8) + control[off+5];

      printf("Coords  col: %d - %d  row: %d - %d\n",a >> 12,a & 0xfff,b >> 12,b & 0xfff);

//      gSpudec.geom.start_col = a >> 12;
//      gSpudec.geom.end_col = a & 0xfff;
//      gSpudec.geom.start_row = b >> 12;
//      gSpudec.geom.end_row = b & 0xfff;

      off+=6;
      break;
    case 0x06:
      /* Graphic lines */
      *(d1) = (control[off] << 8) + control[off+1];
      *(d2) = (control[off+2] << 8) + control[off+3];
      printf("Graphic pos  color: %d  b/w: %d\n",*d1,*d2);
      off+=4;
      break;
    case 0xff:
      /* All done, bye-bye */
      printf("Done!\n");
      return;
      break;
    default:
      printf("spudec: Error determining control type 0x%02x.\n",type);
      return;
      break;
    }

    /* printf("spudec: Processsed control type 0x%02x.\n",type); */
  } while(off < size);
}



