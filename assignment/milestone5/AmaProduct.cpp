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
		file << fileTag_ << ',' << 
			sku() << ',' << name() << ',' << price() << ',' << taxed() << ',' << quantity() << ',' << unit_ << ',' << qtyNeeded();

		if (addNewLine)
			file << endl;

		return file;
	}

	fstream& AmaProduct::load(fstream& file)
	{
		char *sku_, *name_;
		int quantity_, qtyNeeded_;
		double price_;
		bool taxed_;
		
		// skip tag
		file.ignore();
		file.ignore();

		// read fields
		file >> sku_
			>> name_ 
			>> price_ 
			>> taxed_ 
			>> quantity_ 
			>> unit_ 
			>> qtyNeeded_;

		// set values
		sku(sku_);
		name(name_);
		price(price_);
		taxed(taxed_);
		quantity(quantity_);
		qtyNeeded(qtyNeeded_);

		return file;
	}

	ostream& AmaProduct::write(ostream& os, bool linear) const
	{
		if (err_.isClear())
		{
			if (linear)
			{
				os << os.left << os.width(MAX_SKU_LEN) << sku()
					<< '|'
					<< os.left << os.width(20) << name()
					<< '|'
					<< os.right << os.precision(2) << os.width(7) << cost()
					<< '|'
					<< os.right << os.width(4) << quantity()
					<< '|'
					<< os.left << os.width(10) << unit_
					<< '|'
					<< os.right << os.width(4) << qtyNeeded();
			}
			else
			{
				os << "Sku: " << sku() << endl
					<< "Name: " << name() << endl
					<< "Price: " << cost() << endl
					<< "Price after tax: " << (price() > 0) ? os << price() : os << "N/A" << endl
					<< "Quantitiy On Hand: " << quantity() << endl
					<< "Quanttity Needed: " << qtyNeeded();
			}
		}
		else
			os << err_;

		return os;
	}

	istream& AmaProduct::read(istream& istr)
	{
		char *sku_, *name_;
		int quantity_, qtyNeeded_;
		double price_;
		bool taxed_;

		cout << "Sku: ";
		istr >> sku_;
		sku(sku_);

		cout << "Name: ";
		istr >> name_;
		name(name_);

		cout << "Unit: ";
		istr >> unit_;

		cout << "Taxed? (y/n): ";
		istr >> taxed_;
		taxed(taxed_);

		cout << "Price: ";
		istr >> price_;
		price(price_);

		cout << "Quantity On hand: ";
		istr >> quantity_;
		quantity(quantity_);

		cout << "Quantity Needed: ";
		istr >> qtyNeeded_;
		qtyNeeded(qtyNeeded_);

		return istr;
	}
}