#include <cstring>
#include <iostream>
#include "String.h"

using namespace std;

namespace sict
{
	void String::deallocate()
	{
		delete[] data_;
		data_ = nullptr;
		memSize_ = 0;
	}

	void String::allocate(int memsize)
	{
		delete[] data_;
		data_ = new char[memsize];
		memSize_ = memsize;
	}

	void String::resize(int memsize)
	{
		char * temp = new char[memsize];
		
		if (data_ != nullptr)
		{
			int i = 0;
			while (data_[i] != '\0' && i <= memsize - 1)
			{
				temp[i] = data_[i];
				i++;
			}

			delete[] data_;
			data_ = temp;

			memSize_ = memsize;
			len_ = i;
		}
	}

	String::String()
	{
		data_ = nullptr;
		memSize_ = 0;
		len_ = 0;
	}

	void String::init(const char* str, int memSize)
	{
		data_ = nullptr;

		if (memSize < strlen(str))
			memSize = strlen(str) + 1;

		data_ = new char[memSize];
		strcpy(data_, str);
		len_ = strlen(data_);
	}

	String::String(const char* str, int memSize)
	{
		init(str, memSize);
	}

	String::String(const String& S)
	{
		init(S.data_, S.memSize_);
	}

	String& String::operator=(const String& S)
	{
		if (this != &S)
		{
			delete[] data_;
			init(S.data_, S.memSize_);
		}

		return *this;
	}

	String::~String()
	{
		delete[] data_;
	}

	int String::length()const
	{
		return len_;
	}

	int String::memSize()const
	{
		return memSize_;
	}

	String::operator const char *()const
	{
		return data_;
	}

	istream& String::read(istream& istr)
	{
		char c;
		int i = 0;
		while (c = istr.get() != '\n')
		{
			if (i > memSize_)
				resize(memSize_ + ExpansionSize);

			data_[i] = c;
			i++;
		}
		data_[i] = NULL;

		return istr;
	}

	// operator overloads


	String& String::operator+=(const char* str)
	{
		int tempLen = strlen(str);

		if (len_ + tempLen + 1 > memSize_)
			resize(len_ + tempLen + 1);

		strcat(data_, str);
		len_ = strlen(data_);

		return *this;
	}

	String& String::operator+=(String& s)
	{
		return operator+=(s.data_);
	}

	String String::operator + (const String& s) const
	{
		String temp = *this;
		temp += s;

		return temp;
	}

	String& String::operator++()
	{
		String copy = *this;

		copy.resize(copy.memSize_ + 2);
		
		for (int i = 0; i < copy.memSize_ + 1; i++)
			copy[i + 1] = copy[i];

		copy[0] = ' ';

		return copy;
	}

	String& String::operator++(int n)
	{
		String copy = *this;

		copy.resize(copy.memSize_ + 1);
		copy[memSize_ - 1] = ' ';

		return copy;
	}

	char& String::operator[](int index)
	{
		if (data_[index] < 0 || data_[index] > len_)
			resize(index + ExpansionSize);

		return data_[index];
	}
	
	String::operator int()const
	{
		return strlen(data_);
	}

	std::ostream& operator<<(std::ostream& ostr, const String &s)
	{
		ostr << s.data_;
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, String &s)
	{
		s.read(istr);
		return istr;
	}
}