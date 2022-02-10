cmake_minimum_required(VERSION 3.0.2)
project(PosControl)

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
    mavros_msgs
    sensor_msgs
    
    Abstraction
    Domain
    Application
    Adapter
    calling
    threading
    coex
)


###################################
## catkin specific configuration ##
###################################
catkin_package(
	INCLUDE_DIRS
		include
		../coex/include
#  LIBRARIES ${PROJECT_NAME}
	CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS
)


###########
## Build ##
###########
## Specify additional locations of header files
include_directories(
	include
	../threading/include
	../calling/include
	../Abstraction/include
	../Domain/include
	../Application/include
	../Adapter/include
	../coex/include 
	${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(BridgeNode 
	include/PosControl/Header.h
	src/PosBridge.cpp
	src/RosBridge.cpp
	src/StateBuilder.cpp
)

add_executable(TestPose
	src/TestPose.cpp
)

add_executable(TestMC
	src/TestMC.cpp
)

add_executable(TestRC
	src/TestRC.cpp
)

add_executable(TestRC2
	src/TestRC2.cpp
)

add_executable(TestThrust
	src/TestThrust.cpp
)



## Add cmake target dependencies of the executable
add_dependencies(BridgeNode ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController Adapter_lib Application_lib Domain_lib Abstraction_lib)
add_dependencies(TestPose ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)
add_dependencies(TestMC ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)
add_dependencies(TestRC ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)
add_dependencies(TestRC2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController calling_lib threading_lib)
add_dependencies(TestThrust ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)

## Specify libraries to link a library or executable target against
target_link_libraries(BridgeNode ${catkin_LIBRARIES} coexController Adapter_lib Application_lib Domain_lib Abstraction_lib)
target_link_libraries(TestPose ${catkin_LIBRARIES} coexController)
target_link_libraries(TestMC ${catkin_LIBRARIES} coexController)
target_link_libraries(TestRC ${catkin_LIBRARIES} coexController)
target_link_libraries(TestRC2 ${catkin_LIBRARIES} coexController calling_lib threading_lib)
target_link_libraries(TestThrust ${catkin_LIBRARIES} coexController)








