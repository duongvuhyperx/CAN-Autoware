#include <cmath>
#include <thread>
 #include <stdio.h> 
#include <iostream>
#include <ros/ros.h>
#include <vector>

#include <geometry_msgs/TwistStamped.h>
#include <autoware_msgs/VehicleCmd.h>
#include <autoware_msgs/VehicleStatus.h>
#include "g30esli_interface_util.h"
#include "can_utils/cansend.h"
#include "can_utils/cansend_util.h"
#include "can_utils/ymc_can.h"


// Initialize variables
bool g_terminate_thread = false;
int g_mode;
using namespace std;
double _current_vel_mps;
int id;

// Initialize publisher globally
ros::Publisher g_current_twist_pub;

// Initially it sends no data to topic
std::string raw_data = "No data";


// Function to read can data
void readCanData (FILE* fp){
  std::vector<std::string> data;
  char buf[64];
  while (fgets(buf, sizeof(buf), fp) != NULL && !g_terminate_thread)
  { 
    
     raw_data = std::string(buf);

    if (raw_data.size() > 0)
    {
      // split data to strings
      // data format is like this
      // can0  200   [8]  08 00 00 00 01 00 01 29
      std::vector<std::string> parsed_data = ymc::splitString(raw_data);
     

      // delete first 3 elements
      //std::vector<std::string> 
      data = parsed_data;
      
      data.erase(data.begin(), data.begin() + 3);

      id = std::stoi(parsed_data.at(1), nullptr, 10);
       _current_vel_mps = ymc::translateCanData(id, data, &g_mode);

       // Display Data coming on can bus from vehicle
       ROS_INFO("Data coming on Can bus = %s", raw_data.c_str());
       
    }
  }
        

}



// Main
int main(int argc, char* argv[])
{
  // initialize ros
   ros::init(argc, argv, "from_vehicle");
   ros::NodeHandle n;
  
  // calling publisher
    ros::Publisher g_current_twist_pub = n.advertise<autoware_msgs::VehicleStatus>("cantopic", 10);
       
  // set loop time
    ros::Rate loop_rate(0.8);

 // read data from canbus
 FILE* fp = popen("candump can0", "r");

 // set thread (Note its important to make this because the topic and can bus communication will be done parallely otherwise the port is busy)  
 std::thread t2(readCanData, fp);
    
    // Publish the message of can bus on ros topic
      while (ros::ok()){
  
         autoware_msgs::VehicleStatus ts;
         ts.header.frame_id = "base_link";
         ts.tm = raw_data.c_str();
         g_current_twist_pub.publish(ts);
         loop_rate.sleep();

 }
    // close thread and port
    g_terminate_thread = true;
    t2.join();
    pclose(fp);
  return 0;
}





