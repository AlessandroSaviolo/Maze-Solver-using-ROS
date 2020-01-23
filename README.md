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

## 2. Dataset

The following datasets have been used to test the performances of the proposed method:

- [LawnBowling](https://drive.google.com/open?id=1ImEiJeWE5nSepkQyOHGX90o8bUpgpyfh)

- [Black](https://drive.google.com/open?id=146jKk2x2GreUJfNYRGtkaNTTYpvtcwuA)

- [Nature](https://drive.google.com/open?id=1wSUHjC3bgSeaRjh690Ter3PETxZbdNWS)

- [Random](https://drive.google.com/open?id=1QB9PeDCGmEZBwDh27nDcw6yM3FU-c7p0)

## 3. Methodology

The features considered by the shadow detector for the comparison of different segments of the image are intensity, color information and texture.

To better present the different steps that compose the proposed algorithm, the output produced by each step is illustrated. In particular, the following image is considered:

<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/1.jpg" width="600">
 </p>

### Steps:

0.  Preprocessing: filters are applied to the image in order to get better results in the segmentation step

<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/2.jpg" width="600">
 </p>

1.  Segmentation: 𝑘means is used to segment the image

<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/3.jpg" width="600">
 </p>

2.  Intensity thresholding: image is converted to HSV color space and the intensity channel is thresholded

<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/4.jpg" width="600">
 </p>

3.  Candidates computation: segments belonging to the white components of the thresholded image (at point 2) are selected as shadow candidates

<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/5.png" width="600">
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/6.png" width="600">
</p>

4.  Candidates merging: “similar” candidates are merged (the illustrated matrix is used to identify candidates that need to be merged)

<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/8.png" width="600">
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/9.png" width="600">
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/10.png" width="600">
 </p>

5.  Candidates comparison: candidates are compared with their non-candidate neighbors and selected as shadow based on chromaticity and texture

<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/12.png" width="600">
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/13.png" width="600">
 </p>
 
 After computing these 5 steps, the algorithm outputs the detected shadows:
 
<p align="center"> 
    <img src="https://github.com/AlessandroSaviolo/Shadow-Detector/blob/master/steps-output/14.jpg" width="600">
 </p> 

