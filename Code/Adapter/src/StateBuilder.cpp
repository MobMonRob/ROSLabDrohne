#include <Adapter/StateBuilder.h>

#include <iostream>




StateBuilder::StateBuilder(int MedianingEntries, int AveragingEntries, int OffsetingEntries)
	: AvgHandler_(AveragingEntries),
	OffsetHandler_(OffsetingEntries),
	Offsetting_(true),
	Valid_(false)
{
}




void StateBuilder::setOffsetState(IMUState S)
{
	this->OffsetHandler_.clear();
	this->OffsetHandler_.addEntry(S);
}

void StateBuilder::setOffsettingFlag(bool Flag)
{
	std::cout << "StateOffsettig = " << (Flag ? "TRUE" : "FALSE") << std::endl;


	if (!Flag)
	{
		this->OffsetState_ = this->OffsetHandler_.getAvgState();

		if (this->getOffsettingFlag())
		{
			std::cout << "StateOffset: " << this->getOffsetState().getString() << std::endl;
		}
	}

	this->Offsetting_ = Flag;
}

void StateBuilder::setOffsetTime(Timestamp Time)
{
	if (this->OffsetTime_ == Timestamp())
	{
		this->OffsetTime_ = Time;

		std::cout << "OffsetTime = " << this->OffsetTime_.getTime().getValue() << std::endl;
	}
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
	if (this->getValidFlag())
	{
		IMUState Entry(LinearAcceleration, RotationalValues, GroundClearance, Time);


		this->setOffsetTime(Time);

		this->MedianHandler_.addEntry(Entry - this->OffsetTime_);
		this->AvgHandler_.addEntry(this->getStateMedianRaw());

		if (this->getOffsettingFlag() || this->OffsetHandler_.getSize() < 1)
		{
			this->OffsetHandler_.addEntry(Entry - this->OffsetTime_);
		}
	}

	return this->getState();
}


IMUState StateBuilder::getState()
{
	IMUState ReturnItem;


	if (this->getValidFlag() && !this->getOffsettingFlag())
	{
		ReturnItem = (this->getStateAvgRaw() - this->getOffsetState()) + this->OffsetTime_;
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
	std::cout << "StateBuilder Reset..." << std::endl;

	this->clearStateHandler();
	this->OffsetHandler_.clear();
	this->setOffsettingFlag(true);
	this->OffsetState_ = IMUState();
}


