// This is the vehicle node and the vehicle send the message if the user request

#include <cmath>
#include <thread>
 #include <stdio.h> 
#include <ros/ros.h>

#include <autoware_msgs/VehicleStatus.h>

#include "g30esli_interface_util.h"
#include "can_utils/cansend.h"
#include "can_utils/cansend_util.h"
#include "can_utils/ymc_can.h"
using namespace std;
// device
std::string can_device;




int main(int argc, char* argv[])
{
  // set message type
  autoware_msgs::VehicleStatus set_msg;
  // cansend tool
mycansend::CanSender msg_cansend;
ros::init(argc, argv, "vehicle_data");
 ros::NodeHandle private_nh("~");

// Set can device
  private_nh.param<std::string>("device", can_device, "can0");

 // initilize cansend tool
  msg_cansend.init(can_device);

 // set canID and other sending data size
  std::string send_id("220");
  
  
  int a;
  cout << "Please see status description"<< endl << "For Door status press 1" << endl << "For Gear Shift press 2" << endl << "For speed press 3" << endl << "For Lamp press 4" << endl << "For steering angle press 5" << endl << "What status do you want:";
  cin >> a;
 
  // Door Status
  if (a == 1){
 unsigned char data[8] = {};
 int door_status;
 int value_door;
 cout << "What is door status:";
 cin >> door_status; 
 if (door_status == 0)
 {
  value_door=0;
  
 }
 else if (door_status == 1)
 {
  value_door=1;
  
 }
 else if (door_status == 2)
 {
  value_door=2;
  
 }
 else if (door_status == 3)
 {
  value_door=3;
  
 }
 else 
 {
  ROS_ERROR("No door status found");
  exit(1);
 }
  data[0] = 0; data[1] = value_door; data[2] = 0; data[3] = 0;
  data[4] = 0; data[5] = 0; data[6] = 0; data[7] = 0;
  size_t data_size = sizeof(data) / sizeof(data[0]);
  char can_cmd[256];
  std::strcpy(can_cmd, mycansend::makeCmdArgument(data, data_size, send_id).c_str());
  msg_cansend.send(can_cmd);
  }

// Gear status msg
else if (a == 2){
 unsigned char data[8] = {};
 int gear_status;
 int value_gear;
 
 cout << "What is Gear status:";
 cin >> gear_status; 
 if (gear_status == 0)
 {
  value_gear=0;
  
 }
 else if (gear_status == 1)
 {
  value_gear=1;
 
 }
 else if (gear_status == 2)
 {
  value_gear=2;
  
 }
 else if (gear_status == 3)
 {
  value_gear=3;
  
 }
 else 
 {
  ROS_ERROR("No gear status found");
  exit(1);
 }
  data[0] = 0; data[1] = value_gear; data[2] = 0; data[3] = 0;
  data[4] = 0; data[5] = 0; data[6] = 0; data[7] = 0;
  size_t data_size = sizeof(data) / sizeof(data[0]);
  char can_cmd[256];
  std::strcpy(can_cmd, mycansend::makeCmdArgument(data, data_size, send_id).c_str());
  msg_cansend.send(can_cmd);
  }

// Speed status msg
else if (a == 3){
 unsigned char data[8] = {};
 set_msg.speed = 3; 
 
 
  data[0] = 0; data[1] = 0; data[2] = 0; data[3] = 0;
  data[4] = 0; data[5] = 0; data[6] = 0; data[7] = set_msg.speed;
  size_t data_size = sizeof(data) / sizeof(data[0]);
  char can_cmd[256];
  std::strcpy(can_cmd, mycansend::makeCmdArgument(data, data_size, send_id).c_str());
  msg_cansend.send(can_cmd);
  }

//Light Status msg
else if (a == 4)
{
  unsigned char data[8] = {};
 int brake_light = 0;
 set_msg.light = 0;
 int reverse_light = 0;
 set_msg.LAMP_LEFT;
 int temp_out = 26;
 int temp_in = 18;
 int door_interface = 0;
 data[0] = brake_light; data[1] = set_msg.light; data[2] = reverse_light; data[3] = set_msg.LAMP_LEFT;
  data[4] = temp_in; data[5] = temp_out; data[6] = door_interface; data[7] = 0;
size_t data_size = sizeof(data) / sizeof(data[0]);
  char can_cmd[256];
  std::strcpy(can_cmd, mycansend::makeCmdArgument(data, data_size, send_id).c_str());
  msg_cansend.send(can_cmd);
}

// Steering value status
else if (a == 5){
 unsigned char data[8] = {};
 set_msg.angle = 45; 
 
 
  data[0] = set_msg.angle; data[1] = 0; data[2] = 0; data[3] = 0;
  data[4] = 0; data[5] = 0; data[6] = 0; data[7] = 0;
  size_t data_size = sizeof(data) / sizeof(data[0]);
  char can_cmd[256];
  std::strcpy(can_cmd, mycansend::makeCmdArgument(data, data_size, send_id).c_str());
  msg_cansend.send(can_cmd);
  }
else
{
 ROS_ERROR("This is not a valid request for status");
}
  // Please run the status node after every status
  ros::spinOnce();
  
  return 0;
}





