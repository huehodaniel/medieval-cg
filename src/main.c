/*!
 * \file
 *
 * Este eh o arquivo principal do programa do trabalho final de Computacao Grafica. Neste arquivo esta
 * a funcao \ref main que eh chamada quando o programa eh executado.
 *
 * Universidade Federal De Sao Paulo.
 *
 * Diciplina: Computacao Grafica.
 *
 * Professora: Ana Luisa Dine Martins Lemos.
 *
 * Trabalho: Adaptacao 3D do jogo Batalha Medieval do console Odyssey 2 (http://www.youtube.com/watch?v=FZxl9OC24Ic).
 *
 * Alunos:
 *  - Arua de Mello Sousa (aruams@gmail.com)
 *  - Daniel Gracia dos Santos (duodigdaniel@gmail.com)
 *  - Kim Archanjo Tostes (kimtostes@gmail.com)
 *  - Rafael Barbosa Januzi (rjanuzi@gmail.com)
 *
 * \Date 29/08/2013
 */

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

// String cabecalho
#define HEADER "-- Computação Grafica, turma de 2013, vespertino --"

/* Constantes de configuracao para o programa em particular */
const char* APP_NAME = "Batalha Medieval";
const int WINDOW_POSITION_X = 200, WINDOW_POSITION_Y = 200;
const int WINDOW_SIZE_X = 800, WINDOW_SIZE_Y = 600;

/*
 * Funcoes e variaveis para interacao e desenho
 * - todas as funcoes que sejam ponto de entrada para o GLUT devem ser precedidas de um define criando um alias para a funcao
 * -- Mouse: #define MOUSE_FUNC <nome_da_funcao>
 * -- Desenho: #define DRAW_FUNC <nome_da_funcao>
 * -- Teclado: #define KBD_FUNC <nome_da_funcao>
 * -- Teclado (soltar tecla): #define KBD_UP_FUNC <nome_da_funcao>
 * -- Teclas Especiais: #define SPKEY_FUNC <nome_da_funcao>
 * -- Miscelanea: #define MISC_FUNC <nome_da_funcao>
 * -- Movimento do mouse: #define MOUSEMOV_FUNC <nome_da_funcao>
 */
 
// Angulos de visao
int ang = 0;
int viewangX = 0;
int viewangY = 0;
int viewangZ = 0;
int direcaoCanhao1 = 0;
int direcaoCanhao2 = 0;
int moverCanhao1 = 0;
int moverCanhao2 = 0;

// Posiao do pointer
int x_pointer = 0;
int z_pointer = 0;
int pass = 10;

// Estado do jogo
typedef enum _modoJogo { INICIO, JOGO, FIM } modoJogo;
modoJogo modo = INICIO;

double pessoa_estagio_anima = 0.0, pessoa_estagio_incremento = 3.0;

//Vetor de estados do teclado (para permitir multiplas teclas pressionadas)
bool keystate[256], spkeystate[256];

/*!
 * \brief Funcao de animacao geral.
 *
 * Essa funcao eh responsavel pela atualizacao das variaveis utilizadas nas animacoes que envolvem os
 * personagens do jogo.
 *
 * \param value No nosso caso esse parametro existe apenas para manter a assinatura da funcao de animacao
 * requerida pelo OpenGL.
 *
 * \return void;
 */
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
/*!
 * \brief Funcao de inicializacoes gerais do projeto.
 *
 * Nessa funcao estao inclusas a inicializacoes gerais para o programa, por exemplo o carregamento da matriz identidade
 * a visao perspectiva, etc.
 *
 * \return void;
 */
void misc()
{
	int wx = WINDOW_SIZE_X/2, wy = WINDOW_SIZE_Y/2;

	//Determinando face solida para poligonos
	glPolygonMode(GL_FRONT, GL_FILL);
	glClearColor(0.1, 0.6, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	//Carregando matriz identidade
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(0,0,-1);

	//Carregando modo de visualizacao ortograica
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

    gluLookAt(0.0, 0.0, 1.0,   //posicao da camera
              0.0, 0.0, 0.0,   //para onde a camera aponta
              0.0, 1.0, 0.0);  //vetor view-up

    range(i, 0, 255) keystate[i] = spkeystate[i] = false;
    glutTimerFunc(10, anima_func, 1);
    glMatrixMode(GL_PROJECTION);
}

/*!
 * \brief Funcao de start do teclado.
 *
 * \return void;
 */
void keyboardOpStart() {
	if(keystate[13]) {
		modo = JOGO;
		viewangY = 0;
		viewangX = 35;
		glutPostRedisplay();
	}
}

const int force_inc = 3;

/*!
 * \brief Funcao responsavel pelas acoes do teclado
 *
 * Essa funcao eh chamada quando uma tecla eh pressionada.
 * As teclas reconhecidas sao:
 *  - 'm': Tiro do jogador 1
 *  - 'z': Tirp do jogador 2
 *  - 'n' ou 'j': Girar o canhao do jogador 1
 *  - 's' ou 'x': Girar o canhao do jogador 2
 *
 * \param p1 Variavel utilizada na logica do programa para o jogador 1 \ref plInfo .
 * \param p1 Variavel utilizada na logica do programa para o jogador 2 \ref plInfo .
 *
 * \return void;
 */
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

    if(DEBUG){
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

/*!
 * \brief Funcao utilizada quando um operacao iniciada pelo teclado termina.
 *
 * \return void;
 */
void keyboardOpEnd() {
	if(keystate[13]) exit(0);
}

#define DRAW_FUNC drawfunc
/*!
 * \brief Funcao que desenha todos os objetos na tela.
 *
 * Essa eh a funcao chamada pelo OpenGL sempre que os objetos devem ser re/desenhados na tela.
 *
 * \return void;
 */
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
				glTranslatef(-p1.x, p1.y, p1.z);
				glutSolidSphere(15, 20, 20);
			});
            transform({
                glTranslatef(-800,-260,-60);
                glScalef(0.4,0.4,0.4);
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

    glutSwapBuffers();
}

#define KBD_FUNC keyboard
/*!
 * \brief Funcao chamada pelo OpenGL quando uma tecla eh utilizada.
 *
 *	Quando uma tecla normal, ou seja, alfa-numerica eh utilizada, o OpenGL dispara essa funcao,
 *	que modifica a variavel global \ref keystate que por sua vez sera utilizada pela funcao
 *	\ref keyboardOp para realizar alguma alteracao no estado atual do jogo.
 *
 * \param key Tecla utilizada pelo usuario. (Padrao OpenGL)
 * \param x Posicao do mouse, em relacao ao eixo x, na tela no momento em que a tecla foi utilizada. (Padrao OpenGL)
 * \param y Posicao do mouse, em relacao ao eixo y, na tela no momento em que a tecla foi utilizada. (Padrao OpenGL)
 *
 * \return void;
 */
void keyboard(unsigned char key, int x, int y) {
    dprintf("%d\n", key);
    keystate[key] = true;
}

#define KBD_UP_FUNC keyboardUp
/*!
 * \brief Funcao chamada pelo OpenGL quando uma tecla eh utilizada (liberada).
 *
 *	Quando uma tecla normal, ou seja, alfa-numerica eh utilizada (liberada), o OpenGL dispara essa funcao,
 *	que modifica a variavel global \ref keystate que por sua vez sera utilizada pela funcao
 *	\ref keyboardOp para realizar alguma alteracao no estado atual do jogo.
 *
 * \param key Tecla utilizada pelo usuario. (Padrao OpenGL)
 * \param x Posicao do mouse, em relacao ao eixo x, na tela no momento em que a tecla foi utilizada. (Padrao OpenGL)
 * \param y Posicao do mouse, em relacao ao eixo y, na tela no momento em que a tecla foi utilizada. (Padrao OpenGL)
 *
 * \return void;
 */
void keyboardUp(unsigned char key, int x, int y) {
    //dprintf("%c\n", key);    
    keystate[key] = false;
}

#define SPKEY_FUNC spkeys
/*!
 * \brief Funcao chamada pelo OpenGL quando uma tecla especial eh utilizada.
 *
 *	Quando uma tecla especial, ou seja, setas, FN, etc. Eh utilizada, o OpenGL dispara essa funcao,
 *	que modifica a variavel global \ref keystate que por sua vez sera utilizada pela funcao
 *	\ref keyboardOp para realizar alguma alteracao no estado atual do jogo.
 *
 * \param key Tecla utilizada pelo usuario. (Padrao OpenGL)
 * \param x Posicao do mouse, em relacao ao eixo x, na tela no momento em que a tecla foi utilizada. (Padrao OpenGL)
 * \param y Posicao do mouse, em relacao ao eixo y, na tela no momento em que a tecla foi utilizada. (Padrao OpenGL)
 *
 * \return void;
 */
void spkeys(int key, int x, int y) {
	dprintf("%d\n", key);
    spkeystate[key] = true;
}


#define SPKEY_UP_FUNC spkeysUp
/*!
 * \brief Funcao chamada pelo OpenGL quando uma tecla especial eh utilizada (liberada).
 *
 *	Quando uma tecla especial, ou seja, setas, FN, etc. Eh utilizada (liberada), o OpenGL dispara essa funcao,
 *	que modifica a variavel global \ref keystate que por sua vez sera utilizada pela funcao
 *	\ref keyboardOp para realizar alguma alteracao no estado atual do jogo.
 *
 * \param key Tecla utilizada pelo usuario. (Padrao OpenGL)
 * \param x Posicao do mouse, em relacao ao eixo x, na tela no momento em que a tecla foi utilizada. (Padrao OpenGL)
 * \param y Posicao do mouse, em relacao ao eixo y, na tela no momento em que a tecla foi utilizada. (Padrao OpenGL)
 *
 * \return void;
 */
void spkeysUp(int key, int x, int y) {
	//dprintf("%d\n", key);
    spkeystate[key] = false;
}

/**
 * Funcoes de configuracao inicial
 **/

/*!
 * \brief Imprime no console dados sobre o programa.
 *
 * \return void;
 */
void LOG_credits()
{
    console(HEADER);
    console(APP_NAME);
}

/*!
 * \brief Funcao para confuguracao da janela.
 *
 *	Funcao que inicia as caracteristicas da janela do OpenGL apresentada pelo programas, por exemplo o modo de exibicao,
 *	posicao, tamanho, etc.
 *
 * \param argc Numero de argumentos recebidos pela funcao \ref main .
 * \param argv Argumentos recebidos pela funcao \ref main .
 *
 * \return void;
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
 * Configura quais funcoes de interacao devem ser chamadas
 */

// Macro que define os nomes de funcoes utilizados por GL_intSetUp para NULL, se elas naoo tiverem sido setadas anteriormente
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

/*!
 * \brief Funcao que configura as funcoes chamadas pelo OpenGL.
 *
 *	O OpenGL chama determinadas funcoes de acordo com a necessidade automaticamente,
 *	para isso eh necessario setar quais funcoes serao chamdas em cada momento, isso eh feito
 *	nessa funcao, por exemplo funcao de resposta ao teclado, a cliques do mouse, etc.
 *
 * \return void;
 */
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

/*!
 * \brief Funcao principal.
 *
 *	Primeira funcao chamada quando o programa eh executado, essa funcao eh resposavel por disparar todas as outras funcoes definidas.
 *
 * \return void;
 */
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
