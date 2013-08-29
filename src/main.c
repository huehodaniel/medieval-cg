#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

#include "macros.h"
#include "figuras.h"
#include "cenario.h"
#include "iluminacao.h"
#include "logica.h"
#include "texturas.h"

// String cabeçalho
#define HEADER "-- Computação Grafica, turma de 2013, vespertino --"

/**
 * Constantes de configuração para o programa em particular
 **/
const char* APP_NAME = "Batalha Medieval";
const int WINDOW_POSITION_X = 200, WINDOW_POSITION_Y = 200;
const int WINDOW_SIZE_X = 800, WINDOW_SIZE_Y = 600;

/**
 * Funções e variáveis para interação e desenho
 * - todas as funções que sejam ponto de entrada para o GLUT devem ser precedidas de um define criando um alias para a função
 * -- Mouse: #define MOUSE_FUNC <nome_da_função>
 * -- Desenho: #define DRAW_FUNC <nome_da_função>
 * -- Teclado: #define KBD_FUNC <nome_da_função>
 * -- Teclado (soltar tecla): #define KBD_UP_FUNC <nome_da_função>
 * -- Teclas Especiais: #define SPKEY_FUNC <nome_da_função>
 * -- Miscelânea: #define MISC_FUNC <nome_da_função>
 * -- Movimento do mouse: #define MOUSEMOV_FUNC <nome_da_função>
 **/
 
// Angulos de visão
int ang = 0;
int viewangX = 0;
int viewangY = 0;
int viewangZ = 0;
int direcaoCanhao1 = 0;
int direcaoCanhao2 = 0;
int moverCanhao1 = 0;
int moverCanhao2 = 0;

// Posição do pointer
int x_pointer = 0;
int z_pointer = 0;
int pass = 10;

// Estado do jogo
typedef enum _modoJogo { INICIO, JOGO, FIM } modoJogo;
modoJogo modo = INICIO;

double pessoa_estagio_anima = 0.0, pessoa_estagio_incremento = 3.0;

//Vetor de estados do teclado (para permitir multiplas teclas pressionadas)
bool keystate[256], spkeystate[256];

void anima_func(int value)
{
	/* Animacao de vitoria */
	if(pessoa_estagio_anima > 100.0 || pessoa_estagio_anima < 0.0)
	{
		pessoa_estagio_incremento *= -1;
	}
	pessoa_estagio_anima += pessoa_estagio_incremento;

	if(modo == INICIO) {
		viewangY += 2;
	}

	glutTimerFunc( 10, anima_func, 1 ); /* Faz a funcao anima_func continuar sendo chamada infinitamente */
	glutPostRedisplay();
}

#define MISC_FUNC misc
void misc()
{
	// determinando face sólida para polígonos
	glPolygonMode(GL_FRONT, GL_FILL);
	// determinando background preto
    //glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearColor(0.1, 0.6, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	// Carregando matriz identidade
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(0,0,-1);
	// Carregando modo de visualização ortográfica
	int wx = WINDOW_SIZE_X/2, wy = WINDOW_SIZE_Y/2;
	//int SCALE=2;
	//glOrtho(-SCALE*wx, SCALE*wx, -SCALE*wy, SCALE*wy, -SCALE*wx, SCALE*wx);
    gluPerspective(90.0,  wx/(wy*1.0),  1.0,  WINDOW_SIZE_X);

    glutIgnoreKeyRepeat(true);

	initFiguras();
	initCenario();
	initLogica();
	glMatrixMode(GL_MODELVIEW);
    initLight();
	
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
	CarregaTexturas();
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

    gluLookAt(0.0, 0.0, 1.0,   //posição da câmera
              0.0, 0.0, 0.0,   //para onde a câmera aponta
              0.0, 1.0, 0.0);  //vetor view-up

    range(i, 0, 255) keystate[i] = spkeystate[i] = false;
    glutTimerFunc(10, anima_func, 1);
    glMatrixMode(GL_PROJECTION);
}

void keyboardOpStart() {
	if(keystate[13]) {
		modo = JOGO;
		viewangY = 0;
		viewangX = 35;
		glutPostRedisplay();
	}
}

const int force_inc = 3;

void keyboardOp(plInfo p1, plInfo p2) {
    if(keystate['m'] && p1.j == JOGANDO) {
         if(p1.p.x <= 0) force_p1(force_inc);
    } else {
        end_force_p1(-direcaoCanhao1);
    }

    if(keystate['z'] && p2.j == JOGANDO) {
        if(p2.p.x <= 0) force_p2(force_inc);
    } else {
        end_force_p2(direcaoCanhao2);
    }


	/* Rotacao em Z */
	/*if(keystate['z']) {
		viewangZ--;
		glutPostRedisplay();
	} else if(keystate['Z']) {
		viewangZ++;
		glutPostRedisplay();
	}*/

    /* Rotacao em Y */
	if(spkeystate[GLUT_KEY_LEFT]) {
		viewangY--;
		glutPostRedisplay();
	} else if(spkeystate[GLUT_KEY_RIGHT]) {
		viewangY++;
		glutPostRedisplay();
	}

	/* Rotacao em X */
	if(spkeystate[GLUT_KEY_DOWN]) {
		viewangX++;
		glutPostRedisplay();
	} else if(spkeystate[GLUT_KEY_UP]) {
		viewangX--;
		glutPostRedisplay();
	}
	
	if(keystate['n']){
		if(direcaoCanhao1 < 40)
			direcaoCanhao1 += 2;
			dprintf("%d\n", direcaoCanhao1);
	}
	
	if(keystate['j']){
		if(direcaoCanhao1 > -40)
			direcaoCanhao1 -= 2;
			dprintf("%d\n", direcaoCanhao1);
	}
	
	if(keystate['s']){
		if(direcaoCanhao2 < 40)
			direcaoCanhao2 += 2;
			dprintf("%d\n", direcaoCanhao2);
	}
	
	if(keystate['x']){
		if(direcaoCanhao2 > -40)
			direcaoCanhao2 -= 2;
			dprintf("%d\n", direcaoCanhao2);
	}

	if(keystate['a']) x_pointer -= pass;
	if(keystate['d']) x_pointer += pass;
	if(keystate['w']) z_pointer += pass;
	if(keystate['s']) z_pointer -= pass;
	if(keystate['e']) dprintf("%d, %d\n", x_pointer, z_pointer);
}

void keyboardOpEnd() {
	if(keystate[13]) exit(0);
}

#define DRAW_FUNC drawfunc
void drawfunc()
{
	plInfo pl1 = getinfo_p1(), pl2 = getinfo_p2();
	if(pl1.j == VENCEU || pl2.j == VENCEU) modo = FIM;

	switch(modo) {
		case INICIO: keyboardOpStart(); break;
		case JOGO: keyboardOp(pl1, pl2); break;
		case FIM: keyboardOpEnd();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    transform({
        glTranslatef(0, 0, -WINDOW_SIZE_X*1.5);
        transform({
        	glTranslatef(0, 200, 0);
	        if(modo == INICIO) {
		    	letreiroIni();
		    } else if(modo == FIM) {
		    	letreiroFim(pl1.j == VENCEU ? 1 : 2);
		    } else {
		    	glTranslatef(-1500, 800, 0);
		    	pontuacao(2, pl2.pnt);
		    	glTranslatef(2500, 0, 0);
		    	pontuacao(1, pl1.pnt);
		    }
		});
	    transform({
            glRotatef(viewangX, 1, 0, 0);
		    glRotatef(viewangY, 0, 1, 0);
		    glRotatef(viewangZ, 0, 0, 1);
		    //glTranslatef(0,0,-1000);
		    cenario();
            transform({
                glRotatef(90,0,1,0); //localizacao do canhao
                glTranslatef(0,-315,-1400);
                glScalef(0.3,0.3,0.3);
				glRotatef(direcaoCanhao2,0,1,0);
				catapulta(0);
			});
			transform({
				glTranslatef(-1400,-315,0);
				glColor(0, 0, 0);
				projetil p2 = pl2.p;
				updateByAngle(&p2);
				//check_colision_p2(p2);
				glTranslatef(p2.x, p2.y, p2.z);
				glutSolidSphere(15, 20, 20);
			});
			transform({
				glRotatef(-90,0,1,0);
				glTranslatef(0,-315,-1400);
				glScalef(0.3,0.3,0.3);
				glRotatef(direcaoCanhao1,0,1,0);
				catapulta(0);
			});
			transform({
				glColor(0, 0, 0);
				glTranslatef(1400,-315,0);
				projetil p1 = pl1.p;
				updateByAngle(&p1);
				//check_colision_p1(p1);
				glTranslatef(-p1.x, p1.y, p1.z);
				glutSolidSphere(15, 20, 20);
			});
            transform({
                glTranslatef(-800,-260,-60);
                glScalef(0.4,0.4,0.4);
                //glScalef(1.5, 1.5, 1.5);
                muralha(pl2.e[4]);
                transform({
		            for(int idx = 3; idx >= 0; idx--) {
		                glRotatef(5,0,1,0);
		                glTranslatef(30,0,-900);
		                muralha(pl2.e[idx]);
		            }
		            repeat(5) {
		                glRotatef(5,0,1,0);
		                glTranslatef(30,0,-900);
		                muralha(M100);
		            }
		        });
		        
		        transform({
		            range(idx, 5, 9) {
		                glRotatef(-5,0,1,0);
		                glTranslatef(60,0,900);
		                muralha(pl2.e[idx]);
		            }
		            repeat(5) {
		                glRotatef(-5,0,1,0);
		                glTranslatef(60,0,900);
		                muralha(M100);
		            }
		        });
            });
            transform({
                glTranslatef(800,-260,-60);
                glScalef(0.4,0.4,0.4);
                //glScalef(1.5, 1.5, 1.5);
                muralha(pl1.e[4]);
                transform({
                    for(int idx = 3; idx >= 0; idx--) {
		                glRotatef(-5,0,1,0);
		                glTranslatef(-30,0,-900);
		                muralha(pl1.e[idx]);
		            }
		            repeat(5) {
		                glRotatef(-5,0,1,0);
		                glTranslatef(-30,0,-900);
		                muralha(M100);
		            }
		        });
		        transform({
		            range(idx, 5, 9) {
		                glRotatef(5,0,1,0);
		                glTranslatef(-60,0,900);
		                muralha(pl1.e[idx]);
		            }
		            repeat(5) {
		                glRotatef(5,0,1,0);
		                glTranslatef(-60,0,900);
		                muralha(M100);
		            }
		        });
            });
            transform({
            	glTranslatef(1500,-315,0);
                glRotatef(-90,0,1,0);
                glScalef(0.15,0.15,0.15);
                pessoa(pl1.j, pessoa_estagio_anima);
            });
            transform({
            	glTranslatef(-1500,-315,0);
                glRotatef(90,0,1,0);
                glScalef(0.15,0.15,0.15);
                pessoa(pl2.j, pessoa_estagio_anima);
            });
            if(DEBUG){
            	glColor(255, 0, 0);
            	glTranslatef(x_pointer, -50, z_pointer);
            	glutSolidSphere(50, 20, 20);
            }    
        });
    }); 

	//==========================


	/*transform({
		glRotatef(viewangX, 1, 0, 0);
		glRotatef(viewangY, 0, 1, 0);
		glRotatef(viewangZ, 0, 0, 1);
        muralha(3);
		//catapulta(0);

		//glTranslatef(100, 100, 0);
		//bandeira(1);
    	//glTranslatef(100, 100, 0);
		//trombete();

		glTranslatef(x1_pos, y1_pos, 0);
		//glutSolidSphere(100, 20, 20); //20
	});

	//Mostrar apenas a pessoa
	transform({
		glRotatef(viewangX, 1, 0, 0);
		glRotatef(viewangY, 0, 1, 0);
		glRotatef(viewangZ, 0, 0, 1);
		//glTranslatef(-400, 0, 0);
		//glScalef(0.5, 0.5, 0.5);
		pessoa_v2(0, pessoa_estagio_anima);
	});*/

	glutSwapBuffers();
}

#define KBD_FUNC keyboard
void keyboard(unsigned char key, int x, int y) {
    dprintf("%d\n", key);
    keystate[key] = true;
}

#define KBD_UP_FUNC keyboardUp
void keyboardUp(unsigned char key, int x, int y) {
    //dprintf("%c\n", key);    
    keystate[key] = false;
}

#define SPKEY_FUNC spkeys
void spkeys(int key, int x, int y) {
	dprintf("%d\n", key);
    spkeystate[key] = true;
}


#define SPKEY_UP_FUNC spkeysUp
void spkeysUp(int key, int x, int y) {
	//dprintf("%d\n", key);
    spkeystate[key] = false;
}

/**
 * Funções de configuração inicial
 **/

/*
 * LOG_credits()
 * Imprime no console dados do programa
 */
void LOG_credits()
{
    console(HEADER);
    console(APP_NAME);
}

/*
 * GL_windowSetUp(int* argc, char* argv)

 * Configura a janela do programa
 */
void GL_windowSetUp(int* argc, char *argv[])
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
	glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	glutInit(argc, argv);
	glutCreateWindow(APP_NAME);
}

/*
 * GL_intSetUp()
 * Configura quais funções de interação devem ser chamadas
 */

// Macro que define os nomes de funções utilizados por GL_intSetUp para NULL, se elas não tiverem sido setadas anteriormente
#ifndef KBD_FUNC
#define KBD_FUNC NULL
#endif

#ifndef KBD_UP_FUNC
#define KBD_UP_FUNC NULL
#endif

#ifndef SPKEY_FUNC
#define SPKEY_FUNC NULL
#endif

#ifndef SPKEY_UP_FUNC
#define SPKEY_UP_FUNC NULL
#endif

#ifndef MOUSE_FUNC
#define MOUSE_FUNC NULL
#endif

#ifndef MOUSEMOV_FUNC
#define MOUSEMOV_FUNC NULL
#endif

// Função de fato
void GL_intSetUp()
{
	glutKeyboardFunc(KBD_FUNC);
    glutKeyboardUpFunc(KBD_UP_FUNC);
	glutSpecialFunc(SPKEY_FUNC);
    glutSpecialUpFunc(SPKEY_UP_FUNC);
	glutMouseFunc(MOUSE_FUNC);
	glutPassiveMotionFunc(MOUSEMOV_FUNC);
}

/*
 * GL_miscSetUp()
 * Macro que invoca qualquer função que tenha sido definida como função de setup auxiliar

 */

// Se nenhuma função tiver sido setada como MISC_FUNC, GL_miscSetUp() não fará nada;
#ifdef MISC_FUNC
#define GL_miscSetUp() MISC_FUNC()
#else
#define GL_miscSetUp() NULL
#endif

/*
 * GL_draw()
 * Macro que chama glDisplayFunc() com argumento fixo - apenas para manter estilo consistente

 */

// Macro que define o nome da função de desenho para __nullDrawFunc e cria uma função de desenho que faz nada, se ela não tiver sido setada
#ifndef DRAW_FUNC
#define DRAW_FUNC __nullDrawFunc
void __nullDrawFunc() {}
#endif

#define GL_draw() glutDisplayFunc(DRAW_FUNC)

/*

 * GL_start()
 * Nome alternativo para glutMainLoop() - apenas para manter estilo consistente
 */

#define GL_start() glutMainLoop()

/**
 * Função principal
 **/
int main(int argc, char *argv[])
{
	LOG_credits();
	GL_windowSetUp(&argc, argv);
	GL_intSetUp();
	GL_miscSetUp();
	GL_draw();
	GL_start();
	return 0;
}
