#ifndef ANIMAL_H
#define ANIMAL_H
#include <utility>
using namespace std;

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

        pair<int, int> getPosition();

        void update();

};

class Aphid : public Animal
{
    //Global variables
    protected:
        int direction;

    //Constructor
    public:
        Aphid();

        Aphid(int position1, int position2);

        void update();

};

class Ladybug : public Animal
{
    protected:
        char direction;
        int subdirection;
        
    public:
            Ladybug();

            Ladybug(int position1, int position2);
            
            void setDirection(char temp_direction);
            
            void update();
};



#endif
