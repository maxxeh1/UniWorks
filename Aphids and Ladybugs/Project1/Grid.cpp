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

	public:
		Grid(int temp_height, int temp_width)
		{
			this->height = temp_height;
			this->width = temp_width;
		}

		void createGrid()
		{
			char **temp_grid = new char *[this->height];
			for (int i = 0; i < height; i++)
			{
				temp_grid[i] = new char[this->width];
			}
			this->grid = &temp_grid;
		}	

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

		int getHeight()
		{
			return this->height;
		}

		int getWidth()
		{
			return this->width;
		}

		char*** getGrid()
		{
			return this->grid;
		}
};
