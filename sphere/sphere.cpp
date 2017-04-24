#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>


void display(void);
void reshape(int x, int y);
void draw_cylinder(GLfloat an, GLfloat height);


//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading
}

void draw_sphere(){
	glutSolidSphere(.5,10,10);
}

void draw_cylinder(GLfloat an, GLfloat height){
	// glTranslatef(x,y,z);
	// glRotatef(90, 90.0, 90.0, 90.0);
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_QUAD_STRIP);
			GLfloat COSan_3 = 0.0;
			GLfloat SINan_3 = 0.0;
			for (an = 0.0; an <= 2.0 * M_PI; an += M_PI / 12.0) {
							glNormal3f((COSan_3 = cos(an)/3.0), (SINan_3 = sin(an)/3.0), 2.0);
							glVertex3f(COSan_3, SINan_3, height/3);
							glVertex3f(COSan_3, SINan_3, -height/3);
			}
	glEnd();
}

/*
*draw_cylinder() function draws the cylinder
*/
void choose_direction(GLfloat an, GLfloat height){
    int new_num = rand() % 8;
		printf("%d\n", new_num);
    switch (new_num) {
        case 0:
            glRotatef(90, 90.0, 90.0, 90.0);
						draw_cylinder(an, height);
            glTranslatef(0.0,height/3,0.0);
						break;
        case 1:
            glRotatef(90, 90.0, 90.0, 90.0);
						draw_cylinder(an, height);
            glTranslatef(0.0, -height/3,0.0);
						break;
        case 2:
            glRotatef(90, 90.0, 0.0, 90.0);
						draw_cylinder(an, height);
						glTranslatef(0.0, height/3, 0.0);
						break;
        case 3:
            glRotatef(90, 90.0, 0.0, 90.0);
						draw_cylinder(an, height);
						glTranslatef(0.0, -height/3, 0.0);
						break;
        default:
						draw_cylinder(an, height);
						glTranslatef(height/3, 0.0, 0.0);
    }
    draw_sphere();
}




void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    // clear the identity matrix.
    glLoadIdentity();

    glTranslatef(-0.5,0.0,-8.0);
    //rotates the cylinder according to the specified values
    // scaling transfomation
    glScalef(1.0,1.0,1.0);

  	//Add directed light
  	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
  	//Coming from the direction (-1, 0.5, 0.5)
  	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
  	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
  	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    //the first two params are for radius and height.
    //The last three are for setting the color of the cylinder
    choose_direction(0.0, 5);
		// choose_direction(0.0, 5);

    // sawp buffers called because we are using double buffering
   glutSwapBuffers();
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

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutCreateWindow("Solid Sphere");
    initRendering();

    glClearColor(0.0,0.0,0.0,0.8);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
