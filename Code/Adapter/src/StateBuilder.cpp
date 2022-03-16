#include <Adapter/StateBuilder.h>




IMUState StateBuilder::createState(Timestamp Time,
	FixedPoint<Accuracy_Value> LinAccelX, FixedPoint<Accuracy_Value> LinAccelY, FixedPoint<Accuracy_Value> LinAccelZ, 
	Unit RotVelUnit, FixedPoint<Accuracy_Value> RotVelX, FixedPoint<Accuracy_Value> RotVelY, FixedPoint<Accuracy_Value> RotVelZ,
	Value GroundClearance)
{
	Vector3D LinAccel(Unit_Acceleration, LinAccelX, LinAccelY, LinAccelZ);
	Vector3D RotVel(RotVelUnit, RotVelX, RotVelY, RotVelZ);


	return this->createState(Time, LinAccel, RotVel, GroundClearance);
}

IMUState StateBuilder::createState(Timestamp Time, Vector3D LinearAcceleration, Vector3D RotationalVelocity, Value GroundClearance)
{
	this->StateHandler_.addEntry(IMUState(LinearAcceleration, RotationalVelocity, GroundClearance, Time) - this->NullPoint_);

	return this->getState();
}

void StateBuilder::reset()
{
	this->clearStateHandler();
	this->NullPoint_ = IMUState();
}


