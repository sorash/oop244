#include <iomanip>
#include <cstring>
#include "Account.h"

using namespace std;

namespace sict
{
	
	Account::Account()
	{
		name_[0] = 0;
		balance_ = 0;
	}
	
	Account::Account(double balance)
	{
		name_[0] = 0;
		balance_ = balance;
	}

	Account::Account(const char name[], double balance)
	{
		strncpy(name_, name, 40);
		name_[40] = 0;
		balance_ = balance;
	}

	void Account::display(bool gotoNewline)const
	{
		cout << (name_[0] ? name_ : "No Name") << ": $" << setprecision(2) << fixed << balance_;
		if (gotoNewline) cout << endl;
	}

	Account& Account::operator+=(const Account& other) {
		
		balance_ += other.balance_;

		return *this;
	}
	
	Account& Account::operator=(const char* name) {

		strcpy(name_, name);

		return *this;
	}

	Account operator+(const Account& other, const Account& other2) {
		
		Account ret;
		ret.name_[0] = '\0';
		ret.balance_ = other.balance_ + other2.balance_;
		
		return ret;
	}

	std::ostream& operator<<(std::ostream& os, const Account& acc)
	{
		acc.display(false);
		return os;
	}
}