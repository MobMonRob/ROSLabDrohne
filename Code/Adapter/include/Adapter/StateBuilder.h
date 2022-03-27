#ifndef STATEBUILDER_H
#define STATEBUILDER_H

#include "DroneController/IMUState.h"
#include "Adapter/StateHandler.h"


class StateBuilder
{
public:
	StateBuilder(int SmoothingEntries = 3, int OffsetingEntries = 10);
	
	void setOffsetPoint(IMUState S);
	void setOffsetting(bool Offsetting) { this->Offsetting_ = Offsetting; };

	IMUState createState(Timestamp Time,
		FixedPoint<Accuracy_Value> LinAccelX, FixedPoint<Accuracy_Value> LinAccelY, FixedPoint<Accuracy_Value> LinAccelZ,
		Unit RotVelUnit, FixedPoint<Accuracy_Value> RotVelX, FixedPoint<Accuracy_Value> RotVelY, FixedPoint<Accuracy_Value> RotVelZ,
		Value GroundClearance);
	IMUState createState(Timestamp Time, Vector3D LinearAcceleration, Vector3D RotationalVelocity, Value GroundClearance);
	
	IMUState getState() { return this->StateHandler_.getAvgState(); };
	IMUState getOffsetPoint() { return this->OffsetHandler_.getAvgState(); };

	void clearStateHandler() { this->StateHandler_.clear(); };
	void reset();

private:
	StateHandler StateHandler_;
	StateHandler OffsetHandler_;
	Timestamp OffsetTime_;
	bool Offsetting_;
};

#endif // STATEBUILDER_H

