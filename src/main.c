#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

#include "figuras.h"
#include "cenario.h"
#include "macros.h"
#include "iluminacao.h"

#define DEBUG 0

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

//Calculo da trajetória

const int TAN45 = 1;
const float SEN45 = 0.851;
const float COS45 = 0.851;
const float G = 9.81;
const float SCALE = 2;

float deltaY(int x, float C) {
	return 1 - G*(2*x + 1)/C;
}

// Angulos de visão
int ang = 0;
int viewangX = 0;
int viewangY = 0;
int viewangZ = 0;

// Posição dos projéteis
float x1_pos = 0, y1_pos = 0;
float x2_pos = 0, y2_pos = 0;

int pessoa_tipo_pessoa = 1;
double pessoa_estagio_anima = 0.0, pessoa_estagio_incremento = 1.0;

bool charging_p1 = false, charging_p2 = false;

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

	//TODO
	/* ATUALIZAR TODOS OS PARAMETROS DAS ANIMACOES */

	glutTimerFunc( 10, anima_func, 1 ); /* Faz a funcao anima_func continuar sendo chamada infinitamente */
	glutPostRedisplay();
}

#define MISC_FUNC misc
void misc()
{
	// determinando face sólida para polígonos
	glPolygonMode(GL_FRONT, GL_FILL);
	// determinando background preto
    glClearColor(0.0, 0.0, 0.0, 0.0);
	//glClearColor(0.1, 0.6, 1.0, 0.0);
	// Carregando matriz identidade
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Carregando modo de visualização ortográfica
	int wx = WINDOW_SIZE_X/2, wy = WINDOW_SIZE_Y/2;
	glOrtho(-SCALE*wx, SCALE*wx, -SCALE*wy, SCALE*wy, -SCALE*wx, SCALE*wx);
    //gluPerspective(90,  wx/(wy*1.0),  0,  WINDOW_SIZE_X);

    glutIgnoreKeyRepeat(true);

	initFiguras();
	initCenario();
    initLight();

    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);

    range(i, 0, 255) keystate[i] = spkeystate[i] = false;
    glutTimerFunc( 10, anima_func, 1 );
}

void shoot_p1(int speed) {
    repeat(140) {
        x1_pos++;
    	y1_pos += deltaY(x1_pos, speed);
    }
	glutPostRedisplay();
    if(y1_pos > 0 && y1_pos < 20000) glutTimerFunc(10, shoot_p1, speed);
    else x1_pos = y1_pos = 0;
}

void shoot_p2(int speed) {
    repeat(140) {
        x2_pos++;
    	y2_pos += deltaY(x2_pos, speed);
    }
	glutPostRedisplay();
    if(y2_pos > 0 && y2_pos < 20000) glutTimerFunc(10, shoot_p2, speed);
    else x2_pos = y2_pos = 0;
}

void force_p1(int f) {
    if(charging_p1) glutTimerFunc(5, force_p1, f + 2);
    else shoot_p1(f*f);
}

void force_p2(int f) {
    if(charging_p2) glutTimerFunc(5, force_p2, f + 2);
    else shoot_p2(f*f);
}

void keyboardOp() {
    if(x1_pos == 0) {
	    if(keystate['m'] && !charging_p1) {
            charging_p1 = true;
            force_p1(10);
        } else if(!keystate['m'] && charging_p1) {
            charging_p1 = false;
        }
    }

    if(x1_pos == 0) {
	    if(keystate[' '] && !charging_p2) {
            charging_p2 = true;
            force_p2(10);
        } else if(!keystate[' '] && charging_p2) {
            charging_p2 = false;
        }
    }

	/* Rotacao em Z */
	if(keystate['z']) {
		viewangZ--;
		glutPostRedisplay();
	} else if(keystate['Z']) {
		viewangZ++;
		glutPostRedisplay();
	}

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

}

#define DRAW_FUNC drawfunc
void drawfunc()
{
    keyboardOp();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glNormal3d(0, 1, 0);
    /*transform({
        glTranslatef(0, 0, -WINDOW_SIZE_X*1.5);
	    transform({
            glRotatef(viewangX, 1, 0, 0);
		    glRotatef(viewangY, 0, 1, 0);
		    glRotatef(viewangZ, 0, 0, 1);
            cenario();
            transform({
                glRotatef(90,0,1,0);
                glTranslatef(0,-330,-700);
                glScalef(0.2,0.2,0.2);
                catapulta(0);
            });
            transform({
                glRotatef(-90,0,1,0);
                glTranslatef(0,-330,-700);
                glScalef(0.2,0.2,0.2);
                glScalef(1.5, 1.5, 1.5);
                catapulta(0);

            });
            transform({
                glTranslatef(-550,-330,0);
                glScalef(0.2,0.2,0.2);
                glScalef(1.5, 1.5, 1.5);
                muralha(0);
            });
            transform({
                glTranslatef(550,-330,0);
                glScalef(0.2,0.2,0.2);
                glScalef(1.5, 1.5, 1.5);
                muralha(0);
            });
            transform({
                glRotatef(90,0,1,0);
                glTranslatef(0,-330,720);
                glScalef(0.05,0.05,0.05);
                glScalef(1.5, 1.5, 1.5);
                pessoa(pessoa_tipo_pessoa, pessoa_estagio_anima);
                glColor(255, 255, 255);
                glTranslatef(0, y1_pos, - x1_pos);
		        glutSolidSphere(200, 20, 20);
            });
            transform({
                glRotatef(-90,0,1,0);
                glTranslatef(0,-330,720);
                glScalef(0.05,0.05,0.05);
                glScalef(1.5, 1.5, 1.5);
                pessoa(pessoa_tipo_pessoa, pessoa_estagio_anima);
                glColor(255, 255, 255);
                glTranslatef(0, y2_pos, - x2_pos);
		        glutSolidSphere(200, 20, 20);
            });    
        });
    }); */

	//==========================


	transform({
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
	/*transform({
		glRotatef(viewangX, 1, 0, 0);
		glRotatef(viewangY-90, 0, 1, 0);
		glRotatef(viewangZ, 0, 0, 1);
		glTranslatef(-400, 0, 0);
		//glScalef(0.5, 0.5, 0.5);
		pessoa(1, pessoa_estagio_anima);
	});*/

	glFlush();
}

#define KBD_FUNC keyboard
void keyboard(unsigned char key, int x, int y) {
    dprintf("%c\n", key);
    keystate[key] = true;
}

#define KBD_UP_FUNC keyboardUp
void keyboardUp(unsigned char key, int x, int y) {
    dprintf("%c\n", key);    
    keystate[key] = false;
}

#define SPKEY_FUNC spkeys
void spkeys(int key, int x, int y) {
	dprintf("%d\n", key);
    spkeystate[key] = true;
}


#define SPKEY_UP_FUNC spkeysUp
void spkeysUp(int key, int x, int y) {
	dprintf("%d\n", key);
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
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
