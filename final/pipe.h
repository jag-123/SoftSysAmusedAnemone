#ifndef PIPE_H
#define PIPE_H

#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

// A macro for unused variables (to bypass those pesky G++ warnings)
#define UNUSED(param) (void)(param)
#define HEIGHT 49
#define WIDTH 79
#define DEPTH 29

deque<vector<float>> part_coords;
deque<vector<float>> part_coords2;
vector<int> directions;
int map[WIDTH+2][HEIGHT+2][DEPTH+2];
int map2[WIDTH+2][HEIGHT+2][DEPTH+2];
int i = 0;


GLubyte red = 0;
GLubyte green = 0;
GLubyte blue = 0;

deque<vector<GLubyte>> color;

int x, y, z;
int screenH, screenW;

const char *title;
float map_half_length ;
int direction;
int move_speed;
int last_direction;
int reset_val = 0;

void grow(int value);
void reset();
void constructMap();
void processKeys(unsigned char key, int x, int y);
void processSpecial(int key, int x, int y);
void addColor();

//Opengl functions
void initGL();
void reshape(GLsizei width, GLsizei height);
void display();

#endif //PIPE_H
