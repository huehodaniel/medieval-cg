/**
 * Coleção de macros utilitárias para ajudar em algumas tarefas bestas.
 * Por enquanto, é principalmente também pra testar se funciona direitinho
 * o sistema de build...
 *
 * Atenção: algumas dessas macros só funcionam se o compilador estiver configurado
 * para compilar o padrão C99, que é o C lecau.
 * Outras funções ainda só rolam no modo G99, que é o C99 + extensões do GCC.
 * Eu já deixei o makefile pra compilar desse jeito, então tanto faz, 
 * mas por precaução eu estou deixando marcado qual precisa de qual. E quem quiser compilar no Visual Studio,
 * HAHAHAHAHAHAHAHAHAHAHAHAHA (infinito).
 *
 * TODO: remover essa introdução porca
 **/

#ifndef MACROS_H
#define MACROS_H

#define DEBUG 1

/**
 * Constante PI
 * 	Porque a gente vai precisar, com certeza.
 **/
#define PI 3.141592654

/**
 * radians(x)
 * 	Converte valor em degraus para radianos
 **/
#define radians(x) (x*PI/180.0)

/**
 * macrofy(body)
 * 	Macro para criar macros, enrola elas dentro de um do-while para evitar erros toscos
 **/
#define macrofy(body) do { body } while(0)

/**
 * range(name, start, end) - C99
 * 	Versão encurtada de um "for" para iterar pelos valores de um intervalo de números
 * 	inteiros utilizando a variavel de nome "name", começando em "start" e indo até "end" - 1.
 *	Exemplo:
 *		int num[] = {1, 2, 3, 4, 5};
 *		range(idx, 0, 5) {
 *			printf("%d\n", num[idx]);
 *		}
 **/
#define range(name, start, end) for(int name = start; name < end; name++)

/**
 * repeat(times) - C99
 * 	Versão mais curta ainda a partir da macro range(), repete um bloco de código "times" vezes
 *	Exemplo:
 *		repeat(3) {
 * 			printf("VIRA VIRA VIRA, ");
 *		}
 *		printf("VIROU!");
 **/
#define repeat(times) range(__tmp__, 0, times)

/**
 * draw(mode, body)
 * 	Macro para utilizar quando for desenhar uma forma utilizando glBegin e glEnd. Serve mais pra você não
 * 	esquecer do glEnd do que qualquer coisa. "mode" é qualquer argumento válido para glBegin, "body" é literalmente um
 * 	pedaço de código a ser executado. Deve ser tratada como uma função (i.e não esquece do ponto e vírgula no final)
 *	Exemplo: 
 *		glColor3f(1.0f, 0.0f, 0.0f);
 *			draw(GL_LINE_LOOP, {
 *				glVertex2f(0.25f, 0.25f);
 *				glVertex2f(-0.25f, 0.25f);
 *				glVertex2f(0.0f, 0.5f);
 *			});
 **/

#define draw(mode, body) macrofy(glBegin(mode); { body } glEnd();)

/**
 * transform(body)
 * 	Macro para utilizar em operações de transformação no OpenGL, quando você precisa usar
 *	glPushMatrix() e glPopMatrix(). "body" aqui é literalmente um pedaço de código que você coloca dentro
 * 	da macro.
 *	Exemplo: 
 *		glColor3f(1.0f, 0.0f, 0.0f);
 *		transform({
 *			glTranslatef(0.5f, 0.5f, 0.0f);
 *			draw(GL_LINE_LOOP, {
 *				glVertex2f(0.25f, 0.25f);
 *				glVertex2f(-0.25f, 0.25f);
 *				glVertex2f(0.0f, 0.5f);
 *			});
 *		});
 **/
#define transform(body) macrofy(glPushMatrix(); {body} glPopMatrix();)

/**
 * glColor(x, y, z)
 * 	Macro para definir cores em formato RGB chamando glColor3f, dividindo todos os parâmetros por 255.0. Sério,
 * 	OpenGL, CADE A PORRA DO PADRÃO RGB
 * 	Exemplo:
 * 		glColor(255, 255, 0);
 * 		glutSolidCube(100);
 **/
#define glColor(x, y, z) glColor3f(x/255.0, y/255.0, z/255.0)

/**
 * dprintf(fmt, ...) - G99
 * 	Versão turbo-plus do printf() que imprime o número da linha, o nome do arquivo e a função onde ela foi chamada.
 *	Só funciona se uma váriavel global ou uma constante de macro DEBUG for setada no arquivo (logo, dá pra ligar e desligar).
 */
#define dprintf(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, ##__VA_ARGS__); } while (0)
                                
/**
 * console(str) - C99
 * 	Versão minimalista do printf() que imprime uma string simples.
 **/
#define console(str) printf("%s\n", str)

#endif /* MACROS_H */
