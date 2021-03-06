// Generated by gencpp from file geometry_msgs/Vector3.msg
// DO NOT EDIT!


#ifndef GEOMETRY_MSGS_MESSAGE_VECTOR3_H
#define GEOMETRY_MSGS_MESSAGE_VECTOR3_H


#include <string>
#include <vector>
#include <map>

#include "../std_msgs/Msg.h"


namespace geometry_msgs
{
    class Vector3 : public Msg
    {
    public:
        Vector3() : Msg(), x(0.0), y(0.0), z(0.0) {};
        Vector3(const Vector3& _alloc) : Msg(), x(_alloc.x), y(_alloc.y), z(_alloc.z) {};

        double x;
        double y;
        double z;

        static geometry_msgs::Vector3* Ptr;
        typedef geometry_msgs::Vector3* ConstPtr;
        static geometry_msgs::Vector3* Vector3Ptr;
        static geometry_msgs::Vector3* Vector3ConstPtr;

        std::ostream& operator<<(std::ostream& s)
        {
            return s;
        };
        bool operator==(const ::geometry_msgs::Vector3& rhs)
        {
            return this->x == rhs.x &&
                this->y == rhs.y &&
                this->z == rhs.z;
        };
        bool operator!=(const ::geometry_msgs::Vector3& rhs)
        {
            return !(*this == rhs);
        };
    }; // Vector3
} // namespace geometry_msgs


#endif // GEOMETRY_MSGS_MESSAGE_VECTOR3_H
