#ifndef PIPE_H
#define PIPE_H

#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

// A macro for unused variables
#define UNUSED(param) (void)(param)

// The dimensions to draw within
#define HEIGHT 49
#define WIDTH 79
#define DEPTH 29

// The queue for where to draw and map for checking directions
deque<vector<float>> part_coords;
deque<vector<float>> part_coords2;
int map[WIDTH+2][HEIGHT+2][DEPTH+2];
int map2[WIDTH+2][HEIGHT+2][DEPTH+2];

// Variables to store the color
GLubyte red = 0;
GLubyte green = 0;
GLubyte blue = 0;

deque<vector<GLubyte>> color;

int x, y, z;
int screenH, screenW;
vector<int> directions;

const char *title;
int direction;
int move_speed;
int last_direction;
int reset_val = 0;

void grow(int value);
void reset();
void constructMap();
void processKeys(unsigned char key, int x, int y);
void processSpecial(int key, int x, int y);

//Opengl functions
void initGL();
void reshape(GLsizei width, GLsizei height);
void display();

#endif //PIPE_H
