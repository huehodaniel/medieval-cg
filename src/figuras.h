#ifndef FIGURAS_H
#define FIGURAS_H

#include "logica.h"

void initFiguras();
void catapulta(float angulo);
void pessoa();

void muralha(muralhaEstado estado);

void pessoa(estadoJogador tipo_pessoa, double estagio_anima);

void letreiroIni();

void letreiroFim(int vencedor);

#endif /** FIGURAS_H **/
