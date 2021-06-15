#include<stdio.h>
#include<stdlib.h>
#include<gl/glut.h>
#include<random>
#include<vector>
#include<thread>
#include<chrono>
#include<functional>

using std::vector;

int dir = 0;
float rang = 0.0;
float th = 0;
float xShip = 0.0;
int BeamVecPoin = 0;
int obsVecPoin = 0;
const int maxObstacals = 8;
float obsSpeedFac = 2.0;
float beamSpeedFac = 3.0;

struct beam{
    float xBeam = 0.0;
    float yBeam = -565.00;
};

struct obstacal {
    float xObs = 0.0;
    float yObs = 610.0;
    float obsSize = 0.0;
    int obsType = 0;
};

std::vector<beam> BeamCordinates;
obstacal obs[maxObstacals];

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
        for (int i = 0; i < (BeamCordinates.size() - 1) && BeamCordinates.size() > 1; i++) {
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
void keyboardUp(unsigned char key, int x, int y) {
    if (key == 'a' ) {
        dir = 0;
    }
    if (key == 'd') {
        dir = 0;
    }
    /*if (key == 32 && BeamCordinates.size() < 11) {
    * 
    * 
    }*/
}
 
void plasmaBeam(float xBeam, float yBeam) { 
   
        glColor3f(1.0, 0.2, 0.3);
        glPushMatrix();
        glTranslatef(xBeam, yBeam, 0.0);
        glScalef(0.8, 2.0, 0.6);
        glutSolidSphere(6, 25, 25);
        glPopMatrix();
        yBeam += 1.0*beamSpeedFac;
}

void fighter_ship(int dir) {
    if (dir == 0)
    {
        if (rang > 0.0 && rang != 0.0) {
            rang -= 0.5;
        }
        else if (rang < 0.0 && rang != 0.0) {
            rang += 0.5;
        }
        glPushMatrix();
        glTranslatef(xShip, -627.0, 0.0);
        glRotatef(rang, 0.0, 1.0, 0.0);
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
        if (rang <= 30) rang += 0.5;
        glPushMatrix();
        glTranslatef(xShip, -627.0, 0.0);
        glRotatef(rang, 0.0, 1.0, 0.0);
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
    if (rang >= -30) rang -= 0.5;
        glPushMatrix();
        glTranslatef(xShip, -627.0, 0.0);
        glRotatef(rang, 0.0, 1.0, 0.0);
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
        glutSolidSphere(2*obsSize, 25, 25);
        glPopMatrix();
        break;
    case 2:
        glPushMatrix();
        glTranslatef(xObs, yObs, 0);
        glRotated(th, -1, -1, 0);
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
    while (true) {
        obs[obsVecPoin].obsType = rand() % 3 + 1;
        float xObs[12] = { 20.0,0.0,120.0,560.0,-567.0,-100.0,-650.0,-300.0,-800.0,760.0,430.0,-60.0 };
        obs[obsVecPoin].xObs = xObs[rand() % 12];
        float ObsSize[5] = { 20.0,10.0,40.0,30.0,25.0 };
        obs[obsVecPoin].obsSize = ObsSize[rand() % 5];
        obs[obsVecPoin++].yObs = 610.0;
        if (obsVecPoin == maxObstacals) obsVecPoin = 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fighter_ship(dir);

    for (int x = 0; x < 10; x++) {
        obstacals(obs[x].xObs, obs[x].yObs -= (0.09 * obsSpeedFac), obs[x].obsType, obs[x].obsSize, th += 0.01);
        if (BeamCordinates.size() > x) {
            printf("vec size:%d\t x: %d\n", BeamCordinates.size(), x);
            plasmaBeam(BeamCordinates[x].xBeam, BeamCordinates[x].yBeam++);
        }
        
    }
    if (BeamCordinates.size() > 1) {
        std::thread th_vp(vaporize);
        th_vp.detach();
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
    std::thread th_genObs(generate_obs);
    th_genObs.detach();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}