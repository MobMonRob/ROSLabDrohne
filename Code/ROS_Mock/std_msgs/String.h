#ifndef STRINGMSG_H
#define STRINGMSG_H

#include <string>

#include "Msg.h"


namespace std_msgs
{
	class String : public Msg
	{
	public:
		typedef std_msgs::String* ConstPtr;


		std::string data;
	};

}


#endif // STRINGMSG_H
