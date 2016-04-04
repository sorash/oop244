#include "product.h"
#include "general.h"
#include <cstring>

using namespace std;

namespace sict
{
	Product::Product()
	{
		sku_[0] = '\0';
		name_ = nullptr;
		taxed_ = true;
		price_ = 0;
		quantity_ = 0;
		qtyNeeded_ = 0;
	}

	Product::Product(const char* sku, const char* name, bool taxed, double price, int qtyNeeded)
	{
		strncpy(sku_, sku, MAX_SKU_LEN);
		
		name_ = new char[strlen(name) + 1];
		strcpy(name_, name);

		taxed_ = taxed;
		price_ = price;
		quantity_ = 0;
		qtyNeeded_ = qtyNeeded;
	}

	Product::Product(const Product& p)
	{
		strncpy(sku_, p.sku_, MAX_SKU_LEN);

		name_ = nullptr;
		name_ = new char[strlen(p.name_) + 1];
		strcpy(name_, p.name_);

		taxed_ = p.taxed_;
		price_ = p.price_;
		quantity_ = p.quantity_;
		qtyNeeded_ = p.qtyNeeded_;
	}
	Product& Product::operator=(const Product& p)
	{
		strncpy(sku_, p.sku_, MAX_SKU_LEN);

		name_ = new char[strlen(p.name_) + 1];
		strcpy(name_, p.name_);

		taxed_ = p.taxed_;
		price_ = p.price_;
		quantity_ = p.quantity_;
		qtyNeeded_ = p.qtyNeeded_;

		return *this;
	}

	Product::~Product()
	{
		delete[] name_;
		name_ = nullptr;
	}

	// setters
	void Product::sku(const char* value)
	{
		strncpy(sku_, value, MAX_SKU_LEN);
	}
	void Product::name(const char* value)
	{
		delete[] name_;
		name_ = new char[strlen(value) + 1];
		strcpy(name_, value);
	}
	void Product::price(double value)
	{
		price_ = value;
	}
	void Product::taxed(bool value)
	{
		taxed_ = value;
	}
	void Product::quantity(int value)
	{
		quantity_ = value;
	}
	void Product::qtyNeeded(int value)
	{
		qtyNeeded_ = value;
	}

	// getters
	char* Product::sku() const
	{
		char* s;
		s = new char[strlen(sku_) + 1];
		strcpy(s, sku_);
		return s;
	}
	char* Product::name() const
	{
		return name_;
	}
	double Product::price() const
	{
		return price_;
	}
	bool Product::taxed() const
	{
		return taxed_;
	}
	int Product::quantity() const
	{
		return quantity_;
	}
	int Product::qtyNeeded() const
	{
		return qtyNeeded_;
	}
	double Product::cost() const
	{
		return taxed_ ? price_ * (1 + TAX) : price_;
	}
	bool Product::isEmpty() const
	{
		return sku_[0] == '\0';
	}

	// operator overloads
	bool Product::operator==(const char* c)	
	{
		return !strcmp(sku_, c);
	}
	int Product::operator+=(int i)
	{
		return quantity_ += i;
	}
	int Product::operator-=(int i)
	{
		return quantity_ -= i;
	}

	// non member
	double operator+=(double d, const Product& p)
	{
		return p.cost() * p.quantity() + d;
	}
	std::istream& operator>>(std::istream& is, Product& p)
	{
		return p.read(is);
	}
	std::ostream& operator<<(std::ostream& os, const Product& p)
	{
		return p.write(os, true);
	}
}