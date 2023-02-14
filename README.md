# Wall Following Robot in a Maze

*Note:- This is an assignment for ENPM809Y course at UMD for MEng in Robotics degree and might contain some information given by professor to test run the cpp code*

This program consists of implementing the “wall following” algorithm to drive a robot to a 
goal. The goal is always reachable and is always adjacent to one of the 4 outer walls of a maze.
For this program we will need to use a third-party library which provides a simulator to
visualize the outputs of your program. This simulator also provides functionalities to detect
walls, set walls, change the color of cells, and set text.

The simulator used in this assignment can be found at https://github.com/mackorone/mms
and this simulator makes use of Qt and hence it must be installed before building the simulator

We can configure the maze simulator to use our c++ code in the following way:

<img src="https://user-images.githubusercontent.com/40595475/218612363-50fd2c17-0880-42d0-83f7-f845bab8d462.png" width="600" height="300" />

The mouse settings can be configured as given below:

<img src="https://user-images.githubusercontent.com/40595475/218612648-61edbab8-24c3-4da2-a447-3332ddca90b0.png" width="600" height="300" />

## The Wall following Algorithm

The purpose of this program is to make the robot traverse through the maze and by either following the left or right
wall depending on passed parameter.

By left hand rule, we are trying to indicate the following algorithm, where G represents the Goal coordinates:

<img src="https://user-images.githubusercontent.com/40595475/218613270-597c8cf5-e1a2-4589-ad9a-a893618d5de5.png" width="200" height="250" title="algorithm" />

The expected output from Left hand Rule and Right hand Rule algorithm:

<img src="https://user-images.githubusercontent.com/40595475/218613351-16e203ba-17c0-49b6-9d9a-3341a411365d.png" width="500" height="250" title="Expected Output" />

Making use of functions such as moveForward(), turnLeft() and turnRight(), we are able to move the robot respectively,
however the complexities lies where we need to keep a track of direction and accordingly make the robot move in the required
direction. The robot starts at (0,0) and faces north.

The directions of this 16x16 maze is represented as follows:

<img src="https://user-images.githubusercontent.com/40595475/218613728-adcc954a-429f-4410-8a69-fb24ad53a605.png" width="300" height="300" title="Expected Output" />

## Detecting the walls

We need to detect walls so we can redirect the robot and this can be done by making use of wallFront(), wallRight()
and wallLeft() function

## Setting walls

Once we are able to find a wall, we want to set walls with method setWall(int x, int y, char direction). This is where the 
direction becomes critical and hence we need to maintain a record of direction on every turning right and left. In this
particular problem, we need to set walls whenever they are detected as an obstacle.

## Implementation
1. Wrote a function to generate a random goal. Keeping the condiiton that if the X coordinate of the goal is 0 or 15 then its Y coordinate is a
number between 0 and 15. If the X coordinate is not 0 or 15, then its Y coordinate is 0.
2. Set the outer walls using the method Simulator::setWall(). Set the walls using a double
for loop.
3. Wrote code for the robot to return back to origin, taking the shortest path and skipping the repetitive path as indicated below:

In the below image, we are using left-hand rule approach to reach final goal and get back taking shortest path:

Left-hand rule approach:

![image](https://user-images.githubusercontent.com/40595475/218615117-5e51f595-99c3-47d4-93c2-3b131588b2e0.png)

Right-hand rule approach:

![image](https://user-images.githubusercontent.com/40595475/218615261-433d2844-9025-476e-83a0-af2beb19da02.png)


*Additional code documentation can be found in the Doxygen produced documentation revealing the different classes and their methods*


