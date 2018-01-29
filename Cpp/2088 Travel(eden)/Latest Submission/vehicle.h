 #ifndef VEHICLE_H
#define VEHICLE_H

#include <cmath>
#include <iostream>
using namespace std;

struct City {
    double x, y;          // position of the city
    string name;  // name of city
};

class Vehicle {
 public:
    Vehicle(double _speed){ speed = _speed; }
    virtual void doTravel(const City& src, const City& dest) = 0;
    double getSpeed() const 
    {
        return speed;
    }
    ~Vehicle() {}

 private:
    double speed;
};

class BicycleStrategy: public Vehicle
{
	public:
		BicycleStrategy(double _speed):Vehicle(_speed){}
		~BicycleStrategy(){}
		void doTravel(const City& src, const City& dest)
		{
			double dis = fabs(src.x - dest.x) + fabs(src.y - dest.y);
			double speed = getSpeed();
			cout << "It takes " << dis / speed << 
			" hours to Travel from " << src.name <<
			" to " << dest.name << " by Bicycle." << endl;
		}
};

class TrainStrategy: public Vehicle
{
	public:
		TrainStrategy(double _speed):Vehicle(_speed){}
		~TrainStrategy(){}
		void doTravel(const City& src, const City& dest)
		{
			double dis = sqrt((src.x - dest.x) * (src.x - dest.x) + (src.y - dest.y) * (src.y - dest.y));
			double speed = getSpeed();
			cout << "It takes " << dis / speed << 
			" hours to Travel from " << src.name <<
			" to " << dest.name << " by Train." << endl;
		}
};

class AirplaneStrategy: public Vehicle
{
	public:
		AirplaneStrategy(double _speed):Vehicle(_speed){}
		~AirplaneStrategy(){}
		void doTravel(const City& src, const City& dest)
		{
			double dis = fabs(src.x - dest.x) > fabs(src.y - dest.y)? fabs(src.x - dest.x):fabs(src.y - dest.y);
			double speed = getSpeed();
			cout << "It takes " << dis / speed << 
			" hours to Travel from " << src.name <<
			" to " << dest.name << " by Airplane." << endl;
		}
};

#endif