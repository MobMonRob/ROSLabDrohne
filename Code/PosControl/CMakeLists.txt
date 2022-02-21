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

add_executable(TestPoseExample
	src/TestPose_Example.cpp
)
add_executable(TestPose
	src/TestPose.cpp
)

add_executable(TestRCHeartbeated
	src/TestRC_Heartbeated.cpp
)
add_executable(TestRCOverride
	src/TestRCOverride.cpp
)
add_executable(TestRCOffboarded
	src/TestRCOverride_OFFBOARD.cpp
)
add_executable(TestRCTransmitter
	src/TestRCTransmitter.cpp
)

add_executable(TestMCHeartbeated
	src/TestMC_Heartbeated.cpp
)
add_executable(TestMCControl
	src/TestMCControl.cpp
)
add_executable(TestMCSend
	src/TestMCSend.cpp
)

add_executable(TestThrust
	src/TestThrust.cpp
)

add_executable(TestPosLocalPos
	src/TestPosLocalPos.cpp
)
add_executable(TestPosLocalPosMasked
	src/TestPosLocalPos_Masked.cpp
)

add_executable(TestPosLocalVel
	src/TestPosLocalVel.cpp
)
add_executable(TestPosLocalVelMasked
	src/TestPosLocalVel_Masked.cpp
)

add_executable(TestPosLocalAccel
	src/TestPosLocalAccel.cpp
)


## Add cmake target dependencies of the executable
add_dependencies(BridgeNode ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController Adapter_lib Application_lib Domain_lib Abstraction_lib)

add_dependencies(TestPoseExample ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)
add_dependencies(TestPose ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)

add_dependencies(TestRCHeartbeated ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController calling_lib threading_lib)
add_dependencies(TestRCOverride ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)
add_dependencies(TestRCOffboarded ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)
add_dependencies(TestRCTransmitter ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController calling_lib threading_lib)

add_dependencies(TestMCHeartbeated ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController calling_lib threading_lib)
add_dependencies(TestMCControl ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController calling_lib threading_lib)
add_dependencies(TestMCSend ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController calling_lib threading_lib)

add_dependencies(TestThrust ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)

add_dependencies(TestPosLocalPos ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)
add_dependencies(TestPosLocalPosMasked ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)
add_dependencies(TestPosLocalVel ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)
add_dependencies(TestPosLocalVelMasked ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)
add_dependencies(TestPosLocalAccel ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} coexController)





## Specify libraries to link a library or executable target against
target_link_libraries(BridgeNode ${catkin_LIBRARIES} coexController Adapter_lib Application_lib Domain_lib Abstraction_lib)

target_link_libraries(TestPose ${catkin_LIBRARIES} coexController)
target_link_libraries(TestPoseExample ${catkin_LIBRARIES} coexController)

target_link_libraries(TestRCHeartbeated ${catkin_LIBRARIES} coexController calling_lib threading_lib)
target_link_libraries(TestRCOverride ${catkin_LIBRARIES} coexController)
target_link_libraries(TestRCOffboarded ${catkin_LIBRARIES} coexController)
target_link_libraries(TestRCTransmitter ${catkin_LIBRARIES} coexController calling_lib threading_lib)

target_link_libraries(TestMCHeartbeated ${catkin_LIBRARIES} coexController calling_lib threading_lib)
target_link_libraries(TestMCControl ${catkin_LIBRARIES} coexController calling_lib threading_lib)
target_link_libraries(TestMCSend ${catkin_LIBRARIES} coexController calling_lib threading_lib)

target_link_libraries(TestThrust ${catkin_LIBRARIES} coexController)

target_link_libraries(TestPosLocalPos ${catkin_LIBRARIES} coexController)
target_link_libraries(TestPosLocalPosMasked ${catkin_LIBRARIES} coexController)
target_link_libraries(TestPosLocalVel ${catkin_LIBRARIES} coexController)
target_link_libraries(TestPosLocalVelMasked ${catkin_LIBRARIES} coexController)
target_link_libraries(TestPosLocalAccel ${catkin_LIBRARIES} coexController)

