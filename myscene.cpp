#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <stdlib.h>
#include <math.h>

#define WHITE       glColor3d(1.0, 1.0, 1.0)
#define SKY_GRAY    glColor3d(.94, .94, .92)
#define GROUND_GRAY glColor3d(.96, .96, .95)
#define HOUSE_TOP   glColor3d(.69, .51, .36)
#define HOUSE_BODY  glColor3d(.84, .75, .68)
#define GREEN_TREE  glColor3d(.30, .38, .19)
#define GREEN_BACK  glColor3d(.90, .94, .87)

void resize(int width, int height)
{
    float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ar, ar, -1.0, 1.0, 2.0, 100.0);
}

void background()
{
    // top-left
    SKY_GRAY;
    glPushMatrix();
        glTranslated(-2, 5.7, -6);
        glutSolidSphere(6, 50, 50);
    glPopMatrix();

    // top-right
    SKY_GRAY;
    glPushMatrix();
        glTranslated(2, 5.7, -6);
        glutSolidSphere(6, 50, 50);
    glPopMatrix();

    // GROUND_GRAY;
    // glPushMatrix();
    //     glTranslated(1.55, -4.4, -6);
    //     glutSolidSphere(4, 50, 50);
    // glPopMatrix();

    // WHITE;
    // glPushMatrix();
    //     glTranslated(0.2, -2.8, -6);
    //     glutSolidSphere(2.2, 50, 50);
    // glPopMatrix();
}

void greentree()
{
    double size = 0.12;
    int parts = 7;
    double x = -1.1;
    double y = 0.55;

    GREEN_BACK;
    glPushMatrix();
    glTranslated(x, y, -7);
    glScalef(1.5, 1.5, 1.5);
    glutSolidSphere(size, parts, parts);
    glPopMatrix();

    GREEN_TREE;
    glPushMatrix();
    glTranslated(x, y, -7);
    glutWireSphere(size, parts, parts);
    glPopMatrix();
}

void house()
{
    double size = 0.8;

    WHITE;
    glPushMatrix();
        glTranslated(-0.9, 0.4, -7);
        glRotatef(10, -1, 1, 0.08);
        glScalef(1.05, 0.1, 1.05);
        glutSolidCube(size);
    glPopMatrix();

    HOUSE_TOP;
    glPushMatrix();
        glTranslated(-0.9, 0.3, -7);
        glRotatef(10, -1, 1, 0.06);
        glScalef(1, 0.15, 1);
        glutSolidCube(size);
    glPopMatrix();

    HOUSE_BODY;
    glPushMatrix();
        glTranslated(-0.9, 0.0, -7);
        glRotatef(10, -1, 1, 0.06);
        glScalef(0.9, 0.6, 0.9);
        glutSolidCube(size);
    glPopMatrix();

    GROUND_GRAY;
    glPushMatrix();
        glTranslated(-0.55, -2.05, -6);
        glutSolidSphere(1.93, 50, 50);
    glPopMatrix();

    WHITE;
    glPushMatrix();
        glTranslated(-1.05, -2.2, -6);
        glutSolidSphere(2, 50, 50);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    background();
    greentree();
    house();

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(960, 640);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Snowy SFU");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glutMainLoop();

    return EXIT_SUCCESS;
}
