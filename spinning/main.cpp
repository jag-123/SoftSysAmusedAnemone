#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "main.h"


int main(int argc, char **argv){

	// Init glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(320,320);
	glutCreateWindow("Hello");

	// Set display function
	glutDisplayFunc(render);

	// Set window reshape function
	glutReshapeFunc(changeSize);

	// Set the idle function
	glutIdleFunc(render);

	// start the main loop
	glutMainLoop();

	return 0;
}

void render(void){
	/*
		Renders the squares and changes the angles
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(	0.0f, 0.0f, 10.0f,
			0.0f, 0.0f,  0.0f,
			0.0f, 1.0f,  0.0f);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);	

	angle += 5.0f;

	glColor3f(.1, .3, .7);
	glBegin(GL_QUADS);
		glVertex3f( -a, -a, 0.0f);
		glVertex3f( -a, -b, 0.0f);
		glVertex3f( -b, -b, 0.0f);
		glVertex3f( -b, -a, 0.0f);
	glEnd();

	glColor3f(.1, .9, .2);
	glBegin(GL_QUADS);
		glVertex3f( a, a, 0.0f);
		glVertex3f( a, b, 0.0f);
		glVertex3f( b, b, 0.0f);
		glVertex3f( b, a, 0.0f);
	glEnd();

	glColor3f(.1, .8, .7);
	glBegin(GL_QUADS);
		glVertex3f( -a, a, 0.0f);
		glVertex3f( -a, b, 0.0f);
		glVertex3f( -b, b, 0.0f);
		glVertex3f( -b, a, 0.0f);
	glEnd();

	glColor3f(.7, .3, .1);
	glBegin(GL_QUADS);
		glVertex3f( a, -a, 0.0f);
		glVertex3f( a, -b, 0.0f);
		glVertex3f( b, -b, 0.0f);
		glVertex3f( b, -a, 0.0f);
	glEnd();

	glutSwapBuffers();
}

void changeSize(int w, int h){
	if(h == 0){
		h = 1;
	}

	float ratio = 1.0 *(w/h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glViewport(0,0,w,h);
	gluPerspective(45,ratio,1,1000);

	glMatrixMode(GL_MODELVIEW);
}