cmake_minimum_required(VERSION 3.0.2)
project(Abstraction)

find_package(
	catkin REQUIRED COMPONENTS
		roscpp
		rospy
		std_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
	LIBRARIES Abstraction_lib
	CATKIN_DEPENDS roscpp rospy std_msgs
)

###########
## Build ##
###########
include_directories(
	include
	include/Abstraction
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(Abstraction_lib
	include/Abstraction/Header.h
	src/TimedValue.cpp
	src/Value.cpp
	src/Vector3D.cpp
)

target_link_libraries(Abstraction_lib ${catkin_LIBRARIES})

#############
## Install ##
#############
install(TARGETS Abstraction_lib 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(DIRECTORY include/Abstraction/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


