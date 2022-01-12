#include "PosControl/State.h"






State::State(Vector3D Translative, Vector3D Angular, Timestamp Time)
	: Accelerations_(Unit_Acceleration), Angles_(Unit_AngleDeg)
{
	if (Translative.getUnit() == Unit_Acceleration)
	{
		this->Accelerations_ = Translative;
	}

	if (Angular.getUnit() == Unit_AngleDeg)
	{
		this->Angles_ = Angular;
	}
	
	this->Time_ = Time;
}

bool State::operator==(const State& S)
{
	bool ReturnBool = true;


	ReturnBool &= (this->getVector_Translative() == S.Accelerations_);
	ReturnBool &= (this->getVector_Angular() == S.Angles_);
	ReturnBool &= (this->getTimestamp() == S.Time_);

	return ReturnBool;
}




