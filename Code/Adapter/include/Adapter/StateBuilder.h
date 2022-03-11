#ifndef STATEBUILDER_H
#define STATEBUILDER_H

#include "DroneController/IMUState.h"


class StateBuilder
{
public:
	void setNullPoint(IMUState S) { this->NullPoint_ = S; };

	IMUState createState(Timestamp Time,
		FixedPoint<Accuracy_Value> LinAccelX, FixedPoint<Accuracy_Value> LinAccelY, FixedPoint<Accuracy_Value> LinAccelZ,
		Unit RotVelUnit, FixedPoint<Accuracy_Value> RotVelX, FixedPoint<Accuracy_Value> RotVelY, FixedPoint<Accuracy_Value> RotVelZ,
		Value GroundClearance);
	IMUState createState(Timestamp Time, Vector3D LinearAcceleration, Vector3D RotationalVelocity, Value GroundClearance);
	
private:
	IMUState NullPoint_;
};

#endif // STATEBUILDER_H

