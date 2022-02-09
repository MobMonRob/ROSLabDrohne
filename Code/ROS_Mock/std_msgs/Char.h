#ifndef CHARMSG_H
#define CHARMSG_H

#include "Msg.h"


namespace std_msgs
{
	class Char : public Msg
	{
	public:
		typedef std_msgs::Char* ConstPtr;


		char data;
	};

}


#endif // CHARMSG_H
