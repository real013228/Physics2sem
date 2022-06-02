#include <iostream>
#include <GL/glut.h>
#include <ctime>
#define END 800
#define BEGINOFCAR -400
#define CRUSHPLACE 400
/*
    Vx = Vcosa;
    Vy = Vsina - gt;
    x = Vx * t;
    y = gt^2/2;

    ] t = 0:
        Vx = Vcar = 60;
        Vy = 0;

 */

void reZero();
void display();
void reshape(int, int);
void init();
void timer(int);
double xPosCar = -10;
double xPosDriver = -10;
double yPosDriver = 20;
double carSpeedX = 6;
double driverSpeedY = 0;
double driverSpeedX = 6;
int crashed = 1;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(1080, 720);

    glutCreateWindow("car and driver");
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
    //CAR
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.2);
        glVertex2d(CRUSHPLACE + BEGINOFCAR + 35, 20);
        glVertex2d(CRUSHPLACE + BEGINOFCAR + 45, 20);
        glVertex2d(CRUSHPLACE + BEGINOFCAR + 45, 0);
        glVertex2d(CRUSHPLACE + BEGINOFCAR + 35, 0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0,0,0.7);
        glVertex2d(xPosCar + BEGINOFCAR, 30);
        glVertex2d(xPosCar + BEGINOFCAR, 0);
        glVertex2d(xPosCar + BEGINOFCAR + 30, 0);
        glVertex2d(xPosCar + BEGINOFCAR + 30, 30);
    glEnd();    
    //DRIVER
    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
        glVertex2d(xPosDriver + BEGINOFCAR + 15, yPosDriver);
        glVertex2d(xPosDriver + BEGINOFCAR + 15, yPosDriver - 10);
        glVertex2d(xPosDriver + BEGINOFCAR + 20, yPosDriver - 10);
        glVertex2d(xPosDriver + BEGINOFCAR + 20, yPosDriver);
    glEnd();
    //ROAD
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex2d(-1000, 0);
    glVertex2d(-1000, -5);
    glVertex2d(1000, -5);
    glVertex2d(1000, 0);

    glEnd();
    glutSwapBuffers();
}

void timer(int) {
    srand(time(0));
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
    switch (crashed) {
        case 1:
            if (xPosCar < CRUSHPLACE) {
                xPosDriver += 6;
                xPosCar += 6;
            } else {
                crashed = -2;
            }
            break;
        //without airbag and safety belt
        case -1:
            if(xPosDriver < END && driverSpeedX != 0) {
                if(yPosDriver > 0) {
                    yPosDriver -= driverSpeedY;
                } else {

                }
                driverSpeedY += 1.5;
                xPosDriver += driverSpeedX;
                if(driverSpeedX > 0) {
                    driverSpeedX -= 0.1;
                } else {
                    driverSpeedX = 0;
                }
            } else {
                crashed = 0;
            }
            break;
        //with airbag or safety belt
        case -2:
            if (carSpeedX > 0) {
                int lifeProbability = rand() % 10;
                if(lifeProbability >= 7) {
                    crashed = 0;
                } else {
                    crashed = -1;
                }
            }
            break;
        case 0:
            reZero();
            break;
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
    glMatrixMode(GL_MODELVIEW);
}

void reZero() {
    crashed = 1;
    xPosCar = -10;
    xPosDriver = -10;
    yPosDriver = 20;
    carSpeedX = 6;
    driverSpeedY = 0;
    driverSpeedX = 6;
}


