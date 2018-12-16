#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
//#include<vlc/vlc.h>

#define PI 3.1415926535
#define TIMER_ID_0 0
#define TIMER_ID_1 1
#define TIMER_ID_2 2
#define TIMER_INTERVAL 20

static int window_width, window_height;
static int animation_ongoing_W=0,animation_ongoing_D=0,animation_ongoing_A=0;
static int xPlus=0,zPlus=0,zMinus=0;

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);

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
	//muzika
	/*libvlc_instance_t *inst;
	libvlc_media_player_t *mp;
	libvlc_media_t *m;

	inst = libvlc_new(0, NULL);
	m = libvlc_media_new_path(inst, "easy.mp3");
	mp = libvlc_media_player_new_from_media(m);
	
	libvlc_media_release(m);
	libvlc_media_player_play(mp);
	//sleep(20);
	libvlc_media_player_stop(mp);
	
	libvlc_media_player_release(mp);
	libvlc_release(inst);*/


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
	gluLookAt(0+xPlus, 70, 0+zPlus-zMinus, 
			   0+xPlus, 1, 0+zPlus-zMinus,
			   1, 0, 0);

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
		glTranslatef(0.5+xPlus,0,4+zPlus-zMinus);
		glutSolidCube(1);
	glPopMatrix();

	//PUTANJA

	//prvi deo(cetvrtine)
	glColor3f(1,0,0);
	glPushMatrix();//duzina 40
		glTranslatef(20,-2,4);
		glScalef(40, 0, 8);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();//duzina 40
		glTranslatef(36,-2,24);  
		glScalef(8, 0, 32);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();//duzina 40
		glTranslatef(56,-2,36);
		glScalef(32, 0, 8);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();//duzina 40
		glTranslatef(68,-2,56);
		glScalef(8, 0, 32);
		glutSolidCube(1);
	glPopMatrix();

	//drugi deo(cetvrtine)
	glColor3f(0,0,1);
	glPushMatrix();//duzina 40
		glTranslatef(88,-2,68);
		glScalef(32, 0, 8);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();//duzina 40
		glTranslatef(100,-2,88);
		glScalef(8, 0, 32);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();//duzina 40
		glTranslatef(120,-2,100);
		glScalef(32, 0, 8);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();//duzina 40
		glTranslatef(132,-2,120);
		glScalef(8, 0, 32);
		glutSolidCube(1);
	glPopMatrix();

	//treci deo(polovine)
	glColor3f(0,1,0);
	glPushMatrix();//duzina 72
		glTranslatef(164,-2,140);
		glScalef(72, 0, 8);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();//duzina 72
		glTranslatef(196,-2,176);
		glScalef(8, 0, 64);
		glutSolidCube(1);
	glPopMatrix();

	//cetvrti deo(2*(1/4) + 4*(1/8))


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
	
			xPlus+=1;
			glutPostRedisplay();
			glutTimerFunc(50,on_timer,0);
		}
	//kada se klikne na slovo D, kocka ide desno
		else if(value == TIMER_ID_1 && animation_ongoing_D == 1){
			
			zPlus+=1;
			glutPostRedisplay();
			glutTimerFunc(50,on_timer,1);
		}
	//kada se klikne na slovo A, kocka ide levo
		else if(value == TIMER_ID_2 && animation_ongoing_A == 1){
			
			zMinus+=1;
			glutPostRedisplay();
			glutTimerFunc(50,on_timer,2);
		}
		else
			return;
}