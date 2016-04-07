#include "SportCar.h"

namespace sict
{
	SportCar::SportCar()
	{
		noOfPassengers_ = 1;
	}

	SportCar::SportCar(int max, int passNo) : Car(max)
	{
		noOfPassengers_ = passNo;
	}

	void SportCar::accelerate()
	{
		speed(speed() + 40);
	}

	void SportCar::brake()
	{
		speed(speed() - 10);
	}

	std::ostream& SportCar::display(std::ostream& ostr) const
	{
		if (speed() > 0)
			ostr << "This sport car is carrying " << noOfPassengers_ << " passengers and is traveling at a speed of " << speed() << " km/h.";
		else
			ostr << "This sport car is carrying " << noOfPassengers_ << " passengers and is parked.";

		return ostr;
	}
}