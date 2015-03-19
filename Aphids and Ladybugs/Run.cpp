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
float aphidMoveProb = 0, aphidKillProb = 0, groupKillProb = 0, 
        aphidReproduceProb = 0, ladyMoveProb = 0, ladyDirectionProb = 0, 
        ladyKillProb = 0, ladyReproduceProb = 0;


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
    vector<Aphid> aphidVector(num_aphids);
    //Loop and grab each aphid position
    for (int i = 0; i < num_aphids; i++)
    {
        in_file >> temp_pos1;
        in_file >> temp_pos2;
        //Set positions of initialised aphids
        aphidVector[i].setHeight(temp_pos1);
        aphidVector[i].setWidth(temp_pos2);
    }

    //Read next line as number of ladybugs
    in_file >> num_ladys;
    vector<Ladybug> ladyVector(num_ladys);
    //Loop and grab each aphid position
    for (int i = 0; i < num_ladys; i++)
    {
        in_file >> temp_pos1;
        in_file >> temp_pos2;
        //Set positions of initialised aphids
        ladyVector[i].setHeight(temp_pos1);
        ladyVector[i].setWidth(temp_pos2);
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
    in_file >> aphidMoveProb;
    in_file >> aphidKillProb;
    in_file >> groupKillProb;
    in_file >> aphidReproduceProb;
    
    //Close current file
    in_file.close();
    
    //Loop through aphid vector and assign object variables
    for (vector<Aphid>::iterator itA = aphidVector.begin();
            itA != aphidVector.end(); ++itA)
    {
        (*itA).setMoveProb(aphidMoveProb);
        (*itA).setGroupKillProb(groupKillProb);
        (*itA).setReproduceProb(aphidReproduceProb);
        (*itA).setFightProb(aphidKillProb);
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
    in_file >> ladyMoveProb;
    in_file >> ladyDirectionProb;
    in_file >> ladyKillProb;
    in_file >> ladyReproduceProb;
    
    //Close the file
    in_file.close();
    
    //Loop through ladybug vector and assign object variables
    for (vector<Ladybug>::iterator itL = ladyVector.begin();  
                itL != ladyVector.end(); ++itL)
    {
        (*itL).setMoveProb(ladyMoveProb);
        (*itL).setDirChangeProb(ladyDirectionProb);
        (*itL).setReproduceProb(ladyReproduceProb);
        (*itL).setFightProb(ladyKillProb);
    }
    
    //Create manager with provided vectors
    Manager currentManager(aphidVector, ladyVector);
    //Set manager vectors up, including a vector to hold all animals
    currentManager.setVectors();
    //Draw the grid for the first time
    currentManager.setupGrid(grid_size[0], grid_size[1]);
    
    //Let the user see the initial grid
    cin.get();
    cin.get();
    
    //Loop through the program forever
    while(true)
    {
        currentManager.updateAll();
        //Pause update for 1000 milliseconds
        this_thread::sleep_for(std::chrono::milliseconds(1000));
    }


}
