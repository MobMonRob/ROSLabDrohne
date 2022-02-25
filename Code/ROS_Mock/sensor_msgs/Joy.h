// Generated by gencpp from file sensor_msgs/Joy.msg
// DO NOT EDIT!


#ifndef SENSOR_MSGS_MESSAGE_JOY_H
#define SENSOR_MSGS_MESSAGE_JOY_H


#include <string>
#include <vector>
#include <map>


#include "../std_msgs/Msg.h"

namespace sensor_msgs
{
    class Joy : public Msg
    {
    public:

        Joy() : Msg(), axes(), buttons() {};
        Joy(const Joy& _alloc) : Msg(), axes(), buttons() {};

        std::vector<float> axes;
        std::vector<int> buttons;

        typedef sensor_msgs::Joy* Ptr;
        typedef sensor_msgs::Joy* ConstPtr;
        typedef sensor_msgs::Joy* JoyPtr;
        typedef sensor_msgs::Joy* JoyConstPtr;

        std::ostream& operator<<(std::ostream& s)
        {

            return s;
        };
        bool operator==(const ::sensor_msgs::Joy& rhs)
        {
            return this->axes == rhs.axes &&
                this->buttons == rhs.buttons;
        };
        bool operator!=(const ::sensor_msgs::Joy& rhs)
        {
            return !(*this == rhs);
        };
    }; // Joy
} // namespace sensor_msgs


#endif // SENSOR_MSGS_MESSAGE_JOY_H
