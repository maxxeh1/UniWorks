#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Animal.h"
#include "Grid.h"
using namespace std;

//Global variables
string file_name;
ifstream in_file;
int num_aphids = 0, num_ladys = 0, temp_pos1 = 0, temp_pos2 = 0, aphid_pos[2], 
        lady_pos[2],grid_size[2];
float moveProb = 0, killProb = 0, groupKillProb = 0, reproduceProb = 0;


//The main function for the program. This will load config files and run the simulator.
int main()
{
    //Welcome messages in console
    cout << "Welcome to the Aphids and Ladybugs simulator.";
    cout << "Please enter the name of the config files you wish to use: \n";
    //Take user input for file name
    //cin >> file_name;

    //Open the file
    in_file.open("config.txt");
    //Check file was opened correctly
    if (in_file.is_open())
    {
        cout << "File opened\n";
    }
    else
    {
        cout << "File not opened\n";
    }

    //Read first line as grid sizes
    in_file >> grid_size[0]; //Grid height
    in_file >> grid_size[1]; //Grid length

    //Create instance of Grid
    Grid currentGrid(grid_size[0], grid_size[1]);
    currentGrid.createGrid();

    //Read next line as number of aphids
    in_file >> num_aphids;
    vector<Aphid> aphidVector(num_aphids);
    //Loop and grab each aphid position
    for (int i = 0; i < num_aphids; i++)
    {
        in_file >> temp_pos1;
        in_file >> temp_pos2;
        //string temp_name;
        //cout << "Please enter a name for this aphid: ";
        //cin >> temp_name;
        //Aphid temp_aphid(temp_pos1, temp_pos2);
        //aphidMap[temp_name] = temp_aphid;
        aphidVector[i].setHeight(temp_pos1);
        aphidVector[i].setWidth(temp_pos2);
    }
    for (vector<Aphid>::iterator itA = aphidVector.begin();  
                    itA != aphidVector.end(); ++itA)
    {
        cout << (*itA).getPosition();
    }
    //Read next line as number of ladybugs
    in_file >> num_ladys;
    vector<Ladybug> ladyVector(num_ladys);
    //Loop and grab each ladybug position
    for (int i = 0; i < num_ladys; i++)
    {
        in_file >> temp_pos1;
        in_file >> temp_pos2;
        //string temp_name;
        //cout << "Please enter a name for this ladybug: ";
        //cin >> temp_name;
        //Aphid temp_aphid(temp_pos1, temp_pos2);
        //aphidMap[temp_name] = temp_aphid;
        ladyVector[i].setHeight(temp_pos1);
        ladyVector[i].setWidth(temp_pos2);
    }
    //Close current file
    in_file.close();
    //Open aphid config file and assign variables
    in_file.open("aphidConfig.txt");
    in_file >> moveProb;
    in_file >> killProb;
    in_file >> groupKillProb;
    in_file >> reproduceProb;
    cout << moveProb << killProb << groupKillProb << reproduceProb;
    
    //Close current file
    in_file.close();
    
    //Open ladybug config file and assign variables
    in_file.open("ladybugConfig.txt"); 
    in_file >> moveProb;
    in_file >> killProb;
    in_file >> groupKillProb;
    in_file >> reproduceProb;
    cout << moveProb << killProb << groupKillProb << reproduceProb;
    
    //Draw the grid
    currentGrid.drawGrid(aphidVector, ladyVector);

    cin.get();
    //Close the file
    in_file.close();
}
