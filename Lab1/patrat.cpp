
#include "glos.h"
#include "gl.h"
#include "glaux.h"
#include <cmath>

#ifdef _WIN32
#include "glut.h"
#else
#include <GLUT/glut.h>
#endif


static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat unghiY = 0;
static GLfloat unghiM = 0;
GLuint textureId1;
GLUquadric* quad;

bool animatieActiva = true;

GLuint incarcaTextura(const char* s)
{
    GLuint textureId = 0;
    AUX_RGBImageRec* pImagineTextura = auxDIBImageLoad(s);

    if (pImagineTextura != NULL)
    {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pImagineTextura->sizeX, pImagineTextura->sizeY,
            0, GL_RGB, GL_UNSIGNED_BYTE, pImagineTextura->data);
    }
    if (pImagineTextura)
    {
        if (pImagineTextura->data) {
            free(pImagineTextura->data);
        }
        free(pImagineTextura);
    }
    return textureId;
}

void myInit() {
    textureId1 = incarcaTextura("parchet.bmp");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);


    GLfloat light_position[] = { 50.0, 50.0, 100.0, 1.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    quad = gluNewQuadric();
}

void CALLBACK MutaStanga() {
    x -= 10;
    animatieActiva = false;
}

void CALLBACK MutaDreapta() {
    x += 10;
    animatieActiva = false;
}

void CALLBACK MutaSus() {
    y += 10;
    animatieActiva = false;
}

void CALLBACK MutaJos() {
    y -= 10;
    animatieActiva = false;
}

void CALLBACK RotesteStanga() {
    unghiY -= 5;
    animatieActiva = false;
}

void CALLBACK RotesteDreapta() {
    unghiY += 5;
    animatieActiva = false;
}

void CALLBACK ManerD() {
    unghiM += 5;
    animatieActiva = false;
}

void CALLBACK ManerS() {
    unghiM -= 5;
    animatieActiva = false;
}

void drawString(const char* str, int x, int y) {
    glRasterPos2i(x, y);

    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}
void CALLBACK display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 100.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glTranslatef(x, y, 0);
    glRotatef(unghiY, 0, 1, 0);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId1);
    glColor3f(1.0, 1.0, 1.0);

    GLfloat wood_mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat wood_mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat wood_mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat wood_mat_shininess[] = { 0.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, wood_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, wood_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wood_mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, wood_mat_shininess);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -10.0, -5.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(50.0, -10.0, -5.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(50.0, -10.0, 5.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-50.0, -10.0, 5.0);

    glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, 0.0, -5.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(50.0, 0.0, -5.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(50.0, 0.0, 5.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-50.0, 0.0, 5.0);

    glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -10.0, -5.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -5.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(50.0, 0.0, -5.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(50.0, -10.0, -5.0);

    glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -10.0, 5.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, 5.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(50.0, 0.0, 5.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(50.0, -10.0, 5.0);

    glTexCoord2f(0.0, 0.0); glVertex3f(-50.0, -10.0, -5.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(-50.0, 0.0, -5.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(-50.0, 0.0, 5.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-50.0, -10.0, 5.0);

    glTexCoord2f(0.0, 0.0); glVertex3f(50.0, -10.0, -5.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(50.0, 0.0, -5.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(50.0, 0.0, 5.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(50.0, -10.0, 5.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef(30.0, 0.0, 0.0);
    glRotatef(unghiM, 0, 1, 0);

    glPushMatrix();
    glRotatef(270, 1, 0, 0);
    gluCylinder(quad, 2.5, 2.5, 50.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 50.0, -15.0);
    gluCylinder(quad, 2.0, 2.0, 30.0, 20, 20);
    glPopMatrix();

    glPopMatrix();

    GLfloat rubber_mat_ambient[] = { 0.02, 0.02, 0.02, 1.0 };
    GLfloat rubber_mat_diffuse[] = { 0.01, 0.01, 0.01, 1.0 };
    GLfloat rubber_mat_specular[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat rubber_mat_shininess[] = { 10.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, rubber_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rubber_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, rubber_mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, rubber_mat_shininess);


    glColor3f(0.0, 0.0, 0.0);


    float wheelOffsetX = 40.0;
    float wheelOffsetY = -12.5;
    float wheelOffsetZ = 7.5;

    glPushMatrix();
    glTranslatef(-wheelOffsetX, wheelOffsetY, -wheelOffsetZ);
    glutSolidTorus(2.5, 5.0, 20, 20);
    glTranslatef(0.0, 0.0, 15.0);
    glutSolidTorus(2.5, 5.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(wheelOffsetX, wheelOffsetY, -wheelOffsetZ);
    glutSolidTorus(2.5, 5.0, 20, 20);
    glTranslatef(0.0, 0.0, 15.0);
    glutSolidTorus(2.5, 5.0, 20, 20);
    glPopMatrix();

    glPopMatrix();

    glFlush();


    glPushMatrix();
    glTranslatef(-25.0, -50.0, 0.0);

    glColor3f(0.0, 0.0, 0.0);
    drawString("Giurgiu Antonia-Roxana", 0, 0);

    glPopMatrix();


    glFlush();
}



void CALLBACK myReshape(GLsizei w, GLsizei h) {
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

void CALLBACK animatie() {
    if (animatieActiva) {
        x += 0.5;
        if (x > 50 || x < -50) {
            x = -x;
        }
        unghiY += 0.5;
        if (unghiY > 180) {
            unghiY -= 180;
        }
    }
    display();
}


int main(int argc, char** argv) {
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH);
    auxInitPosition(0, 0, 800, 600);
    auxInitWindow("O trotineta 3D");
    myInit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);
    auxKeyFunc('a', RotesteStanga);
    auxKeyFunc('z', RotesteDreapta);
    auxKeyFunc('w', ManerD);
    auxKeyFunc('s', ManerS);
    auxReshapeFunc(myReshape);
    auxIdleFunc(animatie);
    auxMainLoop(display);
    return 0;
}