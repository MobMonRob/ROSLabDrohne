#ifndef DRONECONTROLABLE_H
#define DRONECONTROLABLE_H

#include "Domain/SafetyProvider.h"

#include "DroneController/Statusable.h"
#include "DroneController/Batteryable.h"
#include "DroneController/IMUable.h"
#include "DroneController/Transmitable.h"


class DroneControlable : public SafetyProvider
{
public:
	DroneControlable(Statusable* Status, Batteryable* Battery, IMUable* IMU, Transmitable* Transmitter);


	// Status
	bool setArmState(bool ArmState) { return this->Status_->setArmState(ArmState); };
	bool getArmState() { return this->Status_->getArmState(); };
	std::string getStatusTranslation() { return this->Status_->getStatusTranslation(); };
	bool isGrounded() { return this->Status_->isGrounded(); };
	bool isFlying() { return this->Status_->isFlying(); };
	// Battery
	double getVoltage() { return this->Battery_->getVoltage(); };
	double getPercentage() { return this->Battery_->getPercentage(); };
	// IMU
	Vector3D getPosition() { return this->IMU_->getPosition(); };
	Vector3D getOrientation() { return this->IMU_->getOrientation(); };
	// Transmitter
	bool transmitAction(double pitch, double roll, double thrust, double yarn) { return this->Transmitter_->transmitAction(pitch, roll, thrust, yarn); };

protected:
	Statusable* Status_;
	Batteryable* Battery_;
	IMUable* IMU_;
	Transmitable* Transmitter_;
};

#endif // DRONECONTROLABLE_H
