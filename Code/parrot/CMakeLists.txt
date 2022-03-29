cmake_minimum_required(VERSION 3.0.2)
project(parrot)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(
  catkin REQUIRED
  COMPONENTS
    roscpp
    rospy
	std_msgs
	geometry_msgs
	sensor_msgs

	ardrone_autonomy
    
	Domain
	DroneController
    Adapter
)


###################################
## catkin specific configuration ##
###################################
catkin_package(
#  INCLUDE_DIRS include
	LIBRARIES parrotController
	CATKIN_DEPENDS roscpp rospy std_msgs sensor_msgs ardrone_autonomy
#  DEPENDS system_lib
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
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(parrotController
	include/parrot/Header.h
	src/parrotBattery.cpp
	src/parrotControl.cpp
	src/parrotIMU.cpp
	src/parrotStatus.cpp
  	src/parrotTransmitter.cpp
)

## Declare a C++ executable
add_executable(MessageTracker 
	src/MessageTracker.cpp
)

## Add cmake target dependencies of the executable
add_dependencies(parrotController ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} Domain_lib DroneController_lib Adapter_lib)
add_dependencies(MessageTracker ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(parrotController ${catkin_LIBRARIES} Domain_lib DroneController_lib Adapter_lib)
target_link_libraries(MessageTracker ${catkin_LIBRARIES})

#############
## Install ##
#############
## Mark libraries for installation
install(TARGETS parrotController 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

## Mark cpp header files for installation
install(DIRECTORY include/parrot/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


