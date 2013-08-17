#include "texturas.h"

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

    glGenTextures(QTD_TEX, &texturesID[0]);

    //Carrega a textura do poste
    funcoesDeCarregamento("imgs\\Cabeca_Atras.bmp", CABECA_ATRAS);
    funcoesDeCarregamento("imgs\\Cabeca_Baixo.bmp", CABECA_BAIXO);
    funcoesDeCarregamento("imgs\\Cabeca_Frente.bmp", CABECA_FRENTE);
    funcoesDeCarregamento("imgs\\Cabeca_Lado_direito.bmp", CABECA_LADO_DIREITO);
    funcoesDeCarregamento("imgs\\Cabeca_Lado_esquerdo.bmp", CABECA_LADO_ESQUERDO);
    funcoesDeCarregamento("imgs\\Cabeca_Topo.bmp", CABECA_TOPO);
}

void initTexture (){
    /* Habilita o uso de textura bidimensional  */
    glEnable(GL_TEXTURE_2D);
    CarregaTexturas();
}
