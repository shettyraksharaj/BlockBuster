#include<stdio.h>
#include<stdlib.h>
#include<gl/glut.h>
#include<math.h>
#include<vector>
#include<thread>

using std::vector;



float xShip = 0.0;
int BeamVecPoin = 0;

struct beam{
    float xBeam = 0.0;
    float yBeam = -565.00;
};

std::vector<beam> BeamCordinates;

void plasmaBeam(int srt, int end);


void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000.0, 1000.0, -680.0, 680.0, -2000, 2000);
    glMatrixMode(GL_MODELVIEW);
}

void vaporize() {
    if (BeamCordinates[0].yBeam >= 620.00 && BeamVecPoin >= 0) {
                for (int i = 0; i < (BeamCordinates.size()-1) && BeamCordinates.size() > 1; i++) {
                    BeamCordinates[i].xBeam = BeamCordinates[i + 1].xBeam;
                    BeamCordinates[i].yBeam = BeamCordinates[i + 1].yBeam;
                }
                if (BeamVecPoin == 0) {
                    BeamVecPoin = 0;
                    BeamCordinates.resize(BeamVecPoin);
                    return;
                }
                BeamVecPoin--;
                BeamCordinates.resize(BeamVecPoin);
    }
}
void keyboard(unsigned char key, int x, int y) {
    if (key == 'a') {
        xShip -= 15;
    }
    if (key == 'd') {
        xShip += 15;
    }
    if (key == 32 && BeamCordinates.size() < 11) {
        BeamCordinates.resize((BeamVecPoin+1));
        BeamCordinates[BeamVecPoin++].xBeam = xShip;
    }
}
 
void plasmaBeam(int srt, int end) { 
    for (int x = srt; x < end; x++) {
        glColor3f(1.0, 0.2, 0.3);
        glPushMatrix();
        glTranslatef(BeamCordinates[x].xBeam, BeamCordinates[x].yBeam, 0.0);
        glScalef(0.8, 2.0, 0.6);
        glutSolidSphere(6, 25, 25);
        glPopMatrix();
        BeamCordinates[x].yBeam += 3;
    }
}

void fighter_ship() {
    glPushMatrix();
    glColor3f(0.2, 0.6, 0.2);
    glTranslatef(xShip, -670, 0);
    glRotated(90, -1, 0, 0);
    glutSolidCone(15, 100, 20, 20);
    glPushMatrix();
    glTranslated(0, 0, 30);
    glutSolidCone(70, 30, 20, 20);
    glPopMatrix();
    glutSolidCone(60, 20, 20, 20);
    glPopMatrix();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0, 500, 0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(25.0, 25, 25);
    glPopMatrix();
    fighter_ship();
    if (BeamCordinates.size() > 0) {
        vaporize();
        plasmaBeam(0, BeamCordinates.size());
        /*if (BeamCordinates.size() <= 10) {
           
        }
        else if (BeamCordinates.size() > 5) {
            std::thread th_rb1(plasmaBeam, 0, 5);
            std::thread th_rb2(plasmaBeam, 6, BeamCordinates.size());
            th_rb1.join();
            th_rb2.join();
        }*/
    }

    printf_s("size is: %d BeamVecPoin is %d \n", BeamCordinates.size(), BeamVecPoin);
    glutSwapBuffers();
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 680);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("BlockBuster");
    glEnable(GL_DEPTH_TEST);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}