#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

#include "macros.h"
#include "logica.h"

const float G = 9.81;
static const float ANIM_SPEED = 180; //velocidade da bola

static projetil p1, p2;
static force f1, f2;
static muralhaEstado e1[9], e2[9];
static bool charging1 = false, charging2 = false;
static bool colide1 = false, colide2 = false;
static estadoJogador jg1 = JOGANDO, jg2 = JOGANDO;

#define _auxInit(i) \
	p##i.x = p##i.y = p##i.z = p##i.ang = f##i.val = 0; \
	range(idx, 0, 9) e##i[idx] = M100;
	
void initLogica() {
	_auxInit(1);
	_auxInit(2);
}

void updateByAngle(projetil *p) {
    float old = p->x;
    p->x = fabsf(p->x*cos(-radians(p->ang)));
    p->z = old*sin(-radians(p->ang));
}

#define _getinfo(i) \
    plInfo v; \
    v.p = p##i; \
    v.f = f##i; \
    v.e = &e##i[0]; \
    v.j = jg##i; \
    return v

plInfo getinfo_p1() { _getinfo(1); }

plInfo getinfo_p2() { _getinfo(2); }

static float deltaY(int x, float C) {
	return 1 - G*(2*x + 1)/C;
}

static inline bool valid(int v, int vmax) {
    return v > 0 && v < vmax;
}

static inline int pow2(int x) {
	return x * x;
}

// Salve Wolfram
static float intervalos[9][2] = {
    {-1550, -1215.70},
    {-1215.70, -874.05},
    {-874.05, -526.71},
    {-526.71, -175.75},
    {-175.75, 175.75},
    {175.75, 526.71},
    {526.71, 874.05},
    {874.05, 1215.70},
    {1215.70, 1550}
};

static int getMuralha(float z) {
    range(i, 0, 9) {
        dprintf("%f, %f, %f\n", intervalos[i][0], z, intervalos[i][1]);
        if(z >= intervalos[i][0] && z <= intervalos[i][1]) return i;
    }
    return 4;
}

// Seja a equação da parábola para a muralha oponente igual a f(x) = 0.00012z² + 810 + x0
// e a equação da parábola para a própria muralha igual a f(x) = - 0.00012z² + 600 + x0
#define _validateColision(i, j, p) \
    float z = 0.00012*pow2(p.z); \
    bool oponente = p.x >= z + 2210 && p.x <= z + 2260; \
    bool propria  = p.x >= -z + 600 && p.x <= -z + 650; \
    if(oponente || propria) { \
        int muralha = getMuralha(p.z); \
        dprintf("%d\n", muralha); \
        if(oponente){\
            if(p.y > e##j[muralha]*50) return; \
            else colide##i = true; \
            e##j[muralha]--; \
            if(e##j[muralha] == M0) { \
                jg##i = VENCEU; \
                jg##j = PERDEU; \
            } \
        } else { \
            if(p.y > e##i[muralha]*50) return; \
            else colide##i = true; \
            e##i[muralha]--; \
            if(e##i[muralha] == M0) { \
                jg##j = VENCEU; \
                jg##i = PERDEU; \
            } \
        } \
        glutPostRedisplay(); \
    }

void check_colision_p1(projetil p) { 
    _validateColision(1, 2, p)
}

void check_colision_p2(projetil p) { 
    _validateColision(2, 1, p)
}

#define _shoot(speed, i) macrofy(\
    projetil upd; \
    repeat(ANIM_SPEED) { \
        p##i.x++; \
    	p##i.y += deltaY(p##i.x, speed); \
        upd = p##i; \
        updateByAngle(&upd); \
        check_colision_p##i(upd); \
        if(colide##i) break; \
    } \
    glutPostRedisplay(); \
    if(!colide##i && valid(upd.x, 20000) && valid(upd.y, 20000)) \
        glutTimerFunc(10, shoot_p##i, speed); \
    else { \
        p##i.x = p##i.y = p##i.z = 0; \
        colide##i = false; \
    })

void shoot_p1(int speed) { _shoot(speed, 1); }

void shoot_p2(int speed) { _shoot(speed, 2); }

#define _force(inc, i) macrofy( \
    if(charging##i) { \
        f##i.val += inc; \
        glutTimerFunc(5, _force_p##i, inc); \
    } \
    else { \
        shoot_p##i(pow2(f##i.val)); \
        f##i.val = 0;\
    })

static void _force_p1(int inc) { _force(inc, 1); }

static void _force_p2(int inc) { _force(inc, 2); }

#define _auxforce(i) macrofy( \
    if(charging##i) return; \
    f##i.val = 0; \
    charging##i = true;)

void force_p1(int inc) { 
    _auxforce(1);
    _force_p1(inc); 
}

void force_p2(int inc) { 
    _auxforce(2);
    _force_p2(inc); 
}

#define _auxendforce(i) macrofy( \
	if(charging##i) { \
		charging##i = false; \
		p##i.ang = ang; \
	})

void end_force_p1(float ang) { 
	_auxendforce(1);
}

void end_force_p2(float ang) { 
	_auxendforce(2);
}
