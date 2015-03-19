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
void Grid::createGrid()
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
 * @param vector<Aphid> aphidVector
 * @param vector<Ladybug> ladyVector
 */
void Grid::drawGrid(vector<Aphid>& aphidVector, vector<Ladybug>& ladyVector)
{
    //Local variables
    int cellAphids = 0, cellLadys = 0, column = 0, row = 0; 
    bool ladyBug = false, aphid = false;
    
    //Draw the grid, looping through aphid and ladybug vectors
    cout << " ";
    //Loop through columns and print column numbers
    for (int colCount = 0; colCount < this->width; colCount++)
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
            for (vector<Aphid>::iterator itA = aphidVector.begin();  
                    itA != aphidVector.end(); ++itA)
            {
                //If an aphid's positions match current position in grid
                if ((*itA).getHeight() == i && (*itA).getWidth() == j)
                {
                    //Increment number of aphids in cell
                    ++cellAphids;
                    //Sets boolean check to tell there was an aphid found here
                    aphid = true;
                }
            }
            //Loop through ladybugs
            for (vector<Ladybug>::iterator itL = ladyVector.begin(); 
                    itL != ladyVector.end(); ++itL)
            {
                //If a ladybug's positions match current position in grid
                if ((*itL).getHeight() == i && (*itL).getWidth() == j)
                {
                    //Increment number of ladybugs in cell
                    ++cellLadys;
                    //Sets boolean check to tell there was a ladybug found here
                    ladyBug = true;
                }                                
            }
            //If a ladybug or aphid is found, fill the "cell", if not fill with
            //space
            if(ladyBug && aphid)
            {
                cout << "|L"; 
                //Replace double digits with ~
                if(cellLadys >= 10)
                {
                    cout << "~";
                }
                else
                {
                    cout << cellLadys;
                }
                cout << "A";
                //Replace double digits with ~
                if(cellAphids >= 10)
                {
                    cout << "~";
                }
                else
                {
                    cout << cellAphids;
                }
            }
            else if(aphid)
            {
                cout << "|A";
                //Replace double digits with ~
                if(cellAphids >= 10)
                {
                    cout << "~";
                }
                else
                {
                    cout << cellAphids;
                }
                cout << "  ";
            }
            else if(ladyBug)
            {
                cout << "|  L";
                //Replace double digits with ~
                if(cellLadys >= 10)
                {
                    cout << "~";
                }
                else
                {
                    cout << cellLadys;
                }
            }
            //If cell is not filled 
            else if (!aphid || !ladyBug)
            {
                cout << "|    ";
            }
            //Reset condition variables
            aphid = false;
            ladyBug = false;
            cellAphids = 0;
            cellLadys = 0;
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
int Grid::getHeight()
{
    return this->height;
}

/**
 * Retrieves the width of the grid
 * @return int width
 */
int Grid::getWidth()
{
    return this->width;
}

/**
 * Sets height of grid
 * @param temp_height
 */
void Grid::setHeight(int temp_height)
{
    this->height = temp_height;
}

/**
 * Sets width of grid
 * @param temp_width
 */
void Grid:: setWidth(int temp_width)
{
    this->width = temp_width;
}