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
	FixedPoint<Accuracy_Vector> Devider(0);
	IMUState Sum;


	for (int i = 0; i < BufferSize; i++)
	{
		Optional<IMUState> Data = this->getData(i);


		if (Data.getValid())
		{
			Sum += Data.getData();
			Devider += FixedPoint<Accuracy_Vector>(1);
		}
	}
	
	return IMUState(Sum.getLinear() / Devider,
		Sum.getRotational() / Devider,
		Sum.getGroundClearance() / Devider,
		Sum.getTimestamp());
}

IMUState StateHandler::getMedianState()
{
	Vector3D A(Unit_Acceleration);
	Vector3D R(Unit_AngleVelDeg);
	Value GC;
	Timestamp Time = this->getTime();
	std::size_t BufferSize = this->getSize();


	if (BufferSize > 0)
	{
		std::vector<FixedPoint<Accuracy_Value>> VectorAx;
		std::vector<FixedPoint<Accuracy_Value>> VectorAy;
		std::vector<FixedPoint<Accuracy_Value>> VectorAz;
		std::vector<FixedPoint<Accuracy_Value>> VectorRx;
		std::vector<FixedPoint<Accuracy_Value>> VectorRy;
		std::vector<FixedPoint<Accuracy_Value>> VectorRz;
		std::vector<Value> VectorGC;
		FixedPoint<Accuracy_Vector> Devider(0);



		for (int i = 0; i < BufferSize; i++)
		{
			Optional<IMUState> DataWrapper = this->getData(i);


			if (DataWrapper.getValid())
			{
				IMUState State = DataWrapper.getData();
				Vector3D LinearAcceleration = State.getLinear();
				Vector3D RotationalVelocity = State.getRotational();

				VectorAx.push_back(LinearAcceleration.getX());
				VectorAy.push_back(LinearAcceleration.getY());
				VectorAz.push_back(LinearAcceleration.getZ());

				VectorRx.push_back(RotationalVelocity.getX());
				VectorRy.push_back(RotationalVelocity.getY());
				VectorRz.push_back(RotationalVelocity.getZ());

				VectorGC.push_back(State.getGroundClearance());

				Devider += FixedPoint<Accuracy_Vector>(1);
			}
		}

		{	// sort
			// maybe use nth_element?
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

IMUState StateHandler::getVariance()
{
	std::vector<FixedPoint<Accuracy_Value>> VectorAx;
	std::vector<FixedPoint<Accuracy_Value>> VectorAy;
	std::vector<FixedPoint<Accuracy_Value>> VectorAz;
	std::vector<FixedPoint<Accuracy_Value>> VectorRx;
	std::vector<FixedPoint<Accuracy_Value>> VectorRy;
	std::vector<FixedPoint<Accuracy_Value>> VectorRz;
	Value VectorGC;


	for (int i = 0; i < this->getSize(); i++)
	{
		Optional<IMUState> DataWrapper = this->getData(i);


		if (DataWrapper.getValid())
		{
			IMUState State = DataWrapper.getData();
			Vector3D LinearAcceleration = State.getLinear();
			Vector3D RotationalVelocity = State.getRotational();


			VectorAx.push_back(LinearAcceleration.getX());
			VectorAy.push_back(LinearAcceleration.getY());
			VectorAz.push_back(LinearAcceleration.getZ());

			VectorRx.push_back(RotationalVelocity.getX());
			VectorRy.push_back(RotationalVelocity.getY());
			VectorRz.push_back(RotationalVelocity.getZ());

			VectorGC = State.getGroundClearance();
		}
	}

	return IMUState(Vector3D(Unit(""), StateHandler::calcVariance(VectorAx), StateHandler::calcVariance(VectorAy), StateHandler::calcVariance(VectorAz)),
		Vector3D(Unit(""), StateHandler::calcVariance(VectorRx), StateHandler::calcVariance(VectorRy), StateHandler::calcVariance(VectorRz)),
		VectorGC,
		this->getTime());
}




FixedPoint<Accuracy_Value> StateHandler::calcVariance(std::vector<FixedPoint<Accuracy_Value>> Data)
{
	FixedPoint<Accuracy_Value> ReturnValue;
	FixedPoint<Accuracy_Value> Average;
	std::size_t Counter = 0;

	
	for (std::vector<FixedPoint<Accuracy_Value>>::iterator it = Data.begin(); it != Data.end(); it++)
	{
		Average += *it;
		Counter++;
	}

	Average /= static_cast<int>(Counter);

	for (std::vector<FixedPoint<Accuracy_Value>>::iterator it = Data.begin(); it != Data.end(); it++)
	{
		ReturnValue += (*it - Average) * (*it - Average);
	}

	return FixedPoint<Accuracy_Value>();
}


