#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <stdlib.h>

#define WHITE glColor3d(1, 1, 1)
#define SKY_GRAY glColor3d(.94, .94, .92)
#define GROUND_GRAY glColor3d(.96, .96, .95)

void resize(int width, int height)
{
    float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // top-left
    SKY_GRAY;
    glPushMatrix();
        glTranslated(-3, 5.5, -6);
        glutSolidSphere(6, 50, 50);
    glPopMatrix();

    // top-right
    SKY_GRAY;
    glPushMatrix();
        glTranslated(3, 5.5, -6);
        glutSolidSphere(6, 50, 50);
    glPopMatrix();

    GROUND_GRAY;
    glPushMatrix();
        glTranslated(3.5, -7, -6);
        glutSolidSphere(6, 50, 50);
    glPopMatrix();

    WHITE;
    glPushMatrix();
        glTranslated(0.5, -8, -6);
        glutSolidSphere(6, 50, 50);
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
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
