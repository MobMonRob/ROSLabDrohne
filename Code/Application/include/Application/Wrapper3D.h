#ifndef WRAPPER3D_H
#define WRAPPER3D_H

#include <vector>

#include "Abstraction/Vector3D.h"
#include "Abstraction/TimedValue.h"

#include "Domain/Outputable.h"
#include "Domain/Controller_I.h"

#include "AccelToPos.h"
#include "AngVelToAng.h"

template<class T>
class Wrapper3D
{
public:
	Wrapper3D(Unit UnitInput, Unit UnitOutput);
	void setInput(Vector3D Input, Timestamp Time);
	
	Vector3D getVector();
	Vector3D getVectorSuspention() { return this->Collector_.at(0); };

	void setLock(bool Lock);

private:
	T X_;
	T Y_;
	T Z_;

	std::vector<Vector3D> Collector_;
	bool LockedInput_ = true;
	Unit UnitInput_;
	Unit UnitOutput_;
};



template<class T>
inline Wrapper3D<T>::Wrapper3D(Unit UnitInput, Unit UnitOutput)
	: UnitInput_(UnitInput),
	UnitOutput_(UnitOutput)
{
	this->Collector_.push_back(Vector3D(UnitInput));
}


template<class T>
inline void Wrapper3D<T>::setLock(bool Lock)
{
	this->LockedInput_ = Lock;

	if (!this->LockedInput_)
	{
		Vector3D Sum(this->UnitInput_);
		int Count = this->Collector_.size();


		for (int i = 0; i < Count; i++)
		{
			Sum = Sum + this->Collector_.at(i);
		}

		this->Collector_.clear();
		this->Collector_.push_back(Sum / Count);
	}
}







template<>
inline void Wrapper3D<AccelToPos>::setInput(Vector3D Input, Timestamp Time)
{
	if (this->LockedInput_)
	{
		this->Collector_.push_back(Input);
	}
	else
	{
		Vector3D InputAdapted = Input - this->getVectorSuspention();


		this->X_.setInput(TimedValue(Input.getUnit(), InputAdapted.getX(), Time));
		this->X_.getOutput();
		this->Y_.setInput(TimedValue(Input.getUnit(), InputAdapted.getY(), Time));
		this->Y_.getOutput();
		this->Z_.setInput(TimedValue(Input.getUnit(), InputAdapted.getZ(), Time));
		this->Z_.getOutput();
	}
}

template<>
inline Vector3D Wrapper3D<AccelToPos>::getVector()
{
	return Vector3D(Unit_Length,
		X_.getOutput().getValue(),
		Y_.getOutput().getValue(),
		Z_.getOutput().getValue());
}





template<>
inline void Wrapper3D<AngVelToAng>::setInput(Vector3D Input, Timestamp Time)
{
	if (this->LockedInput_)
	{
		this->Collector_.push_back(Input);
	}
	else
	{
		Vector3D InputAdapted = Input - this->Collector_.at(0);


		this->X_.setInput(TimedValue(Input.getUnit(), InputAdapted.getX(), Time));
		this->X_.getOutput();
		this->Y_.setInput(TimedValue(Input.getUnit(), InputAdapted.getY(), Time));
		this->Y_.getOutput();
		this->Z_.setInput(TimedValue(Input.getUnit(), InputAdapted.getZ(), Time));
		this->Z_.getOutput();
	}
}

template<>
inline Vector3D Wrapper3D<AngVelToAng>::getVector()
{
	return Vector3D(Unit_Length,
		X_.getOutput().getValue(),
		Y_.getOutput().getValue(),
		Z_.getOutput().getValue());
}

#endif // WRAPPER3D_H

