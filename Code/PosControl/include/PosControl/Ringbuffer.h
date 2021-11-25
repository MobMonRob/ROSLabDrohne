#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <vector>

#include "PosControl/Optional.h"


template <typename DataType>
class Ringbuffer
{
public:
	Ringbuffer(size_t MaxElements = 1);

	void addItem(DataType Item);


	Optional<DataType> getData(int Index = 0);
	size_t getSize() { return this->Buffer_.size(); };

private:
	std::vector<DataType> Buffer_;
	size_t MaxSize_;
};


template<typename DataType>
inline Ringbuffer<DataType>::Ringbuffer(size_t MaxElements)
{
	this->MaxSize_ = MaxElements;
}



template<typename DataType>
inline void Ringbuffer<DataType>::addItem(DataType Item)
{
	this->Buffer_.push_back(Item);

	while (this->getSize() > this->MaxSize_)
	{
		this->Buffer_.erase(this->Buffer_.begin());
	}
}



template<typename DataType>
inline Optional<DataType> Ringbuffer<DataType>::getData(int Index)
{
	Optional<DataType> ReturnItem;


	if (Index >= 0 && Index < this->getSize())
	{
		ReturnItem = Optional<DataType>(this->Buffer_.at(Index), true);
	}

	return ReturnItem;
}



#endif // RINGBUFFER_H