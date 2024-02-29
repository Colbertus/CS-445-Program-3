// Graphics Pgm 3 for Colby McClure

#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
using namespace std; 

// To compile and link the code: g++ mcclurePgm3.cpp -o mcclurePgm3.exe -Wall -lGL -lGLU -lglut -lGLEW 
// In case WSL can't run executable: export MESA_GL_VERSION_OVERRIDE=4.5

// Set the canvas size to be 600 x 600 
#define canvas_Width 600
#define canvas_Height 600

// Name the canvas 
char canvas_Name[] = "Colby McClure Diamond Drop";

void beginText() {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3i(200, 300, 0); 

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

void drawDiamond() {

    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(300, 500, 0);
    glScalef(25, 25, 25);
    glutWireTetrahedron();
    glLoadIdentity();

}

void display_func() {

    // Set the background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    beginText(); 
    drawDiamond(); 
    glFlush(); 
}

// This is my driver function 
int main(int argc, char ** argv) {

	// Initiate glut
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	// Start the keyboard and display function along with the loop
	glutDisplayFunc(display_func);
	glutMainLoop();
	return 0;
}