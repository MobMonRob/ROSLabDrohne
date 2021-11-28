#include "PosControl/State.h"


Unit State::UnitTranslative = Unit("m/s²");
Unit State::UnitAngular = Unit("°");


State::State(Vector3D Translative, Vector3D Angular, Timestamp Time)
	: Translative_(State::UnitTranslative), Angular_(State::UnitAngular)
{
	if (Translative.getUnit() == State::UnitTranslative)
	{
		this->Translative_ = Translative;
	}

	if (Angular.getUnit() == State::UnitAngular)
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




