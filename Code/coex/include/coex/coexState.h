#ifndef COEXSTATE_H
#define COEXSTATE_H

#include <ros/ros.h>

#include <string>
#include <map>

#include <mavros_msgs/State.h>
#include <mavros_msgs/SetMode.h>

#include "calling/Caller.h"

#include "threading/AutoClient.h"

/* https://dev.px4.io/v1.10_noredirect/en/ros/mavros_offboard.html
 * PX4 has a timeout of 500ms between two Offboard commands. => The publishing rate must be faster than 2 Hz.
 * If this timeout is exceeded, the commander will fall back to the last mode the vehicle was in before entering Offboard mode.
 */


class coexState : public Caller
{
public:
	coexState();
	~coexState();
	
	bool setMode(std::string Mode);
	bool setArmState(bool arming);
	
	bool getConnected() { return this->State_.connected; };
	bool getArmed();
	std::string getMode() { return this->State_.mode; };
	bool getManualInput() { return this->State_.manual_input; };
	std::string getSystemStatus();
	std::string getSystemStatus(int StatusID);
	double getTime() { return this->State_.header.stamp.toSec();};
	
	void cbState(const mavros_msgs::State::ConstPtr& State);	
	
private:
	void initSystemStatus();
	
private:
	ros::NodeHandle nh_;
	ros::Subscriber SubState_;
	AutoClient<mavros_msgs::SetMode> ClMode_;
	
	mavros_msgs::State State_;
	std::map<int, std::string> SystemStatus_;
};

#endif // COEXSTATE_H


