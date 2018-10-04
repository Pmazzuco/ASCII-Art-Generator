#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

// Protótipos
void load(char* name, Img* pic);

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

int main(int argc, char** argv)
{
    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    load(argv[1], &pic);

    /*
    printf("Primeiros 10 pixels da imagem:\n");
    for(int i=0; i<10; i++) {
        printf("[%03d %03d %03d] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
    }
    */


    //toGray
    int totalPixels = pic.height*pic.width;


    int grayImage[pic.width][pic.height];

    for (int i = 0; i < pic.height; i ++) {
        //grayImage[i] = (int) ((int)image->img[i].r*0.3 + (int)image->img[i].g*0.59 + (int)image->img[i].b*0.11);
        for (int j = 0; j < pic.width; j++) {
            grayImage[j][i] = (int) ((float)pic.img[i*pic.width+j].r*0.3 + (float)pic.img[i*pic.width+j].g*0.59 + (float)pic.img[i*pic.width+j].b*0.11);
        }

    }

    /*
    //test print toGray
    for (int i = 0; i < pic.width; i++) {
        for (int j = 0; j < pic.height; j++) {
            printf("[%03d] ", grayImage[i][j]);
        }
    }
    */


    //Compact
    float outSize;
    outSize = atof(argv[2]);

    int blockHSize = (int)(1*100)/outSize;
    int blockVSize = (int)(2*100)/outSize;
    int maxHorizontal = (int)(pic.width/blockHSize);
    int maxVertical = (int)(pic.height/blockVSize);

    char gradient[] = {'.', ':', 'c', 'o', 'C', 'O', '@'};
    char output[maxHorizontal][maxVertical];

    int media = 0;
    for (int i = 0; i < maxVertical ; i++) {
        for (int j = 0; j < maxHorizontal; j++) {
            media = 0;
            for (int k = i*blockVSize; k < i*blockVSize+blockVSize; k++) {
                for (int l = j*blockHSize; l < j*blockHSize+blockHSize; l++) {
                    media = media + grayImage[l][k];
                }
            }
            media = (int)(media / (blockHSize*blockVSize));
            if (media >= 0 && media <= 255) {
                output[j][i] = gradient[media/36];
            }
        }
    }


    printf("<html><head></head>");
    printf("<body style=\"background: black;\" leftmargin=0 topmargin=0> ");
    printf("<style> \npre  {\n\tcolor: white;\n\tfont-family: Courier;\n\tfont-size: 8px;\n}\n</style>\n");
    printf("<pre>\n");
    //test print compact
    for (int i = 0; i < maxVertical; i++) {
        printf("\t");
        for (int j = 0; j < maxHorizontal; j++) {
            printf("%c", output[j][i]);
        }
        printf("\n");
    }

    printf("\n</pre>\n</body>\n</html>\n");


    free(pic.img);
}
