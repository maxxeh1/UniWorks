#ifndef ANIMAL_H
#define ANIMAL_H
#include <utility>
#include "AnimalVisitor.h"
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
    //Protected variables
    protected:
        int direction;
        float group_kill_prob;

    public:
        //Default constructor
        Aphid();
        
        //Destructor
        ~Aphid();
        
        /**
         * Constructor to just set positions of an aphid
         * @param int position1
         * @param int position2
         */
        Aphid(int position1, int position2);

        /**
         * Second constructor that takes probabilities as well as positions
         * @param int position1
         * @param int position2
         * @param float mv_prob
         * @param float re_prob
         * @param float kill_prob
         * @param float g_kill_prob
         */
        Aphid(int position1, int position2, float mvProb, float reProb, 
        float killProb, float gKillProb);
        
        /**
         * Sets aphid's group kill probability
         * @param float prob
         */
        void set_group_kill_prob(float prob);
       
        /**
         * Returns aphid's group kill probability
         * @return float group_kill_prob
         */
        float get_group_kill_prob();

        /**
         * Checks if aphid will move, then decides a direction. Then increments 
         * the position of the aphid in chosen direction. Also checks if aphid will go
         * out of bounds, and change the direction. At the end, decrements the aphid's
         * life
         * @param grid_height
         * @param grid_width
         * @return boolean moved
         */
        bool update(int grid_height, int grid_width);
        
        /**
         * Visitor pattern function. Decides which visit() function to call 
         * @param AnimalVisitor animal
         */
        void visit_with(AnimalVisitor &animal);
        
        /**
         * Visitor pattern function. Chosen polymorphically. Checks if an aphid 
         * will be marked for reproduction
         * @param AnimalVisitor animal
         * @return boolean will_reproduce
         */
        bool visit(Aphid &animal);
        
        /**
         * Visitor pattern function. Chosen polymorphically. Checks if an aphid 
         * will fight a ladybug
         * @param AnimalVisitor animal
         * @return boolean will_fight
         */
        bool visit(Ladybug &animal);

};

class Ladybug : public Animal//, public AnimalInteractor
{
    //Protected variables
    protected:
        LadyDirection direction;
        int subdirection;
        float dir_change_prob = 0;
        
    public:
        //Default constructor
        Ladybug();

        //Destructor
        ~Ladybug();
            
        /**
         * Constructor to just set positions of an ladybug
         * @param int position1
         * @param int position2
         */
        Ladybug(int position1, int position2);

        /**
         * Second constructor that takes probabilities as well as positions
         * @param int position1
         * @param int position2
         * @param float mv_prob
         * @param float re_prob
         * @param float kill_prob
         * @param float d_change_prob
         */
        Ladybug(int position1, int position2, float mv_prob, float re_prob, 
                    float kill_prob, float d_change_prob);

        /**
         * Sets the preferred direction for the ladybug
         * @param int nSteps
         */
        void set_direction(int nSteps);

        /**
         * Sets the probability to change preferred direction
         * @param float prob
         */
        void set_dir_change_prob(float prob);

        /**
         * Returns the probability to change preferred direction
         * @return float dir_change_prob
         */
        float get_dir_change_prob();

        /**
         * Visitor pattern function. Decides which visit() function to call 
         * @param AnimalVisitor animal
         */
        void visit_with(AnimalVisitor &animal);

        /**
         * Visitor pattern function. Chosen polymorphically. Checks if a ladybug
         * will fight an aphid
         * @param AnimalVisitor animal
         * @return boolean will_fight
         */
        bool visit(Aphid &animal);

        /**
         * Visitor pattern function. Chosen polymorphically. Checks if a ladybug
         * will be marked for reproduction
         * @param AnimalVisitor animal
         * @return boolean will_reproduce
         */
        bool visit(Ladybug &animal);

        /**
         * Updates a ladybug based on their preferred direction. First checks if the 
         * ladybug will move. Then checks if the ladybug will change their preferred
         * direction. Then chooses a new direction, NOT the original one. Performs 
         * constant checks for if the ladybug will go out bounds before incrementing.
         * Then reduces the ladybug's life.
         * @param int grid_height
         * @param int grid_width
         * @return boolean moved
         */
        bool update(int grid_height, int grid_width);
};





#endif
