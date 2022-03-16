#ifndef STATEBUILDER_H
#define STATEBUILDER_H

#include "DroneController/IMUState.h"
#include "Adapter/StateHandler.h"


class StateBuilder
{
public:
	void setNullPoint() { this->setNullPoint(this->StateHandler_.getAvgState()); };
	void setNullPoint(IMUState S) { this->NullPoint_ = S; };

	IMUState createState(Timestamp Time,
		FixedPoint<Accuracy_Value> LinAccelX, FixedPoint<Accuracy_Value> LinAccelY, FixedPoint<Accuracy_Value> LinAccelZ,
		Unit RotVelUnit, FixedPoint<Accuracy_Value> RotVelX, FixedPoint<Accuracy_Value> RotVelY, FixedPoint<Accuracy_Value> RotVelZ,
		Value GroundClearance);
	IMUState createState(Timestamp Time, Vector3D LinearAcceleration, Vector3D RotationalVelocity, Value GroundClearance);
	
	IMUState getState() { return this->StateHandler_.getAvgState(); };

	void clearStateHandler() { this->StateHandler_.clear(); };
	void reset();

private:
	StateHandler StateHandler_;
	IMUState NullPoint_;
};

#endif // STATEBUILDER_H

