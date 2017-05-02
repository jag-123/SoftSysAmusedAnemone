#include <ctime>
#include <deque>
#include <GL/glut.h>
#include <algorithm>
#include "pipe.h"

#define MOVE_SPEED 25

using namespace std;

int main(int argc, char** argv){
    //Seeding the random generator
    srand(time(NULL));

    //Init glut
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(screenW, screenH);
    glutCreateWindow("Pipe Screensaver");
    glutFullScreen();

    //Set the glut functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(processKeys);
    glutTimerFunc(MOVE_SPEED, grow, 0);

    //Initializing direction
    direction = rand()%6;
    lastDirection = direction;

    //Initializing color
    red = rand()%255;
    green =rand()%255;
    blue =rand()%255;
    addColor();

    //Add the first point
    vector<float> point;
    int x = rand()%(HEIGHT/2);
    point.push_back((float)x+1);
    int y = rand()%(WIDTH/2);
    point.push_back((float)y+1);
    int z = rand()%(DEPTH/2);
    point.push_back((float)z+1);
    map[x+1][y+1][z+1]=1;
    partCoords.push_back(point);

    //Construct the map
    constructMap();

    //Init opengl and start the mainloop
    initGL();
    glutMainLoop();
    return 0;
}

void grow(int value){
    UNUSED(value);

    if(partCoords.size() > 200){
        reset();
    }

    if(partCoords2.size() > 2000) {
      partCoords2.clear();
      color.clear();
    }

    //Get the last coordinates
    int last_part = partCoords.size() - 1;
    vector<float> newHead = partCoords[last_part];

    /*
        Directions:
        0 - up
        1 - down
        2 - right
        3 - left
        4 - out
        5 - in
    */

    //Checks valid moves and adds them to the queue
    if(map[(int)newHead[0]+1][(int)newHead[1]+2][(int)newHead[2]+1]==0){
        directions.push_back(0);
    }
    if(map[(int)newHead[0]+1][(int)newHead[1]][(int)newHead[2]+1]==0){
        directions.push_back(1);
    }
    if(map[(int)newHead[0]+2][(int)newHead[1]+1][(int)newHead[2]+1]==0){
        directions.push_back(2);
    }
    if(map[(int)newHead[0]][(int)newHead[1]+1][(int)newHead[2]+1]==0){
        directions.push_back(3);
    }
    if(map[(int)newHead[0]+1][(int)newHead[1]+1][(int)newHead[2]+2]==0){
        directions.push_back(4);
    }
    if(map[(int)newHead[0]+1][(int)newHead[1]+1][(int)newHead[2]]==0){
        directions.push_back(5);
    }

    //Reset if no valid directions
    if(directions.empty()){
        reset();
        grow(0);
        return;
    }

    //Weight the current direction to encourage moving in the same
    //direction if that is a valid direction
    for(int n:directions){
        if(n == lastDirection){
            for(int i=0; i<10; i++){
                directions.push_back(lastDirection);
            }
        }
    }

    //Choose direction to move out of valid directions
    int direction = directions.at(rand()%directions.size());
    lastDirection = direction;

    //Choose direction to move out of valid directions
    //and modify the new head depending on that direction
    switch(direction){
        case 0:
            newHead[1]++;
            break;
        case 1:
            newHead[1]--;
            break;
        case 2:
            newHead[0]++;
            break;
         case 3:
            newHead[0]--;
            break;
        case 4:
            newHead[2]++;
            break;
        case 5:
            newHead[2]--;
            break;
    }

    //Add a value to the map where there is a pipe representing the direction
    //that the pipe is moving
    map[(int)newHead[0]+1][(int)newHead[1]+1][(int)newHead[2]+1] = direction/2 + 1;

    addColor();

    //Push the new head onto the coords
    partCoords.push_back(newHead);

    directions.clear();
    glutTimerFunc(MOVE_SPEED, grow, 0);
}

void reset(){
    resetVal += 1;

    //Adds the current pipe to the queue of all created pipes on the screen
    partCoords2.insert( partCoords2.end(), partCoords.begin(), partCoords.end() );
    partCoords.clear();

    //New color
    red = rand()%255;
    green =rand()%255;
    blue =rand()%255;

    addColor();

    //Create a new pipe start
    vector<float> point;
    int x = rand()%(HEIGHT/2);
    point.push_back((float)x+1);
    int y = rand()%(WIDTH/2);
    point.push_back((float)y+1);
    int z = rand()%(DEPTH/2);
    point.push_back((float)z+1);
    map[x+1][y+1][z+1]=1;
    partCoords.push_back(point);
}

void constructMap(){
    /*
        Constructs the map with walls being 1 and all other space 0
    */
    for(int row=0; row<WIDTH+2; row++){
        for(int col=0; col<HEIGHT+2; col++){
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

void addColor(){
    vector<GLubyte> current_color;
    current_color.push_back(red);
    current_color.push_back(green);
    current_color.push_back(blue);
    color.push_back(current_color);
}

void initGL(){
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);

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

    /*UNCOMMENT NEXT THREE LINE FOR MELLOW PARTY MODE*/
    // red = rand()%255;
    // green =rand()%255;
    // blue =rand()%255;

    int x, y, z;
    for(unsigned int b = 0; b < partCoords2.size(); b++){
        glLoadIdentity();

        //Get the current part coordinates
        x = partCoords2[b][0];
        y = partCoords2[b][1];
        z = partCoords2[b][2];

        glTranslatef(x-(WIDTH-15)/2, -y+(HEIGHT+1)/2, z-2*DEPTH);

        //Rotate based on direction that the pipe should be facing
        if(map[x+1][y+1][z+1] == 2){
            glRotatef(90, 0.0f, 1.0f, 0.0f);
        }
        if(map[x+1][y+1][z+1] == 1){
            glRotatef(90, 1.0f, 0.0f, 0.0f);
        }

        //Draw the pipe
        glBegin(GL_QUAD_STRIP);
            glColor3ub(color.at(b)[0], color.at(b)[1], color.at(b)[2]);
            GLfloat COSan_3 = 0.0;
            GLfloat SINan_3 = 0.0;
            for(GLfloat an = 0.0; an <= 2.0 * M_PI; an += M_PI / 12.0) {
                        glNormal3f((COSan_3 = cos(an)/3.0), (SINan_3 = sin(an)/3.0), 2.0);
                        glVertex3f(COSan_3, SINan_3, 0.5f);
                        glVertex3f(COSan_3, SINan_3, -0.5f);
            }
        glEnd();
    }
    for(unsigned int a = 0; a < partCoords.size(); a++){
        glLoadIdentity();

        /*UNCOMMENT NEXT THREE LINE FOR FULL PARTY MODE*/
        // red = rand()%255;
        // green =rand()%255;
        // blue =rand()%255;

        //Get the current part coordinates
        x = partCoords[a][0];
        y = partCoords[a][1];
        z = partCoords[a][2];

        //Rotate based on direction that the pipe should be facing
        glTranslatef(x-(WIDTH-15)/2, -y+(HEIGHT+1)/2, z-2*DEPTH);

        if(map[x+1][y+1][z+1] == 2){
            glRotatef(90, 0.0f, 1.0f, 0.0f);
        }
        if(map[x+1][y+1][z+1] == 1){
            glRotatef(90, 1.0f, 0.0f, 0.0f);
        }

        //Draw the pipe
        glBegin(GL_QUAD_STRIP);
            glColor3ub(red, green, blue);
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
