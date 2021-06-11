// C program to illustrate OpenGL game
#include<stdio.h>
#include<gl/glut.h>
#include<math.h>
float xship = 0.0;

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
        xship -=15;
    }
    if (key == 'd') {
        xship += 15;
    }
}

void fighter_ship() {
    glColor3f(0.3, 0.1, 0.3);
    glTranslatef(xship, -670, 0);
    glPushMatrix();
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
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
}