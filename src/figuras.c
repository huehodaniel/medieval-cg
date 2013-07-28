#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

#include "macros.h"
#include "figuras.h"

bool inited = false;
GLUquadricObj *obj;

void initFiguras() {
  if(!inited) {
      obj = gluNewQuadric();
      gluQuadricDrawStyle(obj,GLU_FILL);
      inited = true;
  }
}

void roda() {
  transform({
    glColor(255, 255, 0);
    
    glTranslatef(0, 0, -5);
    gluDisk(obj, 50, 70, 20, 20);
    
    glColor(255, 255, 127);
    transform({
      glTranslatef(0, 0, 5);
      glScalef(10, 2, 1);
      glutSolidCube(10);
      glScalef(1/5.0, 5, 1);
      glutSolidCube(10);
    });
    
    glColor(255, 255, 0);
    gluCylinder(obj,70,70,10,20,20);
    gluCylinder(obj,50,50,10,20,20);
    glTranslatef(0, 0, 10);
    gluDisk(obj, 50, 70, 20, 20);
  });
}

void catapulta(float angulo) {
  transform({
    glTranslatef(0, -40, 70);
    glRotatef(90, 0, 1, 0);
    
    transform({
      glColor(255, 127, 127);
      glScalef(1, 1, 10);
      glutSolidCube(10);
    });
    
    glTranslatef(0, 0, -45);
    roda();
    glTranslatef(0, 0, 90);
    roda();
  });
  
  transform({
    glColor(255, 0, 0);
    gluDisk(obj, 0, 20, 20, 20);
    glColor(0, 255, 0);
    gluCylinder(obj,20,40,30,20,20);
    glTranslatef(0, 0, 30);
    gluCylinder(obj,40,40,100,20,20);
    glTranslatef(0, 0, 100);
    gluCylinder(obj,40,25,30,20,20);
    glTranslatef(0, 0, 30);
    gluCylinder(obj,25,20,100,20,20);
  });
}

void pessoaJogo(float angPerna, float angBraco) {
  
}

void pessoaVence() {
  
}

void pessoaMorta() {
  
}

void muralha(muralhaEstado estado) {
  
}

void castelo() {
  
}