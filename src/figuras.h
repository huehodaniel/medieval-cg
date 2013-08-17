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

// AlguÃ©m um dia
void pessoa();
void pessoa_v2();

// AruÃ£ vai fazer o castelo
// Daniel vai fazer bandeira e trombete
void bandeira(int jogador);
void trombete();

#endif /** FIGURAS_H **/
