#include <string>
#include <iostream>
#include "Animal.h"
using namespace std;


//Global variables


//Constructor

	Aphid::Aphid()
	{
		position[0] = 0;
		position[1] = 1;
	}

	Aphid::Aphid(int position1, int position2)
	{
		position[0] = position1;
		position[1] = position2;
	}

	void Aphid::test()
	{
		cout << "Testing Testing";
	}

