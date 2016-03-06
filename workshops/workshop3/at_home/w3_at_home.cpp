// OOP244 Workshop 3: Dynamic Memory
// File	w3_at_home.cpp
// Version 1.0
// Date	
// Author	
// Description
///////////////////////////////////////////////////////////


#include <iostream>
#include <cstring>
#include "Weather.h"
using namespace std;
using namespace sict;
double findLow(const char* date, const Weather *data, int dataSize);
int main(){
  int i; //  loop counter
  int n; //the count of days worth of weather
  // create the weather pointer here

  cout << "Weather Data\n";
  cout << "=====================" << endl;
  cout << "Days of Weather: ";
  cin >> n;
  cin.ignore();
  // allocate dynamic memory here

  for (i = 0; i < n; i++){
    char date_description[7];
    double high;
    double low;

    // ... add code to accept user input for
    //weather

  }
  cout << endl
    << "Weather report:" << endl
    << "Date        high  low" << endl
    << "======================" << endl;

  for (i = 0; i < n; i++){
    weather[i].display();
  }

  char query[7];
  cout << endl << "Enter the date you are looking for: ";
  //accept user input for the date to find
  //(in this example stored in char query[7])
  // and display the found low temprature.

  cin.getline(query, 7, '\n');
  double low = findLow(query, weather, n);
  cout << "Low temperature: " << low << endl;
  // deallocate dynamic memory here

  return 0;

}

