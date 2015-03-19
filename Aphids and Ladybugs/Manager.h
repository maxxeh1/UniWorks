#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <memory>
#include "Animal.h"
#include "Grid.h"
using namespace std;

class Manager
{
    //Let animal and children see protected variables
    friend class Animal;
    
    //Initialise protected variables
    protected:
        int turn = 0;
        Grid current_grid;
        vector<Aphid> current_aphids;
        vector<Aphid*> dead_aphids;
        vector<Ladybug> current_ladys;
        vector<Ladybug*> dead_ladys;
        vector<Animal*> all_animals;
        vector<Animal*> dead_animals;
    
    //Define functions to be implemented
    public:
        /**
         * Manager constructor, assigns vectors to the manager
         * @param new_aphids
         * @param new_ladys
         */
        Manager(vector<Aphid> new_aphids, vector<Ladybug> new_ladys);
        
        /**
         * Sets up the grid with inputted values
         * @param grid_height
         * @param grid_width
         */
        void setup_grid(int grid_height, int grid_width);
        
        /**
         * Resets the vector which holds all the animals, and fills it with updated 
         * vectors at any point in the simulation. Ensures no dangling pointers to 
         * deleted objects
         */
        void set_vectors();
        
        /**
         * This function is the core of the program. It loops through vectors 
         * of aphids and ladybugs, and updates them in turn based on their 
         * probability. If an aphid and a ladybug meet in one cell, there's a 
         * chance for them to fight. If two of the same kind meet in one cell, 
         * there's a chance for them to reproduce. This functions ties in 
         * Functionality from all sections of the code to make the program do 
         * what it is supposed to do.
         */
        void update_all();
        
        /**
         * Checks if an animal is in the same cell as another animal
         * @param moved_animal
         * @param current_animal
         * @return boolean
         */
        bool check_same_cell(Animal &moved_animal, Animal &current_animal);
        
        void kill_animal(vector<Animal> these_animals, 
            vector <Animal*> marked_animals);
        
        /**
         * This function marks a specific animal for death.
         * Not used in the program, but can be used for debugging
         * @param animal_to_kill
         */
        void mark_death(Animal &animal_to_kill);
        
        /**
         * This function marks a specific animal for reproduction.
         * Not used in the program, but can be used for debugging
         * @param animal_to_reproduce
         */
        void mark_reproduce(Animal &animal_to_reproduce);
        
        /**
         * Returns the size of the ladybug vector
         * @return int ladybug_count
         */
        int get_ladybug_count();
        
        /**
         * Returns the size of the aphid vector
         * @return int aphid_count
         */
        int get_aphid_count();

};

#endif