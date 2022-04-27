#ifndef IMPACTOK_H
#define IMPACTOK_H

#include "Domain/SafetyRequirement.h"

#include "DroneController/IMUState.h"


class ImpactOK : public SafetyRequirement
{
public:
	ImpactOK(FixedPoint<Accuracy_Value> Threshold) : Threshold_(Threshold*Threshold), Valid_(true) {};

	bool updateAcceleration(Vector3D Acceleration);
	bool meets() override { return this->Valid_; };

	void reset() { this->Valid_ = true; };

private:
	FixedPoint<Accuracy_Value> Threshold_;
	bool Valid_;
};

#endif // IMPACTOK_H
