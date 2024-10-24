#include <iostream>
#include <string>
#include <cstdlib> 
bool goodend = false;
bool badend = false;
enum State
{
	hide,
	reveal,
	flag

};
struct Grid
{
	Grid() : values(nullptr), width(-1), height(-1), tabrand(nullptr), bomb(0)
	{
	}
	~Grid()
	{
		for (int row = 0; row < height; row++)
		{
			delete[] tabrand[row];
		}
		delete[]tabrand;
		tabrand = nullptr;
		destroy();
	}

	void initiate()
	{


		std::cout << "choose the width : ";
		std::cin >> width;
		std::cout << std::endl;


		std::cout << "choose the height : ";
		std::cin >> height;
		std::cout << std::endl;




		//if grid too small
		if (width < 3 || height < 3)
		{
			do
			{
				std::cout << "invalid size enter a size greater than 3 ";
				std::cout << std::endl;
				std::cout << "choose the width : ";
				std::cin >> width;
				std::cout << std::endl;


				std::cout << "choose the height : ";
				std::cin >> height;
				std::cout << std::endl;
			} while (width < 3 || height < 3);
		}
		std::cout << "choose the number of bomb : ";
		std::cin >> bomb;
		std::cout << std::endl;
		// if too much bomb
		if (bomb > (20 * width * height) / 100)
			do
			{
				std::cout << "choose a valid number of bomb under 20% of case";
				std::cout << std::endl;
				std::cout << "choose the number of bomb : ";
				std::cin >> bomb;
				std::cout << std::endl;
			} while (bomb > (20 * width * height) / 100);

		//create the 2 grids 
		create(width, height);
		tableaualéatoire();

	}
	void floodfill(State** newValues, int row, int col) {
		//carefull of limits
		if (row < 0 || row >= height || col < 0 || col >= width|| newValues[row][col] == reveal) return;
		

		newValues[row][col] = reveal; // reveal the Cell

		
		if (tabrand[row][col] == '0') 
			for (int i = -1; i <= 1; ++i) 
				for (int j = -1; j <= 1; ++j) 
					floodfill(newValues, row + i, col + j);
				
			
		
	}


	void destroy()
	{
		for (int row = 0; row < height; ++row)
		{
			delete[] values[row];


		}
		delete[] values;
		values = nullptr;

	}
	State** values;
	int width;
	int height;
	char** tabrand;
	int bomb;
	void tableaualéatoire()
	{




		tabrand = new char* [height];
		// create the hiden grid
		for (int row = 0; row < height; row++)
			tabrand[row] = new char[width];

		for (int row = 0; row < height; ++row)
			for (int col = 0; col < width; ++col)
				tabrand[row][col] = '0';
		// place the numbers and bombs
		int bombPlaced = 0;
		while (bombPlaced < bomb)
		{

			int row = rand() % height;
			int col = rand() % width;


			if (tabrand[row][col] != 'B')
			{
				tabrand[row][col] = 'B';
				bombPlaced++;
				incrementSurroundingCase(row, col);
			}
		}

	}
	void incrementSurroundingCase(int bombrow, int bombcol)
	{
		//increment the numbers around the bomb
		for (int row = bombrow - 1; row <= bombrow + 1; ++row)
			for (int col = bombcol - 1; col <= bombcol + 1; ++col)
				if (row >= 0 && row < height && col >= 0 && col < width && tabrand[row][col] != 'B')
				{
					tabrand[row][col]++;
				}


	}


	char whatisthecharhide(int row, int col)
	{
		if (tabrand[row][col] == 'B')
		{
			hashitabomb();
			return tabrand[row][col];
		}
		else
		{
			return tabrand[row][col];

		}
	}


	void create(int width_, int height_)
	{
		//create the visible grid 
		width = width_;
		height = height_;
		values = new State * [height];
		for (int row = 0; row < height; ++row)
			values[row] = new State[width];

		for (int row = 0; row < height; ++row)
			for (int col = 0; col < width; ++col)
				values[row][col] = hide;
	}
	void show()
	{
		std::cout << "   ";
		for (int col = 0; col < width; ++col)
		{
			//code for spaces between line numbers
			std::string num_col = std::to_string(col + 1);
			std::cout << std::string(3 - num_col.length(), ' ') << num_col;
		}
		std::cout << std::endl;

		for (int row = 0; row < height; ++row)
		{
			//code for spaces between column numbers
			std::string num_row = std::to_string(row + 1);
			std::cout << std::string(3 - num_row.length(), ' ') << num_row;

			for (int col = 0; col < width; ++col)
			{
				if (values[row][col] == hide)
					std::cout << "[" << "-" << "]";

				else if (values[row][col] == reveal)
				{
					std::cout << "[" << whatisthecharhide(row, col) << "]";

				}

				else if (values[row][col] == flag)
					std::cout << "[" << "<" << "]";
				//in case of error
				else
					std::cout << "[" << "z" << "]";
			}
			std::cout << std::endl;

		}

		//Count the number box revealed for Win
		int RevealCell = 0;
		for (int row = 0; row < height; ++row)
			for (int col = 0; col < width; ++col)
			{

				if (values[row][col] == reveal)
				{
					++RevealCell;
				}
			}
		if (RevealCell == (height * width) - bomb)
			haswinn();
	}


	void iterate()
	{
		int heighttemp = 0;
		int widthtemp = 0;
		std::cout << "height : ";
		std::cin >> heighttemp;

		std::cout << "width : ";
		std::cin >> widthtemp;
		//if invalid position
		if (heighttemp > height || widthtemp > width)
		{
			do
			{
				std::cout << "Invalid position please try again" << std::endl;
				std::cout << "height : ";
				std::cin >> heighttemp;
				std::cout << "width : ";
				std::cin >> widthtemp;
			} while (heighttemp > height || widthtemp > width);
		}


		int choice = 0;
		std::cout << "which action  1: flag / 2 reveal : ";
		std::cin >> choice;

		State** newValues = new State * [height];
		for (int row = 0; row < height; ++row)
			newValues[row] = new State[width];
		for (int row = 0; row < height; ++row)
		{
			for (int col = 0; col < width; ++col)
			{
				newValues[row][col] = values[row][col];
			}
		}

		switch (choice)
		{
		case (1):


			
			newValues[heighttemp - 1][widthtemp - 1] = flag;

			destroy();
			values = newValues;
			break;
		case (2):
			if (tabrand[heighttemp - 1][widthtemp - 1] == '0') {
				floodfill(newValues, heighttemp - 1, widthtemp - 1); 
			}
			else {
				newValues[heighttemp - 1][widthtemp - 1] = reveal;
				
					
			}

			
			
			


			destroy();
			values = newValues;
			break;
		default:
			std::cout << "error" << std::endl;
			break;
		}



	}
	bool hashitabomb()
	{
		return badend = true;
	}
	bool haswinn()
	{
		return goodend = true;
	}
};
int main()
{

	srand(static_cast<unsigned int>(time(0)));

	Grid grid;

	grid.initiate();

	while (!goodend && !badend)
	{
		grid.show();
		std::cout << std::endl;
		if (goodend == true || badend == true)
		{
			break;
		}
		grid.iterate();
	}
	if (goodend)
	{
		std::cout << std::endl;
		std::cout << "WINNER ! You will become a Jedi, May the force be with you  :)";
		std::cout << std::endl;

	}
	else if (badend)
	{
		std::cout << std::endl;
		std::cout << "Oh you have lost ... I think the Sith take apprentices :(";
		std::cout << std::endl;
	}
	return 0;
}
