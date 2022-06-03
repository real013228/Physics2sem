#include <iostream>
#include <GL/glut.h>
#include <ctime>

void display();
void reshape(int, int);
void init();
void timer(int);
void drawArrow();
void drawDipole();
double angle = 120;
double xLeftDipole = -4;
double xRightDipole = 4;
double yDownDipole = -0.25;
double yUpDipole = 0.25;
double angleSpeed = 2;
double angleSpeedSpeed = 0.1;
double angleSpeedSpeedSpeed = 0.1;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(1080, 720);

    glutCreateWindow("dipole");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000, timer, 0);
    init();
    glutMainLoop();
    return 0;
}

void init() {
    glClearColor(0.6, 0.7, 0.6, 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawArrow();
    drawDipole();
    glutSwapBuffers();
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void drawArrow() {
    for(int i = 0; i < 20; ++i) {
        glBegin(GL_POLYGON);
            glColor3f(0.5, 0.5, 0.5);
            glVertex2d(-10, -10 + i);
            glVertex2d(-10, -9.9 + i);
            glVertex2d(10, -9.9 + i);
            glVertex2d(10, -10 + i);
        glEnd();
        glBegin(GL_TRIANGLES);
            glColor3f(0.5, 0.5, 0.5);
            glVertex2d(9.5, -9.8 + i);
            glVertex2d(10, -9.9 + i);
            glVertex2d(9.5, -10.1 + i);
        glEnd();
    }
}
void drawDipole() {
    glPushMatrix();
    if(int(angle) % 360 < 180) {
        glRotatef(angle, 0, 0, 1);

    } else {
        glRotatef(angle, 0, 0, -1);
    }
    if (angle > 0) {
        angle -= angleSpeed;
        angleSpeed += angleSpeedSpeed;
    } else {
        angle += angleSpeed;
        angleSpeed += angleSpeedSpeed;
    }
    if(angleSpeedSpeed > 0) {
        angleSpeedSpeed -= angleSpeedSpeedSpeed;
    }
    glBegin(GL_POLYGON);
        glColor3f(0.4, 9, 0.5);
        glVertex2d(xLeftDipole, yDownDipole);
        glVertex2d(xLeftDipole, yUpDipole);
        glVertex2d(xRightDipole, yUpDipole);
        glVertex2d(xRightDipole, yDownDipole);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(0, 0, 0.8);
        glVertex2d(xLeftDipole+0.3, yDownDipole-0.1);
        glVertex2d(xLeftDipole+0.3, yUpDipole+0.1);
        glVertex2d(xLeftDipole-0.3, yUpDipole+0.1);
        glVertex2d(xLeftDipole-0.3, yDownDipole-0.1);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(0.8, 0, 0);
        glVertex2d(xRightDipole+0.3, yDownDipole-0.1);
        glVertex2d(xRightDipole+0.3, yUpDipole+0.1);
        glVertex2d(xRightDipole-0.3, yUpDipole+0.1);
        glVertex2d(xRightDipole-0.3, yDownDipole-0.1);
    glEnd();
    glPopMatrix();
}


