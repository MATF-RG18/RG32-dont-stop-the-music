#include <stdio.h>
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

typedef struct{
    float x,y,z;
} Prepreka;

Prepreka nizp1[15];
int br_prepreka1 = 0;
Prepreka nizp2[15];
int br_prepreka2 = 0;

double x_kocke = 3;
double y_kocke = 1;
double z_kocke = 0;

double x1_putanje1 = 1;
double x2_putanje1 = 3;
double x3_putanje1 = 5;
double y_putanje1 = 0.25;
double z_putanje1 = 25;

double x1_putanje2 = 1;
double x2_putanje2 = 3;
double x3_putanje2 = 5;
double y_putanje2 = 0.25;
double z_putanje2 = 75;

void kocka();
// void nebo();
void putanja1();
void putanja2();
void igra(int value);
void prepreke_putanja1();
void prepreke_putanja2();
void prepreka(double x, double y, double z);

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

    // nebo();
    kocka();
    
    putanja1();
    putanja2();

    for (int i = 0 ; i < br_prepreka1 ; i ++ ) {
        Prepreka pr = nizp1[i];
        prepreka(pr.x, pr.y, pr.z);
    }

    for (int i = 0 ; i < br_prepreka2 ; i ++ ) {
        Prepreka pr = nizp2[i];
        prepreka(pr.x, pr.y, pr.z);
    }
    
    glutSwapBuffers();
}

static void on_release(unsigned char key,int x,int y){
    switch(key){
        case 'a':
        case 'A':
            kretanje[0] -= 1;break;
        case 'd':
        case 'D': kretanje[1] -= 1;break;
    }
}

void igra(int value){
    if(value)
        return;

    if(kretanje[0] && x_kocke < 5.5){
        x_kocke += 0.2;
    }
    if(kretanje[1] && x_kocke > 0.5){
        x_kocke -= 0.2;
    }

    z_putanje1 -= 0.2;
    z_putanje2 -= 0.2;

    for (int i = 0 ; i < br_prepreka1 ; i++) {
        nizp1[i].z -= 0.2;
    }

    for (int i = 0 ; i < br_prepreka2 ; i++) {
        nizp2[i].z -= 0.2;
    }

    if(z_putanje1 <= -25) {
        z_putanje1 = 75;
        prepreke_putanja1();
    }

    if(z_putanje2 <= -25) {
        z_putanje2 = 75;
        prepreke_putanja2();
    }

    glutPostRedisplay();
    if(glavni_tajmer) {
        glutTimerFunc(30,igra,timer_id1);
    }
}

void prepreke_putanja1(){
    int prepreka_u_redu = 0;
    br_prepreka1 = 0;

    static int moguce_x_koordinate_prepreke[] = {1,3,5};
    for(int i = 10 ; i < 50 ; i += 10){
        prepreka_u_redu = ((int)rand() % 2) + 1;
        int trenutna_prepreka = 0;
        
        while(trenutna_prepreka < prepreka_u_redu){
            Prepreka pr;

            pr.x = moguce_x_koordinate_prepreke[(int)rand()%3];
            pr.y = 1;
            pr.z = z_putanje1 + i - 25;
            nizp1[br_prepreka1++] = pr;
            trenutna_prepreka++;
        }
    }

}

void prepreke_putanja2(){
    int prepreka_u_redu = 0;
    br_prepreka2 = 0;
    
    static int moguce_x_koordinate_prepreke[] = {1,3,5};
    for(int i = 10 ; i < 50 ; i += 10){
        prepreka_u_redu = ((int)rand() % 2) + 1;
        int trenutna_prepreka = 0;
        
        while(trenutna_prepreka < prepreka_u_redu){
            Prepreka pr;

            pr.x = moguce_x_koordinate_prepreke[(int)rand()%3];
            pr.y = 1;
            pr.z = z_putanje2 + i - 25;
            nizp2[br_prepreka2++] = pr;
            trenutna_prepreka++;
        }
    }
}

void kocka(){
    glPushMatrix();
        glColor3f(0.6, 0, 0.4);
        glTranslatef(x_kocke, y_kocke, z_kocke);
        glutSolidCube(0.5);
    glPopMatrix();
}

void putanja1(){
    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(x1_putanje1, y_putanje1, z_putanje1);
        glScalef(2, 0.5, 50);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(x2_putanje1, y_putanje1, z_putanje1);
        glScalef(2, 0.5, 50);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 0, 1);
        glTranslatef(x3_putanje1, y_putanje1, z_putanje1);
        glScalef(2, 0.5, 50);
        glutSolidCube(1);
    glPopMatrix();
}

void putanja2(){
    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(x1_putanje2, y_putanje2, z_putanje2);
        glScalef(2, 0.5, 50);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(x2_putanje2, y_putanje2, z_putanje2);
        glScalef(2, 0.5, 50);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 0, 1);
        glTranslatef(x3_putanje2, y_putanje2, z_putanje2);
        glScalef(2, 0.5, 50);
        glutSolidCube(1);
    glPopMatrix();
}

void prepreka(double x, double y, double z){
    glPushMatrix();
        glColor3f(0.6, .3, 0.4);
        glTranslatef(x, y, z);
        glutSolidCube(2);
    glPopMatrix();
}

// void nebo() {
//     glPushMatrix();
//         glColor3f(0, .5, .5);
//         glTranslatef(3, 0, 0);
//         glScalef(2, 0.5, 50);
//         glutSolidSphere(25,50,50);
//     glPopMatrix();
// }
