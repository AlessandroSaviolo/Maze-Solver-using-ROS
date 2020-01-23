#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"
#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>

const short int lightpin = 7;
const short int toptouchpin = 2;
const short int bottomtouchpin = 3;
const short int beaconpin = 5;

const short int usfronttrigpin = 10;
const short int usfrontechopin = 11;
const short int usfrontlefttrigpin = 14;
const short int usfrontleftechopin = 13;

//const short int usbacktrigpin = 10;
//const short int usbackechopin = 11;
const short int usbacklefttrigpin = 9;
const short int usbackleftechopin = 8;


void start() {

	std::cout << "Press touch sensor, please.\n";
	bool start = false;
	while (!start) {
		if (digitalRead(toptouchpin)) {
			start = true;
			continue;
		}
	}
	std::cout << "Obscure light sensor, please.\n";
	start = false;
	while (!start) {
		if (digitalRead(lightpin)) {
			start = true;
			continue;
		}
	}
	std::cout << "Thanks, program started.\n";
}


bool spin(ros::Publisher pub, std_msgs::Int32MultiArray speeds, int led_spinning_num, ros::Rate led_spinning_len, ros::Rate led_spinning_len_2) {

	speeds.data.clear();
	speeds.data.push_back(-100);
	speeds.data.push_back(100);
	pub.publish(speeds);
	ros::spinOnce();
	for (int i = 0; i < led_spinning_num; i++) {
		if (!digitalRead(lightpin)) {
			//speeds.data.clear();
			//speeds.data.push_back(100);
			//speeds.data.push_back(-100);
			//pub.publish(speeds);
			//ros::spinOnce();
			//led_spinning_len_2.sleep();
			return true;
		}
		led_spinning_len.sleep();
	}
	return true;
}

bool lookaround(ros::Publisher pub, std_msgs::Int32MultiArray speeds, int led_lookaround_num, ros::Rate led_lookaround_len, ros::Rate led_lookaround_len_2) {

	std::cout << "lookaround \n";

	speeds.data.clear();
	speeds.data.push_back(-120);
	speeds.data.push_back(120);
	pub.publish(speeds);
	ros::spinOnce();
	for (int i = 0; i < led_lookaround_num; i++) {
		if (!digitalRead(lightpin)) {
			speeds.data.clear();
			speeds.data.push_back(120);
			speeds.data.push_back(-120);
			pub.publish(speeds);
			ros::spinOnce();
			led_lookaround_len_2.sleep();
			return true;
		}
		led_lookaround_len.sleep();
	}

	speeds.data.clear();
	speeds.data.push_back(120);
	speeds.data.push_back(-120);
	pub.publish(speeds);
	ros::spinOnce();
	for (int i = 0; i < led_lookaround_num * 2; i++) {
		if (!digitalRead(lightpin)) {
			speeds.data.clear();
			speeds.data.push_back(-120);
			speeds.data.push_back(120);
			pub.publish(speeds);
			ros::spinOnce();
			led_lookaround_len_2.sleep();
			return true;
		}	
		led_lookaround_len.sleep();
	}

	speeds.data.clear();
	speeds.data.push_back(-120);
	speeds.data.push_back(120);
	pub.publish(speeds);
	ros::spinOnce();
	for (int i = 0; i < led_lookaround_num * 1.05; i++) {
		if (!digitalRead(lightpin)) {
			speeds.data.clear();
			speeds.data.push_back(120);
			speeds.data.push_back(-120);
			pub.publish(speeds);
			ros::spinOnce();
			led_lookaround_len_2.sleep();
			return true;
		}	
		led_lookaround_len.sleep();
	}
	return false;
}


int pulseIn(int pin, int level, int timeout) {
   struct timeval tn, t0, t1;
   long micros;
   gettimeofday(&t0, NULL);
   micros = 0;

	while (digitalRead(pin) != level) {
		gettimeofday(&tn, NULL);
		if (tn.tv_sec > t0.tv_sec)
			micros = 1000000L;
		else
			micros = 0;
		micros += (tn.tv_usec - t0.tv_usec);
		if (micros > timeout)
			return 0;
	}

   gettimeofday(&t1, NULL);

	while (digitalRead(pin) == level) {
		gettimeofday(&tn, NULL);
		if (tn.tv_sec > t0.tv_sec)
			micros = 1000000L;
		else
			micros = 0;
		micros = micros + (tn.tv_usec - t0.tv_usec);
		if (micros > timeout)
			return 0;
	}

	if (tn.tv_sec > t1.tv_sec)
		micros = 1000000L;
	else
		micros = 0;
   micros = micros + (tn.tv_usec - t1.tv_usec);

   return micros;
}


int compute_distance(const short int trig, const short int echo) {

	std::cout << "compute distance \n";

	ros::Rate impuls_time(100);
	ros::Rate init(10);

	digitalWrite(trig, LOW);
	init.sleep();
	digitalWrite(trig, HIGH);
	impuls_time.sleep();
	digitalWrite(trig, LOW);

	return pulseIn(echo, 1, 20000) * 0.5 * 0.03432;
}


void make_turn(int direction, ros::Publisher pub, std_msgs::Int32MultiArray speeds, int turn_num, ros::Rate turn_len) {

	std::cout << "make turn \n";

	if (direction) {
		speeds.data.clear();
		speeds.data.push_back(-100);
		speeds.data.push_back(150);
		pub.publish(speeds);
		ros::spinOnce();
		for (int i = 0; i < turn_num; i++) {
			turn_len.sleep();
		}
	}
	else {
		while (true) {
			speeds.data.clear();
			speeds.data.push_back(100);
			speeds.data.push_back(-100);
			pub.publish(speeds);
			ros::spinOnce();
			turn_len.sleep();
			speeds.data.clear();
			speeds.data.push_back(0);
			speeds.data.push_back(0);
			pub.publish(speeds);
			ros::spinOnce();
			if (compute_distance(usfronttrigpin, usfrontechopin) > 20 && compute_distance(usfrontlefttrigpin, usfrontleftechopin) > compute_distance(usbacklefttrigpin, usbackleftechopin)) {
				break;
			}
		}
	}
}


void output_distances() {

	std::cout << "front dist: " << compute_distance(usfronttrigpin, usfrontechopin) << "\n";
	std::cout << "frontleft dist: " << compute_distance(usfrontlefttrigpin, usfrontleftechopin) << "\n";
	std::cout << "backleft dist: " << compute_distance(usbacklefttrigpin, usbackleftechopin) << "\n";
}


void back_home(ros::Publisher pub, std_msgs::Int32MultiArray speeds, ros::Rate forward_len, int turn_num, ros::Rate turn_len) {

	int sleeping = 0;
	int backleft_dist, frontleft_dist, front_dist, tmp, tmp_left, tmp_right;

	while(true) {

		if (sleeping > 0) {
			sleeping--;
		}

		frontleft_dist = compute_distance(usfrontlefttrigpin, usfrontleftechopin);
		backleft_dist = compute_distance(usbacklefttrigpin, usbackleftechopin);
		tmp = frontleft_dist - backleft_dist;

		if (tmp < 30 && tmp > -30) {
			speeds.data.clear();
			tmp_left = 150 - 10 * tmp * 0.5;
			tmp_right = 150 + 10 * tmp * 0.5;
			speeds.data.push_back(tmp_left);
			speeds.data.push_back(tmp_right);
			pub.publish(speeds);
			ros::spinOnce();
			forward_len.sleep();

			speeds.data.clear();
			speeds.data.push_back(0);
			speeds.data.push_back(0);
			pub.publish(speeds);
			ros::spinOnce();
		}
		else {
			speeds.data.clear();
			speeds.data.push_back(150);
			speeds.data.push_back(150);
			pub.publish(speeds);
			ros::spinOnce();
			forward_len.sleep();

			speeds.data.clear();
			speeds.data.push_back(0);
			speeds.data.push_back(0);
			pub.publish(speeds);
			ros::spinOnce();
		}

		front_dist = compute_distance(usfronttrigpin, usfrontechopin);

		if (front_dist != 0 && front_dist < 15) {

			speeds.data.clear();
			speeds.data.push_back(-150);
			speeds.data.push_back(-150);
			pub.publish(speeds);
			ros::spinOnce();
	
			while (front_dist < 14) {
				front_dist = compute_distance(usfronttrigpin, usfrontechopin);
			}

			speeds.data.clear();
			speeds.data.push_back(0);
			speeds.data.push_back(0);
			pub.publish(speeds);
			ros::spinOnce();

			// turn right
			make_turn(0, pub, speeds, turn_num, turn_len);
		}
		else if (front_dist != 0 && front_dist < 20) {

			speeds.data.clear();
			speeds.data.push_back(150);
			speeds.data.push_back(150);
			pub.publish(speeds);
			ros::spinOnce();
	
			while (front_dist < 16) {
				front_dist = compute_distance(usfronttrigpin, usfrontechopin);
			}

			speeds.data.clear();
			speeds.data.push_back(0);
			speeds.data.push_back(0);
			pub.publish(speeds);
			ros::spinOnce();

			// turn right
			make_turn(0, pub, speeds, turn_num, turn_len);
		}

		backleft_dist = compute_distance(usbacklefttrigpin, usbackleftechopin);

		if ((sleeping == 0) && (backleft_dist == 0 || backleft_dist > 55)) {

			// turn left
			make_turn(1, pub, speeds, turn_num, turn_len);
			sleeping = 10;
		}
	}
}

void take_pack(ros::Publisher pub, std_msgs::Int32MultiArray speeds, int led_spinning_num, ros::Rate led_spinning_len, ros::Rate led_spinning_len_2, ros::Rate forward_len, int turn_num, ros::Rate turn_len) {

	while (true) {

		if (digitalRead(bottomtouchpin)) {
			back_home(pub, speeds, forward_len, turn_num, turn_len);
			speeds.data.clear();
			speeds.data.push_back(0);
			speeds.data.push_back(0);
			pub.publish(speeds);
			ros::spinOnce();
			return;
		}
		else if (!digitalRead(lightpin)) {
			speeds.data.clear();
			speeds.data.push_back(100);
			speeds.data.push_back(100);
			pub.publish(speeds);
			ros::spinOnce();
		}	
		else {
			if (spin(pub, speeds, led_spinning_num, led_spinning_len, led_spinning_len_2)) {
				speeds.data.clear();
				speeds.data.push_back(100);
				speeds.data.push_back(100);
				pub.publish(speeds);
				ros::spinOnce();
			}
			else {
				speeds.data.clear();
				speeds.data.push_back(-100);
				speeds.data.push_back(-100);
				pub.publish(speeds);
				ros::spinOnce();
			}
		}
	}
}


int main(int argc, char **argv) {

	// initialize publisher node
	ros::init(argc, argv, "publisher");
	ros::NodeHandle n;

	// publish to potatopic topic
	ros::Publisher pub = n.advertise<std_msgs::Int32MultiArray>("potatopic", 1);

	// use this command without sudo
	setenv("WIRINGPI_GPIOMEM", "1", 1);

	// library setup function
	wiringPiSetup();
	pinMode(lightpin, INPUT);
	pinMode(toptouchpin, INPUT);
	pinMode(bottomtouchpin, INPUT);
	pinMode(beaconpin, INPUT);

	pinMode(usfronttrigpin, OUTPUT);
	pinMode(usfrontechopin, INPUT);
	pinMode(usfrontlefttrigpin, OUTPUT);
	pinMode(usfrontleftechopin, INPUT);
	pinMode(usbacklefttrigpin, OUTPUT);
	pinMode(usbackleftechopin, INPUT);

	// int fd = wiringPiI2CSetup(68);

	// std::cout << "wiringPiI2CSetup(68): " << fd << "\n";

	// std::cout << "wiringPiI2CRead(fd): " << wiringPiI2CRead(fd) << "\n";
	// std::cout << "wiringPiI2CReadreg8(fd): " << wiringPiI2CReadReg8(fd, 8) << "\n";
	
	// beacon input
	unsigned short int beacon_rev = 0;
	
	// create message to be published
	std_msgs::Int32MultiArray speeds;

	// length of one step
	ros::Rate turn_len(300);
	ros::Rate forward_len(1.5);
	ros::Rate led_lookaround_len(400);
	ros::Rate led_lookaround_len_2(30);
	ros::Rate led_spinning_len(400);
	ros::Rate led_spinning_len_2(30);
	ros::Rate not_moving_len(0.5);

	// number of steps
	int turn_num = 45;
	int forward_num = 400;
	int led_lookaround_num = 100;
	int led_spinning_num = 100;

	// variables
	int backleft_dist, frontleft_dist, front_dist;
	int tmp_right, tmp_left;
	int tmp;
	int gap;
	int not_moving = 0;
	int count = 2;
	int sleeping = 0;
	bool turn = false;
	int prev_frontleft = 0;
	int prev_backleft = 0;
	int prev_front = 0;

	// start the program
	start();

	// output_distances();

	while (ros::ok()) {

		if (not_moving >= 2) {
			speeds.data.clear();
			speeds.data.push_back(-200);
			speeds.data.push_back(-200);
			pub.publish(speeds);
			ros::spinOnce();
			not_moving_len.sleep();
		}

		if (sleeping > 0) {
			sleeping--;
		}
 
		frontleft_dist = compute_distance(usfrontlefttrigpin, usfrontleftechopin);
		backleft_dist = compute_distance(usbacklefttrigpin, usbackleftechopin);
		tmp = frontleft_dist - backleft_dist;

		if (tmp < 30 && tmp > -30) {
			speeds.data.clear();
			tmp_left = 100 - 8 * tmp * 0.5;
			tmp_right = 100 + 8 * tmp * 0.5;
			speeds.data.push_back(tmp_left);
			speeds.data.push_back(tmp_right);
			pub.publish(speeds);
			ros::spinOnce();
			forward_len.sleep();

			speeds.data.clear();
			speeds.data.push_back(0);
			speeds.data.push_back(0);
			pub.publish(speeds);
			ros::spinOnce();

			//if (!digitalRead(lightpin)) {		
			//	take_pack(pub, speeds, led_spinning_num, led_spinning_len, led_spinning_len_2, forward_len, turn_num, turn_len);
			//	return 0;
			//}
		}
		else {
			speeds.data.clear();
			speeds.data.push_back(100);
			speeds.data.push_back(100);
			pub.publish(speeds);
			ros::spinOnce();
			forward_len.sleep();

			speeds.data.clear();
			speeds.data.push_back(0);
			speeds.data.push_back(0);
			pub.publish(speeds);
			ros::spinOnce();

			//if (!digitalRead(lightpin)) {		
			//	take_pack(pub, speeds, led_spinning_num, led_spinning_len, led_spinning_len_2, forward_len, turn_num, turn_len);
			//	return 0;
			//}
		}

		front_dist = compute_distance(usfronttrigpin, usfrontechopin);

		if (front_dist != 0 && front_dist < 15) {

			speeds.data.clear();
			speeds.data.push_back(-120);
			speeds.data.push_back(-120);
			pub.publish(speeds);
			ros::spinOnce();
		
			while (front_dist < 14) {
				front_dist = compute_distance(usfronttrigpin, usfrontechopin);
			}

			speeds.data.clear();
			speeds.data.push_back(0);
			speeds.data.push_back(0);
			pub.publish(speeds);
			ros::spinOnce();

			// turn right
			make_turn(0, pub, speeds, turn_num, turn_len);
		}
		else if (front_dist != 0 && front_dist < 20) {

			speeds.data.clear();
			speeds.data.push_back(100);
			speeds.data.push_back(100);
			pub.publish(speeds);
			ros::spinOnce();
		
			while (front_dist < 16) {
				front_dist = compute_distance(usfronttrigpin, usfrontechopin);
			}

			speeds.data.clear();
			speeds.data.push_back(0);
			speeds.data.push_back(0);
			pub.publish(speeds);
			ros::spinOnce();

			// turn right
			make_turn(0, pub, speeds, turn_num, turn_len);
		}

		backleft_dist = compute_distance(usbacklefttrigpin, usbackleftechopin);

		if ((sleeping == 0) && (backleft_dist == 0 || backleft_dist > 55)) {

			// turn left
			make_turn(1, pub, speeds, turn_num, turn_len);
			sleeping = 10;
		}

		if (frontleft_dist == prev_frontleft && backleft_dist == prev_backleft && front_dist == prev_front) {
			not_moving++;
		}
		else {
			not_moving = 0;
		}

		prev_frontleft = frontleft_dist;
		prev_backleft = backleft_dist;
		prev_front = front_dist;
		
	}

	return 0;
}

