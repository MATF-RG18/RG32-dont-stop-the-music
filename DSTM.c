#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

static int window_width, window_height;

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);


int main(int argc, char *argv[])
{
	
	//inicijalizacija	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	//pravimo prozor
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("el DJ por favor no pares la musica!");

	//postavljamo boju koja ce da cisti
	glClearColor(0.75, 0.75, 0.75, 0);

	//pozivamo funkcije
	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);

	glEnable(GL_DEPTH_TEST);

	//ulazimo u glavnu petlju
	glutMainLoop();

	return 0;
}


static void on_keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27:
			exit(0);
			break;
	}

}

static void on_reshape(int width, int height){

	window_width = width;
	window_height = height;
}

static void on_display(void){

	//cistimo bufere
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//postavljamo projekciju
	glViewport(0, 0, window_width, window_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)window_width/window_height, 1, 1500);

	//postavljamo kameru
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20, 35, 20, 
			   0, 1, 0,
			   0, 1, 0);

	glLineWidth(6);

	//iscrtavamo koordinatni sistem
	glBegin(GL_LINES);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(100, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 100, 0);

		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 100);

	glEnd();

	//Napravila sam pod 
	glColor3f(0.3764,0.3764,0.3764);
	glPushMatrix();
	glTranslatef(0,-5,0);
	glScalef(30, 0, 30);
	
	glutSolidCube(1);
	glPopMatrix();
	
	//Napravila sam kockicu u beneton zelenoj boji :)
	glColor3f(0,0.3686,0.082);
	//glPushMatrix();

	//glPopMatrix();
	glutSolidCube(1);

	glFlush();

	//menjamo bafere
	glutSwapBuffers();


}