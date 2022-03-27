cmake_minimum_required(VERSION 3.0.2)
project(coex)

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
    mavros_msgs
    sensor_msgs
    
    threading
    calling
    Adapter
)


################################################
## Declare ROS messages, services and actions ##
################################################
## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
    std_msgs
    geometry_msgs
    mavros_msgs
    sensor_msgs
)


###################################
## catkin specific configuration ##
###################################
catkin_package(
#  INCLUDE_DIRS include
	LIBRARIES coexController
	CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs mavros_msgs sensor_msgs 
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
include_directories(
	include
	../calling/include
	../threading/include
	../Abstraction/include
	../Domain/include
	../Application/include
	../Adapter/include
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(coexController
	../Adapter/include/Adapter/Transmitable.h
	include/coex/Header.h
	src/coexBattery.cpp
	src/coexControl.cpp
	src/coexMC.cpp
	src/coexOrientation.cpp
	src/coexRC.cpp
	src/coexRC_Receiver.cpp
	src/coexRC_Transmitter.cpp
	src/coexState.cpp
  	src/coexTransmitable.cpp
  	src/Joystick.cpp
	src/JoystickAxis.cpp
)

## Add cmake target dependencies of the executable
add_dependencies(coexController ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coex_generate_messages_cpp threading_lib calling_lib Application_lib)

## Specify libraries to link a library or executable target against
target_link_libraries(coexController ${catkin_LIBRARIES} threading_lib calling_lib Application_lib)


#############
## Install ##
#############
## Mark libraries for installation
install(TARGETS coexController 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

## Mark cpp header files for installation
install(DIRECTORY include/coex/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


