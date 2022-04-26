#include <Adapter/StateBuilder.h>

#include <iostream>




StateBuilder::StateBuilder(int MedianingEntries, int AveragingEntries, int OffsetingEntries)
	: AvgHandler_(AveragingEntries),
	OffsetHandler_(OffsetingEntries),
	Offsetting_(true)
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

IMUState StateBuilder::createState(Timestamp Time, Vector3D LinearAcceleration, Vector3D RotationalValues, Value GroundClearance)
{
	IMUState Entry(LinearAcceleration, RotationalValues, GroundClearance, Time);


	if (this->OffsetTime_ == Timestamp())
	{
		this->OffsetTime_ = Time;

		std::cout << "set OffsetTime to " << this->OffsetTime_.getTime().getValue() << std::endl;
	}

	if (this->getOffsetting() || this->OffsetHandler_.getSize() < 1)
	{
		this->OffsetHandler_.addEntry(Entry - this->OffsetTime_);
	}
	
	this->MedianHandler_.addEntry(Entry - this->OffsetTime_);
	this->AvgHandler_.addEntry(this->getStateMedianRaw());

	return this->getState();
}


IMUState StateBuilder::getState()
{
	IMUState ReturnItem;


	if (!this->getOffsetting())
	{
		ReturnItem = this->getStateAvgRaw() - this->getOffsetState();
	}

	return ReturnItem;
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


