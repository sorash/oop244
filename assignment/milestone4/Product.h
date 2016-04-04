#ifndef PRODUCT_SICT_
#define PRODUCT_SICT_

#include <iostream>
#include "general.h"
#include "streamable.h"

namespace sict
{
	class Product : public Streamable
	{
		char sku_[MAX_SKU_LEN + 1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_, qtyNeeded_;

	public:
		Product();
		Product(const char* sku, const char* name, bool taxed = true, double price = 0, int qtyNeeded = 0);
		Product(const Product&);
		Product& operator=(const Product&);
		~Product();

		// setters
		void sku(const char*);
		void name(const char*);
		void price(double);
		void taxed(bool);
		void quantity(int);
		void qtyNeeded(int);

		// getters
		char* sku() const;
		char* name() const;
		double price() const;
		bool taxed() const;
		int quantity() const;
		int qtyNeeded() const;
		double cost() const;
		bool isEmpty() const;

		// operator overloads
		bool operator==(const char*);
		int operator+=(int);
		int operator-=(int);
	};

	// non-member operator overloads
	double operator+=(double, const Product&);
	std::istream& operator>>(std::istream& is, Product& p);
	std::ostream& operator<<(std::ostream& os, const Product&);
}

#endif