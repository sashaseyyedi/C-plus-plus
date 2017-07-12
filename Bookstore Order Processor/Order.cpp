#include "Order.h"

Order::Order()
{
	orderedEAN = EAN();
	ordered = 0;
	delivered = 0;
}

Order::Order(const EAN& ean)
{
	if(ean.empty() == false)
	{
		orderedEAN = ean;
		ordered = 0;
		delivered = 0;
	}
	else
	{
		*this = Order();
	}
}

EAN& Order::getEAN()
{
	return orderedEAN;
}

int Order::outstanding() const
{
	return ordered - delivered;
}

bool Order::add(std::istream& is)
{
	int n = -1;
	bool valid = false;

	while(valid == false && orderedEAN.empty() == false && n != 0)
	{
		std::cout << "Quantity (0 to quit) : ";
		is >> n;
		if(n > 0)
		{
			ordered = ordered + n;
			valid = true;
		}
		if(n < 0)
		{
			std::cout << "Enter a positive number.  Try again." << std::endl;
		}
	}

	if(n == 0)
	{
		std::cout << "**No delivery Recorded" << std::endl;
	}
	
	return valid;
}

bool Order::add(int n)
{
	bool tf = false;

	if(n > 0 && orderedEAN.empty() == false)
	{
		ordered = ordered + n;
		tf = true;
	}

	return tf;
}

bool Order::receive(std::istream& is)
{
	int n = -1;
	bool valid = false;
	
	
	while(valid == false && orderedEAN.empty() == false && n != 0)
	{
		std::cout << "Quantity (0 to quit) : ";
		is >> n;
		if(ordered < delivered + n)
		{
			std::cout << n << " not on order. " <<  "Only "  << ordered - delivered << " are on order.  Try again." << std::endl;
		}
		if(n > 0 && ordered  >= delivered + n)
		{
			delivered = delivered + n;
			valid = true;
		}

		if(n < 0)
		{
			std::cout << "Enter a positive number.  Try again." << std::endl;
		}
	}
	
	if(n == 0)
	{
		std::cout << "**No delivery Recorded" << std::endl;
	}

	return valid;
}

void Order::display(std::ostream& os) const
{
	os << orderedEAN << std::setw(9) << ordered << std::setw(11) << delivered;
}

std::ostream& operator<<(std::ostream& os, const Order& order)
{
	order.display(os);
	return os;
}