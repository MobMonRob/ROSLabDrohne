#include "DroneController/PoseBuildable.h"

#include <iostream>



PoseBuildable::PoseBuildable()
	: Valid_(false),
	Calibration_(false),
	AccelerationOffset_(Unit_Acceleration),
	Calculate_(false)
{
}


void PoseBuildable::setValidFlag(bool Flag)
{
	if (Flag != this->getValidFlag())
	{
		std::cout << "PoseBuildable::setValidFlag = " << (Flag ? "TRUE" : "FALSE") << std::endl;


		this->setPosition();
	}

	this->Valid_ = Flag;
}



void PoseBuildable::setCalibrationFlag(bool Flag)
{
	if (Flag != this->getCalibrationFlag())
	{
		std::cout << "PoseCalibration = " << (Flag ? "TRUE" : "FALSE") << std::endl;

		if (Flag)
		{
			this->setCalculationFlag(false);

			this->setPosition();
		}
		else
		{
			this->calcOffset();
		}

		this->Calibration_ = Flag;
		this->CalibrationBegin_ = Timestamp();
	}
}

void PoseBuildable::setCalibrationBegin(Timestamp Time)
{
	if (this->CalibrationBegin_ == Timestamp())
	{
		this->CalibrationBegin_ = Time;

		std::cout << "CalibirationTime = " << this->CalibrationBegin_.getTime().getValue() << std::endl;
	}
}

void PoseBuildable::setOffsetAcceleration(FixedPoint<Accuracy_Value> OffsetX, FixedPoint<Accuracy_Value> OffsetY, FixedPoint<Accuracy_Value> OffsetZ)
{
	this->AccelerationOffset_ = Vector3D(Unit_Acceleration, OffsetX, OffsetY, OffsetZ);
}


void PoseBuildable::setCalculationFlag(bool Flag)
{
	if (Flag != this->getCalculationFlag())
	{
		std::cout << "PoseCalculation = " << (Flag ? "TRUE" : "FALSE") << std::endl;

		if (Flag)
		{
			this->setCalibrationFlag(false);
			this->setPosition();
		}

		this->Calculate_ = Flag;
		this->CalculationBegin_ = Timestamp();
	}
}

void PoseBuildable::setCalculationBegin(Timestamp Time)
{
	if (this->CalculationBegin_ == Timestamp())
	{
		this->CalculationBegin_ = Time;

		std::cout << "CalculationTime = " << this->CalculationBegin_.getTime().getValue() << std::endl;
	}
}


