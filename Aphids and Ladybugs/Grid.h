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
		//Constructor
		Grid(int temp_height, int temp_width);

		/**
			Creates a 2D array based on object variables
			for later drawing as a grid
		*/
		void createGrid();

		/**
			Draws the array as a #x# grid
		*/
		void drawGrid(vector<Aphid>& aphidVector, vector<Ladybug>& ladyVector, int num_aphids, int num_ladys);

		/**
			Retrieves the height of the grid
			@return height variable
		*/
		int getHeight();

		/**
			Retrieves the width of the grid
			@return width variable
		*/
		int getWidth();
};

#endif
