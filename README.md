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

- Turning Left around the Corner: [video](https://drive.google.com/open?id=1uL91m3qKWXh3cAUHWBK753OTw1f-OLUo)

- Turning Right away from the Wall: [video](https://drive.google.com/open?id=13IyM1QUc8puFO04YyQsOi69TPIz-a-xj)

- Driving Forward Along the Wall: [video](https://drive.google.com/open?id=11nRQmE2CjdI5d-o7rK5lUJJoIlie7RMg)

In order to drive forward along a wall, the wheels speed must be adjusted constantly. To do so, the following formula is used to compute the two different wheels speed:

<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Maze-Solver-using-ROS/blob/master/formula.png" width="300">
 </p>
 
By using these moving patterns the robot is able to solve the maze (find the LED puck). [Example](https://drive.google.com/open?id=1-Kx9mA5S-UhEnGjChlHMnuGxu_Cgq6-G).
 
 ## 3. Flow Chart
 
 <p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Maze-Solver-using-ROS/blob/master/flowchart.jpg" width="1000">
 </p>

## License

Copyright (C) 2021 Alessandro Saviolo, [FlexSight SRL](http://www.flexsight.eu/), Padova, Italy
```
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```
