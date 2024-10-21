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
	Grid() : values(nullptr), width(-1), height(-1), tabrand(nullptr)
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
		if (width < 2 || width < 2)
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
	void tableaualéatoire()
	{

		int bomb = (20 * width * height) / 100;


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

			}
		}
		//placer les chiffres autour des bombes
		for (int row = 0; row < height ; ++row)
			for (int col = 0; col < width; ++col)
			{
				if (tabrand[row][col] == 'B')
				{
					tabrand[row][col] = 'B';
				}
				else
				{

					if (row != 0 && row != height - 1 && col != 0 && col != width - 1) // tout sauf les bordure
					{
						if (tabrand[row - 1][col - 1] == 'B')// case en hat a gauche
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row - 1][col] == 'B')//case en haut au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row - 1][col + 1] == 'B')// case en haut a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col + 1] == 'B')// case en bas a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col] == 'B')// case en bas au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col - 1] == 'B')// case en bas a gauche 
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row][col - 1] == 'B')// case au millieu a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row][col + 1] == 'B')// case au millieu a gauche 
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;
					}
					else if (row == 0 && col == 0) // le coin en haut gauche
					{
						if (tabrand[row][col - 1] == 'B')// case au millieu a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col] == 'B')// case en bas au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col + 1] == 'B')// case en bas a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;
					}
					else if (row == 0 && col == width - 1) // le coin en haut a droite 
					{
						if (tabrand[row][col + 1] == 'B')// case au millieu a gauche 
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col] == 'B')// case en bas au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col - 1] == 'B')// case en bas a gauche 
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;
					}
					else if (row == height - 1 && col == 0) // le coin en bas a gauche
					{
						if (tabrand[row - 1][col] == 'B')//case en haut au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row - 1][col + 1] == 'B')// case en haut a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row][col - 1] == 'B')// case au millieu a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;
					}
					else if (row == height - 1 && col == width - 1) // le coin en bas a droite
					{
						if (tabrand[row - 1][col] == 'B')//case en haut au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row - 1][col - 1] == 'B')// case en hat a gauche
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row][col + 1] == 'B')// case au millieu a gauche 
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;
					}
					else if (row == 0 && col != 0 && col != width - 1) //en haut 
					{
						if (tabrand[row + 1][col + 1] == 'B')// case en bas a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col] == 'B')// case en bas au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col - 1] == 'B')// case en bas a gauche 
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row][col - 1] == 'B')// case au millieu a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row][col + 1] == 'B')// case au millieu a gauche 
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;
					}
					else if (row == height - 1 && col != 0 && col != width - 1) //en bas
					{
						if (tabrand[row - 1][col - 1] == 'B')// case en hat a gauche
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row - 1][col] == 'B')//case en haut au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row - 1][col + 1] == 'B')// case en haut a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row][col - 1] == 'B')// case au millieu a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row][col + 1] == 'B')// case au millieu a gauche 
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;
					}
					else if (col == 0 && row != 0 && row != height - 1) // a gauche
					{
						if (tabrand[row - 1][col] == 'B')//case en haut au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row - 1][col + 1] == 'B')// case en haut a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col + 1] == 'B')// case en bas a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col] == 'B')// case en bas au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row][col - 1] == 'B')// case au millieu a droite
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;
					}
					else if (col == width - 1 && row != 0 && row != height - 1) // a droite
					{
						if (tabrand[row - 1][col - 1] == 'B')// case en hat a gauche
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row - 1][col] == 'B')//case en haut au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col] == 'B')// case en bas au milieu
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row + 1][col - 1] == 'B')// case en bas a gauche 
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;

						if (tabrand[row][col + 1] == 'B')// case au millieu a gauche 
							//tabrand[row][col]++;
							tabrand[row][col] = tabrand[row][col] + 1;
					}
				}

			}







		/*for (int row = 0; row < height; ++row)
		{
			for (int col = 0; col< width; ++col)
			{
				std::cout << tabrand[row][col] << " ";


			}
			std::cout << std::endl;
		}*/
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
	void show()
	{
		std::cout << "   ";
		for (int col = 0; col < width; ++col)
		{
			std::string num_col = std::to_string(col+1);
			std::cout << std::string(3 - num_col.length(), ' ') << num_col;
		}
		std::cout << std::endl;

		for (int row = 0; row < height; ++row)
		{
			std::string num_row = std::to_string(row+1);
			std::cout << std::string(3 - num_row.length(), ' ') << num_row;
			for (int col = 0; col < width; ++col)
			{
				if (values[row][col] == hide)
					std::cout << "[" << "-" << "]" ;

				else if (values[row][col] == reveal)
				{
					std::cout << "["<< whatisthecharhide(row, col) << "]";

				}

				else if (values[row][col] == flag)
					std::cout << "[" << "<" << "]" ;
				else
					std::cout << "[" << "z" << "]" ;
			}
			std::cout << std::endl;
			
		}

		int hiddenCells = 0;

		for (int row = 0; row < height; ++row)
			for (int col = 0; col < width; ++col)
			{

				if (values[row][col] == reveal)
				{
					++hiddenCells;
				}
			}
		if (hiddenCells == (height * width) - ((20 * width * height) / 100))
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




				}
			}
			newValues[heighttemp - 1][widthtemp - 1] = reveal;

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
