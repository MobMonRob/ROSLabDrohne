#ifndef JOYSTICKAXIS_H
#define JOYSTICKAXIS_H


class JoystickAxis
{
public:
	JoystickAxis(double Min, double Max);
	JoystickAxis(double Min, double Max, double Middle);
	
	double normalize(double Value);
	double denormalize(double Value);
	
private:
	double Min_;
	double Max_;
	double Middle_;
};

#endif // JOYSTICKAXIS_H


