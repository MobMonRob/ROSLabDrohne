cmake_minimum_required(VERSION 3.0.2)
project(Adapter)

find_package(
	catkin REQUIRED COMPONENTS
		roscpp
		rospy
		std_msgs
		
		Abstraction
		Domain
		Application
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
	LIBRARIES Adapter_lib
	CATKIN_DEPENDS roscpp rospy std_msgs
)

###########
## Build ##
###########
include_directories(
	include
	../Abstraction/include
	../Domain/include
	../Application/include
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(Adapter_lib
	include/Adapter/Header.h
	src/ActionAdapter.cpp
	src/ActionAdapter_Mock.cpp
)

target_link_libraries(Adapter_lib ${catkin_LIBRARIES})

#############
## Install ##
#############
install(TARGETS Adapter_lib 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(DIRECTORY include/Adapter/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


