#include "Animal.cpp"
#include <string>
#include <iostream>
using namespace std;

class Aphid : public Animal
{
	//Global variables


	//Constructor
	public:
		Aphid()
		{
			position[0] = 0;
			position[1] = 1;
		}

		Aphid(int position1, int position2)
		{
			position[0] = position1;
			position[1] = position2;
		}

		void test()
		{
			cout << "Testing Testing";
		}

};
