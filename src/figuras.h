#ifndef FIGURAS_H
#define FIGURAS_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "macros.h"
#include "texturas.h"

void initFiguras();
void catapulta(float angulo);
void pessoa();

typedef enum _muralhaEstado { _M100, _M80, _M60, _M40, _M20, _M0 } muralhaEstado;

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
