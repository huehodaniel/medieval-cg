#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

#include "macros.h"
#include "logica.h"

const float G = 9.81;
static const float ANIM_SPEED = 240; //velocidade da bola

static projetil p1, p2;
static force f1, f2;
static muralhaEstado e1, e2;
static bool charging1 = false, charging2 = false;
static bool colide1 = false, colide2 = false;

#define _auxInit(i) \
	p##i.x = p##i.y = p##i.z = p##i.ang = f##i.val = 0; \
	e##i = M100
	
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
    v.e = e##i; \
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

#define _auxColision(i) macrofy(\
        e##i++; \
        if(e##i >= M0) { \
            0; \
        }) 

void check_colision_p1(projetil p) { 
    // Seja a equação da parábola para a muralha 1 igual a f(x) = 0.00012z² + 810
    if(p.z >= 0.00012*pow2(p.x) + 810 && p.z - 910 <= 0) {
        colide1 = true;
        _auxColision(2);        
    }
}

void check_colision_p2(projetil p) { 
    // Seja a equação da parábola para a muralha 2 igual a f(x) = 0.00012z² + 810
    //dprintf("%f, %f", p.x, p.z);
    if(p.z >= 0.00012*pow2(p.x) + 810 && p.z - 910 <= 0) {
        colide2 = true;
        _auxColision(1);        
    }
}

#define _shoot(speed, i) macrofy(\
    repeat(ANIM_SPEED) { \
        p##i.x++; \
    	p##i.y += deltaY(p##i.x, speed); \
    } \
	glutPostRedisplay(); \
    if(!colide##i && valid(p##i.x, 20000) && valid(p##i.y, 20000)) \
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
		dprintf("%f\n", p##i.ang); \
	})

void end_force_p1(float ang) { 
	_auxendforce(1);
}

void end_force_p2(float ang) { 
	_auxendforce(2);
}
