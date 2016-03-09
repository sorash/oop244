// OOP244 Workshop 2: Compound types and privacy
// File	???????
// Version 1.0
// Date	???????????
// Author	?????????
// Description
// ?????????????????????
//
//
// Revision History
///////////////////////////////////////////////////////////
// Name			Date		Reason
// 
///////////////////////////////////////////////////////////
#include <iostream>
#include <cstring>
using namespace std;
#include "AccountNumber.h"

namespace sict{

	// member functions' (methods') definition go here
	void AccountNumber::name(const char name[])
	{

		// set name for account
		strcpy(_name, name);
	}
	
	void AccountNumber::accountNumber(int bankCode, int branchCode, int accountNumber)
	{

		// set values
		_bankCode = bankCode;
		_branchCode = branchCode;
		_accountNumber = accountNumber;

		// make sure values are valid
		if (bankCode >= MIN_BANKCODE && bankCode <= MAX_BANKCODE)
		{
			if (branchCode >= MIN_BRANCHCODE && branchCode <= MAX_BRANCHCODE)
			{
				if (accountNumber >= MIN_ACCNO && accountNumber <= MAX_ACCNO)
				{

					_validAccNumber = true;
				}
			}
		}
		else
			_validAccNumber = false;
	}

	void AccountNumber::display() const
	{

		// display messages based on validity of account
		if (isValid())
			cout << "Name: " << _name << ", Account number: " << _bankCode << "-"
				<< _branchCode << "-" << _accountNumber << endl;
		else
			cout << _name << " does not have a valid account number." << endl;
	}
	
	bool AccountNumber::isValid() const
	{

		return _validAccNumber;
	}
}