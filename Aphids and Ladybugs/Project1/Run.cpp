#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Global variables
string file_name;
ifstream in_file;
int grid_size[2];
int num_aphids;
int num_ladys;
int aphid_pos[2];
int lady_pos[2];

//The main function for the program. This will load config files and run the simulator.
int main()
{
	//Welcome messages in console
	cout << "Welcome to the Aphids and Ladybugs simulator.";
	cout << "Please enter the name of the config files you wish to use: \n";
	//Take user input for file name
	cin >> file_name;
	//Test user input
	cout << file_name;
	//Open the file
	in_file.open(file_name);
	//Check file was opened correctly
	if (in_file.is_open())
	{
		cout << "File opened\n";
	}
	else
	{
		cout << "File not opened\n";
	}
	cin.get();
	//Read first line as grid sizes
	in_file >> grid_size[0]; //Grid height
	in_file >> grid_size[1]; //Grid length
	in_file >> num_aphids;
	while (1)
	{
		in_file >> aphid_pos[0];
	}
	cout << grid_size[0] << " " << grid_size[1];
	cin.get();
	//Close the file
	in_file.close();
}