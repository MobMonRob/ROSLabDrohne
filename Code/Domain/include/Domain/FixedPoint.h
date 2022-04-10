#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H


#include <cmath>



const int Accuracy_Value = -6;
const int Accuracy_Time = -4;
const int Accuracy_Vector = Accuracy_Value;
const int Accuracy_Constant = -10;

template<int T>
class FixedPoint
{
public:
	FixedPoint<T>() : ValueRaw_(0) {};
	FixedPoint<T>(int Value);
	FixedPoint<T>(double Value);
	FixedPoint<T>(const FixedPoint<T>& FP);

	template<int TIn>
	bool operator==(const FixedPoint<TIn>& FP) const;
	bool operator==(const FixedPoint<T>& FP) const { return this->ValueRaw_ == FP.ValueRaw_; };

	template<int TIn>
	bool operator!=(const FixedPoint<TIn>& FP) const { return !this->operator==(FP); };

	bool operator<(const FixedPoint<T>& FP) const { return this->ValueRaw_ < FP.ValueRaw_; };
	bool operator<=(const FixedPoint<T>& FP) const { return this->ValueRaw_ <= FP.ValueRaw_; };
	bool operator>(const FixedPoint<T>& FP) const { return this->ValueRaw_ > FP.ValueRaw_; };
	bool operator>=(const FixedPoint<T>& FP) const { return this->ValueRaw_ >= FP.ValueRaw_; };

	template<int TIn>
	FixedPoint<T> operator+(const FixedPoint<TIn>& FP);
	template<int TIn>
	FixedPoint<T> operator+(const FixedPoint<TIn>& FP) const;
	template<int TIn>
	void operator+=(const FixedPoint<TIn>& FP);
	void operator+=(int Value) { this->operator+=(FixedPoint<T>(Value)); };
	void operator+=(double Value) { this->operator+=(FixedPoint<T>(Value)); };

	template<int TIn>
	FixedPoint<T> operator-(const FixedPoint<TIn>& FP);
	template<int TIn>
	FixedPoint<T> operator-(const FixedPoint<TIn>& FP) const;
	template<int TIn>
	void operator-=(const FixedPoint<TIn>& FP);
	void operator-=(int Value) { this->operator-=(FixedPoint<T>(Value)); };
	void operator-=(double Value) { this->operator-=(FixedPoint<T>(Value)); };

	template<int TIn>
	FixedPoint<T> operator*(const FixedPoint<TIn>& FP);
	template<int TIn>
	FixedPoint<T> operator*(const FixedPoint<TIn>& FP) const;
	template<int TIn>
	void operator*=(const FixedPoint<TIn>& FP);
	void operator*=(int Value);
	void operator*=(double Value) { this->operator*=(FixedPoint<T>(Value)); };

	template<int TIn>
	FixedPoint<T> operator/(const FixedPoint<TIn>& FP);
	template<int TIn>
	FixedPoint<T> operator/(const FixedPoint<TIn>& FP) const;
	template<int TIn>
	void operator/=(const FixedPoint<TIn>& FP);
	void operator/=(int Value);
	void operator/=(double Value) { this->operator/=(FixedPoint<T>(Value)); };

	long long getValueRaw() const { return this->ValueRaw_; };
	double getValue() const;

	template<int TIn>
	static FixedPoint<T> convert(FixedPoint<TIn> FP);
	
private:
	static long long powl10(int Power);

protected:
	long long ValueRaw_ = 0;
};


template<int T>
inline FixedPoint<T>::FixedPoint(int Value)
{
	this->ValueRaw_ = Value;

	if (T < 0)
	{
		this->ValueRaw_ *= FixedPoint<T>::powl10(-T);
	}
	if (T > 0)
	{
		this->ValueRaw_ /= FixedPoint<T>::powl10(T);
	}
}

template<int T>
inline FixedPoint<T>::FixedPoint(double Value)
{
	if (T < 0)
	{
		this->ValueRaw_ = static_cast<long long>(Value * FixedPoint<T>::powl10(-T));
	}
	if (T > 0)
	{
		this->ValueRaw_ = static_cast<long long>(Value / FixedPoint<T>::powl10(T));
	}
}

template<int T>
inline FixedPoint<T>::FixedPoint(const FixedPoint<T>& FP)
{
	this->ValueRaw_ = FP.ValueRaw_;
}



template<int T>
template<int TIn>
inline bool FixedPoint<T>::operator==(const FixedPoint<TIn>& FP) const
{
	bool ReturnBool = false;


	if (T == TIn)
	{
		ReturnBool = this->getValueRaw() == FP.getValueRaw();
	}
	if (T < TIn || (T > TIn && T - TIn < 6))
	{
		FixedPoint<T> InValue = FixedPoint<T>::convert(FP);


		ReturnBool = this->operator==(InValue);
	}

	return ReturnBool;
}


template<int T>
template<int TIn>
inline FixedPoint<T> FixedPoint<T>::operator+(const FixedPoint<TIn>& FP)
{
	FixedPoint<T> ReturnItem(*this);


	ReturnItem += FP;

	return ReturnItem;
}

template<int T>
template<int TIn>
inline FixedPoint<T> FixedPoint<T>::operator+(const FixedPoint<TIn>& FP) const
{
	FixedPoint<T> ReturnItem(*this);


	ReturnItem += FP;

	return ReturnItem;
}

template<int T>
template<int TIn>
inline void FixedPoint<T>::operator+=(const FixedPoint<TIn>& FP)
{
	FixedPoint<T> InValue = FixedPoint<T>::convert(FP);

	this->ValueRaw_ += InValue.getValueRaw();
}

template<int T>
template<int TIn>
inline FixedPoint<T> FixedPoint<T>::operator-(const FixedPoint<TIn>& FP)
{
	FixedPoint<T> ReturnItem(*this);

	ReturnItem -= FP;


	return ReturnItem;
}

template<int T>
template<int TIn>
inline FixedPoint<T> FixedPoint<T>::operator-(const FixedPoint<TIn>& FP) const
{
	FixedPoint<T> ReturnItem(*this);

	ReturnItem -= FP;


	return ReturnItem;
}

template<int T>
template<int TIn>
inline void FixedPoint<T>::operator-=(const FixedPoint<TIn>& FP)
{
	FixedPoint<T> InValue = FixedPoint<T>::convert(FP);

	this->ValueRaw_ -= InValue.getValueRaw();
}

template<int T>
template<int TIn>
inline FixedPoint<T> FixedPoint<T>::operator*(const FixedPoint<TIn>& FP)
{
	FixedPoint<T> ReturnItem(*this);

	ReturnItem *= FP;


	return ReturnItem;
}

template<int T>
template<int TIn>
inline FixedPoint<T> FixedPoint<T>::operator*(const FixedPoint<TIn>& FP) const
{
	FixedPoint<T> ReturnItem(*this);

	ReturnItem *= FP;


	return ReturnItem;
}

template<int T>
template<int TIn>
inline void FixedPoint<T>::operator*=(const FixedPoint<TIn>& FP)
{
	this->ValueRaw_ *= FP.ValueRaw_;

	if (T < 0)
	{
		this->ValueRaw_ /= FixedPoint<T>::powl10(-T);
	}
	if (T > 0)
	{
		this->ValueRaw_ *= FixedPoint<T>::powl10(T);
	}
}
template<int T>
inline void FixedPoint<T>::operator*=(int Value)
{
	this->ValueRaw_ = this->getValueRaw() * Value;
}

template<int T>
template<int TIn>
inline FixedPoint<T> FixedPoint<T>::operator/(const FixedPoint<TIn>& FP)
{
	FixedPoint<T> ReturnItem(*this);

	ReturnItem /= FP;


	return ReturnItem;
}

template<int T>
template<int TIn>
inline FixedPoint<T> FixedPoint<T>::operator/(const FixedPoint<TIn>& FP) const
{
	FixedPoint<T> ReturnItem(*this);

	ReturnItem /= FP;


	return ReturnItem;
}

template<int T>
template<int TIn>
inline void FixedPoint<T>::operator/=(const FixedPoint<TIn>& FP)
{
	this->ValueRaw_ *= FixedPoint<T>::powl10(-TIn);
	this->ValueRaw_ /= FP.ValueRaw_;
}
template<int T>
inline void FixedPoint<T>::operator/=(int Value)
{
	this->ValueRaw_ = this->getValueRaw() / Value;
}





template<int T>
inline double FixedPoint<T>::getValue() const
{
	double ReturnValue = static_cast<double>(this->getValueRaw());


	if (T < 0)
	{
		ReturnValue /= FixedPoint<T>::powl10(-T);
	}
	if (T > 0)
	{
		ReturnValue *= FixedPoint<T>::powl10(T);
	}

	return ReturnValue;
}



template<int T>
template<int TIn>
inline FixedPoint<T> FixedPoint<T>::convert(FixedPoint<TIn> FP)
{
	FixedPoint<T> FP_Out;
	int Shift = TIn - T;


	FP_Out.ValueRaw_ = FP.getValueRaw();

	while (Shift != 0)
	{
		if (Shift < 0)
		{
			FP_Out.ValueRaw_ /= 10;

			Shift++;
		}
		if (Shift > 0)
		{
			FP_Out.ValueRaw_ *= 10;

			Shift--;
		}
	}

	return FP_Out;
}


template<int T>
inline long long FixedPoint<T>::powl10(int Power)
{
	long long ReturnValue = 1;


	for (int i = Power; i > 0; i--)
	{
		ReturnValue *= 10;
	}

	return ReturnValue;
}


const FixedPoint<Accuracy_Constant> Fixed_PI(3.141592653589793238462643383279);

#endif // FIXEDPOINT_H

