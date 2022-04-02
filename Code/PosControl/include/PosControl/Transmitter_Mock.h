#ifndef TRANSMITTER_MOCK_H
#define TRANSMITTER_MOCK_H

#include "DroneController/Transmitable.h"

#include <ros/ros.h>

#include "parrot/parrotStatus.h"
#include "parrot/parrotBattery.h"

#define TRANSMIT_ROLL	1
#define TRANSMIT_PITCH	1
#define TRANSMIT_YARN	1
#define TRANSMIT_THRUST	1





class Transmitter_Mock : public Transmitable
{
public:
	Transmitter_Mock(int Mask = TRANSMIT_ROLL | TRANSMIT_PITCH | TRANSMIT_YARN | TRANSMIT_THRUST);
	~Transmitter_Mock();

	bool transmitAction(double roll, double pitch, double yarn, double thrust) override;			// from Transmitable

private:
	ros::NodeHandle nh_;
	ros::Publisher Pub_;
	int SendMask_;
};

#endif // TRANSMITTER_MOCK_H


