#ifndef SICT_DATE_H__
#define SICT_DATE_H__

#include <iostream>

// error codes
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace sict
{
	class Date
	{
	private:
		int year_;
		int mon_;
		int day_;
		int readErrorCode_;	// holds an error code to validify the date value

		int value()const;	// returns a unique integer based on the date, used to compare two dates
		void errCode(int errorCode);	// sets readErrorCode_ to a valid value
	
	public:
		Date();
		Date(int year, int month, int day);

		bool operator==(const Date& D)const;
		bool operator!=(const Date& D)const;
		bool operator<(const Date& D)const;
		bool operator>(const Date& D)const;
		bool operator<=(const Date& D)const;
		bool operator>=(const Date& D)const;

		int mdays(int mon)const;	// returns number of days in a month
		int errCode()const;	// returns the readErrorCode_ value
		bool bad()const;	// returns true if readErrorCode_ is not zero

		std::istream& read(std::istream& istr);	// reads date in format: YYY?MM?DD
		std::ostream& write(std::ostream& ostr)const;	// writes the date in format: YYYY/MM/DD
	};

	// custom IO for date
	std::istream& operator>>(std::istream& istr, Date& d);
	std::ostream& operator<<(std::ostream& ostr, const Date& d);
}

#endif