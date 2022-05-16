cmake_minimum_required(VERSION 3.0.2)
project(Controller)

add_compile_options(-std=c++11)

find_package(
	catkin REQUIRED COMPONENTS
		roscpp
		rospy
		
		Domain
		DroneController
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
	LIBRARIES Controller_lib
	CATKIN_DEPENDS roscpp rospy
)

###########
## Build ##
###########
include_directories(
	include
	../Domain/include
	../DroneController/include
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(Controller_lib
	./include/Controller/Header.h	
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
	src/PoseController.cpp
	src/TimedDifference.cpp
)

## Add cmake target dependencies of the executable
add_dependencies(Controller_lib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} Domain_lib DroneController_lib)

## Specify libraries to link a library or executable target against
target_link_libraries(Controller_lib ${catkin_LIBRARIES} Domain_lib DroneController_lib)

#############
## Install ##
#############
install(TARGETS Controller_lib 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(DIRECTORY include/Controller/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


