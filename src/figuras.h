#ifndef FIGURAS_H
#define FIGURAS_H

#include "logica.h"

void initFiguras();
void catapulta(float angulo);

void muralha(muralhaEstado estado);

void pessoa(estadoJogador tipo_pessoa, double estagio_anima);

void letreiroIni();
void letreiroFim(int vencedor);
void pontuacao(int jogador, int pontos);

#endif /** FIGURAS_H **/
