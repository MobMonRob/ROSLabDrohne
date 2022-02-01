#ifndef STATE_H
#define STATE_H


#include "PosControl/Value.h"
#include "PosControl/Vector3D.h"
#include "PosControl/Timestamp.h"


class State
{
public:
	State() : State(Vector3D(Unit_Acceleration), Vector3D(Unit_AngleDeg), Value(Unit_Length), Timestamp()) {};
	State(Vector3D Translative, Vector3D Angular, Value GroundClearance, Timestamp Time);

	bool operator==(const State& S);


	Vector3D getVector_Translative() { return this->Accelerations_; };
	Vector3D getVector_Angular() { return this->Angles_; };
	Value getGroundClearance() { return this->GroundClearance_; };
	Timestamp getTimestamp() { return this->Time_; };
	
private:
	Vector3D Accelerations_;
	Vector3D Angles_;
	Value GroundClearance_;
	Timestamp Time_;
};

#endif // STATE_H
