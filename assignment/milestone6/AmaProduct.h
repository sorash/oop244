#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__

#include "Product.h"
#include "ErrorMessage.h"
#include <fstream>
#include <cstring>

using namespace std;

namespace sict
{
	class AmaProduct : public Product
	{
	private:
		char fileTag_;
		char unit_[11];
	protected:
		ErrorMessage err_;
	public:
		AmaProduct(char tag = 'N');
		const char* unit() const;
		void unit(const char* value);
		
		// base functions
		fstream& store(fstream& file, bool addNewLine = true) const;
		fstream& load(fstream& file);
		ostream& write(ostream& os, bool linear) const;
		istream& read(istream& istr);
	};
}
#endif


