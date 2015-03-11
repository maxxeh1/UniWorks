#include <iostream>
#include <vector>
#include "Grid.h"
#include "Animal.h"
using namespace std;


Grid::Grid()
{
    this->height = 10;
    this->width = 10;
}
//Constructor
Grid::Grid(int temp_height, int temp_width)
{
    this->height = temp_height;
    this->width = temp_width;
}

/**
    Creates a 2D array based on object variables
    for later drawing as a grid
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
    Draws the array as a #x# grid
*/
void Grid::drawGrid(vector<Aphid>& aphidVector, vector<Ladybug>& ladyVector)
{
    //Local variables
    int cellAphids = 0, cellLadys = 0, column = 0, row = 0; 
    bool filled = false, ladyBug = false, aphid = false;
    
    //Draw the grid, looping through aphid and ladybug vectors
    cout << " ";
    for (int colCount = 0; colCount < this->width; colCount++)
    {
        cout << " " << column++ << " ";
    }
    cout << endl;
    for (int i = 0; i < this->height; i++)
    {
        cout << row++ << "";
        for (int j = 0; j < this->width; j++)
        {
            for (vector<Aphid>::iterator itA = aphidVector.begin();  
                    itA != aphidVector.end(); ++itA)
            {
                if ((*itA).getHeight() == i && (*itA).getWidth() == j)
                {
                    ++cellAphids;
                    aphid = true;
                    filled = true;
                }
            }
            for (vector<Ladybug>::iterator itL = ladyVector.begin(); 
                    itL != ladyVector.end(); ++itL)
            {
                if ((*itL).getHeight() == i && (*itL).getWidth() == j)
                {
                    ++cellLadys;
                    filled = true;
                    ladyBug = true;
                }                                
            }
            //If a ladybug or aphid is found, fill the "cell", if not fill with
            //space
            if(ladyBug)
            {
                cout << "|L" << cellLadys;
            }
            if(aphid)
            {
                cout << "|A" << cellAphids;
            }
            if (!filled)
            {
                cout << "|  ";
            }
            aphid = false;
            ladyBug = false;
            filled = false;
            cellAphids = 0;
            cellLadys = 0;
        }
        cout << "|\n";
        cout << "  ";
        for (int f = 0; f < this->width; f++)
        {
            cout << "___";
        }
        cout << "\n";
    }
}

/**
    Retrieves the height of the grid
    @return height variable
*/
int Grid::getHeight()
{
    return this->height;
}

/**
    Retrieves the width of the grid
    @return width variable
*/
int Grid::getWidth()
{
    return this->width;
}
