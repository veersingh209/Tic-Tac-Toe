#include "Rectangle.h"

//openGl stuff
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

//Pi
#include <cmath>

//Default Constructor
Rectangle::Rectangle(){
    xCoordinate = 0.0;
    yCoordinate = 0.0;
    width = 0.0;
    hight = 0.0;
    isOccupied = false;
    shape = empty;
}

//Constructor
Rectangle::Rectangle(float xCoordinate, float yCoordinate, float width, float hight){
    this->xCoordinate = xCoordinate;
    this->yCoordinate = yCoordinate;
    this->width = width;
    this->hight = hight;
    shape = empty;
}


bool Rectangle::contains(float mx, float my){
    return mx >= xCoordinate && mx <= xCoordinate + width && my <= yCoordinate && my >= yCoordinate - hight;
}



void Rectangle::draw(){
    glLineWidth(5.0);
    //check if x
    if(shape == xcross){
        glColor3f(1.0, 0.0, 0.0);
        //Draws Xs to screen
        glBegin(GL_LINES);
        //Top Left to Bottom Right (\)
        glVertex2f(xCoordinate + 0.1, yCoordinate - 0.1);
        glVertex2f(xCoordinate + width-0.1, yCoordinate - hight + 0.1);
        
        //Top Right to Bottom Left (/)
        glVertex2f(xCoordinate + width - 0.1, yCoordinate - 0.1);
        glVertex2f(xCoordinate + 0.1, yCoordinate - hight + 0.1);
        
        glEnd();
    }
    //check is cirlce
    if(shape == circle){
        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        
        float inc = 0.1;
        
        for(float theta = 0; theta < 2*M_PI; theta += inc){
            glVertex2f((width/2-0.1)*cos(theta)+xCoordinate+(width/2), (width/2-0.1)*sin(theta) + yCoordinate - hight/2);
            glVertex2f((width/2-0.1)*cos(theta+inc)+xCoordinate+(width/2), (width/2-0.1)*sin(theta+inc) + yCoordinate - hight/2);
        }
        
        glEnd();
    }
    
    glColor3f(1.0, 1.0, 1.0);
    //Draws rectangle to screen
    glBegin(GL_POLYGON);
    //Top Left
    glVertex2f(xCoordinate, yCoordinate);
    //Top Right
    glVertex2f(xCoordinate + hight, yCoordinate);
    //Bottom Right
    glVertex2f(xCoordinate + hight, yCoordinate - hight);
    //Bottom Left
    glVertex2f(xCoordinate, yCoordinate - hight);
    
    glEnd();
}

