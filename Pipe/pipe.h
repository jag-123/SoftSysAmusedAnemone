#ifndef PIPE_H
#define PIPE_H

#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

// A macro for unused variables (to bypass those pesky G++ warnings)
#define UNUSED(param) (void)(param)
#define HEIGHT 28
#define WIDTH 40

deque<deque<float> > part_coords;
vector<int> directions;
int map[WIDTH+2][HEIGHT+2];

const char *title;
float map_half_length ;
int direction;
int move_speed;
bool moved;
int growth_stage;
int growth;


void grow(int value);
void reset();
void constructMap();
void turn();
int randNum();
void moveSnake(int new_direction);
void moveSnakeAuto(int value);

//Opengl functions
void initGL();
void reshape(GLsizei width, GLsizei height);
void display();

#endif //PIPE_H