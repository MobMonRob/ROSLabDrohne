#ifndef POSEBUILDABLE_H
#define POSEBUILDABLE_H

#include "DroneController/Timeable.h"

#include "Domain/FixedPoint.h"

#include "DroneController/IMUState.h"
#include "DroneController/Pose.h"

const FixedPoint<Accuracy_Value> Magic_CalibrationFactor(5);


class PoseBuildable : public Timeable
{
public:
	PoseBuildable();
	

	virtual void setPosition(Vector3D Position = Vector3D(Unit_Acceleration), Vector3D Velocity = Vector3D(Unit_Velocity), Vector3D Uncertainty = Vector3D(Unit_None)) = 0;
	virtual void setOrientation(Vector3D Orientation, Vector3D Uncertainty = Vector3D(Unit_None)) = 0;
	void setValidFlag(bool Flag);
	void setCalibrationFlag(bool Flag);
	void setCalculationFlag(bool Flag);

	virtual Pose getPose() = 0;
	virtual Vector3D getPosition() = 0;
	virtual Vector3D getPositionUncertainty() const = 0;
	virtual Vector3D getOrientation() = 0;
	virtual Vector3D getOrientationUncertainty() const = 0;
	bool getValidFlag() const { return this->Valid_; };
	bool getCalibrationFlag() const { return this->Calibration_; };
	Vector3D getOffsetAcceleration() const { return this->AccelerationOffset_; };
	bool getCalculationFlag() const { return this->Calculate_; };

	virtual bool updatePose(IMUState State) = 0;

	virtual void reset() = 0;

protected:
	void setCalibrationBegin(Timestamp Time);
	void setOffsetAcceleration(FixedPoint<Accuracy_Value> OffsetX, FixedPoint<Accuracy_Value> OffsetY, FixedPoint<Accuracy_Value> OffsetZ);
	virtual void calcOffset() = 0;
	void setCalculationBegin(Timestamp Time);

	Timestamp getCalibrationBegin() const { return this->CalibrationBegin_; };
	Timestamp getCalculationBegin() const { return this->CalculationBegin_; };

private:
	bool Valid_;

	bool Calibration_;
	Timestamp CalibrationBegin_;
	Timestamp CalibrationIntervall_;
	Vector3D AccelerationOffset_;
	
	bool Calculate_;
	Timestamp CalculationBegin_;
};

#endif // POSEBUILDABLE_H
