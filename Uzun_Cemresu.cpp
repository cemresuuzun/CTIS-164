/*
CTIS 164 HOMEWORK 1
Student: Cemresu Uzun
Student ID: 22103968

*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <glutlibrary/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT  800

#define TIMER_PERIOD    61 // Period for Timer
#define TIMER_ON         1 // 0:disable, 1:enable

// Modes to move and stop
#define MOVE             1
#define STOP             0

/* Global Variables of my Program */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // Window width and height
double Cloud1, Cloud2;     //Clouds
int mousex, mousey;        // Mouse pointer position
int xCoorShape, yCoorShape;     // Shape locations
int mode = STOP;         
bool Timer = false;         // timer
int shapeCnt = 0;          // Shape count
int r = 0;


typedef struct {
    int cnt,                //Count
        sx, sy;           // Shape Coordinates
}shape_t;

shape_t Shape[10];

//circle is centered at (x,y) with a radius r
void circle(int x, int y, int r)
{
#define PI 3.14150
    float angle;

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

void displayBackground() {
    
    // SKY
    glColor3ub(200, 200, 500);
    glBegin(GL_QUADS);
    glVertex2f(-500, 550);
    glVertex2f(500, 550);
    glColor3ub(400, 0, 50);
    glVertex2f(500, -300);
    glVertex2f(-500, -300);
    glEnd();

    //SUN
    glColor3ub(254, 247, 10);
    circle(330, 285, 90);
    
    // SEA
    glColor3ub(28, 41, 251);
    glRectf(-500, -50, 500, -400);
    
    if (100 + Cloud1 > 283)
        Cloud1 = -310;
    if (100 + Cloud2 > 283)
        Cloud2 = -310;

    // CLOUDS
    glColor3ub(250, 218, 252);
    circle(-280 + Cloud1, 220, 46);
    circle(-280 + Cloud1, 180, 46);
    circle(-220 + Cloud1, 200, 46);
    circle(-340 + Cloud1, 200, 46);

    glColor3ub(218, 246, 252);
    circle(160 + Cloud2, 270, 55);
    circle(160 + Cloud2, 210, 55);
    circle(100 + Cloud2, 240, 55);
    circle(220 + Cloud2, 240, 55);  

    //Fish 1 Body
    glBegin(GL_QUADS);
    glColor3ub(160, 115, 245);
    glVertex2f(-60, -200);
    glVertex2f(-90, -220);
    glVertex2f(-140, -200);
    glVertex2f(-90, -180);
    glEnd();
    //Fish 1 Tail
    glBegin(GL_POLYGON);
    glColor3ub(151, 45, 245);
    glVertex2f(-140, -200);
    glVertex2f(-160, -180);
    glVertex2f(-160, -220);
    glEnd();
    //Fish 1 Eye
    glColor3ub(251, 28, 143);
    circle(-81, -195, 5);

    vprint(-354, -236, GLUT_BITMAP_HELVETICA_12, "o");
    vprint(-345, -218, GLUT_BITMAP_HELVETICA_12, "o");
    vprint(-52, -177, GLUT_BITMAP_HELVETICA_12, "o");
    vprint(-42, -161, GLUT_BITMAP_HELVETICA_12, "o");


    //Fish 2 Body
    glBegin(GL_QUADS);
    glColor3ub(209, 149, 250);
    glVertex2f(-360, -250);
    glVertex2f(-390, -270);
    glVertex2f(-440, -250);
    glVertex2f(-390, -230);
    glEnd();

    //Fish 2 Tail
    glBegin(GL_POLYGON);
    glColor3ub(199, 0, 57);
    glVertex2f(-440, -250);
    glVertex2f(-460, -230);
    glVertex2f(-460, -270);
    glEnd();

    //Fish 2 Eye
    glColor3ub(249, 127, 169);
    circle(-383, -247, 5);

    //My Name on the Sky
    glColor3ub(199, 0, 57);
    vprint(-265, 289, GLUT_BITMAP_TIMES_ROMAN_24, "C");
    vprint(-214, 340, GLUT_BITMAP_TIMES_ROMAN_24, "E");
    vprint(-169, 289, GLUT_BITMAP_TIMES_ROMAN_24, "M");
    vprint(-119, 340, GLUT_BITMAP_TIMES_ROMAN_24, "R");
    vprint(-84, 293, GLUT_BITMAP_TIMES_ROMAN_24, "E");
    vprint(-45, 336, GLUT_BITMAP_TIMES_ROMAN_24, "S");
    vprint(-5, 295, GLUT_BITMAP_TIMES_ROMAN_24, "U");
    
    // ID Box
    glColor3ub(50, 50, 100);
    glRectf(-500, 400, -300, 300);
    glColor3ub(200, 100, 100);
    glRectf(-490, 390, -290, 290);
    glColor3ub(100, 20, 20);
    vprint(-450, 350, GLUT_BITMAP_9_BY_15, "Cemresu Uzun");
    vprint(-430, 320, GLUT_BITMAP_9_BY_15, "22103968");
}

//Displays my Ships
void displayShip() {
    for (int q = 1; q <= 10; q++) {
        xCoorShape = (Shape + q - 1)->sx;
        yCoorShape = (Shape + q - 1)->sy; 

            //The ship bottom
            glBegin(GL_POLYGON);
            glColor3ub(164, 13, 253);
            glVertex2f(xCoorShape - 100, yCoorShape + 0);
            glVertex2f(xCoorShape + 100, yCoorShape + 0);
            glVertex2f(xCoorShape + 50, yCoorShape - 50);
            glVertex2f(xCoorShape - 50, yCoorShape -50 );
            glEnd(); 
            //Line around ship bottom
            glBegin(GL_LINE_LOOP);
            glColor3ub(215, 123, 249);
            glVertex2f(xCoorShape - 100, yCoorShape + 0);
            glVertex2f(xCoorShape + 100, yCoorShape + 0);
            glVertex2f(xCoorShape + 50, yCoorShape - 50);
            glVertex2f(xCoorShape - 50, yCoorShape - 50);
            glEnd();

            //Upper Part of Ship
            glBegin(GL_POLYGON);
            glColor3ub(215, 123, 249);
            glVertex2f(xCoorShape - 50, yCoorShape + 35);
            glVertex2f(xCoorShape + 50, yCoorShape + 35);
            glVertex2f(xCoorShape + 50, yCoorShape + 0);
            glVertex2f(xCoorShape - 50, yCoorShape + 0);
            glEnd();
            //Line around ship upper part
            glBegin(GL_LINE_LOOP);
            glColor3ub(109, 0, 149);
            glVertex2f(xCoorShape - 50, yCoorShape + 35);
            glVertex2f(xCoorShape + 50, yCoorShape + 35);
            glVertex2f(xCoorShape + 50, yCoorShape + 0);
            glVertex2f(xCoorShape - 50, yCoorShape + 0);
            glEnd();

            //Rectangle window
            glBegin(GL_POLYGON);
            glColor3ub(146, 237, 225);
            glVertex2f(xCoorShape - 30, yCoorShape + 25);
            glVertex2f(xCoorShape + 30, yCoorShape + 25);
            glVertex2f(xCoorShape + 30, yCoorShape + 10);
            glVertex2f(xCoorShape - 30, yCoorShape + 10);
            glEnd();

            //Flag Pole
            glBegin(GL_POLYGON);
            glColor3ub(237, 146, 174);
            glVertex2f(xCoorShape +25, yCoorShape + 35);
            glVertex2f(xCoorShape + 45, yCoorShape + 35);
            glVertex2f(xCoorShape + 45, yCoorShape +85);
            glVertex2f(xCoorShape + 25, yCoorShape +85);
            glEnd();

            //Flag
            glBegin(GL_POLYGON);
            glColor3ub(164, 13, 253);
            glVertex2f(xCoorShape - 25, yCoorShape + 85);
            glVertex2f(xCoorShape + 45, yCoorShape + 125);
            glVertex2f(xCoorShape + 45, yCoorShape + 85);
            glEnd();

            //Circular Windows
            glColor3ub(146, 237, 225);
            circle(xCoorShape - 48, yCoorShape - 22, 13);
            circle(xCoorShape + 53, yCoorShape - 22, 13);
            circle(xCoorShape + 3, yCoorShape - 22, 13);
    }
}

void menu() {
    glColor3ub(50, 70, 400);
    vprint(200, 93, GLUT_BITMAP_9_BY_15, "F1: Start Moving - Stop Moving");  
    glBegin(GL_LINE_LOOP);
    glColor3ub(109, 0, 149);
    glVertex2f(180, 115);
    glVertex2f(180, 80); 
    glVertex2f(480, 80);
    glVertex2f(480, 115);
    glEnd();
}

// Displays onto window using commands
void display() {
    // clear window to black
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    displayBackground();
    menu();
    displayShip();

    glColor3ub(0, 0, 102);
    vprint(380, -380, GLUT_BITMAP_9_BY_15, "(%-3d : %-3d)", mousex, mousey);

    glutSwapBuffers();
}

// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
void onKeyDown(unsigned char key, int x, int y)
{
    // exits when ESC is pressed.
    if (key == 27)
        exit(0);

    // calls display() function to refresh the window
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // calls display() function to refresh the window
    glutPostRedisplay();
}

// Special Keys such as GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN, 
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: 
        up = true; 
        break;
    case GLUT_KEY_DOWN: 
        down = true; 
        break;
    case GLUT_KEY_LEFT: 
        left = true; 
        break;
    case GLUT_KEY_RIGHT: 
        right = true; 
        break;
    }

    if (key == GLUT_KEY_F1) {
        if (mode == STOP) {
            mode = MOVE;
            Timer = true;
        }
        else {
            mode = STOP;
            Timer = false;
        }
    }
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    glutPostRedisplay();
}

void onClick(int button, int stat, int x, int y)
{
    xCoorShape = x - winWidth / 2;
    yCoorShape = winHeight / 2 - y;

    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && shapeCnt < 10 && Timer == false) {
        (*(Shape + r)).cnt= shapeCnt;
        (*(Shape + r)).sx = xCoorShape;
        (*(Shape + r)).sy = yCoorShape;

        shapeCnt++;
        r++;

        if (Shape[shapeCnt].sx > 590) {

            for (int y = 0; y <= 10; y++) {
                Shape[y] = shape_t(); //resets the structure
                shapeCnt = 0;
                r = 0;
            }
        }
    }
    glutPostRedisplay();
}

/* This function is called when the window size changes.
 w : new width of window
 h : new height of the window
*/
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display();
}

void onMoveDown(int x, int y) {
    //calls display function to refresh the window
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    mousex = x - winWidth / 2;
    mousey = winHeight / 2 - y;

    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);

    if (Timer)
        for (int q = 0; q <= 10; q++) {
            Shape[q].sx += 6.1;


        }
    if (Shape[shapeCnt].sx > 800) {
        Timer = false;
    }

    glutPostRedisplay(); 
}
#endif

void Init() {
    // Smoothes shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Barbie Ships");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    glutMouseFunc(onClick);

    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}