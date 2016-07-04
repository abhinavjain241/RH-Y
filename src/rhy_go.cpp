#include <math.h>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"

// #define DEBUG
/** Uncomment the above line and then compile again, to start the node in debug mode.
The debug mode will simply send a fixed velocity to the robot. **/

/**
 * This code demonstrates simple sending of velocity commands to the RH-Y robot in Gazebo.
 Abhinav Jain 2016, Intern at LaRA, HEIG-VD
 */

char controlChar = 's'; //Initially, control character is set to s which means stop

void controlCallback(const std_msgs::String::ConstPtr& msg) {
	ROS_INFO("I got [%s]", msg->data.c_str());
	if (msg->data == "t") {
		controlChar = 't';
	} else if (msg->data == "g") {
		controlChar = 'g';
	} else if (msg->data == "f") {
		controlChar = 'f';
	} else if (msg->data == "h") {
		controlChar = 'h';
	} else {
		controlChar = 's';
	}
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "rhyTest");
  ros::NodeHandle n;
  ros::Publisher vel_pub_0 = n.advertise<geometry_msgs::Twist>("/rhy/cmd_vel", 1);
  ros::Subscriber control_sub = n.subscribe("/server_messages/", 1000, controlCallback);
  ros::Rate loop_rate(5);
  int count = 0;
  while (ros::ok()) {
    geometry_msgs::Twist cmd_vel;
    #ifndef DEBUG
    switch(controlChar) {
		case 't':
		cmd_vel.linear.x = 1;
	    cmd_vel.linear.y = 0;
	    cmd_vel.linear.z = 0;
	    cmd_vel.angular.x = 0;
	    cmd_vel.angular.y = 0;
	    cmd_vel.angular.z = 0;
	    break;
	    case 'g':
	    cmd_vel.linear.x = -1;
	    cmd_vel.linear.y = 0;
	    cmd_vel.linear.z = 0;
	    cmd_vel.angular.x = 0;
	    cmd_vel.angular.y = 0;
	    cmd_vel.angular.z = 0;
	    break;
	    case 'f':
	    cmd_vel.linear.x = 0;
	    cmd_vel.linear.y = 0;
	    cmd_vel.linear.z = 0;
	    cmd_vel.angular.x = 0;
	    cmd_vel.angular.y = 0;
	    cmd_vel.angular.z = -1;
	    break;
	    case 'h':
	    cmd_vel.linear.x = 0;
	    cmd_vel.linear.y = 0;
	    cmd_vel.linear.z = 0;
	    cmd_vel.angular.x = 0;
	    cmd_vel.angular.y = 0;
	    cmd_vel.angular.z = 1;
	    break;
	    case 's':
	    cmd_vel.linear.x = 0;
	    cmd_vel.linear.y = 0;
	    cmd_vel.linear.z = 0;
	    cmd_vel.angular.x = 0;
	    cmd_vel.angular.y = 0;
	    cmd_vel.angular.z = 0;
	    break;
	    default:
	    cmd_vel.linear.x = 0;
	    cmd_vel.linear.y = 0;
	    cmd_vel.linear.z = 0;
	    cmd_vel.angular.x = 0;
	    cmd_vel.angular.y = 0;
	    cmd_vel.angular.z = 0;
    }
    #else
    cmd_vel.linear.x = 1;
    cmd_vel.linear.y = 0;
    cmd_vel.linear.z = 0;
    cmd_vel.angular.x = 0;
    cmd_vel.angular.y = 0;
    cmd_vel.angular.z = 0.4*sin(count);
    #endif
    vel_pub_0.publish(cmd_vel);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }
  return 0;
}
