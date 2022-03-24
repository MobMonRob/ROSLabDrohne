cmake_minimum_required(VERSION 3.0.2)
project(Domain)

add_compile_options(-std=c++11)

find_package(
	catkin REQUIRED COMPONENTS
		roscpp
		rospy
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
	LIBRARIES Domain_lib
	CATKIN_DEPENDS roscpp rospy
)

###########
## Build ##
###########
include_directories(
	include
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(Domain_lib
	./include/Domain/Header.h
	src/SafetyProvider.cpp
	src/TimedValue.cpp
	src/Value.cpp
	src/Vector3D.cpp
)

## Add cmake target dependencies of the executable
add_dependencies(Domain_lib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(Domain_lib ${catkin_LIBRARIES})

#############
## Install ##
#############
install(TARGETS Domain_lib 
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(DIRECTORY include/Domain/
	DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})


