#ifndef COEXTRANSMITABLE_H
#define COEXTRANSMITABLE_H

#include <mavros_msgs/ManualControl.h>

#include "Adapter/Transmitable.h"

#include "coexState.h"
#include "coexBattery.h"


class coexTransmitable : public Transmitable
{
public:
	coexTransmitable() {};
	coexTransmitable(coexState *State, coexBattery *Battery);
	
	bool transmitAction(double pitch, double roll, double thrust, double yarn);
	bool transmitAction(mavros_msgs::ManualControl Msg);
	
protected:
	virtual void transmit(mavros_msgs::ManualControl Msg) = 0;
	
	coexState *State_;
	coexBattery *Battery_;
};

#endif // COEXTRANSMITABLE_H
