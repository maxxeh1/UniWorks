#ifndef GRID_H
#define GRID_H
//class Grid;

//Create a class called Grid
class Grid
{
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
		void drawGrid();

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
