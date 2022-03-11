#include "Adapter/StateHandler.h"



IMUState StateHandler::getAvgState()
{
	int BufferSize = this->getSize();
	IMUState Sum;


	for (int i = 0; i < BufferSize; i++)
	{
		Optional<IMUState> Data = this->getData(i);


		if (Data.getValid())
		{
			Sum += Data.getData();
		}
	}

	return IMUState(Sum.getVector_Linear() / BufferSize,
		Sum.getVector_Angular() / BufferSize, 
		Sum.getGroundClearance() / BufferSize, 
		Sum.getTimestamp());
}


