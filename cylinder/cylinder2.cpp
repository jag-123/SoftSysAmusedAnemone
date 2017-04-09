#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
 
GLfloat gAngle = 0.0;
GLUquadricObj *IDquadric;
 
void timer(int value)
{
  const int desiredFPS=120;
  glutTimerFunc(1000/desiredFPS, timer, ++value);
  GLfloat dt = 1./desiredFPS;
 
  //put your specific idle code here
  //... this code will run at desiredFPS
  gAngle += dt*360./2.; //rotate 360 degrees every 8 seconds
  //end your specific idle code here
 
  glutPostRedisplay(); // initiate display() call at desiredFPS rate
}
 
void display() {
  // Will be called at FPS rate, ok to use global values now to rener scene
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
    glTranslatef(0,0,-100);
    glRotatef(gAngle,0.,1.,0.);
    //glutWireCube(20.); //cube of size 20x20x20
    glColor3ub(40,255,14);
    gluCylinder(IDquadric,10.0f,10.0f,20.0f,32,32);

    // glColor3ub(140,255,14);
    // gluDisk(IDquadric,10.0f,10.0f,32,32);
  glPopMatrix();
 
  glutSwapBuffers();
}
 
void cleanupQuadric(void)          // Properly Kill The Window
{
  gluDeleteQuadric(IDquadric);
  printf( "cleanupQuadric completed\n" );
}
 
void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
 
  IDquadric=gluNewQuadric();      // Create A Pointer To The Quadric Object ( NEW )
  gluQuadricNormals(IDquadric, GLU_SMOOTH);  // Create Smooth Normals ( NEW )
  gluQuadricTexture(IDquadric, GL_TRUE);    // Create Texture Coords ( NEW )
  atexit(cleanupQuadric);
 
  GLdouble Vol = 20*1.8;
  GLdouble Left=-Vol;
  GLdouble Right=Vol;
  GLdouble Bottom=-Vol;
  GLdouble Top=Vol;
  GLdouble Near=0; 
  GLdouble Far=2*Vol;
 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(Left, Right, Bottom, Top,  Near, Far);
 
  GLdouble eyeX=0;
  GLdouble eyeY=0;
  GLdouble eyeZ=-100+Vol;
  GLdouble centerX=0;
  GLdouble centerY=0;
  GLdouble centerZ=-100;
  GLdouble upX=0;
  GLdouble upY=1;
  GLdouble upZ=0;
 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX,eyeY,eyeZ,
            centerX,centerY,centerZ,
            upX,upY,upZ);
}
 
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:  // escape key
         exit(0);
         break;
      default:
         break;
   }
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE);
   glutCreateWindow("Rotating Cylinder");
 
   glutTimerFunc(0,timer,0);
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
 
   init();
 
   glutMainLoop();
   return 0;
}