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
		
		// input buffer
		char in[2000];

		// temp variables
		char _sku[MAX_SKU_LEN + 1], _name[2000], _taxed;
		int _qty, _qtyNeeded;
		double _price;

		// get fields
		file.getline(in, 2000, ',');
		strcpy(_sku, in);
		file.getline(in, 2000, ',');
		strcpy(_name, in);
		file.getline(in, 2000, ',');
		_price = atof(in);
		file.getline(in, 2000, ',');
		_taxed = in[0];
		file.getline(in, 2000, ',');
		_qty = atoi(in);
		file.getline(in, 2000, ',');
		strcpy(unit_, in);
		file.getline(in, 2000, ',');
		_qtyNeeded = atoi(in);
		
		// set fields
		sku(_sku);
		name(_name);
		price(_price);
		_taxed == '1' ? taxed(true) : taxed(false);
		quantity(_qty);
		qtyNeeded(_qtyNeeded);

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
				os << left << setw(MAX_SKU_LEN) << sku() << '|'
					<< left << setw(20) << name() << '|'
					<< right << fixed << setw(7) << setprecision(2) << cost() << '|'
					<< right << setw(4) << quantity() << '|'
					<< left << setw(10) << unit_ << '|'
					<< right << setw(4) << qtyNeeded() << '|';
			}
			else
			{
				os << "Sku: " << sku() << endl
					<< "Name: " << name() << endl
					<< "Price: " << price() << endl
					<< "Price after tax: ";

				taxed() ? os << cost() : os << "N/A";
				
				os << endl
					<< "Quantity On Hand: " << quantity() << ' ' << unit_;
				if (quantity() > 1)
					os << "s";

				os << endl << "Quantity Needed: " << qtyNeeded();
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