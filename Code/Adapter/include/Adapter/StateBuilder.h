#ifndef STATEBUILDER_H
#define STATEBUILDER_H

#include "DroneController/Timeable.h"
#include "DroneController/IMUState.h"
#include "Adapter/StateHandler.h"


class StateBuilder : public Timeable
{
public:
	StateBuilder(int MedianingEntries = 3, int AveragingEntries = 3, int OffsetingEntries = 10);
	
	void setOffsetState(IMUState S);
	void setOffsettingFlag(bool Flag);
	void setOffsetTime(Timestamp Time);
	void setValidFlag(bool Validation) { this->Valid_ = Validation; };

	IMUState createState(Timestamp Time,
		FixedPoint<Accuracy_Value> LinAccelX, FixedPoint<Accuracy_Value> LinAccelY, FixedPoint<Accuracy_Value> LinAccelZ,
		Unit RotVelUnit, FixedPoint<Accuracy_Value> RotVelX, FixedPoint<Accuracy_Value> RotVelY, FixedPoint<Accuracy_Value> RotVelZ,
		Value GroundClearance);
	IMUState createState(Timestamp Time, Vector3D LinearAcceleration, Vector3D RotationalVelocity, Value GroundClearance);
	
	IMUState getState();
	IMUState getStateMedianRaw() { return this->MedianHandler_.getMedianState(); };
	IMUState getStateAvgRaw() { return this->AvgHandler_.getAvgState(); };
	IMUState getOffsetState() { return this->OffsetState_; };
	bool getOffsettingFlag() const { return this->Offsetting_; };
	bool getValidFlag() const { return this->Valid_; };

	void clearStateHandler();
	void reset();

private:
	void updateOffset();



private:
	StateHandler MedianHandler_;
	StateHandler AvgHandler_;
	StateHandler OffsetHandler_;
	Timestamp OffsetTime_;
	IMUState OffsetState_;
	IMUState OffsetVariance_;
	bool Offsetting_;
	bool Valid_;
};

#endif // STATEBUILDER_H

