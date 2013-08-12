#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

#include "figuras.h"
#include "cenario.h"
#include "macros.h"

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
 * -- Teclas Especiais: #define SPKEY_FUNC <nome_da_função>
 * -- Miscelânea: #define MISC_FUNC <nome_da_função>
 * -- Movimento do mouse: #define MOUSEMOV_FUNC <nome_da_função>
 **/

const int TAN45 = 1;
const float SEN45 = 0.851;
const float COS45 = 0.851;
const float G = 9.81;
const float v = 100.00;

float C; 

float deltaY(int x) {
	return 1 - G*(2*x + 1)/C;
}

#define MISC_FUNC misc
void misc()
{
	// determinando face sólida para polígonos
	glPolygonMode(GL_FRONT, GL_FILL);
	// determinando background preto
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Carregando matriz identidade
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Carregando modo de visualização ortográfica
	int wx = WINDOW_SIZE_X/2, wy = WINDOW_SIZE_Y/2;
	glOrtho(-2*wx, 2*wx, -2*wy, 2*wy, -2*wx, 2*wx);
	C = v*v;

	initFiguras();
	initCenario();
}

int ang = 0;
int viewangX = 0;
int viewangY = 0;
int viewangZ = 0;
float x_pos = 0;
float y_pos = 0;
int pessoa_tipo_pessoa = 1;
double pessoa_estagio_anima = 0.0, pessoa_estagio_incremento = 1.0;

#define DRAW_FUNC drawfunc
void drawfunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	transform({
        glRotatef(viewangX, 1, 0, 0);
		glRotatef(viewangY, 0, 1, 0);
		glRotatef(viewangZ, 0, 0, 1);
        /*cenario();
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
            catapulta(0);

        });
        transform({
            glTranslatef(-550,-300,-40);
            glScalef(0.2,0.2,0.2);
            muralha(0);
        });*/
        transform({
            //glTranslatef(550,-300,-40);
            //glScalef(0.2,0.2,0.2);
            muralha(0);
        });
        /*transform({
            glRotatef(90,0,1,0);
            glTranslatef(0,-330,720);
            glScalef(0.05,0.05,0.05);
            pessoa(pessoa_tipo_pessoa, pessoa_estagio_anima);
        });
        transform({
            glRotatef(-90,0,1,0);
            glTranslatef(0,-330,720);
            glScalef(0.05,0.05,0.05);
            pessoa(pessoa_tipo_pessoa, pessoa_estagio_anima);
        });*/
    });

	//==========================


//	transform({
//		glRotatef(viewangX, 1, 0, 0);
//		glRotatef(viewangY, 0, 1, 0);
//		glRotatef(viewangZ, 0, 0, 1);
//		catapulta(0);
//
//		glTranslatef(100, 100, 0);
//		bandeira(1);
//		glTranslatef(100, 100, 0);
//		trombete();
//
//		glTranslatef(x_pos, y_pos, 0);
//		glutSolidSphere(10, 20, 20); //20
//	});

	//Mostrar apenas a pessoa
//	transform({
//		glRotatef(viewangX, 1, 0, 0);
//		glRotatef(viewangY-90, 0, 1, 0);
//		glRotatef(viewangZ, 0, 0, 1);
//		glTranslatef(-400, 0, 0);
//		glScalef(0.5, 0.5, 0.5);
//		pessoa(1, pessoa_estagio_anima);
//	});

	glFlush();
}

#define KBD_FUNC keyboard
void keyboard(unsigned char key, int x, int y) {

	/* Translacao em Y */
	if(key == ' ') {
		x_pos++;
		y_pos += deltaY(x_pos);
		glutPostRedisplay();
	} else if(key == 8) {
		x_pos--;
		y_pos -= deltaY(x_pos);
		glutPostRedisplay();
	}

	/* Rotacao em Z */
	if(key == 'z') {
		viewangZ--;
		glutPostRedisplay();
	} else if(key == 'Z') {
		viewangZ++;
		glutPostRedisplay();
	}
}

#define SPKEY_FUNC spkeys
void spkeys(int key, int x, int y) {

	/* Rotacao em Y */
	if(key == GLUT_KEY_LEFT) {
		viewangY--;
		glutPostRedisplay();
	} else if(key == GLUT_KEY_RIGHT) {
		viewangY++;
		glutPostRedisplay();
	}

	/* Rotacao em X */
	if(key == GLUT_KEY_DOWN) {
		viewangX++;
		glutPostRedisplay();
	} else if(key == GLUT_KEY_UP) {
		viewangX--;
		glutPostRedisplay();
	}
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

#ifndef SPKEY_FUNC
#define SPKEY_FUNC NULL
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
	glutSpecialFunc(SPKEY_FUNC);
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

void anima_func( int value )
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
	glutTimerFunc( 10, anima_func, 1 );
	GL_start();
	return 0;
}
