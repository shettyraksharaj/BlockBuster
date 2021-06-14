#include<stdio.h>
#include<stdlib.h>
#include<gl/glut.h>
#include<math.h>
#include<vector>
#include<thread>

using std::vector;

int dir = 0;
float rang = 0.0;
float th = 0;
float xShip = 0.0;
int BeamVecPoin = 0;

struct beam{
    float xBeam = 0.0;
    float yBeam = -565.00;
};

struct obstacal {
    float xObs = 0.0;
    float yObs = 0.0;
    float obsSize = 0.0;
};

std::vector<beam> BeamCordinates;
std::vector<obstacal> obs;

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
    if (key == 'a' && xShip >= -995) {
        xShip -= 15;
        dir = -1;
    }
    if (key == 'd' && xShip <= 995 ) {
        xShip += 15;
        dir = 1;
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

void fighter_ship(int dir) {
    if (dir == 0)
    {
        glPushMatrix();
        glTranslatef(xShip, -627, 0);
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glScalef(2.0, 4.0, 1.0);
        glTranslatef(0.0, 0.0, 0.0);
        glutSolidCube(20);
        glPopMatrix();

       glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glScalef(1.5, 2.0, 0.5);
        glTranslatef(0.0, -8.0, 27.0);
        glutSolidCube(15);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();
        
        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();
        
        glPushMatrix();
        glColor3f(0.1, 0.0, 0.1);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1, 0.0, 0.1);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(-50.0, -14.0, -1.0); 
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPopMatrix();
    }
    else if (dir == 1) {
        if (rang <= 30) rang += 0.05;
        glPushMatrix();
        glTranslatef(xShip, -627, 0);
        glRotatef(rang, 0, 1, 0);
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glScalef(2.0, 4.0, 1.0);
        glTranslatef(0.0, 0.0, 0.0);
        glutSolidCube(20);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glScalef(1.5, 2.0, 0.5);
        glTranslatef(0.0, -8.0, 27.0);
        glutSolidCube(15);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1, 0.0, 0.1);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1, 0.0, 0.1);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(-50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPopMatrix();
    }
    else if (dir == -1) {
    if (rang >= -30) rang -= 0.05;
        glPushMatrix();
        glTranslatef(xShip, -627, 0);
        glRotatef(rang, 0, 1, 0);
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glScalef(2.0, 4.0, 1.0);
        glTranslatef(0.0, 0.0, 0.0);
        glutSolidCube(20);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glScalef(1.5, 2.0, 0.5);
        glTranslatef(0.0, -8.0, 27.0);
        glutSolidCube(15);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -2.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glScalef(2.0, 0.8, 0.9);
        glTranslatef(-15.0, -21.0, -7.0);
        glutSolidCube(10);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1, 0.0, 0.1);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.1, 0.0, 0.1);
        glScalef(1.0, 5.0, 1.0);
        glRotatef(90, -1, 0, 0);
        glTranslatef(-50.0, -14.0, -1.0);
        glutSolidTorus(7.0, 10.0, 25.0, 25.0);
        glPopMatrix();

        glPopMatrix();
    }
}

void obstacals(float xObs, float yObs, int obsType, float obsSize,float th) {
    switch (obsType) {
    case 1:
        glPushMatrix();
        glTranslatef(xObs, yObs, 0);
        glColor3f(1.0, 0.0, 0.0);
        glutSolidSphere(obsSize, 25, 25);
        glPopMatrix();
        break;
    case 2:
        glPushMatrix();
        glRotated(th,-1,-1,0);
        glTranslatef(xObs, yObs, 0);
        glScalef(3*obsSize, 3*obsSize, 3*obsSize);
        glColor3f(1.0, 0.0, 0.0);
        glutSolidIcosahedron();
        glPopMatrix();
        break;
    case 3:
        glPushMatrix();
        glTranslatef(xObs, yObs, 0);
        glColor3f(1.0, 0.0, 0.0);
        glutSolidTorus(0.5*obsSize,obsSize, 50,50);
        glTranslatef(0.0, 0.0, -20.0);
        glutSolidSphere(0.75*obsSize, 25, 25);
        glPopMatrix();
        break;
    }
}

void generate_obs() {

}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //obstacals(100, 100, 3, 30, th +=0.1 );
    
    fighter_ship(dir);
    if (BeamCordinates.size() > 0) {
        vaporize();
        plasmaBeam(0, BeamCordinates.size());
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