#include "AidApp.h"
#include "AmaProduct.h"
#include "AmaPerishable.h"
#include <iomanip>

using namespace std;

namespace sict
{
	AidApp::AidApp(const char* filename)
	{
		strcpy(filename_, filename);

		for (int i = 0; i < MAX_NO_RECS; i++)
			product_[i] = nullptr;
		
		noOfProducts_ = 0;

		loadRecs();
	}

	// waits for user to hit enter
	void AidApp::pause() const
	{
		cout << "Press Enter to continue..." << endl;
		cin.ignore(2000, '\n');
	}

	// displays options and waits for user selection
	int AidApp::menu()
	{
		int choice;

		cout << "Disaster Aid Supply Management Program" << endl
			<< "1- List products" << endl
			<< "2- Display product" << endl
			<< "3- Add non-perishable product" << endl
			<< "4- Add perishable product" << endl
			<< "5- Add to quantity of purchased products" << endl
			<< "0- Exit program" << endl
			<< "> ";

		cin >> choice;
		cin.clear();

		// check if choice is valid
		if (choice >= 0 && choice <= 5)
			return choice;

		return -1;
	}

	// reads all records from file, or creates a file if it doesn't exist
	void AidApp::loadRecs()
	{
		// open file for reading
		datafile_.open(filename_, ios::in);

		// check if file exists
		if (!datafile_.fail())
		{
			int count = 0;
			char type, in[2000];

			// read records
			while (datafile_.getline(in, 2000, '\n'))
			{
				// read type
				datafile_ >> type;
				datafile_.ignore();

				delete product_[count];

				if (tolower(type) == 'p')	// perishable
				{
					product_[count] = new AmaPerishable;
					product_[count]->load(datafile_);
				}
				else	// non-perishable
				{
					product_[count] = new AmaProduct;
					product_[count]->load(datafile_);
				}

				count++;
			}

			// set number of files read
			noOfProducts_ = count;

			datafile_.close();
		}
		else
		{

			// create the file
			datafile_.open(filename_, ios::out);
			datafile_.close();
		}
	}

	// writes all product records to the file
	void AidApp::saveRecs()
	{
		// open file for writing
		datafile_.open(filename_, ios::out);

		// loop through all products and write them to file
		for (int i = 0; i < noOfProducts_; i++)
			product_[i]->store(datafile_);

		datafile_.close();
	}

	void AidApp::listProducts() const
	{
		// print heading
		cout << setw(3) << "Row" << '|'
			<< left << setw(MAX_SKU_LEN) << "SKU" << '|'
			<< left << setw(20) << "Product Name" << '|'
			<< right << setw(7) << "Cost" << '|'
			<< right << setw(4) << "QTY" << '|'
			<< left << setw(10) << "Unit" << '|'
			<< right << setw(4) << "Need" << '|'
			<< setw(10) << "Expiry" << endl;

		cout << setw(4) << setfill('-') << '|'
			<< setw(MAX_SKU_LEN + 1) << setfill('-') << '|'
			<< setw(21) << setfill('-') << '|'
			<< setw(8) << setfill('-') << '|'
			<< setw(5) << setfill('-') << '|'
			<< setw(10) << setfill('-') << '|'
			<< setw(5) << setfill('-') << '|'
			<< "-----------" << setfill(' ') << endl;

		// total for all items
		double total;

		// print all products
		for (int i = 0; i < noOfProducts_; i++)
		{
			cout << right << setw(3) << i + 1 << "|";
			product_[i]->write(cout, true);
			cout << setfill(' ') << endl;

			// add to total
			total += *product_[i];

			// pause when 10 products are printed
			if (i == 10)
				pause();
		}

		for (int i = 0; i < 72; i++)
			cout << '-';
		cout << endl << "Total cost of support: $" << fixed << setprecision(2) << total << endl;
	}

	// searches for an item with the same sku
	int AidApp::SearchProducts(const char* sku) const
	{
		// loop through all products and return the index if found
		for (int i = 0; i < noOfProducts_; i++)
		{
			if (*product_[i] == sku)
				return i;
		}

		return -1;
	}

	// updates the quantity on hand for a product
	void AidApp::addQty(const char* sku)
	{
		// search for the item
		int index = SearchProducts(sku);

		// check if item was found
		if (index != -1)
		{
			// show the product
			product_[index]->write(cout, false);
			cout << endl;

			// ask user for the quantity
			int qty;
			cout << "Please enter the number of purchased items: ";
			cin >> qty;

			// check if entered value is valid
			if (!cin.fail() && !cin.bad())
			{
				// flush buffer
				cin.clear();

				// check if amount is less than or equal to the amount required and add the quantity entered
				int required = product_[index]->qtyNeeded() - product_[index]->quantity();
				if (qty <= required)
				{
					product_[index] += qty;

					// update products
					saveRecs();
					cout << "Updated!" << endl;
				}
				else
				{
					// tell user it is more than required
					cout << "Too many items; only " << required << ", please return the extra " << qty - required << " items." << endl;
				}
			}
			else
				cout << "Invalid quantity value!" << endl;
		}
		else
			cout << "Not found!" << endl;
	}

	// creates a new product
	void AidApp::addProduct(bool isPerishable)
	{
		// hold a temporary product
		Product* temp;

		// create product based on passed type
		isPerishable ? temp = new AmaPerishable : temp = new AmaProduct;
		
		// get product info from user and show errors if creation failed
		istream& read = temp->read(cin);
		if (read.fail() || read.bad())
			temp->write(cout, false);
		else
		{
			// add to products and save records
			noOfProducts_++;
			product_[noOfProducts_] = temp;

			saveRecs();
		}
	}

	// displays the menu and do respective actions
	int AidApp::run()
	{
		int choice, index;
		char sku[2000];
		bool keepRunning = true;

		// show menu and get user choice
		do 
		{
			choice = menu();

			switch (choice)
			{
			case -1:
				// invalid choice
				cout << "===Invalid Selection, try again.===" << endl;
				pause();
				break;

			case 0:
				// terminate program
				cout << "Goodbye!!" << endl;
				keepRunning = false;
				break;

			case 1:
				// list products
				listProducts();
				break;

			case 2:
				// display a product by user give sku
				cout << "Please enter the SKU: ";
				cin >> sku;
				
				index = SearchProducts(sku);
				if (index != -1)
					product_[index]->write(cout, false);
				else
					cout << "Not found!" << endl;

				break;

			case 3:
				// add a non-perishable product and load records
				addProduct(false);
				loadRecs();
				break;

			case 4:
				// add a perishable product and load records
				addProduct(true);
				loadRecs();
				break;

			case 5:
				// add to quantity of a product with user given sku
				cout << "Please enter the SKU: ";
				cin >> sku;

				addQty(sku);
				break;
			}
		} while (choice != 0);

		return 0;
	}
}