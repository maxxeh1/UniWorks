#ifndef ANIMAL_H
#define ANIMAL_H
#include <utility>
#include "AnimalInteractor.h"
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
        float moveProb = 0, fightProb = 0, reproduceProb = 0;
        

    public:
        Animal();
           
        //~Animal();
        
        void setHeight(int height);

        void setWidth(int width);
        
        void setMoveProb(float prob);
        
        int getHeight();

        int getWidth();
        
        float getMoveProb();
        
        pair<int, int> getPosition();
        
        
        void setLife(int tempLife);
        
        int getLife();

        virtual bool update(int grid_height, int grid_width);
        
        bool checkProbability(float probToCheck);
        
        virtual void interactWith(AnimalInteractor &animal) = 0;
};

class Aphid : public Animal, public AnimalInteractor
{
    //Global variables
    protected:
        int direction;

    //Constructor
    public:
        Aphid();
        
        ~Aphid();

        Aphid(int position1, int position2);

        bool update(int grid_height, int grid_width);
        
        void interactWith(AnimalInteractor &animal);
        
        void interact(Aphid &animal);
        
        void interact(Ladybug &animal);

};

class Ladybug : public Animal
{
    protected:
        LadyDirection direction;
        int subdirection;
        float dirChangeProb = 0;
        
    public:
            Ladybug();
            
            ~Ladybug();

            Ladybug(int position1, int position2);
            
            void setDirection(int nSteps);
            
            void setDirChangeProb(float prob);
            
            float getDirChangeProb();
            
            void interactWith(AnimalInteractor &animal);
        
            void interact(Aphid &animal);
        
            void interact(Ladybug &animal);
            
            bool update(int grid_height, int grid_width);
};





#endif
