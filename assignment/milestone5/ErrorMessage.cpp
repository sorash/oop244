#include "ErrorMessage.h"
#include <cstring>

namespace sict
{
	ErrorMessage::ErrorMessage()
	{
		message_ = nullptr;
	}

	ErrorMessage::ErrorMessage(const char* errorMessage)
	{
		message_ = nullptr;
		message(errorMessage);
	}
	
	// sets the message and returns the object
	ErrorMessage& ErrorMessage::operator=(const char* errorMessage)
	{
		message(errorMessage);
		return *this;
	}

	ErrorMessage::~ErrorMessage()
	{
		clear();
	}

	// clears occupied memory by message
	void ErrorMessage::clear()
	{
		delete[] message_;
		message_ = nullptr;
	}

	// checks if message does not occupy memory
	bool ErrorMessage::isClear() const
	{
		return (message_ == nullptr);
	}

	// sets the message to value
	void ErrorMessage::message(const char* value)
	{
		// clear, reallocate memory, and copy the error message
		clear();
		message_ = new char[strlen(value) + 1];
		strcpy(message_, value);
	}

	// gets address of message
	const char* ErrorMessage::message() const
	{
		return message_;
	}

	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& err)
	{
		if (!err.isClear())
		{
			std::cout << err.message();
		}

		return ostr;
	}
}