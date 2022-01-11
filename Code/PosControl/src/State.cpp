#include "PosControl/State.h"






State::State(Vector3D Translative, Vector3D Angular, Timestamp Time)
	: Translative_(Unit_Acceleration), Angular_(Unit_AngleDeg)
{
	if (Translative.getUnit() == Unit_Acceleration)
	{
		this->Translative_ = Translative;
	}

	if (Angular.getUnit() == Unit_AngleDeg)
	{
		this->Angular_ = Angular;
	}
	
	this->Time_ = Time;
}

bool State::operator==(const State& S)
{
	bool ReturnBool = true;


	ReturnBool &= (this->getVector_Translative() == S.Translative_);
	ReturnBool &= (this->getVector_Angular() == S.Angular_);
	ReturnBool &= (this->getTimestamp() == S.Time_);

	return ReturnBool;
}




