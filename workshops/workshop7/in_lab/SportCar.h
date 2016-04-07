#ifndef SICT_SPORTCAR_H_
#define SICT_SPORTCAR_H_

#include "Car.h"

namespace sict
{
	class SportCar : public Car
	{
		int noOfPassengers_;

	public:
		SportCar();
		SportCar(int max, int passNo);

		// implementations of Vehicle's pure virtual methods
		void accelerate();
		void brake();
		std::ostream& display(std::ostream& ostr) const;
	};
}
#endif