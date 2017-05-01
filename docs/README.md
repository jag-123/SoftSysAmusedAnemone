[Carl Moser](https://github.com/cmoser96), [Emma Price](https://github.com/ejprice54321), [Cleophas Kalekem](https://github.com/kalekem), [Jeremy Garcia](https://github.com/jag-123)


## Overview
We implemented a screen saver in C++ using OpenGL based on the [pipes screen saver](https://www.youtube.com/watch?v=Uzx9ArZ7MUU). View or download our code [here](https://github.com/jag-123/SoftSysAmusedAnemone/Pipe).

## Goals
This project was created for our Software Systems course. For this project, our team was interested in implementing graphics using OpenGL and C++. Creating a screensaver that was 3-dimensional and changed over time seemed like a perfect way to improve our skills and create something enjoyable for everyone. 

## Background
Going into this project, half of the team had not used C++ or OpenGL before and the other half had a reasonable amount of experience. Most of the background research that was done in preperation for this project consisted of online tutorials to get all of the members comfortable using OpenGL and a lot of experimentation with example code. The primary outcome of this research was knowledge of how OpenGL creates and displays objects and how it allows objects to change over time. We also learned a lot about how OpenGL programs tend to be structured and which functions act as the building blocks for their programs.

***Provide context for your project by describing the broader space in which it is situated. This section will likely draw upon your annotated bibliography. You’ve already collected this knowledge and shown us you understand it, now frame it for an external audience.***

## Implementation
### Overview
Our pipe screen saver is created with a pipe that grows incrementally around the screen. Once it grows to contain a certain number of pipe units or it cannot grow any more (because it would hit itself otherwise), it stops growing and remains on the screen while more pipes continue to grow. After SOME pipes are created, the entire screen resets and it starts building again.

### Map Creation
In order to grow the pipe, we first needed to create an environment for it to grow in. This took the form of a three-dimensional matrix of integers that was slightly larger than the screen. The map with all of the edges marked as 1 and everything within marked as 0. All places within the map that contain a pipe are marked with an integer according to the direction that the pipe should be facing.

### Pipe Generation
Our pipe is made of a dequeue (double ended queue) that contains vectors representing coordinates where the pipe has been. The pipe begins at a random point and from there it grows according to the timer function. Each time it grows, the pipe randomly chooses a direction to go in and creates a new coordinate which is pushed onto the pipe dequeue. It also changes that point in the map from 0 to 1-3 (based on the direction the pipe should be facing). After this, a for loop goes through the pipe coordinates to draw and rotate a cylinder at each point.

Our pipe coordinates are contained in a dequeue because pipe growth is determine only based on the previous value in the pipe dequeue. Our pipe coordinates are housed in a vector becuase they do not need to change after they are created.

#### Error Checking
When the pipe randomly chooses a direction to grow in, it must first check to see which surrounding coordinates are available. It does so by taking the last coordinate in the pipe queue, and checking the value of the surrounding x, y, and z directions. If that direction is available (is 0), it will that direction to a vector of possible directions that the growing pipe will choose from. The direction vector contains 10 times as many options to continue growing in the direction that pipe is currently pointed, which mimics the choices made within the actualy Pipe Screensaver. If this feature were removed, error checking and pipe generation could be combined to simplify the code.

***What specifically did you accomplish with this project? Within the context of the problem space, enumerate the potential options and explain why you chose what you did. Describe what makes it interesting/challenging, and how you overcame those challenges. Explain your implementation and design decisions with sufficient detail for a technical audience to understand it.***

## Results
The following video is an example of our pipes screen saver in action.

[Pipes Screen Saver](https://github.com/jag-123/SoftSysAmusedAnemone/)

Provide evidence demonstrating that what you built works. Though the details will be different for each project, screenshots and video are likely helpful. Include graphs or other data if appropriate.

## Future Work
