#include "Car.h"

namespace sict
{
	void Car::speed(int value)
	{
		speed_ = value;
	}

	int Car::maxSpeed() const
	{
		return maxSpeed_;
	}

	int Car::speed() const
	{
		return speed_;
	}

	Car::Car(int max)
	{
		maxSpeed_ = max;
		speed_ = 0;
	}
}