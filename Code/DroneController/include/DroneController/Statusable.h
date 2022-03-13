#ifndef STATUSABLE_H
#define STATUSABLE_H

#include "Abstraction/Timestamp.h"
#include "DroneController/Batteryable.h"


class Statusable
{
public:
	Statusable(Batteryable* Batteryable) : Batteryable_(Batteryable) {};

	virtual bool setArmState(bool ArmState) { return false; };


	virtual Timestamp getTime() = 0;
	virtual bool getArmState() { return false; };

	bool isSafe();

protected:
	callbackStatus;







private:
	Batteryable* Batteryable_;
};

#endif // STATUSABLE_H
