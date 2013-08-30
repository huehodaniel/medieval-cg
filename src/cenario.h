/*!
 * \file
 *
 * Neste arquivo sao definidas as constantes e funcoes utilizadas para o desenho
 * de todo o cenario do jogo.
 *
 */

#ifndef CENARIO_H
#define CENARIO_H

#define NUM_TREES 240

extern float tx1[NUM_TREES/2], tx2[NUM_TREES/2], ty1[NUM_TREES/2], ty2[NUM_TREES/2];

/*!
 * \brief Funcao para desenhar a copa das arvores.
 *
 * Essa funcao desenha a copa das arvores mostradas no cenario, as copas sao desenhadas na posicao
 * passada por parametro.
 *
 * \param x Posicao da copa da arvore em relacao ao eixo x.
 * \param y Posicao da copa da arvore em relacao ao eixo y.
 *
 * \return void
 */
void drawBranches(float x, float y);

/*!
 * \brief Funcao para desenhar o tronco das arvores.
 *
 * Essa funcao desenha o tronco das arvores mostradas no cenario, os troncos sao desenhados na posicao
 * passada por parametro.
 *
 * \param x Posicao do tronco da arvore em relacao ao eixo x.
 * \param y Posicao do tronco da arvore em relacao ao eixo y.
 *
 * \return void
 */
void drawTrunk(float x, float y);

/*!
 * \brief Funcao para inicializacao dos parametros utilizados na contrucao do cenario.
 *
 * Essa funcao incializa os parametros utilizados para contrucao do cenario, por exemplo, para posicoes
 * aleatorias das arvores.
 *
 * \return void
 */
void initCenario();

/*!
 * \brief Funcao que desenha e posiciona todos os objetos do cenario.
 *
 * Essa funcao desenha e posicona todos os objetos do cenario, por exemplo, posicao das arvores, rio, muralhas, canhoes, etc.
 *
 * \return void
 */
void cenario();


#endif /** CENARIO_H **/
