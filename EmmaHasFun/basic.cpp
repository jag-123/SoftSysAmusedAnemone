/**********************************************************************/
/******************************************/
/* A Very Simple OpenGL Example!          */
/******************************************/

/* this code just creates a window and draws a rectangle in it */

#include <GL/glut.h>

void init(void);
void display(void);

int main (int argc, char **argv)
{
	glutInit(&argc, argv); //initializes the GLUT library
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); /* initializes display mode,
	with double buffered window and RGB color*/
	glutInitWindowSize(250, 250); // creates window
	glutInitWindowPosition(100, 100); // creates window
	glutCreateWindow("My First OpenGL Application"); // creates window
	init();
	glutDisplayFunc(display); /*sets the function GLUT will use to update view*/
	glutMainLoop(); /*actually runs program*/
	return 0;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);/* set the background (clearing) color to
	RGB(0,0,0) -- black */
	glColor3f(0.0, 0.0, 1.0); /*set the foreground color to blue */
	glMatrixMode(GL_PROJECTION); /*Initialize the matrix state */
	glRotatef(-0.5, 0.0, 0.0, 0.0);
	/*matrix mode projection sets up the viewport and clipping boundary*/
	/*matrix mode modelview is used to rotate, translae, and scale objects quickly*/
	glLoadIdentity();
	/*loads identity matrix into current matrix state (in case of projection),
	basically sets everything to 0*/
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0); /*sets up a clipping volume - a
	box in which drawing commands are rendered. Left, right, bottom, top, near, far*/
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //clear window with specified color
	glRectf(-5.0, 5.0, 5.0, -5.0); // draw rectangle
	glutSwapBuffers();
}
