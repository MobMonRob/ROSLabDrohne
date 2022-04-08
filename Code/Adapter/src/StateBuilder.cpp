#include <Adapter/StateBuilder.h>






StateBuilder::StateBuilder(int MedianingEntries, int AveragingEntries, int OffsetingEntries)
	: AvgHandler_(AveragingEntries),
	OffsetHandler_(OffsetingEntries),
	Offsetting_(false)
{
}




void StateBuilder::setOffsetState(IMUState S)
{
	this->OffsetHandler_.clear();
	this->OffsetHandler_.addEntry(S);
}






IMUState StateBuilder::createState(Timestamp Time,
	FixedPoint<Accuracy_Value> LinAccelX, FixedPoint<Accuracy_Value> LinAccelY, FixedPoint<Accuracy_Value> LinAccelZ, 
	Unit RotVelUnit, FixedPoint<Accuracy_Value> RotVelX, FixedPoint<Accuracy_Value> RotVelY, FixedPoint<Accuracy_Value> RotVelZ,
	Value GroundClearance)
{
	Vector3D LinAccel(Unit_Acceleration, LinAccelX, LinAccelY, LinAccelZ);
	Vector3D RotVel(RotVelUnit, RotVelX, RotVelY, RotVelZ);


	return this->createState(Time, LinAccel, RotVel, GroundClearance);
}

IMUState StateBuilder::createState(Timestamp Time, Vector3D LinearAcceleration, Vector3D RotationalVelocity, Value GroundClearance)
{
	IMUState Entry(LinearAcceleration, RotationalVelocity, GroundClearance, Time);

	if (this->OffsetTime_ == Timestamp())
	{
		this->OffsetTime_ = Time;
	}

	if (this->getOffsetting() || this->OffsetHandler_.getSize() < 1)
	{
		this->OffsetHandler_.addEntry(Entry);
	}

	this->MedianHandler_.addEntry(Entry - this->OffsetTime_);
	this->AvgHandler_.addEntry(this->getStateMedianRaw());

	return this->getState();
}



void StateBuilder::clearStateHandler()
{
	this->MedianHandler_.clear();
	this->AvgHandler_.clear();
}


void StateBuilder::reset()
{
	this->clearStateHandler();
	this->OffsetHandler_.clear();
}


