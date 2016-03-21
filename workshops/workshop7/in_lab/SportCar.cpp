#include "SportCar.h"

namespace sict
{

	SportCar::SportCar()
	{
		noOfPassengers_ = 1;
	}
	SportCar::SportCar(int maxSpeed, int passNum) : Car(maxSpeed)
	{
		noOfPassengers_ = passNum;
	}

	// add 40 to speed
	void SportCar::accelerate()
	{
		speed(speed() + 40);
	}

	// reduce speed by 10
	void SportCar::brake()
	{
		speed(speed() - 10);
	}

	std::ostream& SportCar::display(std::ostream& ostr) const
	{
		if (speed() > 0)
			ostr << "This sport car is carrying " << noOfPassengers_ <<
			" passengers and is traveling at a speed of " << speed() << " km/h." << std::endl;
		else if (speed() == 0)
			ostr << "This sport car is carrying " << noOfPassengers_ <<
			" passengers and is parked." << std::endl;

		return ostr;
	}
}