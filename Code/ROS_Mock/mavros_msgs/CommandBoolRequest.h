// Generated by gencpp from file mavros_msgs/CommandBoolRequest.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_COMMANDBOOLREQUEST_H
#define MAVROS_MSGS_MESSAGE_COMMANDBOOLREQUEST_H


#include <string>
#include <vector>
#include <map>

#include "../std_msgs/Msg.h"


namespace mavros_msgs
{
    struct CommandBoolRequest
    {
    public:

        CommandBoolRequest() : value(false) {};
        CommandBoolRequest(const CommandBoolRequest& _alloc) : value(false) {};

        int value;

        typedef mavros_msgs::CommandBoolRequest* Ptr;
        typedef mavros_msgs::CommandBoolRequest* ConstPtr;
        typedef mavros_msgs::CommandBoolRequest* CommandBoolRequestPtr;
        typedef mavros_msgs::CommandBoolRequest* CommandBoolRequestConstPtr;

        std::ostream& operator<<(std::ostream& s)
        {
            return s;
        };
        bool operator==(const ::mavros_msgs::CommandBoolRequest& rhs)
        {
            return this->value == rhs.value;
        };
        bool operator!=(const ::mavros_msgs::CommandBoolRequest& rhs)
        {
            return !(*this == rhs);
        };
    }; // CommandBoolRequest
} // namespace mavros_msgs


#endif // MAVROS_MSGS_MESSAGE_COMMANDBOOLREQUEST_H