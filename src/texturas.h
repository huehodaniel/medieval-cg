#ifndef TEXTURAS_H
#define TEXTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define WINDOWS 0
#define LINUX 1

#define CABECA_ATRAS 1
#define CABECA_BAIXO 2
#define CABECA_FRENTE 3
#define CABECA_LADO_DIREITO 4
#define CABECA_LADO_ESQUERDO 5
#define CABECA_TOPO 6
#define BRACO_ATRAS 7
#define BRACO_BAIXO 8
#define BRACO_CIMA 9
#define BRACO_FRENTE 10
#define BRACO_LADO 11
#define PERNA_ATRAS 12
#define PERNA_FRENTE 13
#define PERNA_BAIXO 14
#define PERNA_CIMA 15
#define PERNA_LADO 16
#define TORSO_ATRAS 17
#define TORSO_BAIXO 18
#define TORSO_CIMA 19
#define TORSO_LADO 20
#define TORSO_FRENTE 21

#define QTD_TEX 21

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
