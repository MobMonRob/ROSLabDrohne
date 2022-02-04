cmake_minimum_required(VERSION 3.0.2)
project(calling)

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
	LIBRARIES calling_lib
	CATKIN_DEPENDS roscpp rospy std_msgs
)

###########
## Build ##
###########
include_directories(
	include
	include/calling
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(calling_lib
	include/calling/Calling.h
	include/calling/Callable.h
	include/calling/Caller.h
	src/Caller.cpp
)

target_link_libraries(calling_lib ${catkin_LIBRARIES})

#############
## Install ##
#############
install(TARGETS calling_lib 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(DIRECTORY include/calling/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


