#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<GL/glew.h>
#include<gl/glut.h>
#include<random>
#include<vector>
#include<thread>
#include<chrono>
#include<string>
#include<conio.h>
//#include<freetype/freetype.h>
//#include<glm/vec2.hpp>
//#include<glm/vec3.hpp>
//#include<glm/mat4x4.hpp>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include<map>
//#include "fontshaders.h"
//#include "Shaders.h"

//#include FT_FREETYPE_H  
//#define GL_CLAMP_TO_EDGE 0x812F

using std::vector;

short int dir = 0;
float rang = 0.0;
float th = 0;
float xShip = 0.0;
int BeamVecPoin = 0;
int obsVecPoin = 0;
const int maxObstacals = 15;
float obsSpeedFac = 13.5;
float beamSpeedFac = 7.0;
float rof = 1.0;
int playerHealth = 2;
bool firebeams;
bool shipcollision = false;
int shipnorenderframe = 10;
int shipnorenderframetime = 3;
const int maxExplosions = 15;
//unsigned int VAO, VBO;

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
    float eX = 0.0;
    float eY = 0.0;
    bool renderObs = false;
    bool state = true;
    int id;
};

struct explosionsXY {
    float expX = 0;
    float expY = 0;
};

//struct fontProperties {
//    unsigned int TextureID;
//    glm::ivec2   Size;
//    glm::ivec2   Bearing;
//    unsigned int Advance;
//};

std::vector<beam> Beams;
obstacal obs[maxObstacals];
explosionsXY explosions[maxExplosions];
//std::map<char, fontProperties> Characters;

void plasmaBeam(float xBeam, float yBeam);

//Shader fontshader;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1000.0, 1000.0, -680.0, 680.0, -2000, 2000);
    glMatrixMode(GL_MODELVIEW);
    /*fontshader.shaderCompile(vertexShaderSource, fragmentShaderSource);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    fontshader.use();
    glm::mat4 projection = glm::ortho(0.0, 100.0, 0.0, 100.0);
    glUniformMatrix4fv(glGetUniformLocation(fontshader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));*/
}



void vaporize() {
    for (auto& it : Beams) {
        if (it.yBeam >= 620.00) {
            it.renderBeam = false;
        }
    }
    for (int i = 0; i < maxObstacals;i++) {
        if (obs[i].yObs <= -750.00) {
            obs[i].renderObs = false;
        }
    }
}



void firebeam() {
    while (firebeams) {
        if (BeamVecPoin == 99) BeamVecPoin = 0;
        Beams[BeamVecPoin].renderBeam = true;
        Beams[BeamVecPoin].xBeam = xShip;
        Beams[BeamVecPoin++].yBeam = -565.00;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}



void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN) {
        firebeams = true;
        std::thread th_fb(firebeam);
        th_fb.detach();
    }
    else if (button == GLUT_LEFT_BUTTON and state == GLUT_UP)
    {
        firebeams = false;
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

}


void keyboardUp(unsigned char key, int x, int y) {
    if (key == 'a' ) {
        dir = 0;
    }
    if (key == 'd') {
        dir = 0;
    }
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



void fighter_ship(int dir) {//combine rotate into single if else block
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
    GLUquadricObj* sphere = gluNewQuadric();
    gluSphere(sphere, 2.0 * obsSize, 25, 25);
    glPopMatrix();
}



void explosion(float x, float y, int i) {
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(10);
    if (y == obs[i].obsSize*2.0) {
        obs[i].state = true;
        explosions[i].expX = 0;
        explosions[i].expY = 0;
    }
    glBegin(GL_POINTS);
    glVertex3f(obs[i].eX + (1.0 * x), obs[i].eY + (1.0 * y), 0.0);
    glVertex3f(obs[i].eX + (1.5 * x), obs[i].eY + (1.2 * y), 0.0);
    glVertex3f(obs[i].eX + (1.2 * x), obs[i].eY + (0.7 * y), 0.0);
    glVertex3f(obs[i].eX + (0.4 * x), obs[i].eY + (0.2 * y), 0.0);
    glVertex3f(obs[i].eX + (1.1 * x), obs[i].eY + (0.3 * y), 0.0);
    glVertex3f(obs[i].eX + (0.3 * x), obs[i].eY + (1.6 * y), 0.0);
    glVertex3f(obs[i].eX + (0.5 * x), obs[i].eY + (0.7 * y), 0.0);
    glVertex3f(obs[i].eX + (0.64 * x), obs[i].eY + (0.4 * y), 0.0);

    glVertex3f(obs[i].eX + (1.3 * x), obs[i].eY - (1.0 * y), 0.0);
    glVertex3f(obs[i].eX + (0.3 * x), obs[i].eY - (0.2 * y), 0.0);
    glVertex3f(obs[i].eX + (0.5 * x), obs[i].eY - (1.3 * y), 0.0);
    glVertex3f(obs[i].eX + (0.9 * x), obs[i].eY - (0.5 * y), 0.0);
    glVertex3f(obs[i].eX + (1.1 * x), obs[i].eY - (0.8 * y), 0.0);

    glVertex3f(obs[i].eX - (0.8 * x), obs[i].eY - (1.0 * y), 0.0);
    glVertex3f(obs[i].eX - (1.3 * x), obs[i].eY - (0.1 * y), 0.0);
    glVertex3f(obs[i].eX - (1.1 * x), obs[i].eY - (0.6 * y), 0.0);

    glVertex3f(obs[i].eX - (1.0 * x), obs[i].eY + (0.6 * y), 0.0);
    glVertex3f(obs[i].eX - (0.6 * x), obs[i].eY + (0.3 * y), 0.0);
    glVertex3f(obs[i].eX - (1.1 * x), obs[i].eY + (0.2 * y), 0.0);
    glVertex3f(obs[i].eX - (0.35 * x), obs[i].eY + (0.4 * y), 0.0);
    glVertex3f(obs[i].eX - (0.5 * x), obs[i].eY + (1.3 * y), 0.0);
    glEnd();
}



void generate_obs() {
    while (true) {
        if ((!obs[obsVecPoin].renderObs) || obs[obsVecPoin].yObs < -750.0) {
            float xObsChoice[8] = { 0.0,240.0,560.0,-567.0,-100.0,-330.0,-800.0,760.0 };
            float obsSizeChoice[5] = { 20.0,10.0,40.0,30.0,25.0 };
            obs[obsVecPoin].xObs = xObsChoice[rand() % 12];
            obs[obsVecPoin].obsSize = obsSizeChoice[rand() % 5];
            obs[obsVecPoin].renderObs = true;
            obs[obsVecPoin].state = true;
            obs[obsVecPoin].id = obsVecPoin;
            obs[obsVecPoin].obsRadius = 2 * obs[obsVecPoin].obsSize;
            obs[obsVecPoin].x1 = obs[obsVecPoin].xObs - obs[obsVecPoin].obsRadius;
            obs[obsVecPoin].x2 = obs[obsVecPoin].xObs + obs[obsVecPoin].obsRadius;
            obs[obsVecPoin++].yObs = 610.0;
            if (obsVecPoin == maxObstacals) obsVecPoin = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
        for (int x = 0; x < maxObstacals; x++) {
            if (obs[x].renderObs) {
                obs[x].yObs -= (0.09 * obsSpeedFac);
            }
        }
    };
    auto expup = []() {
        for (int x = 0; x < maxExplosions; x++) {
            if (!obs[x].state) {
                explosions[x].expX += 0.5;
                explosions[x].expY += 0.5;
            }
        }
    };
    auto bemup = []() {
        for (int x = 0; x < Beams.size(); x++) {
            if (Beams[x].renderBeam == false)continue;
            if (Beams.size() > x) {
                Beams[x].yBeam += 1.0*beamSpeedFac;
            }
        }
    };
    std::thread th_obs(obsup);
    std::thread th_exp(expup);
    std::thread th_bm(bemup);
    th_obs.join();
    th_exp.join();
    th_bm.join();
}



void collisiondetection_beam_obs() {
    for (int i = 0; i < maxObstacals; i++) {
        for (auto& it : Beams) {
            if ((obs[i].yObs - obs[i].obsRadius) < (it.yBeam + it.yhalsize) && it.renderBeam && obs[i].renderObs) {
                if ((obs[i].x1 < it.xBeam) && (obs[i].x2 > it.xBeam)) {
                    obs[i].renderObs = false;
                    obs[i].state = false;
                    obs[i].eX = obs[i].xObs;
                    obs[i].eY = obs[i].yObs;
                    it.renderBeam = false;
                    it.yBeam = -100000;
                    break;
                }
            }
        }
    }
}



void collisiondetection_ship() {
    for (int i = 0; i < maxObstacals; i++) {
        if ((obs[i].yObs - obs[i].obsRadius) < -585 && ((obs[i].yObs + obs[i].obsRadius)>-672) && obs[i].renderObs) {
            if ((68.0+obs[i].obsRadius)>abs(xShip-obs[i].xObs)) {
                obs[i].renderObs = false;
                playerHealth--;
                shipcollision = true;
            }
        }
    }
}


//int fontInitialize() {
//    FT_Library ft;
//    if (FT_Init_FreeType(&ft))
//    {
//        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//        return -1;
//    }
//
//    FT_Face face;
//    if (FT_New_Face(ft, "C:/Windows/Fonts/Arial.ttf", 0, &face))
//    {
//        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//        return -1;
//    }
//
//    FT_Set_Pixel_Sizes(face, 0, 48);
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
//
//    for (unsigned char c = 0; c < 128; c++)
//    {
//        // load character glyph 
//        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//        {
//            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//            continue;
//        }
//        // generate texture
//        unsigned int texture;
//        glGenTextures(1, &texture);
//        glBindTexture(GL_TEXTURE_2D, texture);
//        glTexImage2D(
//            GL_TEXTURE_2D,
//            0,
//            GL_RED,
//            face->glyph->bitmap.width,
//            face->glyph->bitmap.rows,
//            0,
//            GL_RED,
//            GL_UNSIGNED_BYTE,
//            face->glyph->bitmap.buffer
//        );
//        // set texture options
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        // now store character for later use
//        fontProperties character = {
//            texture,
//            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//            face->glyph->advance.x
//        };
//        Characters.insert(std::pair<char, fontProperties>(c, character));
//    }
//
//    FT_Done_Face(face);
//    FT_Done_FreeType(ft);
//
//}



//void RenderText(Shader &s, std::string text, float x, float y, float scale, glm::vec3 color)
//{
//    // activate corresponding render state	
//    /*s.use();*/
//    glUniform3f(glGetUniformLocation(s.ID, "textColor"), color.x, color.y, color.z);
//    glActiveTexture(GL_TEXTURE0);
//    glBindVertexArray(VAO);
//
//    // iterate through all characters
//    std::string::const_iterator c;
//    for (c = text.begin(); c != text.end(); c++)
//    {
//        fontProperties ch = Characters[*c];
//
//        float xpos = x + ch.Bearing.x * scale;
//        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//        float w = ch.Size.x * scale;
//        float h = ch.Size.y * scale;
//        // update VBO for each character
//        float vertices[6][4] = {
//            { xpos,     ypos + h,   0.0f, 0.0f },
//            { xpos,     ypos,       0.0f, 1.0f },
//            { xpos + w, ypos,       1.0f, 1.0f },
//
//            { xpos,     ypos + h,   0.0f, 0.0f },
//            { xpos + w, ypos,       1.0f, 1.0f },
//            { xpos + w, ypos + h,   1.0f, 0.0f }
//        };
//        // render glyph texture over quad
//        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//        // update content of VBO memory
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        // render quad
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
//    }
//    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /*RenderText(fontshader, "This is sample text", 25.0f, 25.0f, 0.2f, glm::vec3(0.5, 0.8f, 0.2f));*/

    if (shipcollision) {
        if (shipnorenderframetime > 0) {
            if (shipnorenderframe > 0) {
                shipnorenderframe--;
            }
            else if (shipnorenderframe > -5) {
                fighter_ship(dir);
                shipnorenderframe--;
            }
            else {
                shipnorenderframe = 5;
                shipnorenderframetime--;
            }
        }
        else {
            shipcollision = false;
            shipnorenderframe = 10;
            shipnorenderframetime = 3;
        }
    }
    else {
        fighter_ship(dir);
    }


    for (int x = 0; x < maxObstacals; x++) {
        if (obs[x].renderObs) {
            obstacals(obs[x].xObs, obs[x].yObs, obs[x].obsSize);
        }
        if (!obs[x].state) {
           explosion(explosions[x].expX, explosions[x].expY, x);
        }
    }

    for (int x = 0; x < Beams.size(); x++) {
        if (Beams.size() > x && Beams[x].renderBeam) {
            plasmaBeam(Beams[x].xBeam, Beams[x].yBeam);
        }
    }

    collisiondetection_beam_obs();
    collisiondetection_ship();
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
    glewInit();
    init();
    glEnable(GL_DEPTH_TEST);
   /* glEnable(GL_BLEND);*/
    std::thread th_genObs(generate_obs);
    th_genObs.detach();
    /*fontInitialize();*/
    Beams.resize(100);
    std::cout<<glGetString(GL_VERSION);
    glutDisplayFunc(display);
   /* glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}