#ifndef COEXSTATE_H
#define COEXSTATE_H

#include <ros/ros.h>

#include <string>
#include <map>

#include <mavros_msgs/State.h>
#include <mavros_msgs/SetMode.h>

#include "calling/Caller.h"
#include "threading/AutoClient.h"
#include "coex/coexBattery.h"

/* https://dev.px4.io/v1.10_noredirect/en/ros/mavros_offboard.html
 * PX4 has a timeout of 500ms between two Offboard commands. => The publishing rate must be faster than 2 Hz.
 * If this timeout is exceeded, the commander will fall back to the last mode the vehicle was in before entering Offboard mode.
 */


class coexState : public Caller
{
public:
	coexState(coexBattery *Battery, bool silent = false);
	~coexState();
	
	bool operator==(const mavros_msgs::State& S);


	bool setArmState(bool arming);
	bool setMode(std::string Mode);
	
	coexBattery* getBattery() const { return this->Battery_; };
	bool getConnected() const { return this->State_.connected; };
	bool getArmState() const { return this->State_.armed; };
	bool getGuided() const { return this->State_.guided; };
	bool getManualInput() const { return this->State_.manual_input; };
	std::string getMode() const { return this->State_.mode; };
	int getSystemStatusID() const { return this->State_.system_status; };
	std::string getSystemStatus();
	std::string getSystemStatus(int StatusID);
	double getTime() { return this->State_.header.stamp.toSec();};
	std::string getState();
	
	void waitNextState();

	void cbState(const mavros_msgs::State::ConstPtr& State);	
	
private:
	void initSystemStatus();
	
private:
	ros::NodeHandle nh_;
	ros::Subscriber SubState_;
	coexBattery* Battery_;

	mavros_msgs::State State_;
	std::map<int, std::string> SystemStatus_;
	bool silent_;
};


const std::string coexMode_Manual = "MANUAL";
const std::string coexMode_Offboard = "OFFBOARD";
const std::string coexMode_Stabilized = "STABILIZED";

#endif // COEXSTATE_H


