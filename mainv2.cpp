#include <iostream>
#include <string>
#include <cstdlib> 
bool goodend = false;
bool badend = false;
enum State
{
	hide,
	newreveal,
	oldreveal,
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

		std::cout << "choose the number of bomb : ";
		std::cin >> bomb;
		std::cout << std::endl;
		if (bomb > (20 * width * height) / 100)
			do
			{
				std::cout << "choose a valid number of bomb under 20% of case";
				std::cout << std::endl;
				std::cout << "choose the number of bomb : ";
				std::cin >> bomb;
				std::cout << std::endl;
			} while (bomb > (20 * width * height) / 100);
		if (width < 2 || width < 2)
		{
			do
			{
				std::cout << "invalid size enter a size greater than 5 ";
				std::cout << std::endl;
				std::cout << "choose the width : ";
				std::cin >> width;
				std::cout << std::endl;


				std::cout << "choose the height : ";
				std::cin >> height;
				std::cout << std::endl;
			} while (width < 2 || width < 2);
		}

		create(width, height);
		tableaualéatoire();

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
		// creer une grille
		for (int row = 0; row < height; row++)
			tabrand[row] = new char[width];

		for (int row = 0; row < height; ++row)
			for (int col = 0; col < width; ++col)
				tabrand[row][col] = '0';
		// gerer les bomb
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
		width = width_;
		height = height_;
		values = new State * [height];
		for (int row = 0; row < height; ++row)
			values[row] = new State[width];

		for (int row = 0; row < height; ++row)
			for (int col = 0; col < width; ++col)
				values[row][col] = hide;
	}
	void floodfillimpro(int row0, int col0)
	{





	}
	void show()
	{
		int row0 = -1;
		int col0 = -1;
		std::cout << "   ";
		for (int col = 0; col < width; ++col)
		{
			std::string num_col = std::to_string(col + 1);
			std::cout << std::string(3 - num_col.length(), ' ') << num_col;
		}
		std::cout << std::endl;

		for (int row = 0; row < height; ++row)
		{
			std::string num_row = std::to_string(row + 1);
			std::cout << std::string(3 - num_row.length(), ' ') << num_row;
			for (int col = 0; col < width; ++col)
			{
				if (values[row][col] == hide)
					std::cout << "[" << "-" << "]";

				else if (values[row][col] == newreveal)
				{
					std::cout << "[" << whatisthecharhide(row, col) << "]";
					if (whatisthecharhide(row, col) == '0')
					{
						 row0 = row;
						 col0 = col;
					}
				}

				else if (values[row][col] == flag)
					std::cout << "[" << "<" << "]";
				else if (values[row][col] == oldreveal)
				{
					std::cout << "[" << whatisthecharhide(row, col) << "]";
					
				}
				else
					std::cout << "[" << "z" << "]";
			}
			std::cout << std::endl;

		}
		if (row0 != -1 || col0 != -1)
			floodfillimpro(row0 ,col0);

		int hiddenCells = 0;

		for (int row = 0; row < height; ++row)
			for (int col = 0; col < width; ++col)
			{

				if (values[row][col] == oldreveal)
				{
					++hiddenCells;
				}
			}
		if (hiddenCells == (height * width) - bomb)
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

		switch (choice)
		{
		case (1):


			for (int row = 0; row < height; ++row)
			{
				for (int col = 0; col < width; ++col)
				{
					newValues[row][col] = values[row][col];
					if (newValues[row][col] == newreveal)
						newValues[row][col] = oldreveal;



				}
			}
			newValues[heighttemp - 1][widthtemp - 1] = flag;

			destroy();
			values = newValues;
			break;
		case (2):


			for (int row = 0; row < height; ++row)
			{
				for (int col = 0; col < width; ++col)
				{
					newValues[row][col] = values[row][col];
					if (newValues[row][col] == newreveal)
						newValues[row][col] = oldreveal;



				}
			}
			newValues[heighttemp - 1][widthtemp - 1] = newreveal;

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
