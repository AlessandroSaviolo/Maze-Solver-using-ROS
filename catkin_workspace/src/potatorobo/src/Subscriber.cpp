#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"
#include <iostream>

void number_callback(const std_msgs::Int32MultiArray::ConstPtr& msg) {
	ROS_INFO("Roger That!\nRight wheel speed set to %d\nLeft wheel speed set to %d", msg->data[0], msg->data[1]);
	
}

int main(int argc, char **argv) {

	// initialize subscriber node
	ros::init(argc, argv, "subscriber");
	ros::NodeHandle node;

	// subscribe to potatopic topic
	ros::Subscriber subscriber = node.subscribe("potatopic", 1, number_callback);
	ros::spin();
	return 0;
}

