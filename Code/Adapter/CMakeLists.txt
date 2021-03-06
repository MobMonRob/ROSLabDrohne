cmake_minimum_required(VERSION 3.0.2)
project(Adapter)

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
	LIBRARIES Adapter_lib
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
add_library(Adapter_lib
	./include/Adapter/Header.h
	src/StateBuilder.cpp
	src/StateHandler.cpp
)

## Add cmake target dependencies of the executable
add_dependencies(Adapter_lib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} Domain_lib DroneController_lib)

## Specify libraries to link a library or executable target against
target_link_libraries(Adapter_lib ${catkin_LIBRARIES} Domain_lib DroneController_lib)

#############
## Install ##
#############
## Mark libraries for installation
install(TARGETS Adapter_lib 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

## Mark cpp header files for installation
install(DIRECTORY include/Adapter/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


