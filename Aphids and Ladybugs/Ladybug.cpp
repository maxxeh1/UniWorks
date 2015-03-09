#include "Animal.cpp"
using namespace std;

class Ladybug : public Animal
{
	public:
		Ladybug()
			{
				position[0] = 0;
				position[1] = 1;
			}

		Ladybug(int position1, int position2)
		{
			position[0] = position1;
			position[1] = position2;
		}
	
};

