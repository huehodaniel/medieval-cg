#ifndef LOGICA_H
#define LOGICA_H

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
} plInfo;

plInfo getinfo_p1();

plInfo getinfo_p2();

void updateByAngle(projetil* p);

void shoot_p1(int speed);

void force_p1(int inc);

void end_force_p1(float ang);

void shoot_p2(int speed);

void force_p2(int inc);

void end_force_p2(float ang);

#endif //LOGICA_H
