#include "Application/State.h"






State::State(Vector3D Translative, Vector3D Angular, Value GroundClearance, Timestamp Time)
	: Accelerations_(Unit_Acceleration), Angles_(Unit_AngleDeg), GroundClearance_(Unit_Length)
{
	if (Translative.getUnit() == Unit_Acceleration)
	{
		this->Accelerations_ = Translative;
	}

	if (Angular.getUnit() == Unit_AngleDeg)
	{
		this->Angles_ = Angular;
	}
	
	if (GroundClearance.getUnit() == Unit_Length)
	{
		this->GroundClearance_ = GroundClearance;
	}
	
	this->Time_ = Time;
}

bool State::operator==(const State& S)
{
	bool ReturnBool = true;


	ReturnBool &= (this->getVector_Translative() == S.Accelerations_);
	ReturnBool &= (this->getVector_Angular() == S.Angles_);
	ReturnBool &= (this->getGroundClearance() == S.GroundClearance_);
	ReturnBool &= (this->getTimestamp() == S.Time_);

	return ReturnBool;
}

State State::operator-(const State& S)
{
	return State(this->getVector_Translative() - S.Accelerations_,
		this->getVector_Angular() - S.Angles_,
		this->getGroundClearance() - S.GroundClearance_,
		this->getTimestamp());
}


