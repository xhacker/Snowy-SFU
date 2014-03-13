#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <stdlib.h>
#include <math.h>

#define WHITE       glColor3d(1.0, 1.0, 1.0)
#define MOON        glColor3d(.98, .87, .16)
#define SKY_GRAY    glColor3d(.00, .10, .18)
#define GROUND_GRAY glColor3d(.96, .96, .95)
#define HOUSE_TOP   glColor3d(.69, .51, .36)
#define HOUSE_BODY  glColor3d(.84, .75, .68)
#define GREEN_TREE  glColor3d(.30, .38, .19)
#define BLACK_TREE  glColor3d(.44, .39, .38)

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void resize(int width, int height)
{
    float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ar, ar, -1.0, 1.0, -100.0, 100.0);
}

void background()
{
    // top-left
    SKY_GRAY;
    glPushMatrix();
        glTranslated(-2, 5.7, -6);
        glutSolidSphere(6, 200, 200);
    glPopMatrix();

    // top-right
    SKY_GRAY;
    glPushMatrix();
        glTranslated(2, 5.7, -6);
        glutSolidSphere(6, 200, 200);
    glPopMatrix();
}

void moon()
{
    MOON;
    glPushMatrix();
        glTranslated(0.8, 0.6, -6);
        glutSolidSphere(0.2, 200, 200);
    glPopMatrix();
}

// [-R..R]
float myrand(float R)
{
   return (2 * R * rand()) / RAND_MAX - R;
}

void tree(float x1, float y1, float length1, float angle1, int depth,
          float scale, float angle, float rand_r)
{
    if (depth > 0)
    {
        // draw line segment
        float x2 = x1 + length1 * cos(angle1);
        float y2 = y1 + length1 * sin(angle1);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);

        // recursive calls
        float length2 = length1 * (scale + myrand(rand_r));
        float angle2 = angle1 + angle + myrand(rand_r);
        tree(x2, y2, length2, angle2, depth-1, scale, angle, rand_r);
        length2 = length1 * (scale + myrand(rand_r));
        angle2 = angle1 - angle + myrand(rand_r);
        tree(x2, y2, length2, angle2, depth-1, scale, angle, rand_r);
    }
}

void stars()
{
    for (int i = 0; i < 233 / 2; ++i) {
        if (i % 3 == 0) {
            MOON;
        }
        else {
            WHITE;
        }
        double x = myrand(3);
        double y = myrand(0.5) + 0.5;
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }

    WHITE;
    for (int i = 0; i < 233; ++i) {
        double x = myrand(3);
        double y = myrand(0.25) + 0.75;
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }
}

void blacktree()
{
    BLACK_TREE;
    glBegin(GL_LINES);
    tree(0.55, -0.3, 0.18, 1.5, 7,
         0.9, 0.15, 0.1);
    tree(0.95, -0.4, 0.13, 1.5, 6,
         0.8, 0.2, 0.2);
    glEnd();
}

void greentree()
{
    double x = -1.1;
    double y = 0.45;

    GREEN_TREE;
    glBegin(GL_LINES);
    tree(x - 0.07, y - 0.2, 0.07, 1.5, 6,
         0.9, 0.3, 0.1);
    tree(x + 0.1, y - 0.2, 0.05, 1.5, 6,
         0.9, 0.3, 0.1);
    glEnd();
}

void house()
{
    BLACK_TREE;
    glBegin(GL_LINES);
    tree(-0.65, 0.2, 0.1, 1.5, 5,
         0.9, 0.1, 0.1);
    glEnd();

    double size = 0.8;

    WHITE;
    glPushMatrix();
        glTranslated(-1.2, 0.22, -7);
        glRotatef(10, -1, 1, 0.08);
        glScalef(1.03, 0.08, 1.03);
        glutSolidCube(size);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-0.9, 0.3, -7);
        glRotatef(10, -1, 1, 0.08);
        glScalef(1.03, 0.08, 1.03);
        glutSolidCube(size);
    glPopMatrix();


    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    HOUSE_TOP;
    glPushMatrix();
        glTranslated(-1.2, 0.10, -7);
        glRotatef(10, -1, 1, 0.06);
        glScalef(1, 0.15, 1);
        glutSolidCube(size);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-0.9, 0.2, -7);
        glRotatef(10, -1, 1, 0.06);
        glScalef(1, 0.15, 1);
        glutSolidCube(size);
    glPopMatrix();

    HOUSE_BODY;
    glPushMatrix();
        glTranslated(-1.2, -0.19, -7);
        glRotatef(10, -1, 1, 0.06);
        glScalef(0.9, 0.6, 0.9);
        glutSolidCube(size);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-0.9, -0.1, -7);
        glRotatef(10, -1, 1, 0.06);
        glScalef(0.9, 0.6, 0.9);
        glutSolidCube(size);
    glPopMatrix();

    GROUND_GRAY;
    glPushMatrix();
        glTranslated(-0.55, -2.05, -6);
        glutSolidSphere(1.93, 200, 200);
    glPopMatrix();

    WHITE;
    glPushMatrix();
        glTranslated(-1.05, -2.2, -6);
        glutSolidSphere(2, 200, 200);
    glPopMatrix();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    background();
    greentree();
    moon();
    stars();
    house();
    blacktree();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(960, 640);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);

    glutCreateWindow("Snowy SFU");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glutMainLoop();

    return EXIT_SUCCESS;
}
