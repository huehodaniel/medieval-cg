#ifndef TEXTURAS_H
#define TEXTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define CABECA_ATRAS 1
#define CABECA_BAIXO 2
#define CABECA_FRENTE 3
#define CABECA_LADO_DIREITO 4
#define CABECA_LADO_ESQUERDO 5
#define CABECA_TOPO 6

#define QTD_TEX 6

GLuint texturesID[QTD_TEX];

typedef struct {
    int   width;
    int   height;
    char* data;
} BMPImage;

void getBitmapImageData( char* pFileName, BMPImage* pImage );

void funcoesDeCarregamento( char* img, int idImagem );

void CarregaTexturas();

void initTexture ();

#endif /* TEXTURAS_H */
