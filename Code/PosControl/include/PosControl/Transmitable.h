#ifndef TRANSMITABLE_H
#define TRANSMITABLE_H

class Transmitable
{
public:
	virtual void transmitAction(double pitch, double roll, double thrust, double yarn) {};
};

#endif // TRANSMITABLE_H
