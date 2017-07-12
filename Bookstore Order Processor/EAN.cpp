#include "EAN.h"
#include "GS1Prefix.h"

bool isValid(const char* str)
{
	bool tf = false;
	int validEAN = 0;

	if(str != NULL)
	{
		int eanLen = strlen(str);

		//checks if the string is equal to 13
		if(eanLen == 13)
		{
			//iterates as long as y does not equal the end of the string
			for(int y = 1; y <= eanLen; y++)
			{
				//multiplies every second digit by 3 then adds it to the total 
				if(y % 2 == 0)
				{
					int i = str[y-1] - '0';
					i = i * 3;
					validEAN = validEAN + i;
				}
				//adds every other digit to total
				else
				{
					int i = str[y-1] - '0';
					validEAN = validEAN + i;
				}
			}

			//if the EAN diveded by 10 doesnt have a remainder function returns true
			if(validEAN % 10 == 0)
			{
				tf = true;
			}
		}
	}
	return tf;
}

EAN::EAN()
{
	ean[0] = '\0';
	area[0] = '\0';
	publisher[0] = '\0';
	title[0] = '\0';
	type = '\0';
	isReg = false;
}

EAN::EAN(const char* str, const Prefix& list)
{

	if(isValid(str))
	{
		
		strcpy(ean, str);
		if(isRegistered(list) == true)
		{
			type = 1;
		}
	}
	else
	{
		*this = EAN();
	}
}

bool EAN::isRegistered(const Prefix& list)
{
	 isReg = false;
	 char pubCheck[8];
	 //checks if the string is valid EAN if not function returns false
     if(isValid(ean) == true)
	 {
		 if(ean != NULL)
		 {
			 // variable declaration
			 int len = strlen(ean);
			 int setEAN[13];
			 int areaCheck = 0;
			 int areaCtr = 1;
			 int pubCtr = 0;
				 
			 bool valid = true;

			 //iterates through each digit of the string
			 int iterator = 3;
			 
			 //sets str into an int to later find area
			 for(int i = 0; i < len; i++)
			 {
			     setEAN[i] = ean[i] - '0';
			 }
			 
			 //checks if ean has a valid prefix
			 if(setEAN[0] == 9 && setEAN [1] == 7 && (setEAN[2] == 8 || setEAN[2] == 9))
			 {
				 areaCheck = setEAN[iterator];
				 //loops until it is no longer valid
				 while(valid == true)
				 {
					 
		
						 //makes sure area is valid
						 if(areaCtr > 5 )
						 {
							 valid = false;
						 }
						 
						 // iterates the area untill a matching area is found
						 if(areaCtr < 6 && list.isRegistered(areaCheck) == false)
						 {
							 iterator++;
							 areaCheck = (areaCheck * 10) + setEAN[iterator];
							 areaCtr++; 
							 
						 }
						 
						 if(list.isRegistered(areaCheck) == true)
						 {
							 //sets the found area into area
							 for(int y = 0; y < areaCtr; y++ )
							 {
								 area[y] = ean[y + 3];
								 area[y + 1] = '\0';
							 }
							 
							 //adds the amount of area digits to iterator
							 
							 iterator = 3 + areaCtr;

							 // sets a temporary publisher and adds digits untill a registered one is found
							 for(int i = 0; i < 7 && list.isRegistered( areaCheck, pubCheck) == false; i++ )
							 {
								 pubCheck[i] = ean[iterator];
								 pubCheck[i + 1] = '\0';
								 iterator++;
								 pubCtr++;
								 
							 }
							 
							 // checks if the area and publisher found in previous steps matches prefix table
							 if(list.isRegistered( areaCheck, pubCheck) == true )
							 {
								 int a = 0;
								 //sets the tamporary publisher into publisher
								 for(int z = 3 + areaCtr; z < iterator; z++ )
								 {		
									 publisher[a] = ean[z];
									 publisher[a+1] = '\0';
									 a++;
								 }
								 
								 int b = 0;
								 //sets remaining digits excluding last digit to title
								 for(int z = 3 + areaCtr + pubCtr; z < 12; z++ )
								 {		
									 title[b] = ean[z];
									 title[b + 1] = '\0'; 
									 b++;
									 isReg = true;
									 //after all digits has been allocated to title exit while loop
									 if(z == 11)
									 {
										iterator = 14;
									 }
								 }
							 } 
							 // makes sure to exit out of loop
							 valid = false;
						 }
						
				 }
			 }
		 }
	 }
	 return isReg;
}

bool EAN::empty() const
{
	bool tf = false;
	if(ean[0] == '\0')
	{
		tf = true;
	}
	return tf;
}

bool EAN::isRegistered() const
{
	return isReg;
}

void EAN::style(char t)
{
	if(t == ' ')
	{
		type = 2;
	}
	else if(t == '-')
	{
		type = 1;
	}
	else
	{
		type = 0;
	}

}

void EAN::toStr(char* str) const
{
	strcpy(str, ean);
}

void EAN::toStrWithStyle(char* str) const
{
	
	if(isRegistered() == true)
	{
		for(int x = 0; x < 3; x++)
		{
			str[x] = ean[x];
		}
		str[3] = '\0';

		if(type == 2)
		{
			strcat(str, " ");
			strcat(str, area);
			strcat(str, " ");
			strcat(str, publisher);
			strcat(str, " ");
			strcat(str, title);
			strcat(str, " ");
			strcat(str, &ean[12]);
			
		}
		if(type == 1)
		{
			strcat(str, "-");
			strcat(str, area);
			strcat(str, "-");
			strcat(str, publisher);
			strcat(str, "-");
			strcat(str, title);
			strcat(str, "-");
			strcat(str, &ean[12]);
			
		}
		if(type == 0)
		{
			strcpy(str, ean);
		}
	}
	else
	{
		toStr(str);
	}
}

void EAN::display(std::ostream& os) const
{
	char str[18];
	toStrWithStyle(str);
	os << std::setw(17) << std::right << str;
}

bool EAN::read(std::istream& is, const Prefix& list)
{
	char tempEAN[14];
	EAN tempObj;
	bool tf = false;

	while(strcmp(tempEAN, "0") != 0)
	{
		std::cout << "EAN (0 to quit) : ";
		is >> tempEAN;
		
		if(strlen(tempEAN) < 13)
		{
			std::cout << "Too few characters. Try again." << std::endl;
		}
		else if(strlen(tempEAN) > 13) 
		{
			std::cout << "Too many characters. Try again" << std::endl;
		}
		else if(isValid(tempEAN) == false)
		{
			std::cout << "invalid check digit" << std::endl;
		}
		else
		{
			tempObj = EAN(tempEAN, list);
			*this = tempObj;
			tf = true;
			strcpy(tempEAN, "0");
		}
	}
	return tf;
}

bool operator==(const EAN& left, const EAN& right)
{
	char strLeft[14];
	char strRight[14];

	left.toStr(strLeft);
	right.toStr(strRight);

	return strcmp(strLeft, strRight) == 0;
}

std::ostream& operator<<(std::ostream& os, const EAN& ean)
{
	ean.display(os);
	return os;
}