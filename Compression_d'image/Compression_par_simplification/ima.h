#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

#define __OSX__
#ifndef __OSX__
/* pour Bocal */
#include <GL/gl.h>      
#else
/* pour mac 
#include <GLUT/glut.h>*/
///////////////////////////////////
/* pour machine perso*/ 
#include <GL/glut.h>
#endif


struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;


struct pixel_t{
	GLubyte r,g,b;
};
typedef struct pixel_t pixel_t;



typedef unsigned short utab [3][3][3];

int ImageLoad_PPM(char *filename, Image *image);
void imagesave_PPM(char *filename, Image *image);
void upsidedown(Image *);
void gris_uniforme (Image *);

