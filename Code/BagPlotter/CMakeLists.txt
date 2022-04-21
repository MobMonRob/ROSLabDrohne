cmake_minimum_required(VERSION 3.0.2)
project(BagPlotter)

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
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(BagPlotter_ND_AV
	include/BagPlotter/DataCollector.h
	src/DataCollector.cpp
	src/BagPlotter_NavData_AccelVel.cpp
)
add_executable(BagPlotter_GT
	include/BagPlotter/DataCollector.h
	src/DataCollector.cpp
	src/BagPlotter_GeomTwist.cpp
)

## Add cmake target dependencies of the executable
add_dependencies(BagPlotter_ND_AV ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(BagPlotter_GT ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(BagPlotter_ND_AV ${catkin_LIBRARIES})
target_link_libraries(BagPlotter_GT ${catkin_LIBRARIES})
