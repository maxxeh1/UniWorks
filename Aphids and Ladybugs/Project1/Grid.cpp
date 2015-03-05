#include <iostream>
using namespace std;
//class Grid;

//Main function
int main()
{

}

//Create a class called Grid
class Grid
{
	public:
	void createGrid()
	{
		char grid[3][3] = { { 'a', 'b', 'c' }, { 'a', 'b', 'c' }, { 'a', 'b', 'c' } };
		int number = 52;
		int gridSize = sizeof(grid) / sizeof(int);
		char character = '*';
		int position[2] = { 0, 2 };

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i == position[0] && j == position[1])
				{
					cout << character;
				}
				else
				{
					cout << grid[i][j];
				}
				cout << " ";

			}
			cout << "\n";
			cout << "______\n";
		}
		cin.get();
	}
};
