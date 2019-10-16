
#include <cmath>
#include <thread>

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <autoware_msgs/VehicleCmd.h>
#include "can_utils/cansend.h"
#include "can_utils/cansend_util.h"
#include "can_utils/ymc_can.h"
#include "g30esli_interface_util.h"


// device
std::string can_device;




 // Initialize globally 
  double target_velocity = 0;
  double target_steering_angle_deg = 0;
  int target_brake = 0;
  int mode_control = 0;
   int rec_status = 0;
  int head_right = 0;
  int head_left = 0;
   int door_control = 0;
 int turn_signal = 0;

void vehicle_cmd_callback(const autoware_msgs::VehicleCmdConstPtr& msg)
{

    ros::NodeHandle private_nh("~");

// cansend tool
mycansend::CanSender msg_cansend;


// Set can device
  private_nh.param<std::string>("device", can_device, "can0");

 // initilize cansend tool
  msg_cansend.init(can_device);

    
 // Speed Control in km/h (multiply with 3.6)
     target_velocity = msg->twist_cmd.twist.linear.x; 
     int speed = 0;
  //if ((target_velocity >=0)&&(target_velocity <=15))
  //   {
 //     speed = 103; //reverse 
   //  }
  //else if(target_velocity == 0)
  if (target_velocity <=0)
     {
      speed = 100; // stop
     }
  else if ((target_velocity >=0)&&(target_velocity <=20))
     {
      speed = 102; // forward
     }
  else 
     {
      ROS_ERROR("speed out of control");
      speed = 101;
     }
 // Steering Control 

    //  target_steering_angle_deg = msg->twist_cmd.twist.angular.z;
       int steer = 0; // 
       steer = msg->twist_cmd.twist.angular.z;
    //if ((target_steering_angle_deg >=0)&&(target_steering_angle_deg <=1))
     //  {
     //     steer = 2; //right turn

     //  }
   // else if (target_steering_angle_deg == 0)
     //  {
     //     steer = 100; // straight
     //  }
    //else if ((target_steering_angle_deg >=-1)&&(target_steering_angle_deg <=0))
    //   {
    //      steer = 101; //left
    //   } 
   // else 
    // {
     // ROS_ERROR("steer out of control");
     // steer = 101;
   
      // send can data
   //  }
 // Brake Control
    target_brake = msg->brake_cmd.brake;

 // Set Control Mode 1 for automatic 0 for joystick
  mode_control = msg->mode;

 // Set receiver status
    rec_status = 1;

 // Headlight 
    head_right = msg->lamp_cmd.r;
    head_left = msg->lamp_cmd.l;
    int head_status = 0; //0>High 1>low 2>off
  if ((head_right == 0)&&(head_left == 0))
     {
       head_status = 0;
     }

  else if (((head_right == 1)&&(head_left == 0)) || ((head_right == 0)&&(head_left == 1)) || ((head_right == 1)&&(head_left == 1)))
     {
       head_status = 1;
     }
  else if ((head_right == 2)&&(head_left == 2))
     {
       head_status = 2;
     }
  else 
     {
      ROS_ERROR("Head light error");
      head_status = 101;
     }

 // Door Control 0 > not control, 1> open 2>close
    door_control = 0;

 // Turn Signal
    turn_signal = 0;


    // data array 

unsigned char data[8] = {};
data[0] = target_brake;
data[1] = steer;
data[2] = speed;
data[3] = door_control;
data[4] = turn_signal;
data[5] = head_status;
data[6] = rec_status ;
data[7] = mode_control;


// send can data
// safety if wrong speed or steering data
if ((speed == 101) || (steer == 101))
   {
    ROS_ERROR("failure");
   } 
// send right data
else {
std::string send_id("260");
size_t data_size = sizeof(data) / sizeof(data[0]);
char can_cmd[256];
std::strcpy(can_cmd, mycansend::makeCmdArgument(data, data_size, send_id).c_str());
msg_cansend.send(can_cmd);
}

}




int main(int argc, char **argv) 
{
// Initialize ROS
ros::init(argc, argv, "subscribe_vehicle");
ros::NodeHandle n;

// Calling Subscriber 

ros::Subscriber vehicle_cmd_sub = n.subscribe<autoware_msgs::VehicleCmd>("vehicle_cmd", 1, vehicle_cmd_callback);


// send data till user dont stop
ros::spin();
return 0;
}


