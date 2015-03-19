#include <vector>
#include <iostream>
#include <stdlib.h>
#include "Manager.h"
#include "Grid.h"
using namespace std;

/**
 * Manager constructor, assigns vectors to the manager
 * @param new_aphids
 * @param new_ladys
 */
Manager::Manager(vector<Aphid> new_aphids, vector<Ladybug> new_ladys) 
{
    current_aphids = new_aphids;
    current_ladys = new_ladys;
}

/**
 * Sets up the grid with inputted values
 * @param grid_height
 * @param grid_width
 */
void Manager::setup_grid(int grid_height, int grid_width) 
{
    current_grid.set_height(grid_height);
    current_grid.set_width(grid_width);
    current_grid.draw_grid(current_aphids, current_ladys);
}

/**
 * Resets the vector which holds all the animals, and fills it with updated 
 * vectors at any point in the simulation. Ensures no dangling pointers to 
 * deleted objects
 */
void Manager::set_vectors() 
{
    this->all_animals.clear();
    this->current_aphids.shrink_to_fit();
    this->current_ladys.shrink_to_fit();
    //Loop through vector of aphids
    for (vector<Aphid>::iterator it_a = this->current_aphids.begin();
            it_a != this->current_aphids.end(); ++it_a) 
    {
        //Push aphids to vector of aphids and ladybugs
        all_animals.push_back(&(*it_a));
    }
    //Loop through vector of ladybugs
    for (vector<Ladybug>::iterator it_l = this->current_ladys.begin();
            it_l != this->current_ladys.end(); ++it_l) 
    {
        //Push ladybugs to vector of aphids and ladybugs
        all_animals.push_back(&(*it_l));
    }
    this->all_animals.shrink_to_fit();
}

/**
 * This function is the core of the program. It loops through vectors of aphids
 * and ladybugs, and updates them in turn based on their probability. If an 
 * aphid and a ladybug meet in one cell, there's a chance for them to fight. 
 * If two of the same kind meet in one cell, there's a chance for them to 
 * reproduce. This functions ties in functionality from all sections of the code
 * to make the program do what it is supposed to do.
 */
void Manager::update_all() 
{
    //Loop through vector of animals
    for (vector<Animal*>::iterator it_all = all_animals.begin();
            it_all != all_animals.end(); ++it_all) 
    {
        //Check life of aphid or ladybug
        if ((*it_all)->get_life() <= 0) 
        {
            //If aphid or ladybug is dead, mark it for death
            (*it_all)->set_dead(true);
        }            //If aphid or ladybug still has life
        else {
            //Update aphid or ladybug position on grid
            if ((*it_all)->update(current_grid.get_height(),
                    current_grid.get_width())) 
            {
                //Loop through vector of animals again
                for (vector<Animal*>::iterator it_check = all_animals.begin();
                        it_check != all_animals.end(); ++it_check) 
                {
                    //Don't compare to self
                    if (*it_all != *it_check) {
                        //If two animals are in the same cell
                        if (check_same_cell(**it_all, **it_check)) 
                        {
                            /***************DEBUGGING COUTS********************/
                            //cout << "Two in same position" << endl;
                            //Draw the grid to show them in same cell
                            //this->currentGrid.drawGrid(this->currentAphids, 
                            //        this->currentLadys);
                            /**************************************************/
                            /**
                             * Use visitor pattern to call correct function
                             * polymorphically. This marks an aphid or ladybug
                             * for death or reproduction
                             */
                            (*it_all)->visit_with(**it_check);
                            //cin.get(); //For debugging each update
                        }
                    }
                }
            } else //For debugging, or future extensions
            {
                //cout << "Did not move";
            }
        }
    }

    //Loop through current_aphids vector
    vector<Aphid>::iterator it_a = current_aphids.begin();
    while (it_a != current_aphids.end()) 
    {
        //If an aphid is marked for death
        if (it_a->get_dead()) 
        {
            //Delete and destruct aphid
            it_a = current_aphids.erase(it_a);
        }            //Or increment iterator
        else 
        {
            ++it_a;
        }
    }
    //Reset iterator
    it_a = current_aphids.begin();
    //Loop through currentAphids again
    while (it_a != current_aphids.end()) 
    {
        //If an aphid is marked for reproduction
        if (it_a->get_reproduce()) 
        {
            //Create a new aphid object at the end of the vector with same 
            //variables as parent
            current_aphids.emplace_back(it_a->get_height(), it_a->get_width(),
                    it_a->get_move_prob(), it_a->get_reproduce_prob(),
                    it_a->get_fight_prob(), it_a->get_group_kill_prob());
            //Reset reproduce marker 
            it_a->set_reproduce(false);
            //Reset iterator
            it_a = current_aphids.begin();
        }
        //Increment iterator
        ++it_a;
    }

    //Loop through currentLadys vector
    vector<Ladybug>::iterator it_l = current_ladys.begin();
    while (it_l != current_ladys.end()) 
    {
        //If a ladybug is marked for death
        if (it_l->get_dead()) 
        {
            //Delete and destruct ladybug
            it_l = current_ladys.erase(it_l);
        }            
        //Or increment iterator
        else 
        {
            ++it_l;
        }
    }
    //Reset iterator
    it_l = current_ladys.begin();
    //Loop through currentLadys again
    while (it_l != current_ladys.end()) 
    {
        //If a ladybug is marked for reproduction
        if (it_l->get_reproduce()) 
        {
            //Create a new ladybug object at the end of the vector with same 
            //variables as parent
            current_ladys.emplace_back(it_l->get_height(), it_l->get_width(), 
                    it_l->get_move_prob(), it_l->get_reproduce_prob(), 
                    it_l->get_fight_prob(), it_l->get_dir_change_prob());
            //Reset reproduce marker
            it_l->set_reproduce(false);
            //Reset iterator
            it_l = current_ladys.begin();
        }
        //Increment iterator
        ++it_l;
    }

    //Update allAnimals vector with updated positions and animals
    set_vectors();

    /*******ENABLE THIS IF YOU WANT STATISTICS FOR EACH OBJECT*****************/
    /*****************BAD FOR LONG SIMULATIONS*********************************/
    /*for (vector<Animal*>::iterator a = this->allAnimals.begin();
        a != this->allAnimals.end(); ++a)
    {
        if(!(**a).getDead())
        {
            cout << endl << "Width: " << (*a)->getWidth() << "Height: " 
                    << (*a)->getHeight() << "Life: " << (*a)->getLife() << endl;
        }
    }*/

    //Print out remaining ladybugs and aphids
    cout << "Aphids: " << current_aphids.size() << endl << "Ladybugs: "
            << current_ladys.size();
    //Print out turn number
    cout << endl << "Turn: " << turn++ << endl;
    //Draw grid with all updated data
    this->current_grid.draw_grid(this->current_aphids, this->current_ladys);
}

/**
 * Checks if an animal is in the same cell as another animal
 * @param moved_animal
 * @param current_animal
 * @return boolean is_same
 */
bool Manager::check_same_cell(Animal &moved_animal, Animal &current_animal) 
{
    //If the getHeight() and getWidth() functions return the same values, they 
    //are in the same cell
    if (moved_animal.get_height() == current_animal.get_height()
            && moved_animal.get_width() == current_animal.get_width()) 
    {
        return true;
    } 
    else 
    {
        return false;
    }
}

/*void Manager::kill_animal(vector<Animal> these_animals,
        vector <Animal*> marked_animals) 
 * {
    for (vector<Animal*>::iterator itA = this->marked_animals.begin();
            itA != this->marked_animals.end(); ++itA) 
 * {
        //Loop through vector of alive aphids
        for (vector<Animal>::iterator itAlive = this->these_animals.begin();
                itAlive != this->these_animals.end(); ++itAlive) 
 *      {
            //If an aphid exists in deadAphids that exists in currentAphids, 
            //remove the aphid from currentAphids
            if (&(*itAlive) == *itA) 
 *          {
                itAlive = these_animals.erase(itAlive);
                break;
            }
        }
    }
    //Clear the deadAphids vector for the next turn
    this->dead_animals.clear();
}*/

/**
 * This function marks a specific animal for death.
 * Not used in the program, but can be used for debugging
 * @param animal_to_kill
 */
void Manager::mark_death(Animal &animal_to_kill) 
{
    animal_to_kill.set_dead(true);
}

/**
 * This function marks a specific animal for reproduction.
 * Not used in the program, but can be used for debugging
 * @param animal_to_reproduce
 */
void Manager::mark_reproduce(Animal &animal_to_reproduce) 
{
    animal_to_reproduce.set_reproduce(true);
}

/**
 * Returns the size of the ladybug vector
 * @return int ladybug_count
 */
int Manager::get_ladybug_count()
{
    return this->current_ladys.size();
}

/**
 * Returns the size of the aphid vector
 * @return int aphid_count
 */
int Manager::get_aphid_count()
{
    return this->current_aphids.size();
}
