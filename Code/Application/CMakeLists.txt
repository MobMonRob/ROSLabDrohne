cmake_minimum_required(VERSION 3.0.2)
project(Application)

find_package(
	catkin REQUIRED COMPONENTS
		roscpp
		rospy
		std_msgs
		
		Abstraction
		Domain
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
	LIBRARIES Application_lib
	CATKIN_DEPENDS roscpp rospy std_msgs
)

###########
## Build ##
###########
include_directories(
	include
	../Abstraction/include
	../Domain/include
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(Application_lib
	include/Application/Header.h
	src/AccelToPos.cpp
	src/AngVelToAng.cpp
	src/State.cpp
	src/StateHandler.cpp
)

## Add cmake target dependencies of the executable
add_dependencies(Application_lib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} Domain_lib Abstraction_lib)

## Specify libraries to link a library or executable target against
target_link_libraries(Application_lib ${catkin_LIBRARIES} Domain_lib Abstraction_lib)

#############
## Install ##
#############
install(TARGETS Application_lib 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(DIRECTORY include/Application/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


