#ifndef RINGBUFFERITEM_H
#define RINGBUFFERITEM_H



template <typename DataType>
class RingbufferItem
{
public:
	RingbufferItem(RingbufferItem* NextAddr = nullptr);

	bool setNextAddr(RingbufferItem* NextAddr);
	void setData(DataType Data) { this->Data_ = Data; };

	RingbufferItem* getNextAddr() { return this->Next_; };
	DataType getData() { return this->Data_; };

private:
	RingbufferItem* Next_ = nullptr;
	DataType Data_;
};





template<typename DataType>
inline RingbufferItem<DataType>::RingbufferItem(RingbufferItem* NextAddr)
{
	this->setNextAddr(NextAddr);
}


template<typename DataType>
inline bool RingbufferItem<DataType>::setNextAddr(RingbufferItem* NextAddr)
{
	if (this->getNextAddr() == nullptr)
	{
		this->Next_ = NextAddr;
	}

	return this->getNextAddr() == NextAddr;
}












#endif // RINGBUFFERITEM_H
