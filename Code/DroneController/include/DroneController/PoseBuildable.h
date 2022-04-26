#ifndef POSEBUILDABLE_H
#define POSEBUILDABLE_H

#include "Domain/FixedPoint.h"

#include "DroneController/IMUState.h"
#include "DroneController/Pose.h"


class PoseBuildable
{
public:
	virtual void setPosition(Vector3D Position, Vector3D Uncertainty = Vector3D(Unit_None)) = 0;
	virtual void setOrientation(Vector3D Orientation, Vector3D Uncertainty = Vector3D(Unit_None)) = 0;
	void setValid(bool Validation) { this->Valid_ = Validation; };
	void setCalibration(bool Calibration) { this->Calibration_ = Calibration; };

	virtual Pose getPose() = 0;
	virtual Timestamp getTime() const = 0;
	virtual Vector3D getPosition() = 0;
	virtual Vector3D getPositionUncertainty() const = 0;
	virtual Vector3D getOrientation() = 0;
	virtual Vector3D getOrientationUncertainty() const = 0;
	bool getValid() const { return this->Valid_; };
	bool getCalibration() const { return this->Calibration_; };

	virtual bool updatePose(IMUState State) = 0;

	virtual void reset() = 0;

private:
	bool Valid_;
	bool Calibration_;

};

#endif // POSEBUILDABLE_H
