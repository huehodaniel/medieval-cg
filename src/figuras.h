#ifndef FIGURAS_H
#define FIGURAS_H

void initFiguras();
void catapulta();
void pessoaJogo();

typedef enum _muralhaEstado { _M100, _M80, _M60, _M40, _M20, _M0 } muralhaEstado;

// Kim
void muralha(muralhaEstado estado);

// Alguém um dia
void pessoaVence();
void pessoaPerde();
void pessoaMorta();

// Aruã vai fazer o castelo
// Daniel vai fazer bandeira e trombete

#endif /** FIGURAS_H **/
