#include "AmaPerishable.h"

using namespace std;

namespace sict
{
	const Date& AmaPerishable::expiry() const
	{
		return expiry_;
	}

	void AmaPerishable::expiry(const Date& value)
	{
		expiry_ = value;
	}

	fstream& AmaPerishable::store(fstream& file, bool addNewLine) const
	{
		store(file, false);

		file << ',' << expiry_;

		if (addNewLine)
			file << endl;

		return file;
	}

	fstream& AmaPerishable::load(fstream& file)
	{
		load(file);
		expiry_.read(file);
		file.ignore();

		return file;
	}

	ostream& AmaPerishable::write(ostream& ostr, bool linear) const
	{
		write(ostr, linear);

		if (err_.isClear())
		{
			if (linear)
				ostr << '|' << expiry_;
			else
				ostr << endl << "Expiry date: " << expiry_;
		}

		return ostr;
	}

	istream& AmaPerishable::read(istream& istr)
	{
		read(istr);

		if (err_.isClear())
		{
			cout << "Expiry date (YYY/MM/DD):";

			Date temp;
			istr >> temp;
			if (istr.fail())
			{
				switch (temp.errCode())
				{
				case CIN_FAILED:
					err_.message("Invalid Date Entry");
					break;
				case YEAR_ERROR:
					err_.message("Invalid Year in Date Entry");
					break;
				case MON_ERROR:
					err_.message("Invalid Month in Date Entry");
					break;
				case DAY_ERROR:
					err_.message("Invalid Day in Date Entry");
					break;
				}

				istr.setstate(ios::failbit);
			}
			else
				expiry_ = temp;
		}

		return istr;
	}
}