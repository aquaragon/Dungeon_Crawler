#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int MAX_COL = 9;
const int MAX_ROW = 7;
const int NUM_TRAP = 5;
const int NUM_MON = 3;
const char SPACE = '.';
const char TRAP = '#';
const char PLAYER = '@';
const char CASH = '$';
const char MONSTER = 'M';


bool play_again(); //Asks player if they wanna play again
void displayInstructions(); //displays instructions
void createDungeon(char dungeon[MAX_ROW][MAX_COL]); //creates dungeon, places monsters, traps, treasure, and player 
void displayDungeon(char dungeon[MAX_ROW][MAX_COL]); //prints out dungeon with border
void emptyLoc(int & row, int & col, char dungeon[MAX_ROW][MAX_COL]); //function that generates locations to place game elements
char getMove(int x, int y);//acquires and validates move from player
bool checkMove(char dungeon[MAX_ROW][MAX_COL], char move, bool & lose, bool win, int &x, int &y);//checks to see if move is a lose or a win
void updateDungeon(char dungeon[MAX_ROW][MAX_COL], char move, int x, int y);//moves player and monster to their new location
void moveMon(int & monster_move, char dungeon[MAX_ROW][MAX_COL], int i, int j);//picks random and valid location for each monster to move 

//asks player if they'd like to play again
bool play_again()
{
	char repeat;
	cout << "Would you like to play again? (Y or N)" << endl;
	cin >> repeat;
	if (toupper(repeat) == 'Y')
		return true;
	else
		return false;
}

//displays instructions
void displayInstructions()
{
	cout << "Welcome to the Dungeon Crawl Game!\n"
		 << "You will start in a randomizied dungeon\n"
	 	 << "Your mission is to avoid traps (#) , avoid monsters (M) and claim the treasure ($)\n"
		 << "Each move you may go up, down, left or right within the dungeon\n"
		 << "Your player is indicated by @\n"
		 << "Good luck!\n" << endl;

}

//creates dungeon, adds spaces to every array index, places traps, monsters, treasure and player
void createDungeon(char dungeon[MAX_ROW][MAX_COL])
{
	int row, col;
	for (int i = 0; i < MAX_ROW; i++) //creates clear dungeon
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			dungeon[i][j] = SPACE;
		}

	}
	for (int i = 0; i < NUM_TRAP; i++) //assigns randomly located traps
	{
		emptyLoc(row, col, dungeon);
		dungeon[row][col] = TRAP;
	}
	for (int i = 0; i < NUM_MON; i++) //assigns randomly located monsters
	{
		emptyLoc(row, col, dungeon);
		dungeon[row][col] = MONSTER;
	}
	emptyLoc(row, col, dungeon); //places cash and player
	dungeon[row][col] = CASH;
	emptyLoc(row, col, dungeon);
	dungeon[row][col] = PLAYER;
}

//Prints out dungeon with each index of the array and a lined border
void displayDungeon(char dungeon[MAX_ROW][MAX_COL])
{
    cout << "-----------" << endl;
    for (int i = 0; i < MAX_ROW; i++)
    {
        cout << "|";
        for (int j = 0; j <= MAX_COL; j++)
        {
            if(j == MAX_COL)
                cout << "|";
            else
                cout << dungeon[i][j];
        }
		cout << endl;
    }
    cout << "-----------" << endl;
}

//Random location generator, location with space is accepted
void emptyLoc(int & row, int & col, char dungeon[MAX_ROW][MAX_COL])
{
	do {
		row = rand() % MAX_ROW;
		col = rand() % MAX_COL;
	} while (dungeon[row][col] != SPACE);
}

//Acquires move from player, makes sure it is in bounds of the dungeon
char getMove(int x, int y)
{
	bool valid = true;
	char move;
	do
	{
		if (valid == true)
		{
			cout << "Where would you like to move?" << endl;
			cin >> move;
		}
		if (valid == false)
		{
			cout << "Invalid move, please try again" << endl;
			cin >> move;
			valid = true;
		}
		if (move == 'w' && (y - 1 < 0))
			valid = false;

		if (move == 's' && (y + 2 > MAX_ROW ))
			valid = false;

		if (move == 'a' && (x - 1 < 0))
			valid = false;

		if (move == 'd' && (x + 2 > MAX_COL))
			valid = false;

		if (move != 'w' && move != 's' && move != 'a' && move != 'd')
			valid = false;

	} while (valid == false);
	return move;

}

//Checks to see if move made is a loss or a win
bool checkMove(char dungeon[MAX_ROW][MAX_COL], char move, bool & lose, bool win, int & x, int & y)
{
	if (move == 'w')
	{
		if (dungeon[y - 1][x] == MONSTER || dungeon[y - 1][x] == TRAP)
		{
			lose = true;
			y -= 1;
		}

		if (dungeon[y - 1][x] == CASH)
			win = true;
	}

	if (move == 's')
	{
		if (dungeon[y + 1][x] == MONSTER || dungeon[y + 1][x] == TRAP)
		{
			lose = true;
			y += 1;
		}

		if (dungeon[y + 1][x] == CASH)
			win = true;
	}

	if (move == 'a')
	{
		if (dungeon[y][x - 1] == MONSTER || dungeon[y][x - 1] == TRAP)
		{
			lose = true;
			x -= 1;
		}

		if (dungeon[y][x - 1] == CASH)
			win = true;
	}

	if (move == 'd')
	{
		if (dungeon[y][x + 1] == MONSTER || dungeon[y][x + 1] == TRAP)
		{
			lose = true;
			x += 1;
		}

		if (dungeon[y][x + 1] == CASH)
			win = true;
	}
	return win;
}

//Places player and monster in new locations
void updateDungeon(char dungeon[MAX_ROW][MAX_COL], char move, int x, int y)
{
	int count = 0; //keeps count of amount of monsters moved
	int monster_move;
	char forbid_move[MAX_ROW][MAX_COL]; //makes sure monster isn't moved again

	if (move == 'w')
	{
		dungeon[y - 1][x] = PLAYER;
		dungeon[y][x] = SPACE;
	}

	if (move == 's')
	{
		dungeon[y + 1][x] = PLAYER;
		dungeon[y][x] = SPACE;
	}

	if (move == 'a')
	{
		dungeon[y][x - 1] = PLAYER;
		dungeon[y][x] = SPACE;
	}

	if (move == 'd')
	{
		dungeon[y][x + 1] = PLAYER;
		dungeon[y][x] = SPACE;
	}

	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			if (dungeon[i][j] == MONSTER && forbid_move[i][j] != 'x')
			{
				moveMon(monster_move, dungeon, i, j);
				if (monster_move == 0) //up
				{
					dungeon[i - 1][j] = MONSTER;
					dungeon[i][j] = SPACE;
				}

				if (monster_move == 2) //down
				{
					dungeon[i + 1][j] = MONSTER;
					dungeon[i][j] = SPACE;
					forbid_move[i + 1][j] = 'x';
				}

				if (monster_move == 1) //right
				{
					dungeon[i][j + 1] = MONSTER;
					dungeon[i][j] = SPACE;
					forbid_move[i][j + 1] = 'x';
				}

				if (monster_move == 3) //left
				{
					dungeon[i][j - 1] = MONSTER;
					dungeon[i][j] = SPACE;
				}
				
				count++;
			}
			if (count == NUM_MON)
			{
				j = MAX_COL;
				i = MAX_ROW;
			}

		}
	}
		
}
//Finds random and valid location for monster to move
void moveMon(int & monster_move, char dungeon[MAX_ROW][MAX_COL], int i, int j)
{
	bool valid;
	do
	{
		valid = true;
		monster_move = rand() % 4;
		if (monster_move == 0)
		{
			if (dungeon[i - 1][j] != SPACE)
				valid = false;
			if (i - 1 < 0)
				valid = false;
		}

		if (monster_move == 2)
		{
			if (dungeon[i + 1][j] != SPACE)
				valid = false;
			if (i + 1 == MAX_ROW)
				valid = false;
		}

		if (monster_move == 1)
		{
			if (dungeon[i][j + 1] != SPACE)
				valid = false;
			if (j + 1 == MAX_COL)
				valid = false;
		}

		if (monster_move == 3)
		{
			if (dungeon[i][j - 1] != SPACE)
				valid = false;
			if (j - 1 < 0)
				valid = false;
		}
	} while (valid == false);
}

int main()
{
	do
	{
		srand(time(NULL));
		int x = 0;
		int y = 0;
		bool win = false;
		bool lose = false;
		char dungeon[MAX_ROW][MAX_COL];
		displayInstructions();
		createDungeon(dungeon);
		do
		{
			displayDungeon(dungeon);
			for (int i = 0; i < MAX_ROW; i++)
			{
				for (int j = 0; j < MAX_COL; j++)
				{
					if (dungeon[i][j] == '@')
					{
						y = i;
						x = j;
						i = MAX_ROW;
						j = MAX_COL;
					}
				}
			}
			char move = getMove(x, y);
			win = checkMove(dungeon, move, lose, win, x, y);
			if (win == true)
			{
				cout << "You found the treasure\n"
					<< "You win!" << endl;
			}

			else if (lose == true)
			{
				if (dungeon[y][x] == TRAP)
				{
					cout << "You fell through a trap!\n"
						<< "You lose" << endl;
				}

				else
				{
					cout << "Monster got you!\n"
						<< "You lose" << endl;
				}

			}
			else
				updateDungeon(dungeon, move, x, y);
				
		} while (win == false && lose == false);
	} while (play_again());

	return 0;
}
