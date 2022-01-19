#include "PosControl/StateHandler.h"



State StateHandler::getAvgState()
{
	int BufferSize = this->getSize();
	Vector3D Tran(Unit_Length);
	Vector3D Ang(Unit_AngleDeg);
	double Time = 0;

	for (int i = 0; i < BufferSize; i++)
	{
		Optional<State> Data = this->getData(i);


		if (Data.getValid())
		{
			Tran = Tran + Data.getData().getVector_Translative();
			Ang = Ang + Data.getData().getVector_Angular();

			if (Data.getData().getTimestamp().getTime() > Time)
			{
				Time = Data.getData().getTimestamp().getTime();
			}
		}
	}

	return State(Tran / BufferSize, Ang / BufferSize, Timestamp(Time));
}











