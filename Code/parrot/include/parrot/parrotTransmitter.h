#ifndef PARROT_TRANSMITTER_H
#define PARROT_TRANSMITTER_H

#include "DroneController/Transmitable.h"

#include <ros/ros.h>

#include <mavros_msgs/ManualControl.h>
#include <mavros_msgs/OverrideRCIn.h>

#include "parrot/parrotStatus.h"
#include "parrot/parrotBattery.h"


class parrotTransmitter : public Transmitable
{
public:
	parrotTransmitter();
	~parrotTransmitter();


private:
	bool transmitAction(double pitch, double roll, double thrust, double yarn) override;			// from Transmitable
	
private:
};

#endif // PARROT_TRANSMITTER_H


