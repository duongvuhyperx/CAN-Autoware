cmake_minimum_required(VERSION 2.8.3)
project(vehicle)

## Compile as C++11, supported in ROS Kinetic and newer
 add_compile_options(-std=c++11)
 set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
#find_package(autoware_build_flags REQUIRED)
find_package(autoware_msgs REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  autoware_msgs
  geometry_msgs
  rosconsole
  roscpp
  message_generation
  std_msgs
  can_msgs
  socketcan_interface
)



################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
 
  
#generate_messages(
 # DEPENDENCIES
 # geometry_msgs
 # std_msgs
#)
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   autoware_msgs#   geometry_msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    #socketcan_to_topic
    topic_to_socketcan
  CATKIN_DEPENDS
  roscpp
  geometry_msgs
  rosconsole
  autoware_msgs
  message_runtime
  std_msgs
  can_msgs
  socketcan_interface
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${autoware_msgs_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
  include
)

IF (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.1)
  set(LIB_VERSION 2.0) # _GLIBCXX_USE_CXX11_ABI is 1
ELSE ()
  set(LIB_VERSION 1.0) # _GLIBCXX_USE_CXX11_ABI is 0
ENDIF ()



add_executable(publish_vehicle_data
  src/publish_vehicle_data.cpp
)
add_executable(subscribe_vehicle
  src/subscribe_vehicle.cpp
)

add_dependencies(publish_vehicle_data
  ${catkin_EXPORTED_TARGETS}
)
add_dependencies(subscribe_vehicle
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(publish_vehicle_data
  ${catkin_LIBRARIES}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/libymc_can_${LIB_VERSION}${LIB_ARCH}.a
)
target_link_libraries(subscribe_vehicle
 
  ${catkin_LIBRARIES}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/libymc_can_${LIB_VERSION}${LIB_ARCH}.a
)

add_executable(from_vehicle
  src/from_vehicle.cpp
)

add_dependencies(from_vehicle
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(from_vehicle
  ${catkin_LIBRARIES}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/libymc_can_${LIB_VERSION}${LIB_ARCH}.a
)

add_executable(vehicle_data
  src/vehicle_data.cpp
)

add_dependencies(vehicle_data
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(vehicle_data
  ${catkin_LIBRARIES}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/libymc_can_${LIB_VERSION}${LIB_ARCH}.a
)

