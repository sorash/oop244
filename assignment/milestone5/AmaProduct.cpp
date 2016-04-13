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
		if (!err_.isClear())
			os << err_.message();
		else
		{
			if (linear)
			{
				os << left << setw(MAX_SKU_LEN) << sku() << '|';
				os << left << setw(20) << name() << '|';
				os << right << fixed << setw(7) << setprecision(2) << cost() << '|';
				os << right << setw(4) << quantity() << '|';
				os << left << setw(10) << unit_ << '|';
				os << right << setw(4) << qtyNeeded() << '|';
			}
			else
			{
				os << "Sku: " << sku() << endl;
				os << "Name: " << name() << endl;
				os << "Price: " << price() << endl;
				os << "Price after tax: ";

				taxed() ? os << cost() : os << "N/A";
				os << endl;

				os << "Quantity On Hand: " << quantity() << ' ' << unit_ << endl;
				os << "Quantity Needed: " << qtyNeeded();
			}
		}

		return os;
	}

	istream& AmaProduct::read(istream& istr)
	{
		char _sku[MAX_SKU_LEN + 1], _name[2000];
		char _taxed;
		int _quantity, _qtyNeeded;
		double _price;

		cout << "Sku: ";
		istr >> _sku;

		cout << "Name: ";
		istr >> _name;

		cout << "Unit: ";
		istr >> unit_;

		cout << "Taxed? (y/n): ";
		istr >> _taxed;

		if (_taxed == 'Y' || _taxed == 'y' || _taxed == 'N' || _taxed == 'n')
		{
			istr.clear();
			err_.clear();

			cout << "Price: ";
			istr >> _price;

			if (!istr.fail() && !istr.bad())
			{
				istr.clear();
				err_.clear();

				cout << "Quantity On hand: ";
				istr >> _quantity;

				if (!istr.fail() && !istr.bad())
				{
					istr.clear();
					err_.clear();

					cout << "Quantity Needed: ";
					istr >> _qtyNeeded;

					if (istr.fail() || istr.bad())
					{
						err_ = "Invalid Quantity Needed Entry";
						istr.setstate(ios::failbit);
					}
				}
				else
				{
					err_ = "Invalid Quantity Entry";
					istr.setstate(ios::failbit);
				}
			}
			else
			{
				err_ = "Invalid Price Entry";
				istr.setstate(ios::failbit);
			}
		}
		else
		{
			err_ = "Only (Y)es or (N)o are acceptable";
			istr.setstate(ios::failbit);
		}

		if (!istr.fail() && !istr.bad())
		{
			sku(_sku);
			name(_name);
			tolower(_taxed) == 'y' ? taxed(true) : taxed(false);
			price(_price);
			quantity(_quantity);
			qtyNeeded(_qtyNeeded);
		}

		return istr;
	}
}