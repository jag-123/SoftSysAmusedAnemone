#ifndef PIPE_H
#define PIPE_H

#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

// A macro for unused variables (to bypass those pesky G++ warnings)
#define UNUSED(param) (void)(param)
#define HEIGHT 29
#define WIDTH 29
#define DEPTH 29

deque<vector<float>> part_coords;
vector<int> directions;
int map[WIDTH+2][HEIGHT+2][DEPTH+2];

GLubyte red = 0;
GLubyte green = 0;
GLubyte blue = 0;

int x, y, z;

const char *title;
float map_half_length ;
int direction;
int move_speed;
int last_direction;

void grow(int value);
void reset();
void constructMap();

//Opengl functions
void initGL();
void reshape(GLsizei width, GLsizei height);
void display();

#endif //PIPE_H
