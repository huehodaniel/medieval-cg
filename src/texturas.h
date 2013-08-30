/*!
 * \file
 *
 * Este eh o arquivo de cabecalho utilizado pela parte relacionada as texturas utilizadas no projeto,
 * aqui sao definidas as constantes utilizadas, e a assinatura das funcoes implementadas para a utilizacao
 * de texturas.
 *
 */

#ifndef TEXTURAS_H
#define TEXTURAS_H

#define WINDOWS 0
#define LINUX 1

#define CABECA_ATRAS 1
#define CABECA_BAIXO 2
#define CABECA_FRENTE_JOGO 3
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

//texturas da muralha
#define MURALHA1 22
#define MURALHA2 23
#define MURALHA3 24
#define MURALHA4 25
#define MURALHA5 26
#define MURALHA6 27
#define MURALHA7 28
#define MURALHA8 29
#define MURALHA9 30
#define MURALHA10 31
#define MURALHA11 32
#define MURALHA12 33

#define CABECA_FRENTE_VITORIA 34
#define CABECA_FRENTE_DERROTA 35
#define CABECA_FRENTE_MORTE 36
#define BANDEIRA_DERROTA 37
#define BANDEIRA_DERROTA_CABO 38

#define GRAMA 39
#define RIO 40
#define CEU 41

#define QTD_TEX 42

extern GLuint texturesID[QTD_TEX];

typedef struct {
    int   width;
    int   height;
    char* data;
} BMPImage;

/*!
 * \brief Funcao para interpretar uma imagem no formato .bmp.
 *
 * Essa funcao interpreta um arquivo de imagem no formato .bmp e transforma esse arquivo em uma estrutura
 * de dados ( \ref BMPImage ) virtual para a utilizacao dessa imagem como um textura.
 *
 * \param pFileName Caminho do arquivo de imagem no formato bmp.
 * \param pImagem Estrutura de dados utilizada para armazenar a imagem lida.
 *
 * \return void
 */
void getBitmapImageData( char* pFileName, BMPImage* pImage );

/*!
 * \brief Funcao para ler uma imagem no formato .bmp.
 *
 * Essa funcao le um arquivo de imagem no formato .bmp e salva esse arquivo lido de acordo com um id,
 * para a utilizacao da mesma no programa.
 *
 * \param img Caminho do arquivo de imagem.
 * \param idImagem ID para diferenciacao das imagens lidas.
 *
 * \return void
 */
void funcoesDeCarregamento( char* img, int idImagem );

/*!
 * \brief Funcao para carregar todas as texturas utilizadas.
 *
 * Essa funcao realiza a leitura e identificacao de todas as texturas a serem utilizadas no programa.
 *
 * \return void
 */
void CarregaTexturas();

#endif /* TEXTURAS_H */
