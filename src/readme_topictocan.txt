Prerequisites:
1) sudo apt-get install ros-kinetic-autoware-* (if kinetic)
---------------------------------OR----------------------------------------
sudo apt-get install ros-melodic-autoware-* (if melodic)

2) sudo apt-get install can-utils

Set up virtual can for testing

1) sudo modprobe vcan
2) sudo ip link add dev can0 type vcan
3) sudo ip link set up can0



How to compile and run

1) Extract the package and
   cd can-autoware/

2) Only for first time " Open the package delete the devel and build folder"

3) OPen terminal 1 and type
   >> roscore

4) Open terminal 2 and catkin_make in the package root directory 

5) To run subscriber node and send on can bus open terminal 1 type 
   >> source devel/setup.bash
   >> rosrun vehicle subscribe_vehicle 

6) To run publisher node OPen terminal 3 and 
   >> cd can-autoware/ 
   >> source devel/setup.bash
   >> rosrun vehicle publish_vehicle_data

7) OPen 4 terminal for virtual can to see the data transfer on can bus
  >> sudo candump can0


ENjoy
