#ifndef SICT_ENROLLMENT_H_
#define SICT_ENROLLMENT_H_

namespace sict
{
	class Enrollment
	{
	
	private:
		char name_[31];
		char code_[11];
		int year_;
		int semester_;
		int slot_;
		bool enrolled_;
	
	public:
		Enrollment();
		Enrollment(const char* name, const char* code, int year, int semester, int time, bool enrolled = false);
		void set(const char* name, const char* code, int year, int semester, int slot, bool enrolled = false);
		bool hasConflict(const Enrollment &other) const;
		void display(bool nameOnly = false)const;
		bool isValid()const;
		void setEmpty();
		bool isEnrolled() const;

	};
}
#endif // !SICT_ENROLLMENT_H_