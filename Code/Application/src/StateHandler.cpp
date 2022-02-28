#include "Application/StateHandler.h"



State StateHandler::getAvgState()
{
	int BufferSize = this->getSize();
	State Sum;


	for (int i = 0; i < BufferSize; i++)
	{
		Optional<State> Data = this->getData(i);


		if (Data.getValid())
		{
			Sum += Data.getData();
		}
	}

	return State(Sum.getVector_Translative() / BufferSize, 
		Sum.getVector_Angular() / BufferSize, 
		Sum.getGroundClearance() / BufferSize, 
		Sum.getTimestamp());
}


