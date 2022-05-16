#ifndef THRUSTABLE_H
#define THRUSTABLE_H

#include "Domain/Value.h"
#include "Domain/Vector3D.h"

#include "Domain/SafetyProvider.h"
#include "DroneController/Timeable.h"
#include "DroneController/Rotor.h"


const Value PressureAtmosphereNorm(Unit_Pressure_mPa, FixedPoint <Accuracy_Value>(1013));

template<int RotorCount>
class Thrustable : public SafetyProvider, public Timeable
{
public:
	Thrustable(Value C_T, Value Diameter, Vector3D RotorOffset[RotorCount], Value Density, Value Pressure = PressureAtmosphereNorm);

	Value getDensity() { return this->Density_ * this->getPressure() / PressureAtmosphereNorm; };
	Value getPressure() { return this->Pressure_; };
	Vector3D getThrust();

protected:
	void setPressure(Value Pressure) { this->Pressure_ = Pressure; };
	void setRotorSpeed(int RotorNumber, Value RotorSpeed);
	void setTime(Timestamp Time) { Timeable::setTime(Time); };

	Value getRotorSpeed(int RotorNumber);
	Vector3D getThrust(int RotorNumber);
	Vector3D getRotorOffset(int RotorNumber);

private:
	Value Density_;
	Value Pressure_;
	Rotor Rotor_[RotorCount];
	Vector3D RotorOffset_[RotorCount];
};


#endif // THRUSTABLE_H
