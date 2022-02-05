#ifndef COEXTRANSMITABLE_H
#define COEXTRANSMITABLE_H

#include <mavros_msgs/ManualControl.h>

#include "Adapter/Transmitable.h"

#include "coex/coexState.h"
#include "coex/coexBattery.h"


class coexTransmitable : public Transmitable
{
public:
	coexTransmitable() : State_(nullptr), Battery_(nullptr) {};
	coexTransmitable(coexState *State, coexBattery *Battery);
	
	bool transmitAction(double pitch, double roll, double thrust, double yarn);
	bool transmitAction(mavros_msgs::ManualControl Msg);
	
protected:
	bool valid() { return (this->State_ != nullptr && this->Battery_ != nullptr); };
	virtual void transmit(mavros_msgs::ManualControl Msg) = 0;
	
	coexState *State_;
	coexBattery *Battery_;
};

#endif // COEXTRANSMITABLE_H
