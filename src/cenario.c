#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdlib.h>

#include "macros.h"
#include "cenario.h"

GLUquadricObj *obj;

int objId = 1;
float angX = 15;
float angY = 0;
float moonHeight = 12.0;

void initCenario(){
	int i;
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj,GLU_FILL);
    for(i=0;i<NUM_TREES/2; i++){
        x[i] = ((2 * (float)rand() / (float)RAND_MAX - 1)*20)-40;
        y[i] = (2 * (float)rand() / (float)RAND_MAX - 1)*140;
    }
    for(i=NUM_TREES/2;i<NUM_TREES; i++){
        x[i] = ((2 * (float)rand() / (float)RAND_MAX - 1)*20)+40;
        y[i] = (2 * (float)rand() / (float)RAND_MAX - 1)*140;
    }
}

void drawBranches(float x, float y){
    transform({
        glScalef(5,5,5);
        glRotatef(-90,1.0,0.0,0.0);
        glTranslatef(x,y,-65.0);
    	glColor3f(0,0.5,0);
    	glutSolidCone(2,7,20,20);
    });
}

void drawTrunk(float x, float y){
    transform({  
        glScalef(5,5,5);
    	glRotatef(-90,1.0,0.0,0.0);
        glTranslatef(x,y,-70.0); 
    	glColor3f(0.5,0.35,0.05);
    	gluCylinder(obj,0.5,0.5,5,20,20);
    });
}

void cenario(){
    transform({
        glColor3f(0.7,0.7,0.7);
        //glScalef(50,50,50);          
        /*transform({
            glTranslatef(10.0,moonHeight,7.0);
            glutSolidSphere(1.5,50,50);
        });*/
        transform({//desenha chão
            glColor3f(0,0.2,0);
            glTranslatef(0,-350,0);
            glScalef(2,0.001,2);
            glutSolidCube(800);
        });
        transform({//desenha rio
            glColor3f(0,0,1);
            glTranslatef(0,-345,0);
            glScalef(0.2,0.003,2);
            glutSolidCube(800);
        });
        int i;
        for(i=0;i<NUM_TREES; i++){
        	drawTrunk(x[i], y[i]);
        }
        for(i=0;i<NUM_TREES; i++){
        	drawBranches(x[i], y[i]);
        }
    });
}

void giraCenario(int value){
	angY +=1;
    glutPostRedisplay();
    glutTimerFunc(100,giraCenario,0);
}

void sobeLua(int value);

void desceLua(int value){
	moonHeight -=0.1;
    //glutPostRedisplay();
    if (value < 300)
    	glutTimerFunc(20,desceLua,value+1);
    else
    	glutTimerFunc(20,sobeLua,0);
}

void sobeLua(int value){
	moonHeight +=0.1;
    //glutPostRedisplay();
    if (value < 300)
    	glutTimerFunc(20,sobeLua,value+1);
    else
    	glutTimerFunc(15000,desceLua,0);
}

void transformacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           angX+=15;
           break ;
        case GLUT_KEY_DOWN :
           angX-=15;
           break ;
        case GLUT_KEY_LEFT :
           angY-=15;
           break ;
        case GLUT_KEY_RIGHT :
           angY+=15;
           break;
        default:
           break;
     }
     glutPostRedisplay() ;
}

/*int main(int argc, char *argv[])
{
	int i;
	for(i=0;i<100; i++){
		x[i] = (2 * (float)rand() / (float)RAND_MAX - 1)*40;
    	y[i] = (2 * (float)rand() / (float)RAND_MAX - 1)*40;
	}
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB |GLUT_DEPTH);
     glutInitWindowPosition(50,50);
     glutInitWindowSize(600,600);
     glutCreateWindow("Objetos 3D - OpenGL");
     glutDisplayFunc(display);
     glutTimerFunc(500,giraCenario,0);
     glutTimerFunc(15000,desceLua,0);
     glutSpecialFunc(transformacoes);
     init();
     glutMainLoop();
}*/
