#ifndef LOGICA_H
#define LOGICA_H

typedef enum _muralhaEstado { M100, M80, M60, M40, M20, M0 } muralhaEstado;

typedef struct _projetil {
    float x;
    float y;
    float z;
    float ang;
} projetil;

typedef struct _force {
    float val;
} force;

typedef struct _plInfo {
    projetil p;
    force f;
	muralhaEstado e;
} plInfo;

plInfo getinfo_p1();

plInfo getinfo_p2();

void initLogica();

void updateByAngle(projetil* p);

void check_colision_p1(projetil p);

void check_colision_p2(projetil p);

void shoot_p1(int speed);

void force_p1(int inc);

void end_force_p1(float ang);

void shoot_p2(int speed);

void force_p2(int inc);

void end_force_p2(float ang);

#endif //LOGICA_H
