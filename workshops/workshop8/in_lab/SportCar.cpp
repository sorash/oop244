#include "SportCar.h"

namespace sict
{
	SportCar::SportCar()
	{
		noOfPassengers_ = 0;
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
			ostr << "This sport car is carrying " << noOfPassengers_ << " and is traveling at a speed of " << speed() << " km/h.";
		if (speed() == 0)
			ostr << "This sport car is carrying " << noOfPassengers_ << " and is parked.";
		
		return ostr;
	}
}