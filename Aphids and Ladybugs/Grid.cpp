#include <iostream>
#include <vector>
#include "Grid.h"
#include "Animal.h"
using namespace std;
//class Grid;

//Create a class called Grid


	//Public methods

		//Default Constructor
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
		void Grid::drawGrid(vector<Aphid>& aphidVector, vector<Ladybug>& ladyVector, int num_aphids, int num_ladys)
		{
			int cellAphids = 0;
			int cellLadys = 0; 
			bool filled = false;
			for (int i = 0; i < this->height; i++)
			{

				for (int j = 0; j < this->width; j++)
				{
					for (int arr = 0; arr < num_aphids; arr++)
					{
						if (aphidVector[i].getHeight == i && aphidVector[i].getWidth == j)
						{
							cout << "|A" + ++cellAphids;
							filled = true;
						}
					}
					for (int arr1 = 0; arr1 < num_ladys; arr1++)
					{
						if (ladyVector[i].getHeight == i && ladyVector[i].getWidth == j)
						{
							cout << "|L" + ++cellLadys;
							filled = true;
						}
					}
					if (!filled)
					{
						cout << "|  ";
					}
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
