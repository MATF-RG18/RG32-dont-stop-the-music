#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>

#define PI 3.1415926535
#define TIMER_ID_0 0
#define TIMER_ID_1 1
#define TIMER_ID_2 2
#define TIMER_INTERVAL 20

static int window_width, window_height,animation_ongoing_W=0,animation_ongoing_D=0,animation_ongoing_A=0,xPomeraj=0,zPomeraj=0,zNemeraj=0;

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);

int main(int argc, char *argv[])
{
	
	//inicijalizacija	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	//pravimo prozo2
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
	//kamera prati kretanje kocke
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-20+xPomeraj, 20, 15+zPomeraj-zNemeraj, 
			   0+xPomeraj, 1, 0+zPomeraj-zNemeraj,
			   0, 1, 0);

	glLineWidth(6);

	//iscrtavamo koordinatni sistem
	glBegin(GL_LINES);
		//X BLUE
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(100, 0, 0);
		//Y GREEN
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 100, 0);
		//Z RED
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 100);

	glEnd();

	//Napravila sam pod 
	glColor3f(0.3764,0.3764,0.3764);
	glPushMatrix();
	glTranslatef(450,-5,145);
	glScalef(900, 0, 300);
	
	glutSolidCube(1);
	glPopMatrix();
	
	//Napravila sam kockicu u beneton zelenoj boji :)
	glColor3f(0,0.3686,0.082);
	glPushMatrix();
	//POCETNE KOORDINATE(0,0,10)
	glTranslatef(0+xPomeraj,0,0+zPomeraj-zNemeraj);
	glutSolidCube(1);
	glPopMatrix();
	/*
	//krug koji glumi rupu, u boji pozadine
	glPushMatrix();
	glTranslatef(24, 0, 0);
	int i = 0;
	glColor3f(0.75, 0.75, 0.75);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0,0);
	for(i =0; i <= 20; i++){
		glVertex3f(cos(2*i*PI/20)*4, 0,sin(2*i*PI/20)*4);
	}
	glEnd();
	glPopMatrix();
	*/
	//PUTANJA
	//prvi deo
	//prvi delic prvog dela
	glColor3f(0.5,0.5,0.5);
	glPushMatrix();
	glTranslatef(10,-2,-0.3);
	glScalef(20, 0, 4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(22,-2,7.65);
	glScalef(4, 0, 20);
	glutSolidCube(1);
	glPopMatrix();
	//drugi delic prvog dela
	glPushMatrix();
	glTranslatef(30,-2,19);
	glScalef(20, 0, 4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(42,-2,29);
	glScalef(4, 0, 24);//povecala sam za 4 duzinu
	glutSolidCube(1);
	glPopMatrix();

	/*//Napravila sam pod 
	glColor3f(0.3764,0.3764,0.3764);
	glPushMatrix();
	glTranslatef(450,-5,0);
	glScalef(900, 0, 30);
	
	glutSolidCube(1);
	glPopMatrix();*/

	//menjamo bafere
	glutSwapBuffers();


}
//u odnosu na S,A,D ili E kocka se pomera (pravo, levo, desno)ili staje
static void on_keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27:
			exit(0);
			break;
		//napred
		case 'w':
		case 'W':{
			animation_ongoing_W=1;
			animation_ongoing_A=0;
			animation_ongoing_D=0;
			glutTimerFunc(50,on_timer,0);
			break;
		}
		//desno
		case 'd':
		case 'D':{
			animation_ongoing_D=1;
			animation_ongoing_W=0;
			animation_ongoing_A=0;
			glutTimerFunc(50,on_timer,1);
			break;
		}
		//levo
		case 'a':
		case 'A':{
			animation_ongoing_A=1;
			animation_ongoing_W=0;
			animation_ongoing_D=0;
			glutTimerFunc(50,on_timer,2);
			break;
		}
		//!(start)
		case 'e':
		case 'E':{
			animation_ongoing_W=0;
			animation_ongoing_A=0;
			animation_ongoing_D=0;
			break;
		}

	}


}
//ovo je funkcija koja se poziva kada se klikne odredjeno slovo, i regulise kretanje
static void on_timer(int value){
	//kada se klikne na slovo W, kocka ide pravo
		if(value == TIMER_ID_0 && animation_ongoing_W == 1){
	
			xPomeraj+=1;
			glutPostRedisplay();
			glutTimerFunc(50,on_timer,0);
		}
	//kada se klikne na slovo D, kocka ide desno
		else if(value == TIMER_ID_1 && animation_ongoing_D == 1){
			
			zPomeraj+=1;
			glutPostRedisplay();
			glutTimerFunc(50,on_timer,1);
		}
	//kada se klikne na slovo A, kocka ide levo
		else if(value == TIMER_ID_2 && animation_ongoing_A == 1){
			
			zNemeraj+=1;
			glutPostRedisplay();
			glutTimerFunc(50,on_timer,2);
		}
		else
			return;
}