#include"GS1Prefix.h"

Prefix::Prefix(const char* f)
{
     if (f != nullptr) 
	 {
         std::ifstream file(f);
         if (file.is_open()) 
		 {
             int ctr = 0;
             while (file.good()) 
			 {  // version 1.2
                 file >> area[ctr] >> pubLow[ctr] >> pubHgh[ctr]; 
                 if (file.good()) {
                     pubLen[ctr] = std::strlen(pubLow[ctr]);
                     ctr++;
                 }
             }
             if (ctr > 0) {
                 no = ctr;
             }
         }
     }
}

bool Prefix::isRegistered(int a) const
 {
	 bool tf = false;
	 
	 //goes through prefix to find matching area
	 for(int x = 0; x < no; x++)
	 {
		if(area[x] == a)
		{
			tf = true;
			x = no;
		}
	 }
	 return tf;
 }


int Prefix::minNoDigits(int a) const
{
	int digits = 0;
	 
	 //goes through prefix to find matching area
	 for(int x = 0; x < no; x++)
	 {
		if(area[x] == a )
		{
			//sets a variable to the lowest amount of publisher digits within that area
			digits = pubLen[x];
			x = no;
		}
		
	 }
	 return digits;
}

bool Prefix::isRegistered(int a, const char* p) const
 {
	 bool tf = false;
	 
	 //goes through prefix to find matching area
	 for(int x = 0; x < no; x++)
	 {
		if(area[x] == a)
		{
			//if a matching area is found and the amount of digits in publisher = publen 
			if(strlen(p) == pubLen[x])
			{
				//set the minumum publisher range and highes publisher range for that area to an int
				//also sets publisher to an int
				int low = atoi(pubLow[x]);
				int high = atoi(pubHgh[x]);
				int pub = atoi(p);

				//checks if publisher is in the area publisher range
				if(pub >= low && pub <= high)
				{
					tf = true;
					// once tf is true break out of loop 
					x = no;
				}
			}
		}
	 }
	 return tf;
 }
