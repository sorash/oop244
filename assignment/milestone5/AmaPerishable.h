#ifndef SICT_AMAPERISHABLE_H__
#define SICT_AMAPERISHABLE_H__

#include "AmaProduct.h"
#include "Date.h"

namespace sict
{
	class AmaPerishable : public AmaProduct
	{
		Date expiry_;
		AmaPerishable() : AmaProduct('P') {}

	public:
		const Date& expiry() const;
		void expiry(const Date& value);
		fstream& store(fstream& file, bool addNewLine = true) const;
		fstream& load(fstream& file);
		ostream& write(ostream& ostr, bool linear) const;
		istream& read(istream& istr);
	};
}
#endif
