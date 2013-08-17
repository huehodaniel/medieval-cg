#include <stdbool.h>
#include <stdio.h>
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

void pessoa_v2(int tipo_pessoa, double estagio_anima)
{
	glColor3f( 1.0, 0.0, 1.0 );
	switch (tipo_pessoa) {
	/* pessoaJogo */
	case 0:
		/* Desenha cabeca */
		transform({
			glBindTexture(GL_TEXTURE_2D, texturesID[CABECA_FRENTE]);

			glBegin(GL_QUADS);

			glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, -1.0);
			glTexCoord2f(1.0, 0.0); glVertex2f(1.0, -1.0);
			glTexCoord2f(1.0, 1.0); glVertex2f(1.0,  1.0);
			glTexCoord2f(0.0, 1.0); glVertex2f(-1.0,  1.0);

			glEnd();

		});

		/* Desenha torso */
		glColor3f( 1.0, 1.0, 1.0 );
		transform({
			//TODO
		});

		/* Desenha braco esquerdo */
		transform({
			//TODO
		});

		/* Desenha braco direito */
		transform({
			//TODO
		});

		/* Desenha perna esquerda */
		transform({
			//TODO
		});

		/* Desenha perna direita */
		transform({
			//TODO
		});
		break;
		/* pessoaVitoria */
	case 1:
		break;
		/* pessoaDerrota */
	case 2:
		break;
		/* pessoaMorte */
	case 3:
		break;
	default:
		printf("Erro - Entrou no default da funcao 'pessoa()' - Arquivo 'figuras.c'");
		break;
	}
}

/* Funcao generica para todas as pessoas:
 * parametro 'tipo_pessoa':
 * 	- 0 pessoaJogo
 * 	- 1 pessoaVitoria
 * 	- 2 pessoaDerrota
 * 	- 3 pessoaMorte
 * 	*/
void pessoa(int tipo_pessoa, double estagio_anima) {

	switch (tipo_pessoa) {
	/* pessoaJogo */
	case 0:
		/* Desenha cabeca */
		transform({
			glTranslatef( 0.0, 300.0, 0.0 );
			transform({
				/* Desenha rosto */
				glColor3f( 1.0, 1.0, 1.0 );
				transform({
					glScaled( 0.7, 1.0, 0.7 );
					glRotatef( 90.0, 0.0, 1.0, 0.0 );
					glutSolidSphere(100.0, 20, 50);
				});

				/* Olho esquerdo */
				glColor3f( 0.8, 1.0, 0.8 );
				transform({
					glTranslatef( -30.0, 40.0, -60.0 );
					transform({
						glScaled( 0.2, 0.2, 0.05 );
						glutSolidSphere(150.0, 20, 50);
					});
					glColor3f( 0.0, 0.0, 0.0 );
					glScaled( 0.07, 0.07, 0.07 );
					glutSolidSphere(100.0, 20, 50);
				});

				/* Olho direito */
				glColor3f( 0.8, 1.0, 0.8 );
				transform({
					glTranslatef( 30.0, 40.0, -60.0 );
					transform({
						glScaled( 0.2, 0.2, 0.05 );
						glutSolidSphere(150.0, 20, 50);
					});
					glColor3f( 0.0, 0.0, 0.0 );
					glScaled( 0.04, 0.04, 0.04 );
					glutSolidSphere(100.0, 20, 50);
				});

				/* Boca */
				glColor3f( 0.0, 0.0, 1.0 );
				transform({
					glScaled( 0.35, 0.045, 0.25 );
					glTranslatef( 0.0, -500.0, -250.0);
					glutSolidTorus(30.0, 70.0, 20, 20);
				});
			});

		});

		/* Desenha torso */
		glColor3f( 1.0, 1.0, 1.0 );
		transform({
			glScaled( 1.2, 2.2, 1.2  );
			glRotatef( 90.0, 0.0, 1.0, 0.0 );
			glutSolidSphere(100.0, 20, 50);
		});

		/* Desenha braco esquerdo */
		transform({
			glTranslatef( -100.0, 120.0, 0.0);
			glColor3f( 1.0, 1.0, 0.0 );
			transform({/* Desenha braco esquerdo */
				glTranslatef( -10.0, 0.0, -50.0);
				glRotatef( 20.0, 0.0, 0.0, 1.0 );
				glRotatef( 90.0, 0.0, 1.0, 0.0 );
				glScaled( 0.7, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 1.0, 0.0 );
			transform({
				glTranslatef( -10.0, 0.0, -130.0);
				glRotatef( -90.0, 0.0, 1.0, 0.0 );
				glScaled( 0.5, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 0.0, 1.0 );
			transform({
				glTranslatef( -10.0, 0.0, -200.0);
				glScaled( 1.0, 1.0, 1.0 );
				glutSolidSphere(20.0, 20, 50);
			});
		});

		/* Desenha braco direito */
		transform({
			glTranslatef( 60.0, 70.0, 0.0);
			glColor3f( 1.0, 1.0, 0.0 );
			transform({/* Desenha braco esquerdo */
				glTranslatef( 70.0, 0.0, 0.0);
				glRotatef( -70.0, 0.0, 0.0, 1.0 );
				glScaled( 0.7, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 1.0, 0.0 );
			transform({
				glTranslatef( 100.0, -100.0, 0.0);
				glRotatef( -80.0, 0.0, 0.0, 1.0 );
				glScaled( 0.5, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 0.0, 1.0 );
			transform({
				glTranslatef( 110.0, -165.0, 0.0);
				glScaled( 1.0, 1.0, 1.0 );
				glutSolidSphere(20.0, 20, 50);
			});
		});

		/* Desenha perna esquerda */
		transform({
			glTranslatef( -15.0, -250.0, 0.0);
			glColor3f( 1.0, 1.0, 0.0 );
			transform({
				glTranslatef( -70.0, 0.0, 0.0);
				glRotatef( 70.0, 0.0, 0.0, 1.0 );
				glScaled( 0.7, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 1.0, 0.0 );
			transform({
				glTranslatef( -100.0, -100.0, 0.0);
				glRotatef( 80.0, 0.0, 0.0, 1.0 );
				glScaled( 0.5, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 0.0, 1.0 );
			transform({
				glTranslatef( -110.0, -165.0, -20.0);
				glScaled( 1.0, 1.0, 2.0 );
				glutSolidSphere(20.0, 20, 50);
			});
		});

		/* Desenha perna direita */
		transform({
			glTranslatef( 15.0, -250.0, 0.0);
			glColor3f( 1.0, 1.0, 0.0 );
			transform({
				glTranslatef( 70.0, 0.0, 0.0);
				glRotatef( -70.0, 0.0, 0.0, 1.0 );
				glScaled( 0.7, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 1.0, 0.0 );
			transform({
				glTranslatef( 100.0, -100.0, 0.0);
				glRotatef( -80.0, 0.0, 0.0, 1.0 );
				glScaled( 0.5, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 0.0, 1.0 );
			transform({
				glTranslatef( 110.0, -165.0, -20.0);
				glScaled( 1.0, 1.0, 2.0 );
				glutSolidSphere(20.0, 20, 50);
			});
		});
		break;
		/* pessoaVitoria */
	case 1:
		/* Desenha cabeca */
		transform({
			glTranslatef( 0.0, 300.0, 0.0 );
			transform({
				/* Desenha rosto */
				glColor3f( 1.0, 1.0, 1.0 );
				transform({
					glScaled( 0.7, 1.0, 0.7 );
					glRotatef( 90.0, 0.0, 1.0, 0.0 );
					glutSolidSphere(100.0, 20, 50);
				});

				/* Olho esquerdo */
				glColor3f( 0.8, 1.0, 0.8 );
				transform({
					glTranslatef( -30.0, 40.0, -60.0 );
					transform({
						glScaled( 0.2, 0.2, 0.05 );
						glutSolidSphere(150.0, 20, 50);
					});
					glColor3f( 0.0, 0.0, 0.0 );
					glScaled( 0.07, 0.07, 0.07 );
					glutSolidSphere(100.0, 20, 50);
				});

				/* Olho direito */
				glColor3f( 0.8, 1.0, 0.8 );
				transform({
					glTranslatef( 30.0, 40.0, -60.0 );
					transform({
						glScaled( 0.2, 0.2, 0.05 );
						glutSolidSphere(150.0, 20, 50);
					});
					glColor3f( 0.0, 0.0, 0.0 );
					glScaled( 0.04, 0.04, 0.04 );
					glutSolidSphere(100.0, 20, 50);
				});

				/* Boca */
				glColor3f( 0.0, 0.0, 1.0 );
				transform({
					glScaled( 0.35, 0.045, 0.25 );
					glTranslatef( 0.0, -500.0, -250.0);
					glutSolidTorus(30.0, 70.0, 20, 20);
				});
			});

		});

		/* Desenha torso */
		glColor3f( 1.0, 1.0, 1.0 );
		transform({
			glScaled( 1.2, 2.2, 1.2  );
			glRotatef( 90.0, 0.0, 1.0, 0.0 );
			glutSolidSphere(100.0, 20, 50);
		});

		/* Desenha braco esquerdo */
		transform({
			glTranslatef( -100.0, 120.0, 0.0);
			glColor3f( 1.0, 1.0, 0.0 );
			transform({
				glTranslatef( -10.0, 0.0, -50.0);
				glRotatef( 20.0, 0.0, 0.0, 1.0 );
				glRotatef( 90.0, 0.0, 1.0, 0.0 );
				glScaled( 0.7, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			transform({
				glColor3f( 0.0, 1.0, 0.0 );
				transform({
					glTranslatef( -10.0, 0.0, -130.0);
					glRotatef( -90.0, 0.0, 1.0, 0.0 );

					/* Ergue ante-braço */
					/* ---------------------- */
					glTranslatef( 40.0, 0.0, 0.0);
					/* Animacao de levantar o braço */
					glRotatef( (-70.0)*(estagio_anima/100.0), 0.0, 0.0, 1.0 );
					glTranslatef( -40.0, 0.0, 0.0);
					/* ---------------------- */

					glScaled( 0.5, 0.2, 0.2 );
					glutSolidSphere(100.0, 20, 50);
				});
				glColor3f( 0.0, 0.0, 1.0 );
				transform({

					glRotatef( (40.0)*(estagio_anima/100.0), 1.0, 0.0, 0.0 );
					glTranslatef( 0.0, -90.0, -50.0);

					glTranslatef( -10.0, 90.0, -130.0);
					glScaled( 1.0, 1.0, 1.0 );
					glutSolidSphere(20.0, 20, 50);
				});
			});
		});
		/* Desenha braco direito */
		transform({
			glTranslatef( 60.0, 70.0, 0.0);
			glColor3f( 1.0, 1.0, 0.0 );
			transform({
				glTranslatef( 70.0, 0.0, 0.0);
				glRotatef( -70.0, 0.0, 0.0, 1.0 );
				glScaled( 0.7, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 1.0, 0.0 );
			transform({
				glTranslatef( 100.0, -100.0, 0.0);
				glRotatef( -80.0, 0.0, 0.0, 1.0 );
				glScaled( 0.5, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 0.0, 1.0 );
			transform({
				glTranslatef( 110.0, -165.0, 0.0);
				glScaled( 1.0, 1.0, 1.0 );
				glutSolidSphere(20.0, 20, 50);
			});
		});

		/* Desenha perna esquerda */
		transform({
			glTranslatef( -15.0, -250.0, 0.0);
			glColor3f( 1.0, 1.0, 0.0 );
			transform({
				glTranslatef( -70.0, 0.0, 0.0);
				glRotatef( 70.0, 0.0, 0.0, 1.0 );
				glScaled( 0.7, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 1.0, 0.0 );
			transform({
				glTranslatef( -100.0, -100.0, 0.0);
				glRotatef( 80.0, 0.0, 0.0, 1.0 );
				glScaled( 0.5, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 0.0, 1.0 );
			transform({
				glTranslatef( -110.0, -165.0, -20.0);
				glScaled( 1.0, 1.0, 2.0 );
				glutSolidSphere(20.0, 20, 50);
			});
		});

		/* Desenha perna direita */
		transform({
			glTranslatef( 15.0, -250.0, 0.0);
			glColor3f( 1.0, 1.0, 0.0 );
			transform({
				glTranslatef( 70.0, 0.0, 0.0);
				glRotatef( -70.0, 0.0, 0.0, 1.0 );
				glScaled( 0.7, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 1.0, 0.0 );
			transform({
				glTranslatef( 100.0, -100.0, 0.0);
				glRotatef( -80.0, 0.0, 0.0, 1.0 );
				glScaled( 0.5, 0.2, 0.2 );
				glutSolidSphere(100.0, 20, 50);
			});
			glColor3f( 0.0, 0.0, 1.0 );
			transform({
				glTranslatef( 110.0, -165.0, -20.0);
				glScaled( 1.0, 1.0, 2.0 );
				glutSolidSphere(20.0, 20, 50);
			});
		});
		transform({
			glTranslatef( 0.0, 200.0, -40.0);
			glRotatef( (40.0)*(estagio_anima/100.0), 1.0, 0.0, 0.0 );
			glTranslatef( 0.0, 0.0, -120.0);
			//glRotatef( (-60.0)*(estagio_anima/100.0), 1.0, 0.0, 0.0 );
			glTranslatef( 0.0, -240.0, 130.0);

			glTranslatef( -110.0, 240.0, -130.0);
			glRotatef( -40.0, 0.0, 1.0, 0.0 );
			glRotatef( 10.0, 0.0, 0.0, 1.0 );
			trombete();
		});
		break;
		/* pessoaDerrota */
	case 2:
		break;
		/* pessoaMorte */
	case 3:
		break;
	default:
		printf("Erro - Entrou no default da funcao 'pessoa()' - Arquivo 'figuras.c'");
		break;
	}
}

void pessoaVence() {

}

void pessoaMorta() {

}
void muralhaArua(muralhaEstado estado){
	int i,j;
	int matrizMuralha[9][9] = {
		{1,1,1,1,1,1,0,0,0},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
	};
	transform({
		glColor(168, 86, 3);
		glScalef(6, 5, 8);
		glTranslatef(0,-52,-40);
		for(i=1;i<9;i++){
			glTranslatef(0,13,0);
			for(j=0;j<9;j++){
			glTranslatef(0, 0, 13);
			glutSolidCube(11*matrizMuralha[i][j]);
			}
			if (i%2==0)glTranslatef(0,0,-125.5);
			else glTranslatef(0,0,-109.5);
		}
	});
	transform({
		//glTranslatef(0, 0, 0);
		glScalef(10, 10, 78);
		glTranslatef(0, 36, 2.7);
		glutSolidCube(11*matrizMuralha[0][5]);

	});

	transform({
		glTranslatef(0, 480, -130);
		glScalef(10, 10, 10);
		glutSolidCube(11*matrizMuralha[0][0]);

		glTranslatef(0, 0, 17);
		glutSolidCube(11*matrizMuralha[0][1]);

		glTranslatef(0, 0, 17);
		glutSolidCube(11*matrizMuralha[0][2]);

		glTranslatef(0, 0, 17);
		glutSolidCube(11*matrizMuralha[0][3]);
		
		glTranslatef(0, 0, 17);
		glutSolidCube(11*matrizMuralha[0][4]);

	});
}
void muralha(muralhaEstado estado) {

	int tiro1 = 11, tiro2 = 11, tiro3 = 11, tiro4 = 11, tiro5 = 11, tiro6 = 11, tiro7 = 11, tiro8 = 11, tiroAux1 = 51, tiroAux2 = 4;
	switch(estado){
		case 1: tiro1 = 0, tiroAux1 = 40, tiroAux2 = 3; break;
		case 2: tiro1 = 0, tiro2 = 0, tiroAux1 = 40, tiroAux2 = 3; break;
		case 3: tiro1 = 0, tiro2 = 0, tiro3 = 0, tiroAux1 = 40, tiroAux2 = 3; break;
		case 4: tiro1 = 0, tiro2 = 0, tiro3 = 0, tiro4 = 0, tiroAux1 = 40, tiroAux2 = 3; break;
		case 5: tiro1 = 0, tiro2 = 0, tiro3 = 0, tiro4 = 0, tiro5 = 0, tiroAux1 = 40, tiroAux2 = 3; break;
		case 6: return; break;
		default: break;
	}
		transform({
			//glTranslatef(-180,-120,0);
			//glRotatef( 90.0, 0.0, 1.0, 0.0 );
			transform({
				transform({
					glColor(168, 86, 3);
					glScalef(5, 5, 5);

					//PARTE 1
					glTranslatef(0,-30,-7);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					//PARTE 2

					glTranslatef(0, 13, -97);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);
			
					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);
				
				
					//PARTE 3
					glTranslatef(0,13,-97);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro6);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);


					//PARTE 4

					glTranslatef(0, 13, -97);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro5);
			
					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);

					/////

					//PARTE 5
					glTranslatef(0,13,-97);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);


					//PARTE 6

					glTranslatef(0, 13, -97);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);
			
					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);

				
					//PARTE 7
					glTranslatef(0,13,-97);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro4);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);

					glTranslatef(0, 0, 13);
					glutSolidCube(tiro3);

				});

		

				transform({
					glTranslatef(0, 0, 0);
					glScalef(10, 10, tiroAux1);
					glTranslatef(0, 33, tiroAux2);
					glutSolidCube(tiro2);

				});

				transform({

	

						glTranslatef(0, 450, -20);
						glScalef(10, 10, 10);
						glutSolidCube(tiro2);

						glTranslatef(0, 0, 15);
						glutSolidCube(tiro2);

						glTranslatef(0, 0, 15);
						glutSolidCube(tiro1);

						glTranslatef(0, 0, 15);
						glutSolidCube(tiro1);


				});
	
			});

		});

}

void castelo() {

}

void bandeira(int jogador) {
	if(jogador == 1) glColor(255,0,0);
	else glColor(0,0,255);
	transform({
		// TriÃ¢ngulo bizarro
		glRotatef(90, 0, 0, 1);
		draw(GL_POLYGON, {
				glVertex3f(-25, 0, 0);
				glVertex3f(0, 70, 0);
				glVertex3f(25, 0, 0);

				glVertex3f(-25, 0, 0);
				glVertex3f(-25, 0, 5);

				glVertex3f(0, 70, 5);
				glVertex3f(0, 70, 0);
				glVertex3f(0, 70, 5);

				glVertex3f(25, 0, 5);
				glVertex3f(25, 0, 0);
				glVertex3f(25, 0, 5);

				glVertex3f(-25, 0, 5);
		});
		glTranslatef(-25, -10, 0);
		glColor(168, 86, 3);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, 0, -105);
		gluCylinder(obj,5,5,160,20,20);
	});
}

void trombete() {
	glColor(242, 227, 7);
	transform({
		glScalef(1, 0.5, 1);
		glutSolidTorus(10, 50, 20, 20);
	});
	transform({
		glTranslatef(-80, 25, 0);
		glRotatef(90, 0, 1, 0);
		gluCylinder(obj, 7.5, 7.5, 160, 20, 20);
		glTranslatef(0, 0, -40);
		gluCylinder(obj, 15, 7.5, 40, 20, 20);
		glTranslatef(0, 0, 200);
		gluCylinder(obj, 7.5, 5, 40, 20, 20);
	});
		transform({
			glTranslatef(-30, 50, 0);
			repeat(3) {
				transform({
					glRotatef(90, 1, 0, 0);
					gluCylinder(obj, 5, 5, 20, 20, 20);
				});
				transform({
					glRotatef(90, 1, 0, 0);
					gluDisk(obj, 0, 10, 20, 20);
					gluCylinder(obj, 10, 10, 3, 20, 20);
					glTranslatef(0, 3, 0);
					gluDisk(obj, 0, 10, 20, 20);
				});
				glTranslatef(30, 0, 0);
			}
		});
}
