#ifndef TRANSMITABLE_H
#define TRANSMITABLE_H

class Transmitable
{
public:
	virtual bool transmitAction(double pitch, double roll, double thrust, double yarn) = 0;
};

#endif // TRANSMITABLE_H
