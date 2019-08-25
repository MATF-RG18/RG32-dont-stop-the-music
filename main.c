#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

//callback fje
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display();
static int glavni_tajmer;

void kocka();
void putanja();

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    timer_active = 0;

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

static void on_display(void){
    
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

void kocka(){
    glPushMatrix();
        glColor3f(0.6, 0, 0.4);
        glTranslatef(3, 1, 0);
        glutSolidCube(0.5);
    glPopMatrix();
}
void putanja(){
    glPushMatrix();
        glColor3f(0, 0.7, 0.2);
        glTranslatef(3, 0.25, 25);
        glScalef(6, 0.5, 50);
        glutSolidCube(1);
    glPopMatrix();
}
