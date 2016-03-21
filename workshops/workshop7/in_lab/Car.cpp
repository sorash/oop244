#include "Car.h"

namespace sict
{

	Car::Car(int maxSpeed)
	{
		speed(0);
	}

	// set speed value
	void Car::speed(int value)
	{
		speed_ = value;

		if (value > maxSpeed())
			speed_ = maxSpeed();

		if (value < 0)
			speed_ = 0;
	}

	// get maxspeed value
	int Car::maxSpeed() const
	{
		return maxSpeed_;
	}

	// get speed value
	int Car::speed() const
	{
		return speed_;
	}
}