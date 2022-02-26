#ifndef MOCK_ROSTIMING_H
#define MOCK_ROSTIMING_H


namespace ros
{
	class Duration
	{
	public:
		Duration(double Duration = 0) {};

		operator double() { return 0; };
	};

	class Time
	{
	public:
		Time operator-(const Time& T) { return Time(); };
		bool operator>(const Duration& T) { return false; };
		bool operator<(const Duration& T) { return false; };
		bool operator==(const Duration& T) { return false; };
		bool operator<=(const Duration& T) { return false; };
		bool operator>=(const Duration& T) { return false; };
		
		double toSec() { return 0; };


		static Time now() { return Time(); };
	};




	class Rate
	{
	public:
		Rate() {};
		Rate(int i) {};


		void sleep() {};
	};

};

#endif // MOCK_ROSTIMING_H
