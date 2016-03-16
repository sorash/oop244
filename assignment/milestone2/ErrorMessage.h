#ifndef SICT_ERRORMESSAGE_H__
#define SICT_ERRORMESSAGE_H__

#include <iostream>

namespace sict
{
	class ErrorMessage
	{
		char* message_;

	public:
		ErrorMessage();
		ErrorMessage(const char* errorMessage);
		
		ErrorMessage(const ErrorMessage& em) = delete;	// prevent copying of an errormessage object
		ErrorMessage& operator=(const ErrorMessage& em) = delete;	// prevent assigning an errormessage object to another
		ErrorMessage& operator=(const char* errorMessage);
		virtual ~ErrorMessage();
		
		void clear();
		bool isClear() const;
		void message(const char* value);
		const char* message() const;
	};

	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& err);
}

#endif