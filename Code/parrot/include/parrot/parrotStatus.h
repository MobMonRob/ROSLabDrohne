#ifndef PARROTSTATUS_H
#define PARROTSTATUS_H

#include <string>
#include <map>

#include "DroneController/Statusable.h"

#include <ros/ros.h>
#include <ardrone_autonomy/Navdata.h>

#include "parrot/parrotBattery.h"


class parrotStatus : public Statusable
{
public:
	parrotStatus(parrotBattery* Battery);
	~parrotStatus();
	
	bool setArmState(bool ArmState) override;

	bool isGrounded() override { return this->getStatusID() == 2; };
	bool isFlying() override { return (this->getStatusID() == 3 || this->getStatusID() == 7); };


	bool reset();
	
private:
	void initSystemStatus() override;
	void callbackNavdata(const ardrone_autonomy::Navdata::ConstPtr& navdataPtr);

private:
	ros::NodeHandle nh_;
	ros::Subscriber Sub_;
};

#endif // PARROTSTATUS_H

