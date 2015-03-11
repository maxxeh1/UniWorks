#ifndef ANIMAL_H
#define ANIMAL_H

class Animal
{
	protected:
		int position[2];

	public:
		Animal();

		void setHeight(int height);


		void setWidth(int width);


		int getHeight();


		int getWidth();
                
                int getPosition();

};

class Aphid : public Animal
{
	//Global variables


	//Constructor
	public:
		Aphid();

		Aphid(int position1, int position2);

		void test();

};

class Ladybug : public Animal
{
	public:
		Ladybug();

		Ladybug(int position1, int position2);

};



#endif
