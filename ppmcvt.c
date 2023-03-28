#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "pbm.h"

// Convert image to sepia
void sepia(int height, int width, PPMImage* image)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float colors[3];
            colors[0] = round(0.393 * image->pixmap[0][i][j]  + 0.769 * image->pixmap[1][i][j]  + 0.189 * image->pixmap[2][i][j] );
            colors[1] = round(0.349 * image->pixmap[0][i][j]  + 0.686 * image->pixmap[1][i][j]  + 0.168 * image->pixmap[2][i][j] );
            colors[2] = round(0.272 * image->pixmap[0][i][j]  + 0.534 * image->pixmap[1][i][j]  + 0.131 * image->pixmap[2][i][j] );
            for (int k = 0; k < 3; k++)
            {
                if (colors[k] > 255)
                {
                    colors[k] = 255;
                }
            }

            image->pixmap[0][i][j]  = colors[0];
            image->pixmap[0][i][j]  = colors[1];
            image->pixmap[0][i][j]  = colors[2];

        }
    }
    return;
}

// Reflect image horizontally
void mirror(int height, int width, PPMImage* image)
{
    int temp[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width/2); j++)
        {

            temp[0] = image->pixmap[0][i][j]  ;
            temp[1] = image->pixmap[1][i][j]  ;
            temp[2] = image->pixmap[2][i][j]  ;



            image->pixmap[0][i][j]  = image->pixmap[0][i][width - j - 1];
            image->pixmap[1][i][j]  = image->pixmap[1][i][width - j - 1];
            image->pixmap[2][i][j]  = image->pixmap[2][i][width - j - 1];

            image->pixmap[0][i][width - j - 1] = temp[0];
            image->pixmap[1][i][width - j - 1] = temp[1];
            image->pixmap[2][i][width - j - 1] = temp[2];

        }
    }
    return;
}

/*
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
*/
void nup(int height, int width, int scale, PPMImage* image){
    for(int i = 0; i < height; i += scale){
        for(int j = 0; j < width; j += scale){
            image->pixmap[0][i/scale][j/scale] = image->pixmap[0][i][j];
            image->pixmap[1][i/scale][j/scale] = image->pixmap[1][i][j];
            image->pixmap[2][i/scale][j/scale] = image->pixmap[2][i][j];
        }
    }
    return;
}

void bitmap(int h, int w, PBMImage* img1, PPMImage* img2){
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            img1->pixmap[i][j] = \
            ((img2->pixmap[0][i][j] + img2->pixmap[0][i][j] + img2->pixmap[0][i][j])/3 < img2->max/2);
        }
    }
    return; 
}

void grayscale(int h, int w, PGMImage* img1, PPMImage* img2, int mx){
    img1->max = 0;
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            img1->pixmap[i][j] = (double)(((img2->pixmap[0][i][j] + img2->pixmap[1][i][j] + img2->pixmap[2][i][j])/3.0)/img2->max) * mx;
            if(img1->max < img1->pixmap[i][j]){
                img1->max = img1->pixmap[i][j];
            }
        }
    }
    return; 
}

PPMImage* thumbnail(PPMImage* image, int width, int height, int scale) {
    // calculate thumbnail dimensions
    int thumbnail_width = width / scale;
    int thumbnail_height = height / scale;
    PPMImage* thumbnail = new_ppmimage(thumbnail_width,thumbnail_height,image->max);
    for(int i = 0; i < height; i += scale){
        for(int j = 0; j < width; j += scale){
            thumbnail->pixmap[0][i/scale][j/scale] = image->pixmap[0][i][j];
            thumbnail->pixmap[1][i/scale][j/scale] = image->pixmap[1][i][j];
            thumbnail->pixmap[2][i/scale][j/scale] = image->pixmap[2][i][j];
        }
    }
    return thumbnail;
}


void isolate(int height, int width,PPMImage* image, char answer){
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(answer == 'B'){
                image->pixmap[0][i][j] = 0;
                image->pixmap[1][i][j] = 0;
            }
            else if(answer == 'R'){
                image->pixmap[1][i][j] = 0;
                image->pixmap[2][i][j] = 0;
            }
            else if(answer == 'G'){
                image->pixmap[0][i][j] = 0;
                image->pixmap[2][i][j] = 0;
            }
        }
    }
    return;
}

void rm(int height, int width,PPMImage* image, char answer){
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(answer == 'B'){
                image->pixmap[2][i][j] = 0;
            }
            else if(answer == 'R'){
                image->pixmap[0][i][j] = 0;
            }
            else if(answer == 'G'){
                image->pixmap[1][i][j] = 0;
            }
        }
    }
    return;
}


int main( int argc, char *argv[] )
{
    // Define allowable filter
    char *filters = "bgirsmtno";

    // Ensure only one filter
    getopt(argc, argv, filters);

    // Ensure proper usage
    if (argc < 4)
    {
        printf("Usage: ./filter [flag] infile outfile\n");
        return 3;
    }
    
    if((argv[1][1] == 'r' || argv[1][1] == 'i') && !(argv[2][0] == 'R' || argv[2][0] == 'B' || argv[2][0] == 'G')){
        printf("Error: Invalid channel specification: (%s); should be red, green, or blue\n", argv[2]);   
        return 0;
    }
    if(argv[1][1] == 'g' && atoi(argv[2]) > 65536){
        printf("Error: Invalid max grayscale pixel value: %s; must be less than 65,536\n", argv[2]);
        return 0;
    }
    if(argv[1][1] == 'n' || argv[1][1] == 't' && ((int) (argv[2][0] - '0') > 8 || (int) (argv[2][0] - '0') < 1)){
        printf("Error: Invalid scale factor: %d; must be 1-8\n”", (int) (argv[2][0] - '0'));
        return 0;
    }

    // Remember filenames
    char *infilename, *outfile;
    if(argc == 4){
        infilename = argv[3];
        outfile = argv[2];
    }
    else{
        infilename = argv[4];
        outfile = argv[3];
    }
    PPMImage * image =  read_ppmfile(infilename);

    // Filter image
    PPMImage* ret;
    PBMImage * image1;
    PGMImage * image2;
    switch (argv[1][1])
    {
        // Reflection
        case 'c':
            mirror(image->height, image->width, image);
            write_ppmfile(image, outfile);
            break;
        // Sepia
        case 's':
            sepia(image->height, image->width, image);
            write_ppmfile(image, outfile);
            break;
        case 'b':
            image1 = new_pbmimage(image->width, image->height);
            bitmap(image->height, image->width, image1, image);
            write_pbmfile(image1, outfile);
            del_pbmimage(image1);
            break;
        case 'n':
            nup(image->height, image->width, (int) (argv[2][0] - '0'), image);
            write_ppmfile(image, outfile);
            break;
        case 'g':
            image2 = new_pgmimage(image->width, image->height, image->max);
            grayscale(image->height, image->width, image2, image, atoi(argv[2]));
            printf("%d\n", atoi(argv[2]));
            write_pgmfile(image2, outfile);
            del_pgmimage(image2);
            break;
        case 'i':
            isolate(image->height, image->width,image, argv[2][0]);
            write_ppmfile(image, outfile);
            del_ppmimage(image);
            break;
        case 'r':
            rm(image->height, image->width,image, argv[2][0]);
            write_ppmfile(image, outfile);
            del_ppmimage(image);
            break;
        case 't':
            ret = thumbnail(image, image->width, image->height, (int) (argv[2][0] - '0'));
            write_ppmfile(ret, outfile);
            del_ppmimage(ret);
            break;
    }
    del_ppmimage(image);
    return 0;
}
