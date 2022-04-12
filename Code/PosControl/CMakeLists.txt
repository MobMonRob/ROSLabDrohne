cmake_minimum_required(VERSION 3.0.2)
project(PosControl)

add_compile_options(-std=c++11)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(
  catkin REQUIRED
  COMPONENTS
    message_generation
    roscpp
    rospy
    std_msgs
    geometry_msgs
    sensor_msgs

	ardrone_autonomy

    Domain
	DroneController
    Adapter
    Controller
	parrot
)


###################################
## catkin specific configuration ##
###################################
catkin_package(
	INCLUDE_DIRS
		include
#  LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs sensor_msgs ardrone_autonomy
#  DEPENDS
)


###########
## Build ##
###########
## Specify additional locations of header files
include_directories(
	include
	../Domain/include
	../DroneController/include
	../Adapter/include
	../Controller/include
	../parrot/include
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(AutoController 
	include/PosControl/Header.h
	src/Integral1.cpp
	src/Integral2.cpp
	src/PosBridge.cpp
	src/PoseBuilder.cpp
	src/RosBridge.cpp
	src/Transmitter_Mock.cpp
)

add_executable(ManualController 
	src/ManualController.cpp
)

## Add cmake target dependencies of the executable
add_dependencies(AutoController ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} Domain_lib DroneController_lib Adapter_lib Controller_lib parrotController)
add_dependencies(ManualController ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} parrotController)

## Specify libraries to link a library or executable target against
target_link_libraries(AutoController ${catkin_LIBRARIES} Domain_lib DroneController_lib Adapter_lib Controller_lib parrotController)
target_link_libraries(ManualController ${catkin_LIBRARIES} parrotController)
