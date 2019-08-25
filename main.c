#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define timer_id1 0

//callback fje
static void on_keyboard(unsigned char key, int x, int y);
static void on_release(unsigned char key,int x,int y);
static void on_reshape(int width, int height);
static void on_display();
static int glavni_tajmer;

double x_kocke = 3;
double y_kocke = 1;
double z_kocke = 0;

double x1_putanje = 1;
double x2_putanje = 3;
double x3_putanje = 5;
double y_putanje = 0.25;
double z_putanje = 25;

void kocka();
void putanja();
void igra(int value);

static int kretanje[] = {0,0};

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutKeyboardUpFunc(on_release);

    glavni_tajmer = 0;

    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y){
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'p':
    case 'P':
            if(!glavni_tajmer){
                    glutTimerFunc(30, igra ,timer_id1);
                    glavni_tajmer = 1;
            };break;
    case 'a':
    case 'A':
        kretanje[0] = 1;
        glutPostRedisplay();
        break;
    //skretanje u desno
    case 'd':
    case 'D':
        kretanje[1] = 1;
        glutPostRedisplay();
        break;
    }
    
}

static void on_reshape(int width, int height){
    //view port
    glViewport(0, 0, width, height);

    //parametri projekcije:
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1500);
}

static void on_display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //kamera:
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3,4,-6,
                3,0,5,
                0.0,1.0,0.0);

    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(100,0,0);
        glVertex3f(0,0,0);
        glVertex3f(-100,0,0);
        
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,100,0);
        glVertex3f(0,0,0);
        glVertex3f(0,-100,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,100);
        glVertex3f(0,0,0);
        glVertex3f(0,0,-100);
    glEnd();

    kocka();
    
    putanja();
    
    glutSwapBuffers();
}

static void on_release(unsigned char key,int x,int y)
{
    switch(key){
        case 'a':
        case 'A':
            kretanje[0] -= 1;break;
        case 'd':
        case 'D': kretanje[1] -= 1;break;
    }
}

void igra(int value)
{
    if(value)
        return;

    if(kretanje[0] && x_kocke < 5.5){
        x_kocke += 0.2;
    }
    if(kretanje[1] && x_kocke > 0.5){
        x_kocke -= 0.2;
    }

    z_putanje -= 0.2;

    if(z_putanje <= -25) {
        z_putanje = 25;
    }

    glutPostRedisplay();
    if(glavni_tajmer) {
        glutTimerFunc(30,igra,timer_id1);
    }
}

void kocka()
{
    glPushMatrix();
        glColor3f(0.6, 0, 0.4);
        glTranslatef(x_kocke, y_kocke, z_kocke);
        glutSolidCube(0.5);
    glPopMatrix();
}
void putanja()
{
    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(x1_putanje, y_putanje, z_putanje);
        glScalef(2, 0.5, 50);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(x2_putanje, y_putanje, z_putanje);
        glScalef(2, 0.5, 50);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 0, 1);
        glTranslatef(x3_putanje, y_putanje, z_putanje);
        glScalef(2, 0.5, 50);
        glutSolidCube(1);
    glPopMatrix();
}
