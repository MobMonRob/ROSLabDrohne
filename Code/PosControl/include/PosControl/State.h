#ifndef STATE_H
#define STATE_H

#include "PosControl/Timestamp.h"
#include "PosControl/Vector3D.h"


class State
{
public:
	State() : State(Vector3D(Unit_Acceleration), Vector3D(Unit_AngleDeg), Timestamp()) {};
	State(Vector3D Translative, Vector3D Angular, Timestamp Time);

	bool operator==(const State& S);


	Vector3D getVector_Translative() { return this->Accelerations_; };
	Vector3D getVector_Angular() { return this->Angles_; };
	Timestamp getTimestamp() { return this->Time_; };

private:
	Vector3D Accelerations_;
	Vector3D Angles_;
	Timestamp Time_;
};

#endif // STATE_H
