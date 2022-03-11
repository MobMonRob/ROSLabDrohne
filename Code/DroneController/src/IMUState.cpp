#include "DroneController/IMUState.h"






IMUState::IMUState(Vector3D Translative, Vector3D Angular, Value GroundClearance, Timestamp Time)
	: Accelerations_(Unit_Acceleration),
	Angles_(Unit_AngleVelRad),
	GroundClearance_(Unit_Length)
{
	if (Translative.getUnit() == Unit_Acceleration)
	{
		this->Accelerations_ = Translative;
	}

	if (Angular.getUnit() == Unit_AngleVelRad)
	{
		this->Angles_ = Angular;
	}
	
	if (GroundClearance.getUnit() == Unit_Length)
	{
		this->GroundClearance_ = GroundClearance;
	}
	
	this->Time_ = Time;
}


bool IMUState::operator==(const IMUState& S)
{
	bool ReturnBool = true;


	ReturnBool &= (this->getVector_Linear() == S.Accelerations_);
	ReturnBool &= (this->getVector_Angular() == S.Angles_);
	ReturnBool &= (this->getGroundClearance() == S.GroundClearance_);
	ReturnBool &= (this->getTimestamp() == S.Time_);

	return ReturnBool;
}

bool IMUState::operator==(const IMUState& S) const
{
	bool ReturnBool = true;


	ReturnBool &= (this->Accelerations_ == S.Accelerations_);
	ReturnBool &= (this->Angles_ == S.Angles_);
	ReturnBool &= (this->GroundClearance_ == S.GroundClearance_);
	ReturnBool &= (this->Time_ == S.Time_);

	return ReturnBool;
}

void IMUState::operator+=(const IMUState& S)
{
	this->Accelerations_ += S.Accelerations_;
	this->Angles_ += S.Angles_;
	this->GroundClearance_ += S.GroundClearance_;
	
	if (this->Time_ < S.Time_)
	{
		this->Time_ = S.Time_;
	}
}

IMUState IMUState::operator-(const IMUState& S)
{
	return IMUState(this->getVector_Linear() - S.Accelerations_,
		this->getVector_Angular() - S.Angles_,
		this->getGroundClearance() - S.GroundClearance_,
		(this->getTimestamp() > S.Time_ ? this->getTimestamp() : S.Time_));
}


