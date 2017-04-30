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
    move_speed = 10;
    last_direction = 2;
    screenW = 1920;
    screenH = 1080;

    //Init glut
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); 

    glutInitWindowSize(screenW, screenH);
    glutCreateWindow(title);
    glutFullScreen();

    //Set the glut functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecial);

    red = rand()%255;
    green =rand()%255;
    blue =rand()%255;

    vector<float> point;
    int x = rand()%(int)(map_half_length*2);
    point.push_back((float)x);
    int y = rand()%(int)(map_half_length*2);
    point.push_back((float)y);
    int z = rand()%(int)(map_half_length*2);
    point.push_back((float)z);
    part_coords.push_back(point);
    map[x+1][y+1][z+1]=1;

    srand(time(NULL));
    constructMap();


    initGL();
    glutTimerFunc(move_speed, grow, 0);
    glutMainLoop();

    delete title;
    return 0;
}

void grow(int value){
    /*
        Directions:
        0 - up
        1 - down
        2 - right
        3 - left
        4 - out
        5 - in
    */
    UNUSED(value);

    if(part_coords.size() > 5000){
        reset();
    }

    //Get the last coordinates
    int last_part = part_coords.size() - 1;
    vector<float> new_head = part_coords[last_part];


    if(map[(int)new_head[0]+1][(int)new_head[1]+2][(int)new_head[2]+1]==0){
        directions.push_back(0);
    }
    if(map[(int)new_head[0]+1][(int)new_head[1]][(int)new_head[2]+1]==0){
        directions.push_back(1);
    }
    if(map[(int)new_head[0]+2][(int)new_head[1]+1][(int)new_head[2]+1]==0){
        directions.push_back(2);
    }
    if(map[(int)new_head[0]][(int)new_head[1]+1][(int)new_head[2]+1]==0){
        directions.push_back(3);
    }
    if(map[(int)new_head[0]+1][(int)new_head[1]+1][(int)new_head[2]+2]==0){
        directions.push_back(4);
    }
    if(map[(int)new_head[0]+1][(int)new_head[1]+1][(int)new_head[2]]==0){
        directions.push_back(5);
    }

    //Reset if no valid directions
    if(directions.empty()){
        reset();
        grow(1);
        return;
    }

    for(int n:directions){
        if(n == last_direction){
            for(int i=0; i<10; i++){
                directions.push_back(last_direction);
            }
        }
    }

    //Choose direction to move out of valid directions
    int direction = directions.at(rand()%directions.size());

    switch(direction){
        case 0:
            last_direction = 0;
            new_head[0] = new_head[0];
            new_head[1] = new_head[1]+1;
            new_head[2] = new_head[2];
            break;
        case 1:
            last_direction = 1;
            new_head[0] = new_head[0];
            new_head[1] = new_head[1]-1;
            new_head[2] = new_head[2];
            break;
        case 2:
            last_direction = 2;
            new_head[0] = new_head[0]+1;
            new_head[1] = new_head[1];
            new_head[2] = new_head[2];
            break;
         case 3:
            last_direction = 3;
            new_head[0] = new_head[0]-1;
            new_head[1] = new_head[1];
            new_head[2] = new_head[2];
            break;
        case 4:
            last_direction = 4;
            new_head[0] = new_head[0];
            new_head[1] = new_head[1];
            new_head[2] = new_head[2]+1;
            break;
        case 5:
            last_direction = 5;
            new_head[0] = new_head[0];
            new_head[1] = new_head[1];
            new_head[2] = new_head[2]-1;
            break;
    }

    map[(int)new_head[0]+1][(int)new_head[1]+1][(int)new_head[2]+1] = direction/2 + 1;

    //Push the new head onto the coords
    part_coords.push_back(new_head);

    directions.clear();
    glutTimerFunc(move_speed, grow, 0);
}

void reset(){
    cout << "RESETING"<<endl;
    part_coords.clear();
    constructMap();

    // glLightfv(GL_LIGHT1, GL_DIFFUSE, green);

    std::vector<float> point;
    int x = rand()%(int)(map_half_length*2);
    point.push_back((float)x);
    int y = rand()%(int)(map_half_length*2);
    point.push_back((float)y);
    int z = rand()%(int)(map_half_length*2);
    point.push_back((float)z);
    map[x+1][y+1][z+1]=1;

    part_coords.push_back(point);

    red = rand()%255;
    green =rand()%255;
    blue =rand()%255;

    //glutTimerFunc(move_speed, grow, 0);
}

void constructMap(){
    /*
        Constructs the map with walls being 1 and all other space 0
    */
    for(int row=0; row<HEIGHT+2; row++){
        for(int col=0; col<WIDTH+2; col++){
            for(int z=0; z<DEPTH+2; z++){
                if(row==0 || col==0 || z==0){
                    map[row][col][z] = 1;
                }
                else if(row==HEIGHT+1 || col==WIDTH+1 || z==DEPTH+1){
                    map[row][col][z] = 1;
                }
                else{
                    map[row][col][z] = 0;
                }
            }
        }
    }
}

void processKeys(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(0);
            break;
        default:
            return;
    }
}
void processSpecial(int key, int x, int y){
    cout<<key<<endl;
}

void initGL(){
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_COLOR_MATERIAL);
    // glEnable(GL_LIGHTING); //Enable lighting
    // glEnable(GL_LIGHT0); //Enable light #0
    // glEnable(GL_LIGHT1); //Enable light #1
    // glEnable(GL_NORMALIZE); //Automatically normalize normals
    glMatrixMode(GL_PROJECTION);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    //gluPerspective(75.0f, 1, 0.0f, 35.0f);
    gluPerspective(75.0f, (float)screenW/screenH, 0.0f, 35.0f);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void reshape(GLsizei width, GLsizei height){
    screenW = width;
    screenH = height;
    glutReshapeWindow(width, height);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    /*red = rand()%255;
    green =rand()%255;
    blue =rand()%255;*/


    for(unsigned int a = 0; a < part_coords.size(); a++){
        glLoadIdentity();
        red = rand()%255;
        green =rand()%255;
        blue =rand()%255;

        glColor3ub(red, green, blue);

        x = part_coords[a][0];
        y = part_coords[a][1];
        z = part_coords[a][2];

        glTranslatef(x-(WIDTH+1)/2, -y+(HEIGHT+1)/2, z-2*DEPTH);

        //glutSolidSphere(12.0, 50, 50);
        if(map[x+1][y+1][z+1] == 2){
            glRotatef(90, 0.0f, 1.0f, 0.0f);
        }
        if(map[x+1][y+1][z+1] == 1){
            glRotatef(90, 1.0f, 0.0f, 0.0f);
        }

        glBegin(GL_QUAD_STRIP);
            GLfloat COSan_3 = 0.0;
            GLfloat SINan_3 = 0.0;
            for(GLfloat an = 0.0; an <= 2.0 * M_PI; an += M_PI / 12.0) {
                        glNormal3f((COSan_3 = cos(an)/3.0), (SINan_3 = sin(an)/3.0), 2.0);
                        glVertex3f(COSan_3, SINan_3, 0.5f);
                        glVertex3f(COSan_3, SINan_3, -0.5f);
        }
        glEnd();
    }

    glutSwapBuffers();
}
