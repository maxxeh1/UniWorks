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
        float move_prob = 0, fight_prob = 0, reproduce_prob = 0;
        

    public:
        /**
         * Default constructor
         */
        Animal();
           
        //~Animal();
        
        /**
         * Sets dead boolean
         * @param is_dead
         */
        void set_dead(bool is_dead);
        
        /**
         * Returns dead boolean
         * @return boolean dead
         */
        bool get_dead();
        
        /**
         * Sets reproduce boolean
         * @param will_reproduce
         */
        void set_reproduce(bool will_reproduce);
        
        /**
         * Returns reproduce boolean
         * @return boolean reproduce
         */
        bool get_reproduce();
        
        /**
         * Sets height of animal
         * @param int height
         */
        void set_height(int height);

        /**
         * Sets width of animal
         * @param int width
         */
        void set_width(int width);
        
        /**
         * Returns height of animal
         * @return int position
         */
        int get_height();

        /**
         * Returns width of animal
         * @return int position
         */
        int get_width();
        
        /**
         * Set life of animal
         * @param life_span
         */
        void set_life(int life_span);
        
        /**
         * Returns life of animal
         * @return int life
         */
        int get_life();
        
        /**
         * Sets move probability of animal
         * @param float prob
         */
        void set_move_prob(float prob);
        
        /**
         * Returns move probability of animal
         * @return float moveProb
         */
        float get_move_prob();
         
        /**
         * Returns position of animal
         * Used for debugging at the moment
         * @return pair position
         */
        pair<int, int> get_position();
        
        /**
         * Sets fight probability of animal
         * @param float prob
         */
        void set_fight_prob(float prob);
        
        /**
         * Returns fight probability of animal
         * @return float fightProb
         */
        float get_fight_prob();
        
        /**
         * Sets reproduce probability of animal
         * @param float prob
         */
        void set_reproduce_prob(float prob);
        
        /**
         * Returns reproduce probability of animal
         * @return float reproduceProb
         */
        float get_reproduce_prob();
        
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
         * generated float, and tells the program whether to go ahead with 
         * functionality eg. Moving, Killing, Reproducing etc.
         * @param float prob_to_check
         * @return bool will_do
         */
        bool check_probability(float prob_to_check);
        
        /**
         * Visitor pattern function. Defines this function for children.
         * Over-ridden by children
         * @param AnimalVisitor animal
         */
        virtual void visit_with(AnimalVisitor &animal) = 0;
};

class Aphid : public Animal//, public AnimalInteractor
{
    //Global variables
    protected:
        int direction;
        float group_kill_prob;

    //Constructor
    public:
        Aphid();
        
        ~Aphid();
        
        Aphid(int position1, int position2);

        Aphid(int position1, int position2, float mvProb, float reProb, 
        float killProb, float gKillProb);
        
        void set_group_kill_prob(float prob);
       
        float get_group_kill_prob();

        bool update(int grid_height, int grid_width);
        
        void visit_with(AnimalVisitor &animal);
        
        bool visit(Aphid &animal);
        
        bool visit(Ladybug &animal);

};

class Ladybug : public Animal//, public AnimalInteractor
{
    protected:
        LadyDirection direction;
        int subdirection;
        float dir_change_prob = 0;
        
    public:
            Ladybug();
            
            ~Ladybug();
            
            Ladybug(int position1, int position2);

            Ladybug(int position1, int position2, float mvProb, float reProb, 
        float killProb, float dChangeProb);
            
            void setDirection(int nSteps);
            
            void setDirChangeProb(float prob);
            
            float getDirChangeProb();
            
            void visit_with(AnimalVisitor &animal);
        
            bool visit(Aphid &animal);
        
            bool visit(Ladybug &animal);
            
            bool update(int grid_height, int grid_width);
};





#endif
