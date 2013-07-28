/**
 * Modelo para exercícios de CG
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

/**
 * Constantes, macros e tipos gerais para todos os programas
 **/
// Declarando tipo bit
typedef unsigned int bits;
// Imprime string e quebra de linha sem rodeios
#define console(x) printf("%s\n", x)
// String cabeçalho
#define HEADER "-- Computação Grafica, turma de 2013, vespertino --"
// Constante PI
#define PI 3.141592654
// Realiza operações de desenho e transformações geométricas de forma isolada
#define transform(body) glPushMatrix(); {body} glPopMatrix()
// Cria um bloco para desenhos
#define drawShape(type, body) glBegin(type); {body} glEnd()

/**
 * Constantes de configuração para o programa em particular
 **/
const char* AUTHOR_NAME = "Daniel Gracia dos Santos";
const char* APP_NAME = "Nome";
const int WINDOW_POSITION_X = 200, WINDOW_POSITION_Y = 200;
const int WINDOW_SIZE_X = 600, WINDOW_SIZE_Y = 600;

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

#define MISC_FUNC misc
void misc()
{
    // determinando face sólida para polígonos
    glPolygonMode(GL_FRONT, GL_FILL);
    // determinando background preto
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Carregando matriz identidade
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Carregando modo de visualização ortográfica
    int wx = WINDOW_SIZE_X/2, wy = WINDOW_SIZE_Y/2;
    glOrtho(-wx, wx, -wy, wy, -wx, wx);
}

int ang = 0;

#define DRAW_FUNC draw
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    transform({
        glRotatef(ang, 0, 1, 0);
        glutWireTeapot(200);
    });
    glFlush();
}

#define SPKEY_FUNC keyboard
void keyboard(int key, int x, int y) {
    ang +=
        (key == GLUT_KEY_LEFT) ? -1 :
        (key == GLUT_KEY_RIGHT) ? 1 : 0;
    glutPostRedisplay();
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
    console(AUTHOR_NAME);
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

// Função de fato, aceita parâmetro variável
void GL_intAdvSetUp(bits enabled)
{
    glutKeyboardFunc(KBD_FUNC);
    glutSpecialFunc(SPKEY_FUNC);
    glutMouseFunc(MOUSE_FUNC);
    glutPassiveMotionFunc(MOUSEMOV_FUNC);
}

// Macro para chamar a função com o parâmetro constante global ENABLED_INPUT
#define GL_intSetUp() GL_intAdvSetUp(ENABLED_INPUT)

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

