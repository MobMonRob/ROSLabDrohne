#ifndef STATUSABLE_H
#define STATUSABLE_H

#include <map>
#include <string>

#include "DroneController/Timeable.h"
#include "DroneController/Watchdog.h"
#include "Domain/SafetyReceiver.h"

#include "Domain/Timestamp.h"
#include "DroneController/Batteryable.h"


class Statusable : public Timeable, public Watchdog, public SafetyReceiver
{
public:
	Statusable();

	virtual bool setArmState(bool ArmState) = 0;


	virtual bool getArmState() { return false; };
	int getStatusID() const { return this->StatusID_; };
	std::string getStatusTranslation() { return this->getStatusTranslation(this->getStatusID()); };
	std::string getStatusTranslation(int StatusID);

	virtual bool isGrounded() = 0;
	virtual bool isFlying() = 0;

	void safetyTriggered() override { this->setArmState(false); };

protected:
	void setStatusID(int ID) { this->StatusID_ = ID; };
	void addSystemStatus(int ID, std::string Description) { this->StatusTranslation_.insert(std::pair<int, std::string>(ID, Description)); };
	virtual void initSystemStatus() = 0;

private:
	int StatusID_;
	std::map<int, std::string> StatusTranslation_;
};

#endif // STATUSABLE_H
