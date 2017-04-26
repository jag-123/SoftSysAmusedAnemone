#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define UNUSED(param) (void)(param)

GLUquadricObj *quadObj;

void display(){
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();

  float an;
  float SINan_3;
  float COSan_3;

  glBegin(GL_QUAD_STRIP);
  for (an = 0.0; an <= 2.0 * M_PI; an += M_PI / 12.0) {
          glNormal3f((COSan_3 = cos(an) / 3.0), (SINan_3 = sin(an) / 3.0), 0.0);
          glVertex3f(COSan_3, SINan_3, 0.333333);
          glVertex3f(COSan_3, SINan_3, -0.333333);
  }
  glEnd();

  glPopMatrix();
}

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);

  quadObj = gluNewQuadric();
  gluQuadricDrawStyle(quadObj, (GLenum) GLU_FILL);
  gluSphere(quadObj, 3, 16, 16);
  gluDeleteQuadric(quadObj);
}

int main(int argc, char **argv) {
    /** Initialize glut */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("A Pipe");
    glutDisplayFunc(display);
    // glutReshapeFunc(reshape);

    init();

    glutMainLoop(); //start the main loop

    return 0;
}
