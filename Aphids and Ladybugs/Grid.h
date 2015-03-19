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
        void create_grid();

        /**
         * Draws the array as a #x# grid and shows locations of aphids and
         * ladybugs
         * @param vector<Aphid> aphid_vector
         * @param vector<Ladybug> lady_vector
         */
        void draw_grid(vector<Aphid>& aphid_vector, vector<Ladybug>& lady_vector);

        /**
         * Retrieves the height of the grid
         * @return int height
         */
        int get_height();

        /**
         * Retrieves the width of the grid
         * @return int width
         */
        int get_width();
        
        /**
         * Sets height of grid
         * @param temp_height
         */
        void set_height(int temp_height);
        
        /**
         * Sets width of grid
         * @param temp_width
         */
        void set_width(int temp_width);
};

#endif
