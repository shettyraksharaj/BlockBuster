#include<stdio.h>
#include <stdlib.h>
#include<gl/glut.h>
#include<math.h>
#include<vector>

using std::vector;

int BeamVecPoin = 0;
struct beam{
    float xBeam;
    float yBeam = -565;
};

float xShip = 0.0;
void plasmaBeam(float xBeam,float ybeam);

std::vector<beam> BeamCordinates;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000.0, 1000.0, -680.0, 680.0, -2000, 2000);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a') {
        xShip -= 15;
    }
    if (key == 'd') {
        xShip += 15;
    }
    if (key == 32) {
        BeamCordinates.resize(++BeamVecPoin);
        BeamCordinates[BeamVecPoin-1].xBeam = xShip;
    }
}
 
void plasmaBeam(float xBeam, float yBeam) {
    glColor3f(1.0, 0.2, 0.3);
    glPushMatrix();
    glTranslatef(xBeam,yBeam,0.0);
    glScalef(0.8, 2.0, 0.6);
    glutSolidSphere(6, 25, 25);
    glPopMatrix();

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
    if (!BeamCordinates.empty()) {
        for (int x = 0; x < BeamCordinates.size() ; x++) {
            plasmaBeam (BeamCordinates[x].xBeam, BeamCordinates[x].yBeam++);
        }
    }
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