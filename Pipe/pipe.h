#ifndef PIPE_H
#define PIPE_H

#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

// A macro for unused variables (to bypass those pesky G++ warnings)
#define UNUSED(param) (void)(param)
#define HEIGHT 59
#define WIDTH 59
#define DEPTH 59

deque<deque<deque<float>>> part_coords;
vector<int> directions;
int map[WIDTH+2][HEIGHT+2][DEPTH+2];

GLubyte red;
GLubyte green;
GLubyte blue;

const char *title;
float map_half_length ;
int direction;
int move_speed;
bool moved;
int growth_stage;
int growth;
int last_direction;

void grow(int value);
void reset();
void constructMap();
void printMap();

//Opengl functions
void initGL();
void reshape(GLsizei width, GLsizei height);
void display();

#endif //PIPE_H
