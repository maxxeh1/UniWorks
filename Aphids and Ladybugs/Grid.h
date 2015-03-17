#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Animal.h"
using namespace std;
//class Grid;

//Create a class called Grid
class Grid
{
    friend class Animal;
    //Variables
    int height;
    int width;
    char *** grid;

    //Public methods
    public:
        //Default Constructor
        Grid();
        /**
         * Constructor
         * @param int temp_height
         * @param int temp_width
         */
        Grid(int temp_height, int temp_width);

        /**
         * Creates a 2D array based on object variables
         * for later drawing as a grid
         */
        void createGrid();

        /**
         * Draws the array as a #x# grid and shows locations of aphids and
         * ladybugs
         * @param vector<Aphid> aphidVector
         * @param vector<Ladybug> ladyVector
         */
        void drawGrid(vector<Aphid>& aphidVector, vector<Ladybug>& ladyVector);

        /**
         * Retrieves the height of the grid
         * @return int height
         */
        int getHeight();

        /**
         * Retrieves the width of the grid
         * @return int width
         */
        int getWidth();
        
        void setHeight(int temp_height);
        
        void setWidth(int temp_width);
};

#endif
