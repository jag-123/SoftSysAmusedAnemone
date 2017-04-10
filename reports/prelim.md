## Goal

### Overview
Create a simple screensaver in C++ using OpenGL. We are planning to use the [pipe screen saver](https://www.youtube.com/watch?v=Uzx9ArZ7MUU) as the basis for the screen saver we wish to create with C++ using OpenGL. This will include creating at least one pipe that moves across the screen in at least 2-Dimensions without running into itself.
### MVP
Create one single pipe that moves across the screen in 2-dimensions without running into itself.
### Stretch
Have multiple pipes that move around the screen in 3-dimensions without running into each other. The first step will be to create the pipes at different start times and after that we will try to create multiple pipes at once.
### Results
The following is a link to a demo video of a 2-d pipe growing in a terminal window. 
https://github.com/jag-123/SoftSysAmusedAnemone/blob/master/videos/sprint1_video.mp4

### Resources - Annotated Bibliography
## OpenGL:
To better understand OpenGL we all completed various tutorials that walked through the major aspects of OpenGL and some of the functions that are used in every program. Once we understood the basics, we began to implement some heavily commented test code that allowed us to look fully understand the less-used OpenGL functions that we working with. 

- http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/
- https://open.gl/introduction
- http://lazyfoo.net/tutorials/OpenGL/index.php
- https://www.youtube.com/playlist?list=PL2E88A9FE78FBF3B8
- https://www.youtube.com/watch?v=_OAYRV5fjuE

Coming up we will continue to look through OpenGL tutorials and sample code as well as documentation. Hopefully this will allow us to use some of the features that make OpenGL so helpful, like vertex buffer objects. Hopefully we have enough understanding now to work with the OpenGL documentation.
- https://www.opengl.org/documentation/

## C++:

Coming into this sprint, Jeremy and Emma did not have any experience with C++. When they encountered something they did not understand, they primarily referred to TutorialsPoint or StackOverflow. Most of the code that we have worked with so far has been mostly within the OpenGL library, and did not rely on C++ as much so it has not been too challenging yet. 
- https://www.tutorialspoint.com/cplusplus/


## Trello Board

- https://trello.com/b/KTYQjMuP/softsys17-amused-anemone

### Trello Cards 

### Our tasks follow the order of:
- Work on a C++ Tutorial
  - This card does not have a clear deliverable like the others, but it does still have a clear end. Because the “learning” cards were only used in this Sprint, we will not be running into the issue of cards with no deliverables again.
- Work on an OpenGL Tutorial
  -This card is similar to the above one.
- Create a single cylinder
  - Refer to (this folder)[https://github.com/jag-123/SoftSysAmusedAnemone/tree/master/cylinder]
- Build the pipe across the screen
  - Refer to (this folder)[https://github.com/jag-123/SoftSysAmusedAnemone/tree/master/EmmaTest/PipeGrowth]
- Make the pipe turn in two dimensions
  - Refer to (this folder)[https://github.com/jag-123/SoftSysAmusedAnemone/tree/master/Pipe]
- Work on preventing collisions with the pipe
  - Right now we have some collision prevention, but it is not working correctly yet. The pipe know when it has hit the wall, but it is not turning yet. It is also in the pipe folder (here)[https://github.com/jag-123/SoftSysAmusedAnemone/tree/master/Pipe].

## Possible Roadblocks

OpenGL seems to be the biggest upcoming roadblock because the library contains so many functions that it is really challenging to know the full capabilities of each function.
So far, we have found pair programming helpful, but it is hard to schedule long blocks of time for pairs to meet. This sprint we are planning to make smaller tasks that individuals can take on and complete in short amounts of time.
