#ifndef ANIMAL_H
#define ANIMAL_H
#include <utility>
using namespace std;

enum LadyDirection
{
    North,
    East,
    South,
    West,
    NUM_DIRECTIONS
};

class Animal
{
    protected:
        int position[2];
        signed int life;

    public:
        Animal();
           
        //~Animal();
        
        void setHeight(int height);


        void setWidth(int width);


        int getHeight();


        int getWidth();

        pair<int, int> getPosition();
        
        void setLife(int tempLife);
        
        int getLife();

        virtual void update();

};

class Aphid : public Animal
{
    //Global variables
    protected:
        int direction;

    //Constructor
    public:
        Aphid();
        
        ~Aphid();

        Aphid(int position1, int position2);

        void update(int grid_height, int grid_width);

};

class Ladybug : public Animal
{
    protected:
        LadyDirection direction;
        int subdirection;
        
    public:
            Ladybug();
            
            ~Ladybug();

            Ladybug(int position1, int position2);
            
            void setDirection(int nSteps);
            
            void update();
};





#endif
