/*!
 * \file
 *
 * Neste arquivo sao definidas as funcoes utilizadas para desenhar isoladamente cada objeto do jogo.
 */

#ifndef FIGURAS_H
#define FIGURAS_H

#include "logica.h"

/*!
 * \brief Inicializa alguns parametros para os desenhos.
 *
 * \return void
 */
void initFiguras();

/*!
 * \brief Desenha a catapulta, na verdade eh um canhao, mas whatever XD
 *
 * \param angulo Angulo de inclinacao do canhao a ser desenhado.
 *
 * \return void
 */
void catapulta(float angulo);

/*!
 * \brief Desenha um bloco de muralha.
 *
 * \param estado Estado de danificacao da muralha varia de acordo com a quantidade de vezes que a muralha foi atingida.
 *
 * \return void
 */
void muralha(muralhaEstado estado);

/*!
 * \brief Desenha uma pessoa, que eh mostrada ao lado do canhao
 *
 * \param tipo_pessoa Define como a pessoa deve ser desenhada, pessoa morta, pessoa durante o jogo, pessoa quando venceu, etc.
 * \param estagio_anima Estagio da animacao em que a pessoa ser desenhada se encontra, esse parametro eh atualizada na funcao \ref anima_func .
 *
 * \return void
 */
void pessoa(estadoJogador tipo_pessoa, double estagio_anima);

/*!
 * \brief Desenha o letreiro mostrado no inicio do jogo.
 *
 * \return void
 */
void letreiroIni();

/*!
 * \brief Desenha o letreiro apresentado ao final do jogo, apresentando o vencedor.
 *
 * \param vencedor Qual foi o jogador vencedor da partida.
 *
 * \return void
 */
void letreiroFim(int vencedor);

/*!
 * \brief Desenha um letreiro de pontuacao, a posicao e o numero apresentado varia de acordo com os parametros.
 *
 * \param jogador Define a qual jogador pertence o letreiro a ser desenhado, o que defina a sua posicao.
 * \param pontos Pontuacao a ser mostrada no letreiro.
 *
 * \return void
 */
void pontuacao(int jogador, int pontos);

#endif /** FIGURAS_H **/
