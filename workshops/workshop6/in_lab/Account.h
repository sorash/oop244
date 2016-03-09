#ifndef SICT_ACCOUNT_H__
#define SICT_ACCOUNT_H__

#include <iostream>

namespace sict
{
	class Account{
		char name_[41];
		double balance_;
	public:
		Account();
		Account(double balance);
		Account(const char name[], double balance = 0.0);
		void display(bool gotoNewline = true)const;
		Account& operator+=(const Account& other);
		Account& operator=(const char* name);
		friend Account operator+(const Account& other, const Account& other2);
	};

	std::ostream& operator<<(std::ostream& os, const Account& acc);
};

#endif
