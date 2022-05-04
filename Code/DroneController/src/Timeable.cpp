#include "DroneController/Timeable.h"



Timestamp Timeable::OffsetGlobal_ = Timestamp();


void Timeable::setTime(Timestamp Time)
{
	this->Time_ = Time;
	this->setTimeOffsetLocal(Time);
	this->setTimeOffsetGlobal(Time);
}

void Timeable::setTimeOffsetLocal(Timestamp Time)
{
	if (this->getTimeOffsetLocal() == Timestamp())
	{
		this->OffsetLocal_ = Time;
	}
}

void Timeable::setTimeOffsetGlobal(Timestamp Time)
{
	if (Timeable::getTimeOffsetGlobal() == Timestamp())
	{
		Timeable::OffsetGlobal_ = Time;
	}
}

