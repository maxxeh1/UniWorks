#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <chrono>
#include <thread>
#include <time.h>
#include <stdlib.h>
#include "Animal.h"
#include "Grid.h"
#include "Manager.h"
using namespace std;

//Global variables -- preparation for variables to be loaded
string file_name;
ifstream in_file;

int num_aphids = 0, num_ladys = 0, temp_pos1 = 0, temp_pos2 = 0, aphid_pos[2], 
        lady_pos[2],grid_size[2];
float aphid_move_prob = 0, aphid_kill_prob = 0, group_kill_prob = 0, 
        aphid_reproduce_prob = 0, lady_move_prob = 0, lady_direction_prob = 0, 
        lady_kill_prob = 0, lady_reproduce_prob = 0;


/**
 * This is the main function. This is where the program starts and ends.
 * The primary purpose of this function is to initialise, load and setup 
 * everything in the program
 * @return 0 -- Close the program
 */
int main()
{
    //Generate a new seed for rand()
    srand(time(0));
    
    //Welcome messages in console
    cout << "Welcome to the Aphids and Ladybugs simulator.";
    cout << "Please enter the name of the main config file you wish to use (Eg."
            "config.txt) : " << endl;
    //Take user input for file name
    cin >> file_name;

    //Open the file
    in_file.open(file_name);
    //Check file was opened correctly
    if (in_file.is_open())
    {
        cout << "File opened" << endl;
    }
    else
    {
        cout << "File not opened" << endl;
    }

    //Read first line as grid sizes
    in_file >> grid_size[0]; //Grid height
    in_file >> grid_size[1]; //Grid length

    //Read next line as number of aphids
    in_file >> num_aphids;
    vector<Aphid> aphid_vector(num_aphids);
    //Loop and grab each aphid position
    for (int i = 0; i < num_aphids; i++)
    {
        in_file >> temp_pos1;
        in_file >> temp_pos2;
        //Set positions of initialised aphids
        aphid_vector[i].set_height(temp_pos1);
        aphid_vector[i].set_width(temp_pos2);
    }

    //Read next line as number of ladybugs
    in_file >> num_ladys;
    vector<Ladybug> lady_vector(num_ladys);
    //Loop and grab each aphid position
    for (int i = 0; i < num_ladys; i++)
    {
        in_file >> temp_pos1;
        in_file >> temp_pos2;
        //Set positions of initialised aphids
        lady_vector[i].set_height(temp_pos1);
        lady_vector[i].set_width(temp_pos2);
    }
    
    //Close current file
    in_file.close();
    //Open aphid config file and assign variables
        cout << "Please enter the name of the aphid config file you wish to use"
                " (Eg.aphidConfig.txt) : " << endl;
    //Take user input for file name
    cin >> file_name;

    //Open the file
    in_file.open(file_name);
    //Check file was opened correctly
    if (in_file.is_open())
    {
        cout << "File opened" << endl;
    }
    else
    {
        cout << "File not opened" << endl;
    }
    //Assign variables with loaded values
    in_file >> aphid_move_prob;
    in_file >> aphid_kill_prob;
    in_file >> group_kill_prob;
    in_file >> aphid_reproduce_prob;
    
    //Close current file
    in_file.close();
    
    //Loop through aphid vector and assign object variables
    for (vector<Aphid>::iterator itA = aphid_vector.begin();
            itA != aphid_vector.end(); ++itA)
    {
        (*itA).set_move_prob(aphid_move_prob);
        (*itA).set_group_kill_prob(group_kill_prob);
        (*itA).set_reproduce_prob(aphid_reproduce_prob);
        (*itA).set_fight_prob(aphid_kill_prob);
    }
    
    //Open ladybug config file and assign variables
    cout << "Please enter the name of the aphid config file you wish to use "
            "(Eg.ladybugConfig.txt) : " << endl;
    //Take user input for file name
    cin >> file_name;

    //Open the file
    in_file.open(file_name);
    //Check file was opened correctly
    if (in_file.is_open())
    {
        cout << "File opened" << endl;
    }
    else
    {
        cout << "File not opened" << endl;
    }

    //Assign variables with loaded values
    in_file >> lady_move_prob;
    in_file >> lady_direction_prob;
    in_file >> lady_kill_prob;
    in_file >> lady_reproduce_prob;
    
    //Close the file
    in_file.close();
    
    //Loop through ladybug vector and assign object variables
    for (vector<Ladybug>::iterator itL = lady_vector.begin();  
                itL != lady_vector.end(); ++itL)
    {
        (*itL).set_move_prob(lady_move_prob);
        (*itL).setDirChangeProb(lady_direction_prob);
        (*itL).set_reproduce_prob(lady_reproduce_prob);
        (*itL).set_fight_prob(lady_kill_prob);
    }
    
    //Create manager with provided vectors
    Manager current_manager(aphid_vector, lady_vector);
    //Set manager vectors up, including a vector to hold all animals
    current_manager.set_vectors();
    //Draw the grid for the first time
    current_manager.setup_grid(grid_size[0], grid_size[1]);
    
    //Let the user see the initial grid
    cin.get();
    cin.get();
    
    //Loop through the program forever
    while(true)
    {
        current_manager.update_all();
        if(current_manager.get_aphid_count() == 0)
        {
            cout << "Aphids have been wiped out. Ladybugs rule the world.";
            break;
        }
        else if(current_manager.get_ladybug_count() == 0)
        {
            cout << "Ladybugs have been wiped out. Aphids rule the world.";
            break;
        }
        //Pause update for 1000 milliseconds
        this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
