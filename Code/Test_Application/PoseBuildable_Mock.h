#pragma once

#include "gmock/gmock.h"

#include "DroneController/PoseBuildable.h"


class PoseBuildable_Mock : public PoseBuildable
{
public:
	MOCK_METHOD(void, setPosition, (Vector3D Position, Vector3D Uncertainty), (override));
	MOCK_METHOD(void, setOrientation, (Vector3D Orientation, Vector3D Uncertainty), (override));

	MOCK_METHOD(Pose, getPose, (), (override));
	MOCK_METHOD(Timestamp, getTime, (), (const override));
	MOCK_METHOD(Vector3D, getPosition, (), (override));
	MOCK_METHOD(Vector3D, getPositionUncertainty, (), (const override));
	MOCK_METHOD(Vector3D, getOrientation, (), (override));
	MOCK_METHOD(Vector3D, getOrientationUncertainty, (), (const override));

	MOCK_METHOD(bool, updatePose, (IMUState State), (override));

	MOCK_METHOD(void, reset, (), (override));

};

