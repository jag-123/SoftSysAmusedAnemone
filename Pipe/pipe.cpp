#include <ctime>
#include <deque>
#include <GL/glut.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "pipe.h"
using namespace std;

int main(int argc, char** argv){

    //Initializing variables
    title = "OpenGL Pipe";
    map_half_length = 14.0f;
    direction = 2;
    move_speed = 30;
    moved = false;
    growth_stage = 0;
    last_direction = 2;

    //Init glut
    glutInit(&argc, argv);

    glutInitWindowSize(600, 600);
    glutCreateWindow(title);


    //Set the glut functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(move_speed, grow, 0);

    red = rand()%255;
    green =rand()%255;
    blue =rand()%255;

    std::deque<float> row;
    int x = rand()%(int)(map_half_length*2);
    row.push_back((float)x);
    int y = rand()%(int)(map_half_length*2);
    row.push_back((float)y);
    part_coords.push_back(row);
    map[x+1][y+1]=1;


    srand(time(NULL));
    constructMap();
    initGL();
    glutMainLoop();

    return 0;
}

void grow(int value){
    /*
        Directions:
        1 - up
        2 - down
        3 - right
        4 - left
    */
    UNUSED(value);

    //Get the last coordinates
    int last_part = part_coords.size() - 1;
    deque<float> new_head = part_coords[last_part];


    if(map[(int)new_head[0]+1][(int)new_head[1]+2]==0){
        directions.push_back(1);
    }
    if(map[(int)new_head[0]+1][(int)new_head[1]]==0){
        directions.push_back(2);
    }
    if(map[(int)new_head[0]+2][(int)new_head[1]+1]==0){
        directions.push_back(3);
    }
    if(map[(int)new_head[0]][(int)new_head[1]+1]==0){
        directions.push_back(4);
    }
    printMap();

    //Reset if no valid directions
    if(directions.empty()){
        reset();
        return;
    }

    for(int n:directions){
        if(n == last_direction){
            for(int i=0; i<10; i++){
                directions.push_back(last_direction);
            }
        }
    }

    // for(int n:directions){
    //     //std::cout<<n<< "  ";
    // }
    //std::cout<<std::endl;

    //Choose direction to move out of valid directions
    int direction = directions.at(rand()%directions.size());

    if(direction==1){
        last_direction = 1;
        new_head[0] = new_head[0];
        new_head[1] = new_head[1]+1;
    }
    else if(direction==2){
        last_direction = 2;
        new_head[0] = new_head[0];
        new_head[1] = new_head[1]-1;
    }
    else if(direction==3){
        last_direction = 3;
        new_head[0] = new_head[0]+1;
        new_head[1] = new_head[1];
    }
    else if(direction==4){
        last_direction = 4;
        new_head[0] = new_head[0]-1;
        new_head[1] = new_head[1];
    }

    //std::cout<<part_coords.size()<<std::endl;

    std::cout<< "x:" << new_head[0] << " y: " << new_head[1] <<std::endl;
    map[(int)new_head[0]+1][(int)new_head[1]+1] = 1;

    //Push the new head onto the coords
    part_coords.push_back(new_head);

    directions.clear();
    glutTimerFunc(move_speed, grow, 0);
}

void reset(){
    std::cout << "RESETING"<<std::endl;
    part_coords.clear();
    constructMap();

    std::deque<float> row;
    int x = rand()%(int)(map_half_length*2);
    row.push_back((float)x);
    int y = rand()%(int)(map_half_length*2);
    row.push_back((float)y);
    map[x+1][y+1]=1;

    part_coords.push_back(row);

    red = rand()%255;
    green =rand()%255;
    blue =rand()%255;

    glutTimerFunc(move_speed, grow, 0);
}

void constructMap(){
    /*
        Constructs the map with walls being 1 and all other space 0
    */
    for(int row=0; row<HEIGHT+2; row++){
        for(int col=0; col<WIDTH+2; col++){
            if(row==0 || col==0){
                map[row][col] = 1;
            }
            else if(row==HEIGHT+1 || col==WIDTH+1){
                map[row][col] = 1;
            }
            else{
                map[row][col] = 0;
            }
        }
    }
}

void printMap(){
    /*
        Prints the map
    */
    for(int row=0; row<HEIGHT+2; row++){
        for(int col=0; col<WIDTH+2; col++){
            std::cout<<map[row][col];
        }
        std::cout<<std::endl;
    }
}

void initGL(){
    glMatrixMode(GL_PROJECTION);
    gluPerspective(75.0f, 1, 0.0f, 35.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void reshape(GLsizei width, GLsizei height){
    UNUSED(width);
    UNUSED(height);

    // Make the window non-resizable so we don't have to worry about size changes
    glutReshapeWindow(600, 600);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    // The vertex order is clockwise
    // The side order is front, back, left, right, top, bottom (if applicable)

    // Loop over snake size and draw each part at it's respective coordinates

    
    for(unsigned int a = 0; a < part_coords.size(); a++){
        glLoadIdentity();
        glTranslatef(part_coords[a][1]-30, -part_coords[a][0]+30, -40.0f);

        glColor3ub(red, green, blue);

        glBegin(GL_POLYGON);
            glVertex2d( 0.5f,  0.5f);
            glVertex2d( 0.5f, -0.5f);
            glVertex2d(-0.5f, -0.5f);
            glVertex2d(-0.5f,  0.5f);
        glEnd();
    }

    glutSwapBuffers();
}