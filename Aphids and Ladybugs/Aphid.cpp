#include "Animal.cpp"

class Aphid : public Animal
{
	//Global variables
	int position[2];

	//Constructor
	public:
		Aphid(int position1, int position2)
		{
			position[0] = position1;
			position[1] = position2;
		}

};
