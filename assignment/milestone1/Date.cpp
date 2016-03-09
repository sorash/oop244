#include <iomanip>
#include <iostream>

using namespace std;

#include "Date.h"
#include "general.h"

namespace sict
{	
	int Date::value()const
	{
		return year_ * 372 + mon_ * 31 + day_;
	}
	
	int Date::mdays()const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;
		
		return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
	}
}