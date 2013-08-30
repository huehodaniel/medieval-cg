/*!
 * \file
 *
 * Neste arquivo sao implementadas as funcoes utilizadas na ilumincao do jogo, essas funcoes sao definidas no arquivo \ref iluminacao.h
 */

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "iluminacao.h"


GLfloat light0_pos[] = {4.0f,10.0f, 6.0f, 1.0f};
GLfloat white[] = {9.0f, 9.0f, 9.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};


void lightning(){
	//glNormal3f(1.0f, 1.0f, 1.0f);
	//Define luz ambiente
    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

    //Atenuação radial - luz ambiente
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);   //define a0
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15f);    //define a1
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);  //define a2

    //Parâmetros definidos globalmente
    GLfloat global_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    
    glEnable(GL_COLOR_MATERIAL);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE  ) ;


    //Valores RGBA para uma superfície emissora de luz I_surf
    GLfloat surface_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT,GL_EMISSION,surface_emission);
    //Coeficiente de reflexão difusa k_d
    //GLfloat diffuse[] = {0.0f, 0.0f, 0.65f, 1.0f};
    //glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
    //Coeficiente de reflexão especular k_s
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    //Coeficiente de reflexão da luz ambiente k_a
    GLfloat shininess = 100.0f;
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);

    
}

void initLight(){
    /**glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(0.0, 0.0, 1.0,   //posição da câmera
              0.0, 0.0, 0.0,   //para onde a câmera aponta
              0.0, 1.0, 0.0);  //vetor view-up

    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0); //define uma projeção ortogonal
    //gluPerspective(90.0, 1.0, 2.0, 8.0); //define uma projeção perspectiva
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 8.0); //define uma projeção perspectiva simétrica
    //glFrustum(-2.0, 1.0, -1.0, 2.0, 2.0, 8.0); //define uma projeção perspectiva obliqua
    glViewport(0, 0, 500, 500);*/

    lightning();
}
