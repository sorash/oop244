#include "AidApp.h"

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

		if (choice >= 0 && choice <= 5)
			return choice;

		return -1;
	}
}