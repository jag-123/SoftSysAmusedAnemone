#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "cylinder.h"

#define PI 3.1415927

int main(int argc, char **argv) {
    /** Initialize glut */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480); //set the window size
    glutCreateWindow("A Cylinder");
    glClearColor(0.0,0.0,0.0,0.8);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop(); //start the main loop. It doesn't return S

    return 0;
}

/*
*draw_cylinder() function draws the cylinder
*takes four params:
*@param1 - radius of the cylinder
*@param2 - height of the cylinder
*@param3 - sets the red color for the cylinder
*@param4 - sets the green color
*@param5 - sets the blue color

To draw a cylinder:
    -Create a tube and add circles at both ends

*/
void draw_cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B){

    GLfloat x  = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.05;
    GLfloat radius = 0.07;

    /** Draw the tube */
    glColor3ub(240,255,14); //sets the color for the tube - R, G, B
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);

            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of the cylinder */
    glColor3ub(152,155,114); //sets the color for the circle - R, G, B
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();

}

/**
*display() function - draws the figure on the screen
*/
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(-0.5,0.0,-8.0); //translates the figure in x, y, z directions
    glRotatef(80, 80.0, 80.0, 80.0); //rotates the cylinder according to the specified values

    //the first two params are for radius and height.
    //The last three are for setting the color of the cylinder
    draw_cylinder(0.04, 1.0, 250, 200, 200);


    glFlush();
}

/*
*params: windows width and height
*Responsible for resizing the window size as specified by the user
*/
void reshape(int width, int height) {
    if (width == 0 || height == 0){
        return;
    }

    //GL_PROJECTION - Applies subsequent matrix operations to the projection matrix stack.
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity — replaces the current matrix with the identity matrix
    glLoadIdentity();
    //gluPerspective zooms in or out the object. Smaller values zooms it in, larger values zooms out
    gluPerspective(10.0, (GLdouble)width/(GLdouble)height,0.5, 20.0);
    glMatrixMode(GL_MODELVIEW); //GL_MODELVIEW- Applies subsequent matrix operations to the modelview matrix stack.
    //glViewport — sets the viewport
    //specifies the lower left corner of the viewport rectangle, in pixels.
    //The initial value is (0,0)
    glViewport(0, 0, width, height); //width and height are the set values for the window width and height
}
