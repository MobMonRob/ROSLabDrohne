// Generated by gencpp from file mavros_msgs/SetModeRequest.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_SETMODEREQUEST_H
#define MAVROS_MSGS_MESSAGE_SETMODEREQUEST_H


#include <string>
#include <vector>
#include <map>




namespace mavros_msgs
{
    struct SetModeRequest
    {
    public:

        SetModeRequest() : base_mode(0), custom_mode() {};
        SetModeRequest(const SetModeRequest& _alloc) : base_mode(0), custom_mode() {};

        int base_mode;
        std::string custom_mode;

        typedef mavros_msgs::SetModeRequest* Ptr;
        typedef mavros_msgs::SetModeRequest* ConstPtr;
        typedef mavros_msgs::SetModeRequest* SetModeRequestPtr;
        typedef mavros_msgs::SetModeRequest* SetModeRequestConstPtr;

        std::ostream& operator<<(std::ostream& s)
        {
            return s;
        };
        bool operator==(const ::mavros_msgs::SetModeRequest& rhs)
        {
            return this->base_mode == rhs.base_mode &&
                this->custom_mode == rhs.custom_mode;
        };
        bool operator!=(const ::mavros_msgs::SetModeRequest& rhs)
        {
            return !(*this == rhs);
        };
    }; // SetModeRequest
} // namespace mavros_msgs


#endif // MAVROS_MSGS_MESSAGE_SETMODEREQUEST_H
