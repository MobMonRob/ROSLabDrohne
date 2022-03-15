cmake_minimum_required(VERSION 3.0.2)
project(Domain)

add_compile_options(-std=c++11)

find_package(
	catkin REQUIRED COMPONENTS
		roscpp
		rospy
		std_msgs
		
		Abstraction
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
	LIBRARIES Domain_lib
	CATKIN_DEPENDS roscpp rospy std_msgs
)

###########
## Build ##
###########
include_directories(
	include
	../Abstraction/include
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(Domain_lib
	include/Domain/Header.h
	src/Controllable.cpp
	src/Controller_Basic.cpp
	src/Controller_D.cpp
	src/Controller_I.cpp
	src/Controller_Input.cpp
	src/Controller_P.cpp
	src/Controller_PID.cpp
	src/Controller_PT.cpp
	src/ControllerSystem.cpp
	src/Input.cpp
	src/Integral1.cpp
	src/Integral2.cpp
	src/TimedDifference.cpp
)

## Add cmake target dependencies of the executable
add_dependencies(Domain_lib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} Abstraction_lib)

## Specify libraries to link a library or executable target against
target_link_libraries(Domain_lib ${catkin_LIBRARIES} Abstraction_lib)

#############
## Install ##
#############
install(TARGETS Domain_lib 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(DIRECTORY include/Domain/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


