#include <Adapter/StateBuilder.h>






StateBuilder::StateBuilder(int SmoothingEntries, int OffsetingEntries)
	: StateHandler_(SmoothingEntries),
	OffsetHandler_(OffsetingEntries),
	Offsetting_(false)
{
}




void StateBuilder::setOffsetPoint(IMUState S)
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

	if (this->Offsetting_ || this->OffsetHandler_.getSize() < 1)
	{
		this->OffsetHandler_.addEntry(Entry);
	}

	this->StateHandler_.addEntry((Entry - this->getOffsetPoint()) - this->OffsetTime_);

	return this->getState();
}

void StateBuilder::reset()
{
	this->clearStateHandler();
	this->OffsetHandler_.clear();
}


