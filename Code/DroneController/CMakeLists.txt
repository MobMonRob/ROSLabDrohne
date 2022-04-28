cmake_minimum_required(VERSION 3.0.2)
project(DroneController)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(
	catkin REQUIRED
	COMPONENTS
		roscpp
		rospy

		Domain
)


###################################
## catkin specific configuration ##
###################################
catkin_package(
#  INCLUDE_DIRS include
	LIBRARIES DroneController_lib
	CATKIN_DEPENDS roscpp rospy
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
include_directories(
	include
	../Domain/include
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(DroneController_lib
	./include/DroneController/Header.h
	src/Batteryable.cpp
	src/DroneControlable.cpp
	src/IMUable.cpp
	src/IMUState.cpp
	src/Pose.cpp
	src/PoseBuildable.cpp
	src/PoseControlable.cpp
	src/Rotor.cpp
	src/Statusable.cpp
	src/Thrustable.cpp
	src/Watchdog.cpp
	src/ImpactWatcher.cpp
	src/ImpactOK.cpp
	src/PercentageOK.cpp
	src/PercentageOK.cpp
	src/TimeoutOK.cpp
	src/VoltageOK.cpp
)

## Add cmake target dependencies of the executable
add_dependencies(DroneController_lib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} Domain_lib)

## Specify libraries to link a library or executable target against
target_link_libraries(DroneController_lib ${catkin_LIBRARIES} Domain_lib)


#############
## Install ##
#############
## Mark libraries for installation
install(TARGETS DroneController_lib 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

## Mark cpp header files for installation
install(DIRECTORY include/DroneController/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


