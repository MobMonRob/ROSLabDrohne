#ifndef STATUSABLE_H
#define STATUSABLE_H

#include "Abstraction/SafetyProvider.h"

#include "Abstraction/Timestamp.h"
#include "DroneController/Batteryable.h"


class Statusable : public SafetyProvider
{
public:
	Statusable(Batteryable* Batteryable);

	virtual bool setArmState(bool ArmState) { return false; };


	virtual Timestamp getTime() = 0;
	virtual bool getArmState() { return false; };

	virtual bool isSafe() { return false; };
};

#endif // STATUSABLE_H
