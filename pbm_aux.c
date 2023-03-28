#include "pbm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PPMImage * new_ppmimage(unsigned int w, unsigned int h, unsigned int m)
{
    PPMImage* img = (PPMImage*)malloc(sizeof(PPMImage));
    img->pixmap[0] = (unsigned int**)malloc(sizeof(unsigned int) * h);
    img->pixmap[1] = (unsigned int**)malloc(sizeof(unsigned int) * h);
    img->pixmap[2] = (unsigned int**)malloc(sizeof(unsigned int) * h);
    for (unsigned int i = 0; i < h; i++) {
        img->pixmap[0][i] = (unsigned int*)malloc(sizeof(unsigned int) * w);
        img->pixmap[1][i] = (unsigned int*)malloc(sizeof(unsigned int) * w);
        img->pixmap[2][i] = (unsigned int*)malloc(sizeof(unsigned int) * w);
    }
    img->height = h;
    img->width = w;
    img->max = m;
    return img;
}

PBMImage * new_pbmimage(unsigned int w, unsigned int h)
{
    PBMImage* img = (PBMImage*)malloc(sizeof(PBMImage));
    img->pixmap = (unsigned int**)malloc(sizeof(unsigned int) * h);
    for (unsigned int i = 0; i < h; i++) {
        img->pixmap[i] = (unsigned int*)malloc(sizeof(unsigned int) * w);
    }
    img->height = h;
    img->width = w;
    return img;
}

PGMImage * new_pgmimage(unsigned int w, unsigned int h, unsigned int m)
{
    PGMImage* img = (PGMImage*)malloc(sizeof(PGMImage));
    img->pixmap = (unsigned int**)malloc(sizeof(unsigned int) * h);
    for (unsigned int i = 0; i < h; i++) {
        img->pixmap[i] = (unsigned int*)malloc(sizeof(unsigned int) * w);
    }
    img->height = h;
    img->width = w;
    img->max = m;
    return img;
}

void del_ppmimage(PPMImage *p)
{
    for (unsigned int i = 0; i < p->height; i++) {
        free(p->pixmap[0][i]);
        free(p->pixmap[1][i]);
        free(p->pixmap[2][i]);
    }
    free(p->pixmap[0]);
    free(p->pixmap[1]);
    free(p->pixmap[2]);
    free(p);
}

void del_pgmimage(PGMImage *p)
{
    for (unsigned int i = 0; i < p->height; i++) {
        free(p->pixmap[i]);
    }
    free(p->pixmap);
    free(p);
}

void del_pbmimage(PBMImage *p)
{
    for (unsigned int i = 0; i < p->height; i++) {
        free(p->pixmap[i]);
    }
    free(p->pixmap);
    free(p);
}