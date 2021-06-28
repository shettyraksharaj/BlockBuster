#include<stdio.h>
#include<stdlib.h>
#include<gl/glut.h>
#include<random>
#include<vector>
#include<thread>
#include<chrono>
#include<functional>
#include<glm/vec2.hpp>
#include<glm/glm.hpp>


using std::vector;

short int dir = 0;
float rang = 0.0;
float th = 0;
float xShip = 0.0;
int BeamVecPoin = 0;
int obsVecPoin = 0;
const int maxObstacals = 15;
float obsSpeedFac = 3.0;
float beamSpeedFac = 3.0;
int axisListSize = 0;
int id1 = 0;
int id2 = 0;

struct beam{
    float xBeam = 0.0;
    float yBeam = -565.00;
    float xhalsize = 4.8;
    float yhalsize = 12.0;
    bool renderBeam = false;
};

struct obstacal {
    float xObs = 0.0;
    float yObs = 610.0;
    float obsSize = 0.0;
    float obsRadius = 0.0;
    float x1 = 0.0;
    float x2 = 0.0;
    bool renderObs = false;
};

struct axisList {
    float xmin;
    float xmax;
    int id[2];
};

std::vector<beam> Beams;
obstacal obs[maxObstacals];
std::vector<axisList> axisListItems;

void plasmaBeam(float xBeam, float yBeam);

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000.0, 1000.0, -680.0, 680.0, -2000, 2000);
    glMatrixMode(GL_MODELVIEW);
}


void vaporize() {
    for (auto& it : Beams) {
        if (it.yBeam >= 620.00) {
            it.renderBeam = false;
        }
    }
}

void firebeam() {
    if (BeamVecPoin == 100) BeamVecPoin = 0;
    Beams.resize((BeamVecPoin + 1));
    Beams[BeamVecPoin].renderBeam = true;
    Beams[BeamVecPoin++].xBeam = xShip;
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        firebeam();
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
    if (key == 32) {

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
        glScalef(0.8, 2.0, 0.2);
        glutSolidSphere(6, 25, 25);
        yBeam += 1.0*beamSpeedFac;
        glPopMatrix();
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

void obstacals(float xObs, float yObs, float obsSize) {
    glPushMatrix();
    glTranslatef(xObs, yObs, 0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(2.0 * obsSize, 25, 25);
    glPopMatrix();

}

void generate_obs() {
    while (true) {
        if ((!obs[obsVecPoin].renderObs) || obs[obsVecPoin].yObs < -620.0) {
            float xObs[8] = { 0.0,240.0,560.0,-567.0,-100.0,-330.0,-800.0,760.0 };
            obs[obsVecPoin].xObs = xObs[rand() % 12];
            float ObsSize[5] = { 20.0,10.0,40.0,30.0,25.0 };
            obs[obsVecPoin].obsSize = ObsSize[rand() % 5];
            obs[obsVecPoin].renderObs = true;
            obs[obsVecPoin].obsRadius = 2 * obs[obsVecPoin].obsSize;
            obs[obsVecPoin].x1 = obs[obsVecPoin].xObs - obs[obsVecPoin].obsRadius;
            obs[obsVecPoin].x2 = obs[obsVecPoin].xObs + obs[obsVecPoin].obsRadius;
            obs[obsVecPoin++].yObs = 610.0;
            if (obsVecPoin == maxObstacals) obsVecPoin = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        }
        else {
            obsVecPoin++;
            if (obsVecPoin == maxObstacals) obsVecPoin = 0;
            continue;
        }
    }
}
void update() {
    auto obsup = []() {
        for (int x = 0; x < 10; x++) {
            if (obs[x].renderObs) {
                obs[x].yObs -= (0.09 * obsSpeedFac);
            }
        }
    };
    std::thread th_obs(obsup);
    th_obs.detach();

    for (int x = 0; x < Beams.size(); x++) {
        if (Beams[x].renderBeam == false)continue;
        if (Beams.size() > x) {
            Beams[x].yBeam++;
        }
    }
    //th_obs.join();
}

//void updateAxisList() {
//    axisListItems.clear();
//    for (int i = 0; i < 10; i++) {
//        if (obs[i].renderObs) {
//            axisListSize++;
//            axisListItems.resize(axisListSize);
//            axisListItems[axisListSize - 1].xmin = -obs[i].obsRadius + obs[i].xObs-3;
//            axisListItems[axisListSize - 1].xmax = obs[i].obsRadius + obs[i].xObs+3;
//            axisListItems[axisListSize - 1].id[0] = 2;
//            axisListItems[axisListSize - 1].id[1] = i;
//        }
//    }
//    for (auto& it : Beams) {
//        axisListSize++;
//        axisListItems.resize(axisListSize);
//        axisListItems[axisListSize - 1].xmin = -5.8 + it.xBeam;
//        axisListItems[axisListSize - 1].xmax = 5.8 + it.xBeam;
//        axisListItems[axisListSize - 1].id[0] = 1;
//        axisListItems[axisListSize - 1].id[1] = id1++;
//    }
//    std::sort(axisListItems.begin(), axisListItems.end(), [](axisList a, axisList b) {
//        return a.xmin < b.xmin;
//        });
//}

//void sortAndSweep() {
//    struct activeList {
//        float xmin;
//        float xmax;
//        int id[2];
//        bool collision = false;
//    };
//    std::vector <activeList> activelists;
//    activelists.resize(axisListSize);
//    activelists[0].xmin = axisListItems[0].xmin;
//    activelists[0].xmax = axisListItems[0].xmin;
//    activelists[0].id[0] = axisListItems[0].xmin;
//    activelists[0].id[1] = axisListItems[0].xmin;
//    for (int i = 0; i < axisListItems.size();i++) {
//        for (int j = i + 1; j < axisListItems.size(); j++) {
//            if (activelists[i].xmax < axisListItems[j].xmin && ) {
//                activelists[i].xmin = axisListItems[j].xmin;
//                activelists[i].xmax = axisListItems[j].xmin;
//                activelists[i].id[0] = axisListItems[j].xmin;
//                activelists[i].id[1] = axisListItems[j].xmin;
//                
//            }
//            else {
//                activelists[i+1].xmin = axisListItems[j].xmin;
//                activelists[i+1].xmax = axisListItems[j].xmin;
//                activelists[i+1].id[0] = axisListItems[j].xmin;
//                activelists[i+1].id[1] = axisListItems[j].xmin;
//                activelists[i + 1].collision = true;
//                activelists[i].collision = true;
//            }
//        }
//    }
//    for (auto& it : activelists) {
//        collisionDetection();
//    }
//
//}
//
//void collisionDetection(struct activeList activelist1, struct activeList activelist2) {
//    // collision x-axis?
//    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
//        two.Position.x + two.Size.x >= one.Position.x;
//    // collision y-axis?
//    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
//        two.Position.y + two.Size.y >= one.Position.y;
//    // collision only if on both axes
//    // collisionX && collisionY;
//
//}

void collisiondetection() {
    for (int i = 0; i < maxObstacals; i++) {
        for (auto& it : Beams) {
            if ((obs[i].yObs - obs[i].obsRadius) < (it.yBeam + it.xhalsize) && it.renderBeam && obs[i].renderObs) {
                if ((obs[i].x1 < it.xBeam) && (obs[i].x2 > it.xBeam)) {
                    obs[i].renderObs = false;
                    it.renderBeam = false;
                    it.yBeam = -100000;
                    break;
                }
            }
        }
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fighter_ship(dir);
    for (int x = 0; x < 10; x++) {
        if (obs[x].renderObs) {
            obstacals(obs[x].xObs, obs[x].yObs, obs[x].obsSize);
        }
    }
    for (int x = 0; x < Beams.size(); x++) {
        if (Beams.size() > x && Beams[x].renderBeam) {
            plasmaBeam(Beams[x].xBeam, Beams[x].yBeam);
        }
    }
    /*collisionDetection()*/
    /*updateAxisList();*/
    collisiondetection();
    update();
    if (Beams.size() > 1) {
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
   /* std::thread th_detctcol(collisionDetection);
    th_detctcol.detach();*/
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}