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

	template<int TIn>
	void operator*=(const FixedPoint<TIn>& FP);
	void operator*=(int Value);
	void operator*=(double Value);


	long getValueRaw() const { return this->ValueRaw_; };
	double getValue();

	template<int TIn>
	static FixedPoint<T> convert(FixedPoint<TIn> FP);

protected:
	long ValueRaw_;
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
inline void FixedPoint<T>::operator*=(double Value)
{
	this->operator*=(FixedPoint<T>(Value));
}







template<int T>
inline double FixedPoint<T>::getValue()
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
	int Shift = T - TIn;


	FP_Out.ValueRaw_ = FP.getValueRaw() * std::powl(10, Shift);

	return FP_Out;
}

#endif // FIXEDPOINT_H

