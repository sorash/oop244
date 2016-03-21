#include <iomanip>
#include <iostream>

using namespace std;

#include "Date.h"
#include "general.h"

namespace sict
{
	Date::Date()
	{
		year_ = mon_ = day_ = 0;
		readErrorCode_ = NO_ERROR;
	}
	Date::Date(int year, int month, int day)
	{
		year_ = year;
		mon_ = month;
		day_ = day;
		readErrorCode_ = NO_ERROR;
	}

	// returns a unique integer based on the date, used to compare two dates
	int Date::value()const
	{
		return year_ * 372 + mon_ * 31 + day_;
	}

	// returns number of days in a month
	int Date::mdays(int mon)const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;

		return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
	}

	// sets readErrorCode_ to a valid value
	void Date::errCode(int errorCode)
	{
		readErrorCode_ = errorCode;
	}

	// operator overloads
	bool Date::operator==(const Date& D)const
	{
		return value() == D.value();
	}
	bool Date::operator!=(const Date& D)const
	{
		return value() != D.value();
	}
	bool Date::operator<(const Date& D)const
	{
		return value() < D.value();
	}
	bool Date::operator>(const Date& D)const
	{
		return value() > D.value();
	}
	bool Date::operator<=(const Date& D)const
	{
		return value() <= D.value();
	}
	bool Date::operator>=(const Date& D)const
	{
		return value() >= D.value();
	}

	// returns the readErrorCode_ value
	int Date::errCode()const
	{
		return readErrorCode_;
	}

	// returns true if readErrorCode_ is not zero
	bool Date::bad()const
	{
		return readErrorCode_ != 0 ? true : false;
	}

	// reads date in format: YYYY?MM?DD
	std::istream& Date::read(std::istream& istr)
	{
		char delim;
		cin >> year_ >> delim >> mon_ >> delim >> day_;
		if (cin.bad() || cin.fail())
			errCode(CIN_FAILED);
		else
		{
			if (year_ < MIN_YEAR || year_ > MAX_YEAR)
				errCode(YEAR_ERROR);
			else
			{
				if (mon_ < 1 || mon_ > 12)
					errCode(MON_ERROR);
				else
				{
					if (day_ < 1 || day_ > mdays(mon_))
						errCode(DAY_ERROR);
					else
						cout << year_ << ',' << mon_ << ',' << day_ << endl;
				}
			}
		}

		return istr;
	}

	// writes the date in format: YYYY/MM/DD
	std::ostream& Date::write(std::ostream& ostr)const
	{
		cout << year_ << '/' << mon_ << '/' << day_ << endl;
		return ostr;
	}

	// custom IO for date
	std::istream& operator>>(std::istream& istr, Date& d)
	{
		d.read(istr);
		return istr;
	}
	std::ostream& operator<<(std::ostream& ostr, const Date& d)
	{
		d.write(ostr);
		return ostr;
	}
};