#include "DroneController/Thrustable.h"




inline Rotor::Rotor(Value C_T, Value Diameter)
	: C_T_(C_T),
	Diameter_(Diameter),
	RotorSpeed_(Value(Unit_Frequence_RPM, 0))
{
}



Value Rotor::getThrust(Value C_T, Value Diameter, Value Density, Value RotorSpeed)
{
	Value ReturnValue(Unit_Force);
	const int Accuracy_ValueFine = 9;
	FixedPoint<Accuracy_ValueFine> DiameterAccuracy = FixedPoint<Accuracy_ValueFine>::convert(Diameter.getValue());
	FixedPoint<Accuracy_ValueFine> Diameter4 = DiameterAccuracy * DiameterAccuracy * DiameterAccuracy * DiameterAccuracy;
	FixedPoint<Accuracy_Value> Speed2 = RotorSpeed.getValue() * RotorSpeed.getValue();
	FixedPoint<Accuracy_Value> Diameter4Speed2 = FixedPoint<Accuracy_Value>::convert(Diameter4 * FixedPoint<Accuracy_ValueFine>::convert(Speed2));


	/*
	 * https://commons.erau.edu/cgi/viewcontent.cgi?article=1427&context=ijaaa
	 */

	return Value(Unit_Force, Density.getValue() * C_T.getValue() * Diameter4Speed2);
}


