#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <iostream>


class Prefix;

class EAN
{
	char ean[14];
	char area[6];
	char publisher[8];
	char title[7];
	int type;
	bool isReg;
	bool isRegistered(const Prefix& list);
	

public:
	
	EAN();
	EAN(const char* str, const Prefix& list);
	bool empty() const;
	bool isRegistered() const;
	void style(char t);
	void toStr(char* str) const;
	void toStrWithStyle(char* str) const;
	void display(std::ostream& os) const;
	bool read(std::istream& is, const Prefix& list);
};

bool isValid(const char* str);
bool operator==(const EAN& left, const EAN& right);
std::ostream& operator<<(std::ostream& os, const EAN& ean);