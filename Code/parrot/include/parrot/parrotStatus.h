#ifndef PARROTSTATUS_H
#define PARROTSTATUS_H

#include "DroneController/Statusable.h"

#include <ros/ros.h>

#include <string>
#include <map>

#include <mavros_msgs/State.h>
#include <mavros_msgs/SetMode.h>


#include "parrot/parrotBattery.h"

/* https://dev.px4.io/v1.10_noredirect/en/ros/mavros_offboard.html
 * PX4 has a timeout of 500ms between two Offboard commands. => The publishing rate must be faster than 2 Hz.
 * If this timeout is exceeded, the commander will fall back to the last mode the vehicle was in before entering Offboard mode.
 */


class parrotStatus : public Statusable
{
public:
	parrotStatus(parrotBattery* Battery) : Statusable(Battery) {};
	~parrotStatus();
	


	Timestamp getTime() override { return Timestamp();};
	
	
private:
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);


private:
	ros::NodeHandle nh_;
	ros::Subscriber SubStatus_;

	ardrone_autonomy::Navdata Status_;
};


const std::string coexMode_Manual = "MANUAL";
const std::string coexMode_Offboard = "OFFBOARD";
const std::string coexMode_Stabilized = "STABILIZED";

#endif // PARROTSTATUS_H


