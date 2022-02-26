#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H


template<int T>
class FixedPoint
{
public:
	FixedPoint<T>(int Value = 0);
	FixedPoint<T>(float Value = 0.0);
	FixedPoint<T>(double Value = 0.0);

	FixedPoint<T> operator*=(const FixedPoint<T>& FP);




	long getValueRaw() const { return this->ValueRaw_; };
	double getValue();


private:
	long ValueRaw_;
};


template<int T>
inline FixedPoint<T>::FixedPoint(int Value)
{
	this->ValueRaw_ = 0;
}

template<int T>
inline FixedPoint<T>::FixedPoint(float Value)
{
	this->ValueRaw_ = 0;
}

template<int T>
inline FixedPoint<T>::FixedPoint(double Value)
{
	this->ValueRaw_ = 0;
}



template<int T>
inline FixedPoint<T> FixedPoint<T>::operator*=(const FixedPoint<T>& FP)
{
	return FixedPoint<T>(this->getValue());
}






template<int T>
inline double FixedPoint<T>::getValue()
{
	return 0.0;
}



#endif // FIXEDPOINT_H

