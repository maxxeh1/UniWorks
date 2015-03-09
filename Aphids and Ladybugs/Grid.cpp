#include <iostream>
#include <vector>
using namespace std;
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
		Grid()
		{
			this->height = 10;
			this->width = 10;
		}
		//Constructor
		Grid(int temp_height, int temp_width)
		{
			this->height = temp_height;
			this->width = temp_width;
		}

		/**
			Creates a 2D array based on object variables
			for later drawing as a grid
		*/
		void createGrid()
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
		void drawGrid()
		{
			for (int i = 0; i < this->height; i++)
			{

				for (int j = 0; j < this->width; j++)
				{
					cout << "|aa";
				}
				cout << "|\n";
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
		int getHeight()
		{
			return this->height;
		}

		/**
			Retrieves the width of the grid
			@return width variable
		*/
		int getWidth()
		{
			return this->width;
		}
};
