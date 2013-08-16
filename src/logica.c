#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>

#include "macros.h"
#include "logica.h"

const float G = 9.81;
static const float ANIM_SPEED = 240; //velocidade da bola

static projetil p1, p2;
static force f1, f2;
static bool charging1 = false, charging2 = false;

#define _getinfo(i) \
    plInfo v; \
    v.p = p##i; \
    v.f = f##i; \
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

#define _shoot(speed, i) \
    repeat(ANIM_SPEED) { \
        p##i.x++; \
    	p##i.y += deltaY(p##i.x, speed); \
    } \
	glutPostRedisplay(); \
    if(valid(p##i.x, 20000) && valid(p##i.y, 20000)) \
        glutTimerFunc(10, shoot_p##i, speed); \
    else p##i.x = p##i.y = 0

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

void end_force_p1() { charging1 = false; }

void end_force_p2() { charging2 = false; }
