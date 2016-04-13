#include "AmaProduct.h"
#include <iomanip>

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
		char sku_[2000], name_[2000];
		int quantity_, qtyNeeded_;
		double price_;
		char taxed_;
		char delim;
		
		// skip tag
		file.ignore();
		file.ignore();

		// read fields
		file >> sku_
			>> delim
			>> name_ 
			>> delim
			>> price_ 
			>> delim
			>> taxed_ 
			>> delim
			>> quantity_ 
			>> delim
			>> unit_ 
			>> delim
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
				os << left << setw(MAX_SKU_LEN) << sku()
					<< '|'
					<< left << setw(20) << name()
					<< '|'
					<< right << fixed << setw(7) << setprecision(2) << cost()
					<< '|'
					<< right << setw(4) << quantity()
					<< '|'
					<< left << setw(10) << unit_
					<< '|'
					<< right << setw(4) << qtyNeeded()
					<< '|';
			}
			else
			{
				os << "Sku: " << sku() << endl
					<< "Name: " << name() << endl
					<< "Price: " << cost() << endl
					<< "Price after tax: ";
				
				taxed() ? os << price() : os << "N/A";
				
				os << endl << "Quantitiy On Hand: " << quantity() << endl
					<< "Quanttity Needed: " << qtyNeeded() << endl;
			}
		}
		else
			os << err_;

		return os;
	}

	istream& AmaProduct::read(istream& istr)
	{
		char sku_[2000], name_[2000];
		int quantity_, qtyNeeded_;
		double price_;
		char taxed_;

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
		if (taxed_ == 'Y' || taxed_ == 'y' || taxed_ == 'N' || taxed_ == 'n')
		{
			tolower(taxed_) == 'y' ? taxed(true) : taxed(false);
			istr.clear();

			cout << "Price: ";
			istr >> price_;
			if (istr.fail())
			{
				err_.message("Invalid Price Entry");
				istr.setstate(ios::failbit);
			}
			else
			{
				price(price_);

				cout << "Quantity On hand: ";
				istr >> quantity_;
				if (istr.fail())
				{
					err_.message("Invalid Quantity Entry");
					istr.setstate(ios::failbit);
				}
				else
				{
					quantity(quantity_);

					cout << "Quantity Needed: ";
					istr >> qtyNeeded_;
					if (istr.fail())
					{
						err_.message("Invalid Quantity Needed Entry");
						istr.setstate(ios::failbit);
					}
					else
						qtyNeeded(qtyNeeded_);
				}
			}
		}
		else
		{
			err_.message("Only (Y)es or (N)o are acceptable");
			istr.setstate(ios::failbit);
		}

		return istr;
	}
}