#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

GLfloat xRotated, yRotated, zRotated;
GLdouble radius=1;
#define PI 3.1415927


void display(void);
void reshape(int x, int y);


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutCreateWindow("Solid Sphere");
    glClearColor(0.0,0.0,0.0,0.8);
    xRotated = yRotated = zRotated = 30.0;
    xRotated=43;
    yRotated=50;

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
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


void display(void)
{

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(-0.5,0.0,-8.0);
    //rotates the cylinder according to the specified values
    glRotatef(80, 80.0, 80.0, 80.0);
    // // scaling transfomation
    // glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a sphere.
    glutSolidSphere(radius,20,20);
    // Flush buffers to screen

    //the first two params are for radius and height.
    //The last three are for setting the color of the cylinder
    draw_cylinder(0.04, 1.0, 250, 200, 200);

    glFlush();
    // sawp buffers called because we are using double buffering
   // glutSwapBuffers();
}

void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}
