#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdlib.h>

//#define RAND_MAX 30
GLUquadricObj *obj;

int objId = 1;
float angX = 15;
float angY = 0;
float x[100], y[100];
float moonHeight = 12.0;
void init(){
     obj = gluNewQuadric();
     gluQuadricDrawStyle(obj,GLU_FILL);
}
void drawBranches(float x, float y){
    glScalef(0.5,0.5,0.5);
	glRotatef(-90,1.0,0.0,0.0);
	glTranslatef(x,y,-30.0);
	glColor3f(0,0.5,0);
	glutSolidCone(2,7,20,20);
	glPopMatrix();
    glPushMatrix();
}

void drawTrunk(float x, float y){
    glScalef(0.5,0.5,0.5);
	glRotatef(-90,1.0,0.0,0.0);
	glTranslatef(x,y,-35.0);
	glColor3f(0.5,0.35,0.05);
	gluCylinder(obj,0.5,0.5,5,20,20);
	glPopMatrix();
    glPushMatrix();
}

void display()
{
     glClearColor(0.0,0.0,0.2,0.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glOrtho(-10,10,-10,10,-10,10);

     glColor3f(0.7,0.7,0.7);
     glPushMatrix();
	//glTranslatef(2.0,0.0,0.0);
     glRotatef(angX,1,0,0);
     glRotatef(angY,0,1,0);
     glScalef(0.5,0.5,0.5);
     glPushMatrix();
     //glTranslatef(5.0,0.0,0.0);
     glTranslatef(10.0,moonHeight,7.0);
     glutSolidSphere(1.5,50,50);
     glPopMatrix();
     glPushMatrix();
     
     glColor3f(0,0.2,0);
     glTranslatef(-10,-15,0);
	 glScalef(2,0.01,2);
     glutSolidCube(40);
     glPopMatrix();
     glPushMatrix();
     int i;
     for(i=0;i<100; i++){
     	drawTrunk(x[i], y[i]);
     }
     for(i=0;i<100; i++){
     	drawBranches(x[i], y[i]);
     }
     glPopMatrix();
     glPopMatrix();
	glFlush();
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

//int main(int argc, char *argv[])
//{
//	int i;
//	for(i=0;i<100; i++){
//		x[i] = (2 * (float)rand() / (float)RAND_MAX - 1)*40;
//    	y[i] = (2 * (float)rand() / (float)RAND_MAX - 1)*40;
//	}
//     glutInit(&argc,argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB |GLUT_DEPTH);
//     glutInitWindowPosition(50,50);
//     glutInitWindowSize(600,600);
//     glutCreateWindow("Objetos 3D - OpenGL");
//     glutDisplayFunc(display);
//     glutTimerFunc(500,giraCenario,0);
//     glutTimerFunc(15000,desceLua,0);
//     glutSpecialFunc(transformacoes);
//     init();
//     glutMainLoop();
//}
