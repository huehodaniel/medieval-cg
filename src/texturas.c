#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "texturas.h"

//int SO = WINDOWS;
int SO = LINUX;

/* Funções para leitura de imagens .bmp */
void getBitmapImageData( char* pFileName, BMPImage* pImage ) {

    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);
    fseek( pFile, 18, SEEK_CUR );
    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n", pFileName);
    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n", pFileName);
    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read plane count from%s.\n", pFileName);
    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ",pFileName);
    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ",pFileName);
    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);
    fseek( pFile, 24, SEEK_CUR );
    int nTotalImagesize = (pImage->width * pImage->height) * 3;
    pImage->data = (char*) malloc( nTotalImagesize );
    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);
     char charTemp;

     for( i = 0; i < nTotalImagesize; i += 3 )
     {
          charTemp = pImage->data[i];
          pImage->data[i] = pImage->data[i+2];
          pImage->data[i+2] = charTemp;
     }
}

void funcoesDeCarregamento(char* img, int idImagem){

    BMPImage textura;

    getBitmapImageData(img, &textura);
    glBindTexture(GL_TEXTURE_2D, texturesID[idImagem]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textura.width,  textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);

}

void CarregaTexturas(){
	glGenTextures(QTD_TEX, texturesID);

	if ( SO == WINDOWS ) {
		//Carrega as texturas
		funcoesDeCarregamento("resources\\cabeca_atras.bmp", CABECA_ATRAS);
		funcoesDeCarregamento("resources\\cabeca_baixo.bmp", CABECA_BAIXO);
		funcoesDeCarregamento("resources\\cabeca_frente_jogo.bmp", CABECA_FRENTE_JOGO);
		funcoesDeCarregamento("resources\\cabeca_frente_vitoria.bmp", CABECA_FRENTE_VITORIA);
		funcoesDeCarregamento("resources\\cabeca_frente_derrota.bmp", CABECA_FRENTE_DERROTA);
		funcoesDeCarregamento("resources\\cabeca_frente_morte.bmp", CABECA_FRENTE_MORTE);
		funcoesDeCarregamento("resources\\cabeca_lado_direito.bmp", CABECA_LADO_DIREITO);
		funcoesDeCarregamento("resources\\cabeca_lado_esquerdo.bmp", CABECA_LADO_ESQUERDO);
		funcoesDeCarregamento("resources\\cabeca_topo.bmp", CABECA_TOPO);
		funcoesDeCarregamento("resources\\braco_atras.bmp", BRACO_ATRAS);
		funcoesDeCarregamento("resources\\braco_baixo.bmp", BRACO_BAIXO);
		funcoesDeCarregamento("resources\\braco_cima.bmp", BRACO_CIMA);
		funcoesDeCarregamento("resources\\braco_frente.bmp", BRACO_FRENTE);
		funcoesDeCarregamento("resources\\braco_lado.bmp", BRACO_LADO);
		funcoesDeCarregamento("resources\\perna_atras.bmp", PERNA_ATRAS);
		funcoesDeCarregamento("resources\\perna_baixo.bmp", PERNA_BAIXO);
		funcoesDeCarregamento("resources\\perna_cima.bmp", PERNA_CIMA);
		funcoesDeCarregamento("resources\\perna_frente.bmp", PERNA_FRENTE);
		funcoesDeCarregamento("resources\\perna_lado.bmp", PERNA_LADO);
		funcoesDeCarregamento("resources\\torso_atras.bmp", TORSO_ATRAS);
		funcoesDeCarregamento("resources\\torso_baixo.bmp", TORSO_BAIXO);
		funcoesDeCarregamento("resources\\torso_cima.bmp", TORSO_CIMA);
		funcoesDeCarregamento("resources\\torso_lado.bmp", TORSO_LADO);
		funcoesDeCarregamento("resources\\torso_frente.bmp", TORSO_FRENTE);

		funcoesDeCarregamento("resources\\muralha1.bmp", MURALHA1);
		funcoesDeCarregamento("resources\\muralha2.bmp", MURALHA2);
		funcoesDeCarregamento("resources\\muralha3.bmp", MURALHA3);
		funcoesDeCarregamento("resources\\muralha4.bmp", MURALHA4);
		funcoesDeCarregamento("resources\\muralha5.bmp", MURALHA5);
		funcoesDeCarregamento("resources\\muralha6.bmp", MURALHA6);
		funcoesDeCarregamento("resources\\muralha7.bmp", MURALHA7);
		funcoesDeCarregamento("resources\\muralha8.bmp", MURALHA8);
		funcoesDeCarregamento("resources\\muralha9.bmp", MURALHA9);
		funcoesDeCarregamento("resources\\muralha10.bmp", MURALHA10);
		funcoesDeCarregamento("resources\\muralha11.bmp", MURALHA11);
		funcoesDeCarregamento("resources\\muralha12.bmp", MURALHA12);

		funcoesDeCarregamento("resources\\bandeira_derrota.bmp", BANDEIRA_DERROTA);
		funcoesDeCarregamento("resources\\bandeira_derrota_cabo.bmp", BANDEIRA_DERROTA_CABO);

		
	}
	else
	{
		//Carrega as texturas
				funcoesDeCarregamento("./resources/cabeca_atras.bmp", CABECA_ATRAS);
		funcoesDeCarregamento("./resources/cabeca_baixo.bmp", CABECA_BAIXO);
		funcoesDeCarregamento("./resources/cabeca_frente_jogo.bmp", CABECA_FRENTE_JOGO);
		funcoesDeCarregamento("./resources/cabeca_frente_vitoria.bmp", CABECA_FRENTE_VITORIA);
		funcoesDeCarregamento("./resources/cabeca_frente_derrota.bmp", CABECA_FRENTE_DERROTA);
		funcoesDeCarregamento("./resources/cabeca_frente_morte.bmp", CABECA_FRENTE_MORTE);
		funcoesDeCarregamento("./resources/cabeca_lado_direito.bmp", CABECA_LADO_DIREITO);
		funcoesDeCarregamento("./resources/cabeca_lado_esquerdo.bmp", CABECA_LADO_ESQUERDO);
		funcoesDeCarregamento("./resources/cabeca_topo.bmp", CABECA_TOPO);
		funcoesDeCarregamento("./resources/braco_atras.bmp", BRACO_ATRAS);
		funcoesDeCarregamento("./resources/braco_baixo.bmp", BRACO_BAIXO);
		funcoesDeCarregamento("./resources/braco_cima.bmp", BRACO_CIMA);
		funcoesDeCarregamento("./resources/braco_frente.bmp", BRACO_FRENTE);
		funcoesDeCarregamento("./resources/braco_lado.bmp", BRACO_LADO);
		funcoesDeCarregamento("./resources/perna_atras.bmp", PERNA_ATRAS);
		funcoesDeCarregamento("./resources/perna_baixo.bmp", PERNA_BAIXO);
		funcoesDeCarregamento("./resources/perna_cima.bmp", PERNA_CIMA);
		funcoesDeCarregamento("./resources/perna_frente.bmp", PERNA_FRENTE);
		funcoesDeCarregamento("./resources/perna_lado.bmp", PERNA_LADO);
		funcoesDeCarregamento("./resources/torso_atras.bmp", TORSO_ATRAS);
		funcoesDeCarregamento("./resources/torso_baixo.bmp", TORSO_BAIXO);
		funcoesDeCarregamento("./resources/torso_cima.bmp", TORSO_CIMA);
		funcoesDeCarregamento("./resources/torso_lado.bmp", TORSO_LADO);
		funcoesDeCarregamento("./resources/torso_frente.bmp", TORSO_FRENTE);
		
		funcoesDeCarregamento("./resources/muralha1.bmp", MURALHA1);
		funcoesDeCarregamento("./resources/muralha2.bmp", MURALHA2);
		funcoesDeCarregamento("./resources/muralha3.bmp", MURALHA3);
		funcoesDeCarregamento("./resources/muralha4.bmp", MURALHA4);
		funcoesDeCarregamento("./resources/muralha5.bmp", MURALHA5);
		funcoesDeCarregamento("./resources/muralha6.bmp", MURALHA6);
		funcoesDeCarregamento("./resources/muralha7.bmp", MURALHA7);
		funcoesDeCarregamento("./resources/muralha8.bmp", MURALHA8);
		funcoesDeCarregamento("./resources/muralha9.bmp", MURALHA9);
		funcoesDeCarregamento("./resources/muralha10.bmp", MURALHA10);
		funcoesDeCarregamento("./resources/muralha11.bmp", MURALHA11);
		funcoesDeCarregamento("./resources/muralha12.bmp", MURALHA12);

		funcoesDeCarregamento("./resources/bandeira_derrota.bmp", BANDEIRA_DERROTA);
		funcoesDeCarregamento("./resources/bandeira_derrota_cabo.bmp", BANDEIRA_DERROTA_CABO);


	}
}
