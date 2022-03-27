#include "Adapter/StateHandler.h"

#include <algorithm>







Timestamp StateHandler::getTime()
{
	Timestamp ReturnTime;
	Optional<IMUState> StateWrapper = this->getData(this->getSize() - 1);

	if (StateWrapper.getValid())
	{
		ReturnTime = StateWrapper.getData().getTimestamp();
	}

	return ReturnTime;
}




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

	return IMUState(Sum.getLinearAcceleration() / BufferSize,
		Sum.getRotationalVelocity() / BufferSize, 
		Sum.getGroundClearance() / BufferSize, 
		Sum.getTimestamp());
}

IMUState StateHandler::getMedianState()
{
	Vector3D A(Unit_Acceleration);
	Vector3D R(Unit_AngleVelDeg);
	Value GC;
	Timestamp Time = this->getTime();
	int BufferSize = this->getSize();


	if (BufferSize > 0)
	{
		std::vector<FixedPoint<Accuracy_Value>> VectorAx;
		std::vector<FixedPoint<Accuracy_Value>> VectorAy;
		std::vector<FixedPoint<Accuracy_Value>> VectorAz;
		std::vector<FixedPoint<Accuracy_Value>> VectorRx;
		std::vector<FixedPoint<Accuracy_Value>> VectorRy;
		std::vector<FixedPoint<Accuracy_Value>> VectorRz;
		std::vector<Value> VectorGC;



		for (int i = 0; i < BufferSize; i++)
		{
			Optional<IMUState> DataWrapper = this->getData(i);


			if (DataWrapper.getValid())
			{
				IMUState State = DataWrapper.getData();
				Vector3D LinearAcceleration = State.getLinearAcceleration();
				Vector3D RotationalVelocity = State.getRotationalVelocity();

				VectorAx.push_back(LinearAcceleration.getX());
				VectorAy.push_back(LinearAcceleration.getY());
				VectorAz.push_back(LinearAcceleration.getZ());

				VectorRx.push_back(RotationalVelocity.getX());
				VectorRy.push_back(RotationalVelocity.getY());
				VectorRz.push_back(RotationalVelocity.getZ());

				VectorGC.push_back(State.getGroundClearance());
			}
		}

		{	// sort
			std::sort(VectorAx.begin(), VectorAx.end());
			std::sort(VectorAy.begin(), VectorAy.end());
			std::sort(VectorAz.begin(), VectorAz.end());

			std::sort(VectorRx.begin(), VectorRx.end());
			std::sort(VectorRy.begin(), VectorRy.end());
			std::sort(VectorRz.begin(), VectorRz.end());
			
			std::sort(VectorGC.begin(), VectorGC.end());
		}

		if (BufferSize % 2 == 0)
		{
			int Index = BufferSize / 2;
			const FixedPoint<Accuracy_Value> Devider(2);


			A = Vector3D(Unit_Acceleration,
				(VectorAx.at(Index - 1) + VectorAx.at(Index)) / Devider,
				(VectorAy.at(Index - 1) + VectorAy.at(Index)) / Devider,
				(VectorAz.at(Index - 1) + VectorAz.at(Index)) / Devider);
			R = Vector3D(Unit_AngleVelDeg,
				(VectorRx.at(Index - 1) + VectorRx.at(Index)) / Devider,
				(VectorRy.at(Index - 1) + VectorRy.at(Index)) / Devider,
				(VectorRz.at(Index - 1) + VectorRz.at(Index)) / Devider);
			GC = (VectorGC.at(Index - 1) + VectorGC.at(Index)) / Devider;
		}
		else
		{
			int Index = BufferSize / 2;


			A = Vector3D(Unit_Acceleration, VectorAx.at(Index), VectorAy.at(Index), VectorAz.at(Index));
			R = Vector3D(Unit_AngleVelDeg, VectorRx.at(Index), VectorRy.at(Index), VectorRz.at(Index));
			GC = VectorGC.at(Index);
		}
	}

	return IMUState(A, R, GC, Time);
}
