# Maze Solver using ROS

This work is the final project for the course _Mobile Robots_ that I attended during my exchange program at National Chiao Tung University (Taiwan).

The purpose of this project is to assemble a robot and implement the algorithm for making the robot smartly move in a maze and find a LED puck. Both Raspberry Pi and Arduino are used.

<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Maze-Solver-using-ROS/blob/master/robot.png" width="300">
 </p>

## 1. Sensors

The following sensors have been used to assemble the robot:

- 1 Light Sensor

- 3 Ultrasonic Distance Sensor

## 2. Moving Patterns

The following moving patterns have been implemented to allow the robot to smartly move in the maze:

- Turning Left around the corner: [video](https://drive.google.com/open?id=1uL91m3qKWXh3cAUHWBK753OTw1f-OLUo)

- Turning Right away from the Wall: [video](https://drive.google.com/open?id=13IyM1QUc8puFO04YyQsOi69TPIz-a-xj)

- Driving Forward Along the Wall: [video](https://drive.google.com/open?id=11nRQmE2CjdI5d-o7rK5lUJJoIlie7RMg)

In order to drive forward along a wall, the wheels speed must be adjusted constantly. To do so, the following formula is used to compute the two different wheels speed:

<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Maze-Solver-using-ROS/blob/master/formula.png" width="300">
 </p>

## 3. Example of Maze Solved

