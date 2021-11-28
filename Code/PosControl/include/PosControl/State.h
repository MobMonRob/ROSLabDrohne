#ifndef STATE_H
#define STATE_H

#include "PosControl/Timestamp.h"
#include "PosControl/Vector3D.h"


class State
{
public:
	State() : State(Vector3D(State::UnitTranslative_), Vector3D(State::UnitAngular_), Timestamp()) {};
	State(Vector3D Translative, Vector3D Angular, Timestamp Time);

	bool operator==(const State& S);


	Vector3D getVector_Translative() { return this->Translative_; };
	Vector3D getVector_Angular() { return this->Angular_; };
	Timestamp getTimestamp() { return this->Time_; };

public:
	static Unit UnitTranslative;
	static Unit UnitAngular;

private:
	Vector3D Translative_;
	Vector3D Angular_;
	Timestamp Time_;
};

#endif // STATE_H
