#include <ctime>
#include <deque>
#include <GL/glut.h>
#include <unistd.h>

// A macro for unused variables (to bypass those pesky G++ warnings)
#define UNUSED(param) (void)(param)

// Snake direction macros
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

char title[] = "OpenGL Snake";

float map_half_length = 30.0f;

int direction = DOWN;
int move_speed = 100;
bool moved = false;
std::deque< std::deque<float> > part_coords;

bool food_available = false;
int food_coords[2];

int growth_stage = 0;
int growth = 2;

void spawnFood(){
    if(!food_available){
        while(true){
            bool collides = false;

            // Produce a temporary random coordinate
            int temp_food_coords[2] = { food_coords[0] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length,
                                        food_coords[1] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length };

            // Does it collide with the snake?
            for(unsigned int a = 0; a < part_coords.size(); a++){
                if(temp_food_coords[0] == part_coords[a][0] &&
                   temp_food_coords[1] == part_coords[a][1]){
                    collides = true;
                }
            }

            // If it doesn't collide with the snake, then make it the real food coordinates
            if(collides == false){
                food_coords[0] = temp_food_coords[0];
                food_coords[1] = temp_food_coords[1];

                food_available = true;

                break;
            }
        }
    }

    glLoadIdentity();
    glTranslatef(food_coords[0], food_coords[1], -40.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2d( 1.0f,  1.0f);
        glVertex2d( 1.0f, -1.0f);
        glVertex2d(-1.0f, -1.0f);
        glVertex2d(-1.0f,  1.0f);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // The vertex order is clockwise
    // The side order is front, back, left, right, top, bottom (if applicable)

    // Loop over snake size and draw each part at it's respective coordinates
    for(unsigned int a = 0; a < part_coords.size(); a++){
        glLoadIdentity();
        glTranslatef(part_coords[a][0], part_coords[a][1], -40.0f);
        glColor3f(0.0f, 1.0f, 0.0f);

        glBegin(GL_POLYGON);
            glVertex2d( 1.0f,  1.0f);
            glVertex2d( 1.0f, -1.0f);
            glVertex2d(-1.0f, -1.0f);
            glVertex2d(-1.0f,  1.0f);
        glEnd();
    }

    spawnFood();

    glutSwapBuffers();
}

void moveSnake(int new_direction){
    direction = new_direction;

    int last_part = part_coords.size() - 1;
    std::deque<float> new_head = part_coords[last_part];

    if(direction == UP){
        // Did we slither into ourself?
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(part_coords[0][0]        == part_coords[a][0] &&
               part_coords[0][1] + 2.0f == part_coords[a][1]){
                exit(0);
            }
        }

        // Did we slither into a wall?
        if(part_coords[0][1] == map_half_length){
            exit(0);
        }

        // Did we get food?
        if(part_coords[0][0]        == food_coords[0] &&
           part_coords[0][1] + 2.0f == food_coords[1]){
            growth_stage++;
            food_available = false;
        }

        new_head[1] = part_coords[0][1] + 2.0f;
    } else if(direction == DOWN){
        // Did we slither into ourself?
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(part_coords[0][0]        == part_coords[a][0] &&
               part_coords[0][1] - 2.0f == part_coords[a][1]){
                exit(0);
            }
        }

        // Did we slither into a wall?
        if(part_coords[0][1] == -map_half_length){
            exit(0);
        }

        // Did we get food?
        if(part_coords[0][0]        == food_coords[0] &&
           part_coords[0][1] - 2.0f == food_coords[1]){
            growth_stage++;
            food_available = false;
        }

        new_head[1] = part_coords[0][1] - 2.0f;
    } else {
        new_head[1] = part_coords[0][1];
    }

    if(direction == LEFT){
        // Did we slither into ourself?
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(part_coords[0][0] - 2.0f == part_coords[a][0] &&
               part_coords[0][1]        == part_coords[a][1]){
                exit(0);
            }
        }

        // Did we slither into a wall?
        if(part_coords[0][0] == -map_half_length){
            exit(0);
        }

        // Did we get food?
        if(part_coords[0][0] - 2.0f == food_coords[0] &&
           part_coords[0][1]        == food_coords[1]){
            growth_stage++;
            food_available = false;
        }

        new_head[0] = part_coords[0][0] - 2.0f;
    } else if(direction == RIGHT){
        // Did we slither into ourself?
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(part_coords[0][0] + 2.0f == part_coords[a][0] &&
               part_coords[0][1]        == part_coords[a][1]){
                exit(0);
            }
        }

        // Did we slither into a wall?
        if(part_coords[0][0] == map_half_length){
            exit(0);
        }

        // Did we get food?
        if(part_coords[0][0] + 2.0f == food_coords[0] &&
           part_coords[0][1]        == food_coords[1]){
            growth_stage++;
            food_available = false;
        }

        new_head[0] = part_coords[0][0] + 2.0f;
    } else {
        new_head[0] = part_coords[0][0];
    }

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

void keyboard(int key, int x, int y){
    UNUSED(x);
    UNUSED(y);

    switch(key){
        case GLUT_KEY_UP:{
            if(direction == LEFT || direction == RIGHT){
                moved = true;

                moveSnake(UP);
            }

            break;
        }

        case GLUT_KEY_DOWN:{
            if(direction == LEFT || direction == RIGHT){
                moved = true;

                moveSnake(DOWN);
            }

            break;
        }

        case GLUT_KEY_LEFT:{
            if(direction == UP || direction == DOWN){
                moved = true;

                moveSnake(LEFT);
            }

            break;
        }

        case GLUT_KEY_RIGHT:{
            if(direction == UP || direction == DOWN){
                moved = true;

                moveSnake(RIGHT);
            }

            break;
        }
    }

    glutPostRedisplay();
}

void initGL(){
    glMatrixMode(GL_PROJECTION);
    gluPerspective(75.0f, 1, 0.0f, 35.0f);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void moveSnakeAuto(int value){
    if(!moved){
        UNUSED(value);

        if(direction == UP){
            moveSnake(UP);
        } else if(direction == DOWN){
            moveSnake(DOWN);
        } else if(direction == LEFT){
            moveSnake(LEFT);
        } else if(direction == RIGHT){
            moveSnake(RIGHT);
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
    glutSpecialFunc(keyboard);
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
