#ifndef FIGURAS_H
#define FIGURAS_H

#include "logica.h"

void initFiguras();
void catapulta(float angulo);
void pessoa();

// Kim
void muralha(muralhaEstado estado);
void muralhaArua(muralhaEstado estado);

/* Funcao generica para todas as pessoas:
 * parametro 'tipo_pessoa':
 * 	- 0 pessoaJogo
 * 	- 1 pessoaVitoria
 * 	- 2 pessoaDerrota
 * 	- 3 pessoaMorte
 */
void pessoa(int tipo_pessoa, double estagio_anima);

#endif /** FIGURAS_H **/
