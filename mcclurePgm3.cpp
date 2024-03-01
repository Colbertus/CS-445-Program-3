// Graphics Pgm 3 for Colby McClure

#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
#include <cmath> 

using namespace std; 

// To compile and link the code: g++ mcclurePgm3.cpp -o mcclurePgm3.exe -Wall -lGL -lGLU -lglut -lGLEW 
// In case WSL can't run executable: export MESA_GL_VERSION_OVERRIDE=4.5

bool gameStart = false;
bool earthGravity = false;
bool moonGravity = false; 
bool gameOver = false;

int fuel = 200; 
int x_pos = 300;
int y_pos = 575;
float gravTime = 0.0; 


// This function will draw the text on the screen, 'Press E or M to Start'
void beginText() {

    // Set the color of the text to white and place the text cursor 
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3i(200, 300, 0); 

    // Draw the text, 'Press E or M to Start'
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'M');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
}

void fuelNumText() {
    char firstDigitChar;
    char secondDigitChar;
    char lastDigitChar;
    int lastDigit;
    int secondDigit;
    int firstDigit;
    int number;

    number = fuel;
    lastDigit = number % 10;
    lastDigitChar = lastDigit + '0';
    number = number / 10;
    secondDigit = number % 10;
    secondDigitChar = secondDigit + '0';
    number = number / 10;
    firstDigit = number;
    firstDigitChar = firstDigit + '0';

    // Set the color of the fuel text and place the text cursor
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3i(25, 525, 0);

    // Draw the amount of fuel left
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, firstDigitChar);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, secondDigitChar);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lastDigitChar); 

}

void fuelText() {

    // Set the color of the fuel text and place the text cursor
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3i(25, 550, 0);

    // Draw the text, 'Fuel'
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'F');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
}

void winText() {

    // Set the color of the win text and place the text cursor
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3i(300, 300, 0);

    // Draw the text, 'YOU WIN'
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'U');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
}

// This function will draw a diamond 
void drawDiamond() {
    
    float scaleFactor = 25 * (sqrt(2.0) / (2.0)); 
    
    glColor3f(0.5, 0.8, 9.0);
    glTranslatef(x_pos, y_pos, -50);
    glScalef(scaleFactor, scaleFactor, scaleFactor);
    glutWireOctahedron();
    glLoadIdentity();

}

void drawFloor() {

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);

    glVertex3i(0, 8, -50);
    glVertex3i(600, 8, -50);
    glEnd(); 
}

void drawNotch() {
    
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
    
        glVertex3i(25, 0, -50);
        glVertex3i(25, 25, -50);

        glVertex3i(25, 25, -50);
        glVertex3i(50, 25, -50);

        glVertex3i(50, 25, -50);
        glVertex3i(62, 13, -50);

        glVertex3i(62, 13, -50);
        glVertex3i(74, 25, -50);

        glVertex3i(74, 25, -50);
        glVertex3i(99, 25, -50);

        glVertex3i(99, 25, -50);
        glVertex3i(99, 0, -50);

        glEnd(); 
    
}

// This is the display function for the program 
void display_func() {

    // Set the background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    if(gameStart == false) {
        beginText();
    }
    fuelText();
    fuelNumText();
    drawDiamond(); 
    drawFloor();
    drawNotch();

    glFlush(); 
}

void diamondDrop(int val) {
    if(y_pos > 38) {
        if(earthGravity == true) {
            y_pos = (-16.0 * (gravTime * gravTime)) + (0.0 * gravTime) + 575; 
            gravTime += 0.066;
            glutPostRedisplay();
            glutTimerFunc(66, diamondDrop, 0);
        } else {
            y_pos = (-2.65 * (gravTime * gravTime)) + (0.0 * gravTime) + 575;
            gravTime += 0.066;
            glutPostRedisplay();
            glutTimerFunc(66, diamondDrop, 0);
        }
    } else {
        gameOver = true;
        display_func(); 
    }
}

// This is my keyboard event handler function that is in charge of starting the game and using the fuel 
void keyboardInput(unsigned char key, int x, int y) {
    if(gameStart == false) {
        if(key == 'E' || key == 'M') {
            gameStart = true; 
            if(key == 'E') {
                earthGravity = true;
                moonGravity = false; 
            } else if(key == 'M') {
                moonGravity = true;
                earthGravity = false; 
            }
            glutPostRedisplay();
        }
    }
    
    if(gameStart == true) {
        if(key == 'H') {
            x_pos -= 4;
        } else if (key == 'J') {
            x_pos += 4;
        } else if (key == 'U') {
            if(fuel > 5) {
                y_pos += 4;
                fuel -= 5; 
            }
        } else {
            glutTimerFunc(66, diamondDrop, 0);
            
        }
    }
    
}

// Set the canvas size to be 600 x 600 
#define canvas_Width 600
#define canvas_Height 600

// Name the canvas 
char canvas_Name[] = "Colby McClure Diamond Drop";

// This is my driver function 
int main(int argc, char ** argv) {

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	// Start the keyboard and display function along with the loop
	glutDisplayFunc(display_func);
    glutKeyboardFunc(keyboardInput);
	glutMainLoop();
	return 0;
}