// CS 445/545 Prog 3 for Colby McClure

// Requrired libraries for the program
#include <GL/glew.h>
#include <iostream>
#include <GL/freeglut.h> 
#include "OpenGL445Setup-jan24.h"
#include <cmath> 
using namespace std; 

/*****************************************************************************************

Author: Colby McClure
Program: CS 445 Program 3
Architecture Statement: when the program first starts, the display event handler, 
'display_func', will be called all of the objects and text will be drawn on the screen,
including the diamond, the floor, the notch, the fuel text, fuel number, and the 
beginning text prompting the user to hit one of the keys to start the game. I have 
decided to incorporate bools to keep track of the game state, including if the game
has started, what gravity is being used, if the game is over, and if the game has been
won. I have also decided to use a global variable to keep track of the fuel amount. 
When the user hits 'E' or 'M' to start the game, the keyboard event handler, 
'keyboardInput', will be called and the game state will be updated using the global
bools. Depending on whether the user has hit 'E' or 'M', the 'earthGravity' 
or 'moonGravity' bools will be set to true. Depending on which bool is true, the timer
event handler, 'diamondDrop', will apply the correct gravity to the diamond using the 
formula taught in class. Speaking of the timer event handler, it will be called when the
user starts the game with 'E' or 'M' and will apply gravity to the diamond until it reaches 
the bottom of the screen. While gravity is being applied to the object, the user has the 
choice to press several keys to move the diamond left, right, or up. If the user presses
any of these keys, the keyboard event handler will be called and the diamond will move 
accordingly on the screen while the gravity is still applied. But within the keyboard
event handler, if the user presses any of the movement keys, it first checks the game state.
If the game is not over and the game has started, then the diamond will move accordingly
based on what movement control was pressed. If the game has not started or the game is over,
then the diamond will not move. If the user presses the 'U' key, then the diamond will move
up and the fuel will decrease. Regarding the fuel, I used a simple technique to display the
fuel count on the screen. I used the modulus operator to get the last digit of the fuel and
then added the ASCII value of '0' to get the character value of the last digit. I then 
divided the fuel by 10 to get the second digit and repeated the process to get the first 
digit. The game ends when the diamond lands on the floor or in the notch. My timer event 
handler 'diamondDrop' checks if the diamond has landed in the notch or not. If it has, then
change the game state to be won and display the winning screen while also automatically
fitting the diamond into the notch. If the diamond has not landed in the notch, then the
game state will be set to be over and the diamond will stop moving. The game will also end
and the user will not be able to move the diamond. Using the game state bools, I have been
able to keep track of when everything happens and draw accordingly. With these global
bools, I have been able to block things from being drawn in the display event handler.
This technique also can be used to translate the diamond to the winning position.
Last thing to note, in order to get the specific scaling factor of the diamond, I had to 
come up with a formula since the diamond is a wire octahedron. I used the formula,
25 * (sqrt(2) / 2), to get the correct scaling factor. I believe that this formula can 
get all line segments that make up the octahedron to be the correct length. To calculate
the gravity, I had to use the same formula we learned in class, but I had to alter how 
much the time gets incremented along with the call of the timer event handler so I could
meet the requirements of redrawing the animation 15 times per second. The values I chose 
for the timer event handler and the time step increment were based around that specific
requirement.

*****************************************************************************************/

// To compile and link the code: g++ mcclurePgm3.cpp -o mcclurePgm3.exe -Wall -lGL -lGLU -lglut -lGLEW 
// In case WSL can't run executable: export MESA_GL_VERSION_OVERRIDE=4.5

// Needed global variables for the program
bool gameStart = false;
bool earthGravity = false;
bool moonGravity = false; 
bool gameOver = false;
bool gameWin = false; 

// More needed global variables for the program
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

// This function will draw the amount of fuel left on the screen using characters 
void fuelNumText() {
    
    // Instantiate the needed variables for the function
    char firstDigitChar;
    char secondDigitChar;
    char lastDigitChar;
    int lastDigit;
    int secondDigit;
    int firstDigit;
    int number;

    // Set the number to the fuel amount and get the last digit using modulus 
    number = fuel;
    lastDigit = number % 10;

    // Add the ASCII value to '0' to get the character value of the last digit
    lastDigitChar = lastDigit + '0';

    // Divide the number by 10 to get the second digit
    number = number / 10;

    // Get the second digit of the fuel using modulus 
    secondDigit = number % 10;

    // Add the ASCII value to '0' to get the character value of the second digit
    secondDigitChar = secondDigit + '0';

    // Divide the number by 10 to get the first digit
    number = number / 10;

    // Get the first digit of the fuel and add the ASCII value to '0' to get the character value
    firstDigit = number;
    firstDigitChar = firstDigit + '0';

    // Set the color of the fuel text and place the text cursor
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3i(25, 525, 0);

    // Draw the amount of remaining fuel on the screen
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, firstDigitChar);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, secondDigitChar);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, lastDigitChar); 
}

// This function will draw the text, 'Fuel' on the screen
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

// This function will draw the text, 'YOU WIN' on the screen
void winText() {

    // Set the color of the win text and place the text cursor
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3i(250, 300, 0);

    // Draw the text, 'YOU WIN'
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'U');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
}

// This function will draw a wire octahedron on the but will be viewed as a diamond
void drawDiamond() {
    
    // Set the scale factor in order to get the diamond to the correct size
    float scaleFactor = 25 * (sqrt(2.0) / (2.0)); 
    
    // Set the color of the diamond to be a light blue 
    glColor3f(0.5, 0.8, 9.0);

    // If the game has not been won, have the diamond behave as normal
    // If the game has been won, have the diamond stay in the winning position inside the notch 
    if(gameWin == false) {
        glTranslatef(x_pos, y_pos, -50);
    } else {
        glTranslatef(62, 30, -50);
    }

    // Scale the diamond by the scale factor and draw the wire octahedron
    glScalef(scaleFactor, scaleFactor, scaleFactor);
    glutWireOctahedron();

    // Reset the transformation matrix when done 
    glLoadIdentity();
}

// This function draws the blue 'floor' on the screen that is positioned at the bottom of the screen
void drawFloor() {

    // Set the color to blue and begin drawing the lines
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);

    glVertex3i(0, 8, -50);
    glVertex3i(25, 8, -50);

    glVertex3i(99, 8, -50);
    glVertex3i(600, 8, -50);
    glEnd(); 
}

// This function draws the notch on the bottom left side of the screen in which the diamond is supposed to land in
void drawNotch() {

        // Set the color to white and begin drawing the lines
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

    // If the game has not started, display the 'Press E or M to Start' text
    if(gameStart == false) {
        beginText();
    }

    // If the game has been won, then display the 'YOU WIN' text
    if(gameWin == true) {
        winText();
    }

    // The rest of the drawn objects and text on the screen
    fuelText();
    fuelNumText();
    drawDiamond(); 
    drawFloor();
    drawNotch();

    // Flush the buffer and swap the buffers
    glFlush(); 
}

// This is the timer event handler that handles the gravity of the diamond
void diamondDrop(int val) {

    // If the y position of the diamond is greater than 22, then apply gravity to the diamond
    if(y_pos > 22) {

        // If the gravity is set to earth, then apply the earth gravity to the diamond
        if(earthGravity == true) {
            y_pos = (-16.0 * (gravTime * gravTime)) + (0.0 * gravTime) + 575; 
            gravTime += 0.066;
            glutPostRedisplay();
            glutTimerFunc(66, diamondDrop, 0);
        
        // If the gravity is set to moon, then apply the moon gravity to the diamond
        } else {
            y_pos = (-2.65 * (gravTime * gravTime)) + (0.0 * gravTime) + 575;
            gravTime += 0.066;
            glutPostRedisplay();
            glutTimerFunc(66, diamondDrop, 0);
        }
    
    // If the diamond has landed, then check if the diamond has landed in the notch or not
    } else {

        // If the diamond has landed in the notch, then set the game to be won and display the winning screen
        if(x_pos > 50 && x_pos < 75) {
            gameWin = true; 
            gameOver = true; 
            display_func();

        // If the diamond has not landed in the notch, then set the game to be over stop all animation
        } else {
            gameOver = true;
            display_func();
        }
    }
}

// This is my keyboard event handler function that handles game state and movement  
void keyboardInput(unsigned char key, int x, int y) {

    // If the game has not started yet
    if(gameStart == false) {

        // If the key pressed is 'E' or 'M', then start the game and set the gravity to earth or moon
        if(key == 'E' || key == 'M') {
            gameStart = true; 

            // If the key pressed is 'E', then set the gravity to earth
            if(key == 'E') {
                earthGravity = true;
                moonGravity = false; 
            
            // If the key pressed is 'M', then set the gravity to moon
            } else if(key == 'M') {
                moonGravity = true;
                earthGravity = false; 
            }
            glutPostRedisplay();
        }
    }

    // If the game has started and the game is not over
    if(gameStart == true && gameOver == false) {

        // If the key pressed is 'H', 'J', or 'U', then move the diamond left, right, or up respectively
        if(key == 'H') {
            x_pos -= 4;
            glutPostRedisplay();
        } else if (key == 'J') {
            x_pos += 4;
            glutPostRedisplay();
        } else if (key == 'U') {

            // While there is remaining fuel, move the diamond up and decrease the fuel
            if(fuel > 0) {
                y_pos += 4;
                fuel -= 5; 
                glutPostRedisplay();
            }

        // Else, call the timer function to apply gravity to the diamond
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

	// Start the keyboard and display event handlers along with the main loop
	glutDisplayFunc(display_func);
    glutKeyboardFunc(keyboardInput);
	glutMainLoop();
	return 0;
}