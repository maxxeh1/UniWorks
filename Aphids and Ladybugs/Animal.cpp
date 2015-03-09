#include <string>
using namespace std;

class Animal
{
	

	protected:
		int position[2];
		
	public:
		Animal()
		{
			position[0] = 0;
			position[1] = 1;
		}
		void setHeight(int height)
		{
			this->position[0] = height;
		}

		void setWidth(int width)
		{
			this->position[1] = width;
		}

		int getHeight()
		{
			return this->position[0];
		}

		int getWidth()
		{
			return this->position[1];
		}
};
