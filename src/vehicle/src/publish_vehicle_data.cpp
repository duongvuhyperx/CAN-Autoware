 /* Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
*/


// First we include important header files

#include <cmath>
#include <thread>

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <autoware_msgs/VehicleCmd.h>


// Set here what you want to send

int send_steer = 0; //Steering Command
int send_accel = 0; //Acceleration Command
int send_brake = 10; //Brake Command
int send_l = 1;     //Left Lamp
int send_r = 0;       //Right Lamp
int send_gear = 0;   // Gear 
int send_mode = 0;  // Mode
int send_emergency = 0; //Emergency
double send_linear_velocity = 0; // Linear Velocity Command (control)
double send_linear_acceleration = 0; // Linear Acceleration (control)
double send_steering_angle = 0;   // Steering Angle (control)

//twist linear
float send_twist_lx = 160;
float send_twist_ly = 0;
float send_twist_lz = 0; 

//twist rotational
float send_twist_rx = 0;
float send_twist_ry = 0;
float send_twist_rz = 100;






    
int main(int argc, char* argv[])
{
    
    // ROS initialization
  ros::init(argc, argv, "publish_to_vehicle");
  ros::NodeHandle n;
  

  
    // Publish Initialize
  ros::Publisher command= n.advertise<autoware_msgs::VehicleCmd>("vehicle_topic", 10);

   // Send message frequency 
    ros::Rate loop_rate(0.8);

   // Associate the variable with the message file
    autoware_msgs::VehicleCmd vehicle_msg;
    
   
   // publish all the messages untill the program terminated by user 
   while(ros::ok())
   {
   
    // setup to send the steer message
    vehicle_msg.steer_cmd.steer = send_steer;
     
    // setup to send the accel message
    vehicle_msg.accel_cmd.accel = send_accel;

    // setup to send the brake message
    vehicle_msg.brake_cmd.brake = send_brake;
 
    // setup to send the lamp message
    vehicle_msg.lamp_cmd.l = send_l;
    vehicle_msg.lamp_cmd.r = send_r;
    
    // setup to send the gear message
    vehicle_msg.gear = send_gear;

    // setup to send the mode message
    vehicle_msg.mode = send_mode;

    // setup to send the twist linear messages
    vehicle_msg.twist_cmd.twist.linear.x = send_twist_lx;
    vehicle_msg.twist_cmd.twist.linear.y = send_twist_ly;
    vehicle_msg.twist_cmd.twist.linear.z = send_twist_lz;
   
    // setup to send the twist rotation messages
    vehicle_msg.twist_cmd.twist.angular.x = send_twist_rx;
    vehicle_msg.twist_cmd.twist.angular.y = send_twist_ry;
    vehicle_msg.twist_cmd.twist.angular.z = send_twist_rz;

    // setup to send the twist control messages
    vehicle_msg.ctrl_cmd.linear_velocity = send_linear_velocity;
    vehicle_msg.ctrl_cmd.linear_acceleration = send_linear_acceleration;
    vehicle_msg.ctrl_cmd.steering_angle = send_steering_angle;

    // setup to send the twist emergency messages
    vehicle_msg.emergency = send_emergency;

  
    //Publish
    command.publish(vehicle_msg);
    
    // Repeat after set loop
    loop_rate.sleep();
    }
}
