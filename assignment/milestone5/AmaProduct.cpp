#include "AmaProduct.h"
using namespace std;

namespace sict
{
	AmaProduct::AmaProduct(char tag)
	{
		fileTag_ = tag;
	}

	const char* AmaProduct::unit() const
	{
		return unit_;
	}

	void AmaProduct::unit(const char* value)
	{
		strcpy(unit_, value);
	}

	// base functions
	fstream& AmaProduct::store(fstream& file, bool addNewLine) const
	{

	}
	fstream& AmaProduct::load(fstream& file)
	{
		
	}
	ostream& AmaProduct::write(ostream& os, bool linear) const
	{

	}
	istream& AmaProduct::read(istream& istr)
	{

	}
}