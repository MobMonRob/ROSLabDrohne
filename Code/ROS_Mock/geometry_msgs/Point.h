// Generated by gencpp from file geometry_msgs/Point.msg
// DO NOT EDIT!


#ifndef GEOMETRY_MSGS_MESSAGE_POINT_H
#define GEOMETRY_MSGS_MESSAGE_POINT_H


#include <string>
#include <vector>
#include <map>


namespace geometry_msgs
{
class Point
{
public:
    Point()
        : x(0.0)
        , y(0.0)
        , z(0.0) {};
    Point(const Point& _alloc)
        : x(0.0)
        , y(0.0)
        , z(0.0) {};

    double x;
    double y;
    double z;

    typedef geometry_msgs::Point* Ptr;
    typedef geometry_msgs::Point* ConstPtr;
    typedef geometry_msgs::Point* PointPtr;
    typedef geometry_msgs::Point* PointConstPtr;

    std::ostream& operator<<(std::ostream& s)
    {
        return s;
    }
    bool operator==(const geometry_msgs::Point& rhs)
    {
        return this->x == rhs.x &&
            this->y == rhs.y &&
            this->z == rhs.z;
    }
    bool operator!=(const ::geometry_msgs::Point& rhs)
    {
        return !(*this == rhs);
    }
}; // Point
} // namespace geometry_msgs

#endif // GEOMETRY_MSGS_MESSAGE_POINT_H
