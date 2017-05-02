#ifndef PIPE_H
#define PIPE_H

#include <vector>

using namespace std;

//A macro for unused variables
#define UNUSED(param) (void)(param)

//The dimensions to draw within
#define HEIGHT 49
#define WIDTH 79
#define DEPTH 29

//The queue for where to draw and map for checking directions
deque<vector<float>> partCoords;
deque<vector<float>> partCoords2;
int map[WIDTH+2][HEIGHT+2][DEPTH+2];

//Variables to store the color
GLubyte red = 0;
GLubyte green = 0;
GLubyte blue = 0;
deque<vector<GLubyte>> color;

//Set screen dimensions
int screenH = 1080, screenW = 1920;

//Store directions
vector<int> directions;
int direction;
int lastDirection;

//store counter for reset
int resetVal = 0;

void grow(int value);
void reset();
void constructMap();
void processKeys(unsigned char key, int x, int y);
void addColor();

//Opengl functions
void initGL();
void reshape(GLsizei width, GLsizei height);
void display();

#endif //PIPE_H
