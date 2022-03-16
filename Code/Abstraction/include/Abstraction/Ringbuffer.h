#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <cstdlib>
#include <vector>

#include "Abstraction/Optional.h"


template <typename DataType>
class Ringbuffer
{
public:
	Ringbuffer(std::size_t MaxElements = 1);

	void addItem(DataType Item);

	Optional<DataType> getData(int Index = 0);
	std::size_t getSize() { return this->Buffer_.size(); };

	void clear() { this->Buffer_.clear(); };

private:
	std::vector<DataType> Buffer_;
	std::size_t MaxSize_;
};


template<typename DataType>
inline Ringbuffer<DataType>::Ringbuffer(std::size_t MaxElements)
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

