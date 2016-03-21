#include <cstring>
#include "PickupTruck.h"

namespace sict
{

	PickupTruck::PickupTruck()
	{
		loadAmount_ = 0;
		loadedMaterial_[0] = '\0';
	}

	// sets the loaded material and amount
	void PickupTruck::load(const char* mat, int amount)
	{
		loadAmount_ = amount;
		strcpy(loadedMaterial_, mat);
	}

	// clear load amount
	void PickupTruck::unload()
	{
		loadAmount_ = 0;
	}

	// get if truck is loaded or not
	bool PickupTruck::isEmpty() const
	{
		return loadAmount_ == 0;
	}

	// add 20 to speed
	void PickupTruck::accelerate()
	{
		speed(speed() + 20);
	}

	// reduce speed by 5
	void PickupTruck::brake()
	{
		speed(speed() - 5);
	}

	std::ostream& PickupTruck::display(std::ostream& ostr) const
	{
		if (isEmpty())
			ostr << "This pickup truck is not carrying any load";
		else
			ostr << "This pickup truck is carrying " << loadAmount_ << " kgs of " << loadedMaterial_;

		if (speed() > 0)
			ostr << ", traveling at the speed of " << speed() << " km/h." << std::endl;
		else if (speed() == 0)
			ostr << " and is parked." << std::endl;

		return ostr;
	}
}