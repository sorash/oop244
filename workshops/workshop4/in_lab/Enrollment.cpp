#include <iostream>
#include <cstring>
#include "Enrollment.h"

using namespace std;

namespace sict
{

	// constructors
	Enrollment::Enrollment()
	{

		setEmpty();
	}
	Enrollment::Enrollment(const char* name, const char* code, int year, int semester, int time, bool enrolled)
	{

		if (name == nullptr || code == nullptr || year <= 0 || semester <= 0 || time <= 0)
			setEmpty();
		else
			set(name, code, year, semester, time, enrolled);
	}

	// set to safe empty state
	void Enrollment::setEmpty()
	{

		name_[0] = 0;
		code_[0] = 0;
		year_ = 0;
		semester_ = 0;
		slot_ = 0;
		enrolled_ = false;
	}

	// set information
	void Enrollment::set(const char* name, const char* code, int year, int semester, int slot, bool enrolled)
	{

		strcpy(name_, name);
		strcpy(code_, code);
		year_ = year;
		slot_ = slot;
		semester_ = semester;
		enrolled_ = enrolled;
	}

	// checks if the current course interferes with another course entered
	// returns conflict if the year, slot, and semester are the same
	bool Enrollment::hasConflict(const Enrollment &other) const
	{

		return (year_ == other.year_) && (slot_ == other.slot_) && (semester_ == other.semester_);
	}

	bool Enrollment::isValid()const
	{
		return name_ && name_[0];
	}

	bool Enrollment::isEnrolled() const
	{
		
		return enrolled_;
	}


	void Enrollment::display(bool nameOnly)const{
		if (isValid()){
			cout << name_;
			if (!nameOnly){
				cout << endl << code_ << ", Year: " << year_ << " semester: " << semester_ << " Slot: " << slot_ << endl;
				cout << "Status: " << (isEnrolled() ? "E" : "Not e") << "nrolled." << endl;
			}
		}
		else{
			cout << "Invalid enrollment!" << endl;
		}
	}
}