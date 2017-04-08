#include <GL/glut.h>
GLfloat cubeLocale = -3.0f;     // Rotational angle for cube [NEW]
int refreshMills = 15;        // refresh interval in milliseconds [NEW]

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void drawline(float from_x, float from_y, float to_x, float to_y)
{
    // From coordinate position
    glVertex2f(from_x, from_y);

    // To coordinate position
    glVertex2f(to_x, to_y);
}

void drawShape()
{
    // Draw line
    glBegin(GL_QUADS);
    // Right face (x = 1.0f)
    glColor3f(cubeLocale, 0.0f, 0.0f);     // Magenta
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    glEnd();

    cubeLocale+=.1f;
}

/* Called back when timer expired [NEW] */
void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0.0, 4.0, 0.0, 4.0, -1, 1 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw shape one
    glPushMatrix();
    glTranslatef(1.5, 1.5, 0.0);
    drawShape();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("My OpenGL program");
    glutDisplayFunc(render);
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    glutMainLoop();
    return 0;
}
