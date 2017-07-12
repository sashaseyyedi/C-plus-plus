#include <iomanip>
#include <iostream>
#include "EAN.h"



class Order
{
	EAN orderedEAN; 
	int ordered;
	int delivered;

public:

	Order();
	Order(const EAN& ean);
	EAN& getEAN();
	int outstanding() const;
	bool add(std::istream& is);
	bool add(int n);
	bool receive(std::istream& is);
	void display(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const Order& order);