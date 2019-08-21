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

static int window_width, window_height;
static int animation_ongoing_W=0,animation_ongoing_D=0,animation_ongoing_A=0;
static int xPlus=0,zPlus=0,zMinus=0;
static int x_trenutni=0, z_trenutni=0;

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);

int broj_prepreka=1;// 1 ili 2
int tip_prepreke=1;// 1,2 ili 3

/*
 ---broj 1:
 tip 1: x _ _
 tip 2: _ x _
 tip 3: _ _ x
 
 ---broj 2:
 tip 1: x x _
 tip 2: _ x x
 tip 3: x _ x
 */

void prve_prepreke(int broj_prepreka, int tip_prepreke){
    glColor3f(0.9,0.9,0.9);
    
    if(broj_prepreka == 2){
        if(tip_prepreke == 1){
            // LEVO SREDINA
            //levo
            glPushMatrix();
                glTranslatef(50,-3,5);
                glScalef(4, 8, 8);
                glutSolidCube(1);
            glPopMatrix();
        
            //sredina
            glPushMatrix();
                glTranslatef(50,-3,15);
                glScalef(4, 8, 8);
                glutSolidCube(1);
            glPopMatrix();
        }
        else if(tip_prepreke == 2){
            //SREDINA DESNO
            //sredina
            glPushMatrix();
                glTranslatef(75,-3,15);
                glScalef(4, 8, 8);
                glutSolidCube(1);
            glPopMatrix();
    
            //desno
            glPushMatrix();
                glTranslatef(75,-3,25);
                glScalef(4, 8, 8);
                glutSolidCube(1);
            glPopMatrix();
        }
        else if(tip_prepreke ==3){
            //LEVO DESNO
            //levo
            glPushMatrix();
                glTranslatef(100,-3,5);
                glScalef(4, 8, 8);
                glutSolidCube(1);
            glPopMatrix();
            
            //desno
            glPushMatrix();
                glTranslatef(100,-3,25);
                glScalef(4, 8, 8);
                glutSolidCube(1);
            glPopMatrix();
        }
        
    }
    if(broj_prepreka == 1){
        if(tip_prepreke == 1){
            //levo
            glPushMatrix();
                glTranslatef(125,-3,5);
                glScalef(4, 8, 8);
                glutSolidCube(1);
            glPopMatrix();
        }
        else if(tip_prepreke == 2){
            //sredina
            glPushMatrix();
                glTranslatef(150,-3,15);
                glScalef(4, 8, 8);
                glutSolidCube(1);
            glPopMatrix();
        }
        else if(tip_prepreke ==3){
            //desno
            glPushMatrix();
                glTranslatef(175,-3,25);
                glScalef(4, 8, 8);
                glutSolidCube(1);
            glPopMatrix();
        }
        
    }
}

int main(int argc, char *argv[])
{
	
	//inicijalizacija	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	//pravimo prozor
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("kocka do kocke");

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
        
        gluLookAt(-60+xPlus, 40, 0+zPlus-zMinus, //bilo je -40, 30, 0
                    0+xPlus, 1, 0+zPlus-zMinus,//bilo je 0, 1,0
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
	
	//Napravila sam kockicu u beneton zelenoj boji :)
	glColor3f(0,0.3686,0.082);
	glPushMatrix();
	//POCETNE KOORDINATE(0,0,10)
		glTranslatef(0+xPlus,0,14+zPlus-zMinus);//0,3,0 je bilo
		glutSolidCube(2);
	glPopMatrix();

	//PUTANJA 1.
	glColor3f(0.8,0,0.2);
	glPushMatrix();
		glTranslatef(500,-3,5);
		glScalef(1000, 5, 10);
		glutSolidCube(1);
	glPopMatrix();
        
        //PUTANJA 2.
	glColor3f(0.2,0,0.8);
	glPushMatrix();
		glTranslatef(500,-3,15);
		glScalef(1000, 5, 10);
		glutSolidCube(1);
	glPopMatrix();
        
        //PUTANJA 3.
	glColor3f(0.5,0,0.5);
	glPushMatrix();
		glTranslatef(500,-3,25);
		glScalef(1000, 5, 10);
		glutSolidCube(1);
	glPopMatrix();
        
        prve_prepreke(2,3);
        prve_prepreke(1,3);
        prve_prepreke(2,1);
        prve_prepreke(1,1);
        prve_prepreke(1,2);
        prve_prepreke(2,2);

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
    
    if((value != TIMER_ID_0) && (value != TIMER_ID_1) && (value != TIMER_ID_2))
        return;
    
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
    
    x_trenutni=xPlus;
    z_trenutni=14+zPlus-zMinus;
    
   /* if(x_trenutni >998){//prozorce ako se stigne do kraja! //FIXME nesto zabaguje
        glutInitWindowSize(300, 50);
        glutInitWindowPosition(560, 560);
        glutCreateWindow("Budimo realni, nije bitno samo ucestvovati! POBEDA!");
    }*/
   
   //ako se izadje sa putanje, igra se zavrsava
    if(z_trenutni < 2 || z_trenutni > 28){
        animation_ongoing_W=0;
        animation_ongoing_D=0;
        animation_ongoing_A=0;
        glutInitWindowSize(250, 20);
        glutInitWindowPosition(560, 560);
        glutCreateWindow("Bitno je ucestvovati!");
    }
    
                
}