// Generated by gencpp from file ardrone_autonomy/Navdata.msg
// DO NOT EDIT!


#ifndef ARDRONE_AUTONOMY_MESSAGE_NAVDATA_H
#define ARDRONE_AUTONOMY_MESSAGE_NAVDATA_H


#include <string>
#include <vector>
#include <map>

#include "../std_msgs/Msg.h"

namespace ardrone_autonomy
{
class Navdata : public Msg
{
public:

    Navdata()
        : Msg()
        , batteryPercent(0.0)
        , state(0)
        , magX(0)
        , magY(0)
        , magZ(0)
        , pressure(0)
        , temp(0)
        , wind_speed(0.0)
        , wind_angle(0.0)
        , wind_comp_angle(0.0)
        , rotX(0.0)
        , rotY(0.0)
        , rotZ(0.0)
        , altd(0)
        , vx(0.0)
        , vy(0.0)
        , vz(0.0)
        , ax(0.0)
        , ay(0.0)
        , az(0.0)
        , motor1(0)
        , motor2(0)
        , motor3(0)
        , motor4(0)
        , tags_count(0)
        , tm(0.0) {
    };
  Navdata(const Navdata& _alloc)
      : Msg()
      , batteryPercent(0.0)
      , state(0)
      , magX(0)
      , magY(0)
      , magZ(0)
      , pressure(0)
      , temp(0)
      , wind_speed(0.0)
      , wind_angle(0.0)
      , wind_comp_angle(0.0)
      , rotX(0.0)
      , rotY(0.0)
      , rotZ(0.0)
      , altd(0)
      , vx(0.0)
      , vy(0.0)
      , vz(0.0)
      , ax(0.0)
      , ay(0.0)
      , az(0.0)
      , motor1(0)
      , motor2(0)
      , motor3(0)
      , motor4(0)
      , tags_count(0)
      , tm(0.0) {
  };


   float batteryPercent;
   long state;
   long magX;
   long magY;
   long magZ;
   long pressure;
   long temp;
   float wind_speed;
   float wind_angle;
   float wind_comp_angle;
   float rotX;
   float rotY;
   float rotZ;
   long altd;
   float vx;
   float vy;
   float vz;
   float ax;
   float ay;
   float az;
   uint8_t motor1;
   uint8_t motor2;
   uint8_t motor3;
   uint8_t motor4;
   long tags_count;
   std::vector<long> tags_type;
   std::vector<long> tags_xc;
   std::vector<long> tags_yc;
   std::vector<long> tags_width;
   std::vector<long> tags_height;
   std::vector<float> tags_orientation;
   std::vector<float> tags_distance;
   float tm;




  typedef ardrone_autonomy::Navdata* Ptr;
  typedef ardrone_autonomy::Navdata* ConstPtr;
  typedef ardrone_autonomy::Navdata* NavdataPtr;
  typedef ardrone_autonomy::Navdata* NavdataConstPtr;




  std::ostream& operator<<(std::ostream& s)
  {
      return s;
  }
}; // class Navdata
} // namespace ardrone_autonomy


#endif // ARDRONE_AUTONOMY_MESSAGE_NAVDATA_H
