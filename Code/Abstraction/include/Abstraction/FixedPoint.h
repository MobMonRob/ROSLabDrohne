#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H


template<int T>
class FixedPoint
{
public:
	FixedPoint<T>() : ValueRaw_(0) {};
	FixedPoint<T>(int Value);
	FixedPoint<T>(float Value) : FixedPoint(static_cast<double>(Value)) {};
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
	void operator+=(const FixedPoint<TIn>& FP);
	void operator+=(int Value) { this->operator+=(FixedPoint<T>(Value)); };
	void operator+=(double Value) { this->operator+=(FixedPoint<T>(Value)); };

	template<int TIn>
	FixedPoint<T> operator-(const FixedPoint<TIn>& FP);
	template<int TIn>
	void operator-=(const FixedPoint<TIn>& FP);
	void operator-=(int Value) { this->operator-=(FixedPoint<T>(Value)); };
	void operator-=(double Value) { this->operator-=(FixedPoint<T>(Value)); };

	template<int TIn>
	FixedPoint<T> operator*(const FixedPoint<TIn>& FP);
	template<int TIn>
	void operator*=(const FixedPoint<TIn>& FP);
	void operator*=(int Value);
	void operator*=(double Value) { this->operator*=(FixedPoint<T>(Value)); };

	template<int TIn>
	FixedPoint<T> operator/(const FixedPoint<TIn>& FP);
	template<int TIn>
	void operator/=(const FixedPoint<TIn>& FP);
	void operator/=(int Value);
	void operator/=(double Value) { this->operator/=(FixedPoint<T>(Value)); };

	long long getValueRaw() const { return this->ValueRaw_; };
	double getValue() const;

	template<int TIn>
	static FixedPoint<T> convert(FixedPoint<TIn> FP);
	

protected:
	long long ValueRaw_;
};


template<int T>
inline FixedPoint<T>::FixedPoint(int Value)
{
	this->ValueRaw_ = Value;

	if (T < 0)
	{
		this->ValueRaw_ *= std::powl(10, -T);
	}
	if (T > 0)
	{
		this->ValueRaw_ /= std::powl(10, T);
	}
}

template<int T>
inline FixedPoint<T>::FixedPoint(double Value)
{
	this->ValueRaw_ = Value / std::pow(10, T);
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
inline void FixedPoint<T>::operator*=(const FixedPoint<TIn>& FP)
{
	this->ValueRaw_ *= FP.ValueRaw_;
	this->ValueRaw_ *= std::powl(10, TIn);
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
inline void FixedPoint<T>::operator/=(const FixedPoint<TIn>& FP)
{
	this->ValueRaw_ *= std::powl(10, -TIn);
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
	double ReturnValue = this->getValueRaw();


	if (T != 0)
	{
		ReturnValue *= std::powl(10, T);
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




#endif // FIXEDPOINT_H

