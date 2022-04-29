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
	this->setTime(Time);

	if (this->getValidFlag())
	{
		Vector3D Rotation_rad = RotationalValues * FixedPoint<Accuracy_Value>::convert(Fixed_PI) / FixedPoint<Accuracy_Value>(180);
		Vector3D AccelerationRotated = LinearAcceleration.rotate_RollPitchYaw(Rotation_rad.getX(), Rotation_rad.getY(), Rotation_rad.getZ());
		IMUState Entry(AccelerationRotated, RotationalValues, GroundClearance, this->getTime());


		this->MedianHandler_.addEntry(Entry);
		this->AvgHandler_.addEntry(this->getStateMedianRaw());

		if (this->getOffsettingFlag() || this->OffsetHandler_.getSize() < 1)
		{
			this->OffsetHandler_.addEntry(this->AvgHandler_.getAvgState());

			this->updateOffset();
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






void StateBuilder::updateOffset()
{
	if (this->OffsetHandler_.getSize() == this->OffsetHandler_.getSizeMax())
	{
		std::cout << "StateBuilder::updateOffset()" << std::endl;


		IMUState Offset = this->OffsetHandler_.getAvgState();
		IMUState Variance = this->OffsetHandler_.getVariance();

		FixedPoint<Accuracy_Value> OffsetX = this->OffsetState_.getLinear().getX();
		FixedPoint<Accuracy_Value> VarianceX = this->OffsetVariance_.getLinear().getX();
		FixedPoint<Accuracy_Value> OffsetY = this->OffsetState_.getLinear().getY();
		FixedPoint<Accuracy_Value> VarianceY = this->OffsetVariance_.getLinear().getY();
		FixedPoint<Accuracy_Value> OffsetZ = this->OffsetState_.getLinear().getZ();
		FixedPoint<Accuracy_Value> VarianceZ = this->OffsetVariance_.getLinear().getZ();
		FixedPoint<Accuracy_Value> OffsetRX = this->OffsetState_.getRotational().getX();
		FixedPoint<Accuracy_Value> VarianceRX = this->OffsetVariance_.getRotational().getX();
		FixedPoint<Accuracy_Value> OffsetRY = this->OffsetState_.getRotational().getY();
		FixedPoint<Accuracy_Value> VarianceRY = this->OffsetVariance_.getRotational().getY();
		FixedPoint<Accuracy_Value> OffsetRZ = this->OffsetState_.getRotational().getZ();
		FixedPoint<Accuracy_Value> VarianceRZ = this->OffsetVariance_.getRotational().getZ();


		if (Variance.getLinear().getX() < VarianceX)
		{
			OffsetX = Offset.getLinear().getX();
			VarianceX = Variance.getLinear().getX();
		}
		if (Variance.getLinear().getY() < VarianceY)
		{
			OffsetY = Offset.getLinear().getY();
			VarianceY = Variance.getLinear().getY();
		}
		if (Variance.getLinear().getZ() < VarianceZ)
		{
			OffsetZ = Offset.getLinear().getZ();
			VarianceZ = Variance.getLinear().getZ();
		}

		if (Variance.getRotational().getX() < VarianceRX)
		{
			OffsetRX = Offset.getRotational().getX();
			VarianceRX = Variance.getRotational().getX();
		}
		if (Variance.getRotational().getY() < VarianceRY)
		{
			OffsetRY = Offset.getRotational().getY();
			VarianceRY = Variance.getRotational().getY();
		}
		if (Variance.getRotational().getZ() < VarianceRZ)
		{
			OffsetRZ = Offset.getRotational().getZ();
			VarianceRZ = Variance.getRotational().getZ();
		}

		this->OffsetState_ = IMUState(Vector3D(Unit_Acceleration, OffsetX, OffsetY, OffsetZ),
			Vector3D(Unit_State_Angular, OffsetRX, OffsetRY, OffsetRZ),
			Value(Unit_None),
			Offset.getTimestamp());
		this->OffsetVariance_ = IMUState(Vector3D(Unit_None, VarianceX, VarianceY, VarianceZ),
			Vector3D(Unit_None, VarianceRX, VarianceRY, VarianceRZ),
			Value(Unit_None),
			Offset.getTimestamp());
	}
}



