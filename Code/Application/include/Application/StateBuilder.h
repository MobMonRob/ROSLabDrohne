#ifndef STATEBUILDER_H
#define STATEBUILDER_H

#include "Application/State.h"


class StateBuilder
{
public:
	void setNullPoint(State S) { this->NullPoint_ = S; };

	State createState(Timestamp Time, 
		FixedPoint<Accuracy_Value> LinAccelX, FixedPoint<Accuracy_Value> LinAccelY, FixedPoint<Accuracy_Value> LinAccelZ,
		Unit RotVelUnit, FixedPoint<Accuracy_Value> RotVelX, FixedPoint<Accuracy_Value> RotVelY, FixedPoint<Accuracy_Value> RotVelZ,
		Value GroundClearance);
	State createState(Timestamp Time, Vector3D LinearAcceleration, Vector3D RotationalVelocity, Value GroundClearance);
	
private:
	State NullPoint_;
};

#endif // STATEBUILDER_H

