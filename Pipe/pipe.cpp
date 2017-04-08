#include <ctime>
#include <deque>
#include <GL/glut.h>
#include <unistd.h>
#include <iostream>
using namespace std;

// A macro for unused variables (to bypass those pesky G++ warnings)
#define UNUSED(param) (void)(param)

char title[] = "OpenGL Pipe";

float map_half_length = 28.0f;

int direction = 2;
int move_speed = 300;
bool moved = false;
std::deque<std::deque<float> > part_coords;

int growth_stage = 0;
int growth = 2;

void turn();

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // The vertex order is clockwise
    // The side order is front, back, left, right, top, bottom (if applicable)

    // Loop over snake size and draw each part at it's respective coordinates
    for(unsigned int a = 0; a < part_coords.size(); a++){
        glLoadIdentity();
        glTranslatef(part_coords[a][0], part_coords[a][1], -40.0f);
        glColor3f(1.0f, 0.0f, 1.0f);

        glBegin(GL_POLYGON);
            glVertex2d( 1.0f,  1.0f);
            glVertex2d( 1.0f, -1.0f);
            glVertex2d(-1.0f, -1.0f);
            glVertex2d(-1.0f,  1.0f);
        glEnd();
    }

    glutSwapBuffers();
}

int randNum(){
    int new_num = rand() % 50 + 1;
    return new_num;
}

void moveSnake(int new_direction){
    direction = new_direction;

    int last_part = part_coords.size() - 1;
    std::deque<float> new_head = part_coords[last_part];

    float deltaX = 0.0;
    float deltaY = 0.0;
    int snakePart = 0;

    switch (direction)
    {
        case 1:
            deltaY = 2.0;
            snakePart = 1;
        break;
        case 2:
            deltaY = -2.0;
            snakePart = 1;
        break;
        case 3:
            deltaX = 2.0;
            snakePart = 0;
        break;
        case 4:
            deltaX = -2.0;
            snakePart = 0;
        break;
    }

    // Did we slither into ourself?
    for(unsigned int a = 0; a < part_coords.size(); a++){
        if(part_coords[0][0] + deltaX == part_coords[a][0] &&
           part_coords[0][1] + deltaY == part_coords[a][1]){
           turn();
         }
    }

    // Did we slither into a wall?
    if(part_coords[0][snakePart] == map_half_length - 4.0f){
        cout << part_coords[0][snakePart];
        cout << " HIT\n";
        turn();
    }

    new_head[0] = part_coords[0][0] + deltaX;
    new_head[1] = part_coords[0][1] + deltaY;

    part_coords.push_front(new_head);

    if(!growth_stage){
        part_coords.pop_back();
    } else if(growth_stage == growth){
        growth_stage = 0;
    } else {
        growth_stage++;
    }

    glutPostRedisplay();
}

void turn(){
    int new_direction;

    if (direction == 3 || direction == 4){
        new_direction = rand() % 1 + 1;
        moved = true;
        cout << new_direction;
        cout << " new_direction U/D \n";
        moveSnake(new_direction);
    }
    else {
        new_direction = rand() % 1 + 3;
        moved = true;
        cout << new_direction;
        cout << " new_direction L/R \n";
        moveSnake(new_direction);
    }
    glutPostRedisplay();
}

void initGL(){
    glMatrixMode(GL_PROJECTION);
    gluPerspective(75.0f, 1, 0.0f, 35.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void moveSnakeAuto(int value){
    int check = randNum();
    if (check % 7 == 0){
      turn();
    }
    if(!moved){
        UNUSED(value);
        if(direction == 1){
            growth_stage++;
            moveSnake(1);
        } else if(direction == 2){
            growth_stage++;
            moveSnake(2);
        } else if(direction == 3){
            growth_stage++;
            moveSnake(3);
        } else if(direction == 4){
            growth_stage++;
            moveSnake(4);
        }
    } else {
        moved = false;
    }
    glutTimerFunc(move_speed, moveSnakeAuto, 0);
}

void reshape(GLsizei width, GLsizei height){
    UNUSED(width);
    UNUSED(height);

    // Make the window non-resizable so we don't have to worry about size changes
    glutReshapeWindow(600, 600);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    glutCreateWindow(title);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(move_speed, moveSnakeAuto, 0);

    int initSize = 3;

    // Specify the coordinates to each part of the snake
    for(int a = 1; a <= initSize; a++){
        std::deque<float> row;
        row.push_back(0.0f);
        row.push_back((map_half_length + 2.0f + (initSize * 2)) - (a * 2));

        part_coords.push_front(row);
    }

    srand(time(NULL));

    initGL();
    glutMainLoop();

    return 0;
}
