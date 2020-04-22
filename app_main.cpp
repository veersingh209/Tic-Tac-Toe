#include <iostream>
#include <cmath>
#include <cstdlib>\
//Used to store rectangles
#include <vector>
#include <unistd.h>

#include "Rectangle.h"


//openGl stuff
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

//-----------------------------------------------------------
//-----------------------------------------------------------
//----------------------HOW TO USE---------------------------
// Select game mode via Number 1 Key or Number 2 Key
// 1 for one player
// 2 for two player
// Use mouse to select where you'd like to place X/O
// At game completion use R key or Space key to restart game
//
// Made by Veer Singh
// Supporting code provided by Angelo Kyrilov
// CSE 165
//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------


//Stores mouse x Coordinate
float mx = 0.0;
//Stores mouse y Coordinate
float my = 0.0;
//Check is player one
bool playerOne = true;
//Tracks if game has finished
bool endGame = false;
//Tracks if no mode (0), 1 Player (1) or 2 Player game(2)
int gameMode = 0;
//Winner, X(1), O(2)
int winner = 0;


using namespace std;

// Store the width and height of the window
int width = 640, height = 640;

//Rectangle Vector, to store all the rectangles
vector<Rectangle> rectangleGrid;

void drawChooseModeScreen(float xCoordinate, float yCoordinate){
    
    //display winner
    if(endGame){
        // if Xs win
        if (winner == 1){
            
            //Big X
            glColor3f(1.0, 1.0, 1.0);
            glLineWidth(5.0);
            glBegin(GL_LINES);
            
            glVertex2f(xCoordinate + 0.4, yCoordinate - 0.4);
            glVertex2f(-xCoordinate - 0.4, -yCoordinate + 0.4);
            glVertex2f(-xCoordinate - 0.4 , yCoordinate - 0.4);
            glVertex2f(xCoordinate + 0.4, -yCoordinate + 0.4);
          
            glEnd();
            
            //Red Overlay
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_POLYGON);
            
            glVertex2f(xCoordinate, yCoordinate);
            glVertex2f(-xCoordinate, yCoordinate);
            glVertex2f(-xCoordinate, -yCoordinate);
            glVertex2f(xCoordinate, -yCoordinate);
            
            glEnd();
            
            std::cout<< "X Wins!" << std::endl;
            std::cout<< "Press 'r' or space bar to replay or 'esc' to exit" << std::endl;

        }
        
        //if Os win
        if (winner == 2){
            
            //Big Circle
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINES);
            
            float inc = 0.1;
            float radius = 0.7;
            
            for(float theta = 0; theta < 2*M_PI; theta += inc){
                glVertex2f((radius)*cos(theta), (radius)*sin(theta));
                glVertex2f((radius)*cos(theta+inc), (radius)*sin(theta+inc));
            }
            
            glEnd();
            
            
            //Blue Overlay
            glColor3f(0.0, 0.0, 1.0);
            glBegin(GL_POLYGON);
            
            glVertex2f(xCoordinate, yCoordinate);
            glVertex2f(-xCoordinate, yCoordinate);
            glVertex2f(-xCoordinate, -yCoordinate);
            glVertex2f(xCoordinate, -yCoordinate);
            
            glEnd();
            
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_POLYGON);
            
            glEnd();
            
            std::cout<< "O Wins!" << std::endl;
            std::cout<< "Press 'r' or space bar to replay or 'esc' to exit" << std::endl;
            
        }
        
        //if draw
        if (winner == 3){
            
            //Big X
            glColor3f(1.0, 1.0, 1.0);
            glLineWidth(5.0);
            glBegin(GL_LINES);
            
            glVertex2f(xCoordinate + 0.4, yCoordinate - 0.4);
            glVertex2f(-xCoordinate - 0.4, -yCoordinate + 0.4);
            glVertex2f(-xCoordinate - 0.4 , yCoordinate - 0.4);
            glVertex2f(xCoordinate + 0.4, -yCoordinate + 0.4);
            
            glEnd();
            
            
            //Big Circle
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINES);
            
            float inc = 0.1;
            float radius = 0.7;
            
            for(float theta = 0; theta < 2*M_PI; theta += inc){
                glVertex2f((radius)*cos(theta)+0.0, (radius)*sin(theta));
                glVertex2f((radius)*cos(theta+inc)+0.0, (radius)*sin(theta+inc));
            }
            
            glEnd();
            
            //gray overlay
            glColor3f(0.9, 0.9, 0.9);
            glBegin(GL_POLYGON);
            
            glVertex2f(xCoordinate, yCoordinate);
            glVertex2f(-xCoordinate, yCoordinate);
            glVertex2f(-xCoordinate, -yCoordinate);
            glVertex2f(xCoordinate, -yCoordinate);
            
            glEnd();
            
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_POLYGON);
            
            glEnd();
            
            std::cout<< "Its a draw!" << std::endl;
            std::cout<< "Press 'r' or space bar to replay or 'esc' to exit" << std::endl;
        }
    }
    
    //if mode to slected
    if(gameMode == 0){
        
        //Player Divider Line
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        
        glVertex2f(-0.05, 1.0);
        glVertex2f(0.05, 1.0);
        glVertex2f(0.05, -1.0);
        glVertex2f(-0.05, -1.0);
        
        glEnd();
        
        //One Player sign (#1)
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(10.0);
        glBegin(GL_POLYGON);
        
        glVertex2f(xCoordinate + 0.40, yCoordinate - 0.35);
        glVertex2f(xCoordinate + 0.50, yCoordinate - 0.35);
        glVertex2f(xCoordinate + 0.50, yCoordinate - 1.45);
        glVertex2f(xCoordinate + 0.40, yCoordinate  - 1.45);

        glEnd();
        
        //One Player side
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
    
        glVertex2f(xCoordinate, yCoordinate);
        glVertex2f(xCoordinate + -xCoordinate, yCoordinate);
        glVertex2f(xCoordinate + -xCoordinate, -yCoordinate);
        glVertex2f(xCoordinate, -yCoordinate);
    
        glEnd();
        
        
        //Two Player sign (#2)
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(50.0);
        glBegin(GL_POLYGON);
        
        glVertex2f(xCoordinate + 1.25, yCoordinate - 0.35);
        glVertex2f(xCoordinate + 1.65, yCoordinate - 0.35);
        glVertex2f(xCoordinate + 1.65, yCoordinate - 0.45);
        glVertex2f(xCoordinate + 1.25, yCoordinate - 0.45);
        
        glEnd();
        
        //Two Player sign (#2)
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(50.0);
        glBegin(GL_POLYGON);
        
        glVertex2f(xCoordinate + 1.65, yCoordinate - 0.45);
        glVertex2f(xCoordinate + 1.65, yCoordinate - 0.85);
        glVertex2f(xCoordinate + 1.55, yCoordinate - 0.85);
        glVertex2f(xCoordinate + 1.55, yCoordinate - 0.45);
        
        glEnd();
        
        //Two Player sign (#2)
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(50.0);
        glBegin(GL_POLYGON);
        
        glVertex2f(xCoordinate + 1.65, yCoordinate - 0.85);
        glVertex2f(xCoordinate + 1.25, yCoordinate - 0.85);
        glVertex2f(xCoordinate + 1.25, yCoordinate - 0.95);
        glVertex2f(xCoordinate + 1.65, yCoordinate - 0.95);
        
        glEnd();
        
        
        //Two Player sign (#2)
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(50.0);
        glBegin(GL_POLYGON);
        
        glVertex2f(xCoordinate + 1.25, yCoordinate - 0.95);
        glVertex2f(xCoordinate + 1.25, yCoordinate - 1.45);
        glVertex2f(xCoordinate + 1.35, yCoordinate - 1.45);
        glVertex2f(xCoordinate + 1.35, yCoordinate - 0.95);
        
        glEnd();
        
        //Two Player sign (#2)
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(50.0);
        glBegin(GL_POLYGON);

        glVertex2f(xCoordinate + 1.35, yCoordinate - 1.45);
        glVertex2f(xCoordinate + 1.65, yCoordinate - 1.45);
        glVertex2f(xCoordinate + 1.65, yCoordinate - 1.35);
        glVertex2f(xCoordinate + 1.35, yCoordinate - 1.35);
        
        
        glEnd();

    
        //Two Player side
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
    
        glVertex2f(-xCoordinate, yCoordinate);
        glVertex2f(-xCoordinate, -yCoordinate);
        glVertex2f(xCoordinate - xCoordinate, -yCoordinate);
        glVertex2f(xCoordinate - xCoordinate, yCoordinate);
    
        glEnd();
        
        std::cout<< " " << std::endl;
        std::cout<< "Press '1' for One Player or '2' for Two Player!" << std::endl;
        std::cout<< " " << std::endl;
    
    }
    //if mode selected
    if(gameMode == 1 || gameMode == 2){
        //Draw rectangles, Xs, and Os to screen
        for (int i = 0; i < rectangleGrid.size(); i++){
            rectangleGrid[i].draw();
        }
    }
}

//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);
    
	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    drawChooseModeScreen(-0.95, 0.95);
    
//    //Draw rectangles, Xs, and Os to screen
//    for (int i = 0; i < rectangleGrid.size(); i++){
//        rectangleGrid[i].draw();
//    }

    
	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

void gameRestart(){
    if (endGame){
        for (int i = 0; i < rectangleGrid.size(); i++) {
            rectangleGrid[i].shape = empty;
            rectangleGrid[i].isOccupied = false;
            endGame = false;
            playerOne = true;
            gameMode = 0;
        }
    }
}

//find winner
void checkWinner(vector<Rectangle> rectangleGrid){
    //All X's in first row
    if ( rectangleGrid[0].shape == xcross && rectangleGrid[1].shape == xcross && rectangleGrid[2].shape == xcross ){
        endGame = true;
        winner = 1;
    }
    //All X's in second row
    if ( rectangleGrid[3].shape == xcross && rectangleGrid[4].shape == xcross && rectangleGrid[5].shape == xcross ){
        endGame = true;
        winner = 1;
    }
    //All X's in third row
    if ( rectangleGrid[6].shape == xcross && rectangleGrid[7].shape == xcross && rectangleGrid[8].shape == xcross ){
        endGame = true;
        winner = 1;
    }
    //All X's in first column
    if ( rectangleGrid[0].shape == xcross && rectangleGrid[3].shape == xcross && rectangleGrid[6].shape == xcross ){
        endGame = true;
        winner = 1;
    }
    //All X's in second column
    if ( rectangleGrid[1].shape == xcross && rectangleGrid[4].shape == xcross && rectangleGrid[7].shape == xcross ){
        endGame = true;
        winner = 1;
    }
    //All X's in third column
    if ( rectangleGrid[2].shape == xcross && rectangleGrid[5].shape == xcross && rectangleGrid[8].shape == xcross ){
        endGame = true;
        winner = 1;
    }
    //X's in diagonal (top left to bottom right)
    if ( rectangleGrid[0].shape == xcross && rectangleGrid[4].shape == xcross && rectangleGrid[8].shape == xcross ){
        endGame = true;
        winner = 1;
    }
    //X's in diagonal (top right to bottom left)
    if ( rectangleGrid[2].shape == xcross && rectangleGrid[4].shape == xcross && rectangleGrid[6].shape == xcross){
        endGame = true;
        winner = 1;
    }
    
    
    //All 0's in first row
    if ( rectangleGrid[0].shape == circle && rectangleGrid[1].shape == circle && rectangleGrid[2].shape == circle){
        endGame = true;
        winner = 2;
    }
    //All 0's in second row
    if ( rectangleGrid[3].shape == circle && rectangleGrid[4].shape == circle && rectangleGrid[5].shape == circle){
        endGame = true;
        winner = 2;
    }
    //All 0's in third row
    if ( rectangleGrid[6].shape == circle && rectangleGrid[7].shape == circle && rectangleGrid[8].shape == circle){
        endGame = true;
        winner = 2;
    }
    //All 0's in first row
    if ( rectangleGrid[0].shape == circle && rectangleGrid[3].shape == circle && rectangleGrid[6].shape == circle){
        endGame = true;
        winner = 2;
    }
    //All 0's in second row
    if ( rectangleGrid[1].shape == circle && rectangleGrid[4].shape == circle && rectangleGrid[7].shape == circle){
        endGame = true;
        winner = 2;
    }
    //All 0's in third row
    if ( rectangleGrid[2].shape == circle && rectangleGrid[5].shape == circle && rectangleGrid[8].shape == circle){
        endGame = true;
        winner = 2;
    }
    //0's in diagonal (top left to bottom right)
    if ( rectangleGrid[0].shape == circle && rectangleGrid[4].shape == circle && rectangleGrid[8].shape == circle){
        endGame = true;
        winner = 2;
    }
    //0's in diagonal (top right to bottom left)
    if ( rectangleGrid[2].shape == circle && rectangleGrid[4].shape == circle && rectangleGrid[6].shape == circle){
        endGame = true;
        winner = 2;
    }
    
    //Check for draw
    if(rectangleGrid[0].isOccupied && rectangleGrid[1].isOccupied && rectangleGrid[2].isOccupied && rectangleGrid[3].isOccupied && rectangleGrid[4].isOccupied && rectangleGrid[5].isOccupied && rectangleGrid[6].isOccupied && rectangleGrid[7].isOccupied && rectangleGrid[8].isOccupied){
        endGame = true;
        winner = 3;
    }
}


//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}

void runGame(int b, int s, int x, int y){
    //if mouse is clicked
    if (b == 0){
        //if left click
        if (s == 0){
            //Checks if game finshed
            if(!endGame) {
                for(int i = 0; i < rectangleGrid.size(); i++) {
                    //check if in rectangle
                    if (rectangleGrid[i].contains(mx, my)) {
                        if (rectangleGrid[i].isOccupied == false) {
                            //if playerOnes trun
                            if(playerOne){
                                rectangleGrid[i].shape = xcross;
                            }
                            else {
                                rectangleGrid[i].shape = circle;
                            }
                            //lock rectangle from being re-written
                            rectangleGrid[i].isOccupied = true;
                            //Swtich Players
                            playerOne = !playerOne;
                            //check for winner
                            checkWinner(rectangleGrid);
                            //two player mode
                            if (gameMode == 2 && !endGame){
                                //generate random number
                                int rand();
                                int numb = (rand() % 10);
                                //check if random number is already filled
                                while (rectangleGrid[numb].isOccupied){
                                    numb = (rand() % 10);
                                }
                                //place O
                                for (int i = 0; i < rectangleGrid.size(); i++) {
                                    if (!rectangleGrid[numb].isOccupied){
                                        rectangleGrid[numb].shape = circle;
                                        rectangleGrid[numb].isOccupied = true;
                                        playerOne = !playerOne;
                                        break;
                                    }
                                }
                                //check for winner
                                checkWinner(rectangleGrid);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}

//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	mx = (float)x;
	my = (float)y;

	windowToScene(mx, my);
    
    runGame(b, s, x, y);

    
	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {

	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        //check for esc
        case 27:
            exit(0);
            break;
        case 'r':
            gameRestart();
            break;
        case ' ':
            gameRestart();
            break;
        case '1':
            gameMode = 1;
            break;
        case '2':
            gameMode = 2;
            break;
        default:
            break;
    }

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}


void idle() {

}

int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
    glutCreateWindow("CSE165-Lab2: Tic Tac Toe");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

    
    //Row 1
    //Create top left rectanlge
    rectangleGrid.push_back(Rectangle(-0.95, 0.95, 0.6, 0.6));
    //Create top middle rectangle
    rectangleGrid.push_back(Rectangle(-0.3, 0.95, 0.6, 0.6));
    //Create right rectangle
    rectangleGrid.push_back(Rectangle(0.35, 0.95, 0.6, 0.6));
    
    //Row 2
    //Create top left rectanlge
    rectangleGrid.push_back(Rectangle(-0.95, 0.3, 0.6, 0.6));
    //Create top middle rectangle
    rectangleGrid.push_back(Rectangle(-0.3, 0.3, 0.6, 0.6));
    //Create right rectangle
    rectangleGrid.push_back(Rectangle(0.35, 0.3, 0.6, 0.6));
    
    //Row 3
    //Create top left rectanlge
    rectangleGrid.push_back(Rectangle(-0.95, -0.35, 0.6, 0.6));
    //Create top middle rectangle
    rectangleGrid.push_back(Rectangle(-0.3, -0.35, 0.6, 0.6));
    //Create right rectangle
    rectangleGrid.push_back(Rectangle(0.35, -0.35, 0.6, 0.6));
    
    
	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
    glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);
    
    glutIdleFunc(idle);

	// Start the main loop
	glutMainLoop();
}
