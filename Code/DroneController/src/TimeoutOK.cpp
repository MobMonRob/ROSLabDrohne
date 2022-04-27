#include "DroneController/TimeoutOK.h"


bool TimeoutOK::updateTime(Timestamp Time)
{
	this->Valid_ &= this->Time_Last_ - Time < this->Threshold_;

	this->Time_Last_ = Time;

	return this->meets();
}

