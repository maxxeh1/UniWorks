#include <iostream>
#include <vector>
#include <iomanip>
#include "Grid.h"
#include "Animal.h"
using namespace std;

/**
 * Default constructor
 */
Grid::Grid()
{
    this->height = 10;
    this->width = 10;
}
/**
 * Constructor
 * @param int temp_height
 * @param int temp_width
 */
Grid::Grid(int temp_height, int temp_width)
{
    this->height = temp_height;
    this->width = temp_width;
}

/**
 * Creates a 2D array based on object variables
 * for later drawing as a grid
 */
void Grid::create_grid()
{
    char **temp_grid = new char *[this->height];
    for (int i = 0; i < height; i++)
    {
        temp_grid[i] = new char[this->width];
    }
    this->grid = &temp_grid;
}	

/**
 * Draws the array as a #x# grid and shows locations of aphids and
 * ladybugs
 * @param vector<Aphid> aphid_vector
 * @param vector<Ladybug> lady_vector
 */
void Grid::draw_grid(vector<Aphid>& aphid_vector, vector<Ladybug>& lady_vector)
{
    //Local variables
    int cell_aphids = 0, cell_ladys = 0, column = 0, row = 0; 
    bool ladybug = false, aphid = false;
    
    //Draw the grid, looping through aphid and ladybug vectors
    cout << " ";
    //Loop through columns and print column numbers
    for (int col_count = 0; col_count < this->width; col_count++)
    {
        cout << setw(5) << column++;
    }
    cout << endl;
    //Loop through rows and nested loop through columns to print locations of 
    //aphids and ladybugs, as well as the number of them in each cell
    for (int i = 0; i < this->height; i++)
    {
        //Set width to be the same, regardless of what's in it
        //Increment row number
        cout << setw(3) << row++;
        //Loop through width of grid
        for (int j = 0; j < this->width; j++)
        {
            //Loop through aphids
            for (vector<Aphid>::iterator itA = aphid_vector.begin();  
                    itA != aphid_vector.end(); ++itA)
            {
                //If an aphid's positions match current position in grid
                if ((*itA).get_height() == i && (*itA).get_width() == j)
                {
                    //Increment number of aphids in cell
                    ++cell_aphids;
                    //Sets boolean check to tell there was an aphid found here
                    aphid = true;
                }
            }
            //Loop through ladybugs
            for (vector<Ladybug>::iterator itL = lady_vector.begin(); 
                    itL != lady_vector.end(); ++itL)
            {
                //If a ladybug's positions match current position in grid
                if ((*itL).get_height() == i && (*itL).get_width() == j)
                {
                    //Increment number of ladybugs in cell
                    ++cell_ladys;
                    //Sets boolean check to tell there was a ladybug found here
                    ladybug = true;
                }                                
            }
            //If a ladybug or aphid is found, fill the "cell", if not fill with
            //space
            if(ladybug && aphid)
            {
                cout << "|L"; 
                //Replace double digits with ~
                if(cell_ladys >= 10)
                {
                    cout << "~";
                }
                else
                {
                    cout << cell_ladys;
                }
                cout << "A";
                //Replace double digits with ~
                if(cell_aphids >= 10)
                {
                    cout << "~";
                }
                else
                {
                    cout << cell_aphids;
                }
            }
            else if(aphid)
            {
                cout << "|A";
                //Replace double digits with ~
                if(cell_aphids >= 10)
                {
                    cout << "~";
                }
                else
                {
                    cout << cell_aphids;
                }
                cout << "  ";
            }
            else if(ladybug)
            {
                cout << "|  L";
                //Replace double digits with ~
                if(cell_ladys >= 10)
                {
                    cout << "~";
                }
                else
                {
                    cout << cell_ladys;
                }
            }
            //If cell is not filled 
            else if (!aphid || !ladybug)
            {
                cout << "|    ";
            }
            //Reset condition variables
            aphid = false;
            ladybug = false;
            cell_aphids = 0;
            cell_ladys = 0;
        }
        cout << "|\n";
        cout << "    ";
        //Print row seperators
        for (int f = 0; f < this->width; f++)
            
        {
            cout << "_____";
        }
        cout << "\n";
    }
}

/**
 * Retrieves the height of the grid
 * @return int height
 */
int Grid::get_height()
{
    return this->height;
}

/**
 * Retrieves the width of the grid
 * @return int width
 */
int Grid::get_width()
{
    return this->width;
}

/**
 * Sets height of grid
 * @param temp_height
 */
void Grid::set_height(int temp_height)
{
    this->height = temp_height;
}

/**
 * Sets width of grid
 * @param temp_width
 */
void Grid:: set_width(int temp_width)
{
    this->width = temp_width;
}