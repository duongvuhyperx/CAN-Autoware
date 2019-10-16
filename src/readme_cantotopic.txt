

Set up virtual can for testing (Every time the system is shut down you have to do this vcan procedure)

1) sudo modprobe vcan
2) sudo ip link add dev can0 type vcan
3) sudo ip link set up can0

---------------------------------------------------------

How to compile and run

1) Extract the package and
   cd can-autoware/

2) Only for first time " Open the package delete the devel and build folder"

3) OPen terminal 1 and type
   >> roscore

4) Open terminal 2 and catkin_make in the package root directory 
5) if you open the new terminal then you should go the directory and then do >> source devel/setup.bash

5) To ask the vehicle status:
   
   >> rosrun vehicle vehicle_data

6) To receive the data from vehicle to user using can bus and for can bus to topic OPen terminal 3 and 
   >> cd can-autoware/ 
   >> source devel/setup.bash
   >> rosrun vehicle from_vehicle

7) OPen 4 terminal and see the can data on topic
  >> cd can-autoware/ 
   >> source devel/setup.bash
  >> rostopic echo /cantopic 


ENjoy
