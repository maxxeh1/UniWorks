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

class Animal: public AnimalInteractor
{
    protected:
        int position[2];
        signed int life;
        bool dead = false, reproducing = false;
        float moveProb = 0, fightProb = 0, reproduceProb = 0;
        

    public:
        Animal();
           
        //~Animal();
        
        void setDead(bool isDead);
        
        bool getDead();
        
        void setReproduce(bool hasBaby);
        
        bool getReproduce();
        
        void setHeight(int height);

        void setWidth(int width);
        
        void setMoveProb(float prob);
        
        void setReproduceProb(float prob);
        
        float getReproduceProb();
        
        void setFightProb(float prob);
        
        float getFightProb();
        
        int getHeight();

        int getWidth();
        
        float getMoveProb();
        
        pair<int, int> getPosition();
        
        
        void setLife(int tempLife);
        
        int getLife();

        virtual bool update(int grid_height, int grid_width);
        
        bool checkProbability(float probToCheck);
        
        virtual void visitWith(AnimalInteractor &animal) = 0;
};

class Aphid : public Animal//, public AnimalInteractor
{
    //Global variables
    protected:
        int direction;
        float groupKillProb;

    //Constructor
    public:
        Aphid();
        
        ~Aphid();
        
        Aphid(int position1, int position2);

        Aphid(int position1, int position2, float mvProb, float reProb, 
        float killProb, float gKillProb);
        
        void setGroupKillProb(float prob);
       
        float getGroupKillProb();

        bool update(int grid_height, int grid_width);
        
        void visitWith(AnimalInteractor &animal);
        
        bool visit(Aphid &animal);
        
        bool visit(Ladybug &animal);

};

class Ladybug : public Animal//, public AnimalInteractor
{
    protected:
        LadyDirection direction;
        int subdirection;
        float dirChangeProb = 0;
        
    public:
            Ladybug();
            
            ~Ladybug();
            
            Ladybug(int position1, int position2);

            Ladybug(int position1, int position2, float mvProb, float reProb, 
        float killProb, float dChangeProb);
            
            void setDirection(int nSteps);
            
            void setDirChangeProb(float prob);
            
            float getDirChangeProb();
            
            void visitWith(AnimalInteractor &animal);
        
            bool visit(Aphid &animal);
        
            bool visit(Ladybug &animal);
            
            bool update(int grid_height, int grid_width);
};





#endif
