#ifndef ANIMAL_H
#define ANIMAL_H
#include <utility>
#include "AnimalInteractor.h"
using namespace std;

//Define an enumerator for choosing directions to go in
enum LadyDirection
{
    North,
    East,
    South,
    West,
    NUM_DIRECTIONS //Count of how many directions are held
};

//Animal class inherits from a visitor pattern class
class Animal: public AnimalVisitor 
{
    //Define protected variables
    protected:
        int position[2];
        signed int life = 0;
        bool dead = false, reproducing = false;
        float moveProb = 0, fightProb = 0, reproduceProb = 0;
        

    public:
        /**
         * Default constructor
         */
        Animal();
           
        //~Animal();
        
        /**
         * Sets dead boolean
         * @param isDead
         */
        void setDead(bool isDead);
        
        /**
         * Returns dead boolean
         * @return boolean dead
         */
        bool getDead();
        
        /**
         * Sets reproduce boolean
         * @param hasBaby
         */
        void setReproduce(bool hasBaby);
        
        /**
         * Returns reproduce boolean
         * @return boolean reproduce
         */
        bool getReproduce();
        
        /**
         * Sets height of animal
         * @param int height
         */
        void setHeight(int height);

        /**
         * Sets width of animal
         * @param int width
         */
        void setWidth(int width);
        
        /**
         * Returns height of animal
         * @return int position
         */
        int getHeight();

        /**
         * Returns width of animal
         * @return int position
         */
        int getWidth();
        
        /**
         * Set life of animal
         * @param tempLife
         */
        void setLife(int tempLife);
        
        /**
         * Returns life of animal
         * @return int life
         */
        int getLife();
        
        /**
         * Sets move probability of animal
         * @param float prob
         */
        void setMoveProb(float prob);
        
        /**
         * Returns move probability of animal
         * @return float moveProb
         */
        float getMoveProb();
         
        /**
         * Returns position of animal
         * Used for debugging at the moment
         * @return pair position
         */
        pair<int, int> getPosition();
        
        /**
         * Sets fight probability of animal
         * @param float prob
         */
        void setFightProb(float prob);
        
        /**
         * Returns fight probability of animal
         * @return float fightProb
         */
        float getFightProb();
        
        /**
         * Sets reproduce probability of animal
         * @param float prob
         */
        void setReproduceProb(float prob);
        
        /**
         * Returns reproduce probability of animal
         * @return float reproduceProb
         */
        float getReproduceProb();
        
        /**
         * Updates an animal's positions based on grid size 
         * Not used, just over-ridden by children
         * @param int grid_height
         * @param int grid_width
         * @return bool hasMoved
         */
        virtual bool update(int grid_height, int grid_width);
        
        /**
         * Checks the probability of any probability variable against a randomly 
         * generated float, and tells the program whether to go ahead with functionality
         * eg. Moving, Killing, Reproducing etc.
         * @param float probToCheck
         * @return bool willDo
         */
        bool checkProbability(float probToCheck);
        
        /**
         * Visitor pattern function. Defines this function for children.
         * Over-ridden by children
         * @param AnimalVisitor animal
         */
        virtual void visitWith(AnimalVisitor &animal) = 0;
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
        
        void visitWith(AnimalVisitor &animal);
        
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
            
            void visitWith(AnimalVisitor &animal);
        
            bool visit(Aphid &animal);
        
            bool visit(Ladybug &animal);
            
            bool update(int grid_height, int grid_width);
};





#endif
