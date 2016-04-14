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
		AmaProduct::store(file, false);

		file << ',' << expiry_;

		if (addNewLine)
			file << endl;

		return file;
	}

	fstream& AmaPerishable::load(fstream& file)
	{
		AmaProduct::load(file);

		expiry_.read(file);
		file.ignore();

		return file;
	}

	ostream& AmaPerishable::write(ostream& ostr, bool linear) const
	{
		AmaProduct::write(ostr, linear);

		if (err_.isClear() && !isEmpty())
		{
			if (linear)
				ostr << expiry_;
			else
				ostr << endl << "Expiry date: " << expiry_;
		}

		return ostr;
	}

	istream& AmaPerishable::read(istream& istr)
	{
		AmaProduct::read(istr);

		if (err_.isClear())
		{
			cout << "Expiry date (YYYY/MM/DD): ";

			Date temp;
			istr >> temp;

			if (temp.bad())
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
			{
				err_.clear();
				istr.clear();

				expiry_ = temp;
			}
		}

		return istr;
	}
}