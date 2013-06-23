/** Imports de bibliotecas do sistema **/
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

/** Imports de dentro do projeto **/
#include "macros.h"

/** Ligando o debug... **/
#define DEBUG 1

int main()
{
    dprintf("Olá mundo e a todos que habitam nele!\n");
    repeat(10) {
		printf("Estou pronto!\n");
    }
    return 0;
}
