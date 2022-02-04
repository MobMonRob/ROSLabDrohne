#ifndef MSG_H
#define MSG_H



class Stamp
{
public:
	double operator- (const Stamp& S) { return 0; };

	double toSec() { return 0; };
};

class Header
{
public:
	Stamp stamp;



};


class Msg
{
public:
	Msg() : header() {};
	Header header;
};

#endif // MSG_H
