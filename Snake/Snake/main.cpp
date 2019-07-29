/*
	Author: Neville Bulmer
	Date: 29/07/2019
	Description: A basic snake game created in c++.
				 User input is defined in the Input method.
				 All logic is in the Logic method I.e. did the snake hit either itself or a wall.
				 All drawing is done in the draw method, see diagram in the notes.
*/

// Include library io stream for standar input, output streams.
#include <iostream>
// Include for conio, used in the controls functionality.
#include <conio.h>
// Include library windows to time element I.e. slow the game, this will 
// introduce more flickering within the command line.

// Using the standard library for namspacing.
using namespace std;

// Used to check if game over has occured I.e. death.
bool gameOver;
// Width of the game window.
const int width = 20;
// Height of the game window.
const int height = 20;
// X and Y values for the player along with X and Y values for the spawned fruit.
int x, y, fruitX, fruitY, score;
// Array of all x coordinate tail peices.
int tailX[100];
// Array of all y coordinate tail peices.
int tailY[100];
// The length of the tail.
int nTail;

// Enum for directions I.e. LEFT RIGHT UP and DOWN.
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

// Initialise enum Direction equal to a name or Direction.
Direction direction;

void Setup()
{
	gameOver = false;
	// Start the game at a stopped position.
	direction = STOP;
	// Start the players x position to center.
	x = width / 2;
	// Start the players y position to center.
	y = height / 2;
	// Sets the spawn for the fruits x position to random devided by the width, ensures it never spawns outside of the game window.
	fruitX = rand() % width;
	// Sets the spawn for the fruits y position to random devided by the height, ensures it never spawns outside of the game window.
	fruitY = rand() % height;
	// Sets the initial score for the game to zero.
	score = 0;
}

// Method Draw, responsible for everything visual on the screen.
void Draw()
{
	// Clear the terminal on game start.
	system("cls");
	
	// for each loops responsible for printing the blocks which make up the walls of the game board.
	//    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22
	// 1  # # # # # # # # # #  #  #  #  #  #  #  #  #  #  #  #  #
	// 2  #                                                     #
	// 3  #                                                     #
	// 4  #                                                     #
	// 5  #                                                     #
	// 6  #                                                     #
	// 7  #                                                     #
	// 8  #                                                     #
	// 9  #                                                     #
	// 10 #                                                     #
	// 11 #                                                     #
	// 12 #                                                     #
	// 13 #                                                     #
	// 14 #                                                     #
	// 15 #                                                     #
	// 16 #                                                     #
	// 17 #                                                     #
	// 18 #                                                     #
	// 19 #                                                     #
	// 20 # # # # # # # # # #  #  #  #  #  #  #  #  #  #  #  #  #
	//    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22

	// for each loop which check if i is less than the width of the game board.
	for (int i = 0; i < width + 2; i++)
	{
		// print the first wall block.
		cout << "#";
	}

	// Print end line.
	cout << endl;

	// for each loop which check if i is less than the height of the game board.
	for (int i = 0; i < height; i++)
	{
		// for each loop which check if j is less than the width of the game board.
		for (int j = 0; j < width; j++)
		{
			// if j is equal to zero.
			if (j == 0)
			{
				// print the first wall block.
				cout << "#";
			}
			
			// if 
			// i, height is equal to the y, height / 2
			// and
			// j, width is equal to the x, width / 2.
			if (i == y && j == x)
			{
				// print O I.e. the head of the snake.
				cout << "O";
			} 
			// else if 
			// i, height is equal to the fruitY
			// and
			// j, width is equal to the fruitX.
			else if (i == fruitY && j == fruitX)
			{
				// print a fruit.
				cout << "F";
			} else {
				// Initialise a boolean (print) equal to false.
				bool print = false;

				// for each look to check if a fruit has been eaten, 
				// if it has then a new o will be added to the tail.
				for (int k = 0; k < nTail; k++)
				{
					// if 
					// tails k position is equal to j
					// and
					// tails y position is equal to i.
					if (tailX[k] == j && tailY[k] == i)
					{
						// Print a new o onto the tail.
						cout << "o";
						// boolean print is set equal to true.
						print = true;
					}
				}

				// if not currently printing new tail positions then spaces are used.
				if (!print)
				{
					// print a new space.
					cout << " ";
				}
			}
			
			// if j, width is equal to width - 1.
			if (j == width - 1)
			{
				// print a new wall positiojn as it signafies the end of the game board, 
				// see diagram above.
				cout << "#";
			}
		}

		// Print end line.
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
	{
		// prints a wall peice.
		cout << "#";
	}
	// Prints an end line.
	cout << endl;

	// Prints the score underneath the game board.
	cout << "Score: " << score << endl;
}

// Method Input, rtesponsible for all of the inputs from the user.
void Input()
{
	// if _kbhit, if using a key on the keyboard.
	if (_kbhit())
	{
		// switch to get the charactors being pressed.
		switch (_getch())
		{
			// If w is pressed move up the game board.
			case 'w':
				direction = UP;
				break;
			// If a is pressed move accross the game board.
			case 'a':
				direction = LEFT;
				break;
			// If s is pressed move down the game board.
			case 's':
				direction = DOWN;
				break;
			// If d is pressed move accross the game board.
			case 'd':
				direction = RIGHT;
				break;
			// If q is pressed quit the current game.
			case 'q':
				gameOver = true;
				break;
		}
	}
}

// Method Logic, responsible for all of the logic throughout the game.
void Logic()
{
	// int prevX is set equal to the tailX initial position.
	int prevX = tailX[0];
	// int prevY is set equal to the taily initial position.
	int prevY = tailY[0];
	// Initialise int pre2X and prev2Y
	int prev2X, prev2Y;

	// tailX[0] is set equal to the current x position of the head.
	tailX[0] = x;
	// tailY[0] is set equal to the current y position of the head.
	tailY[0] = y;

	// for loop checking if i is equal to the tails length.
	for (int i = 1; i < nTail; i++)
	{
		// set the previouse x coordinate equal to the tails x coordinate of position i.
		prev2X = tailX[i];
		// set the previouse y coordinate equal to the tails y coordinate of position i.
		prev2Y = tailY[i];

		// set the tails x coordinate of position i equal to the previouse x coordinate.
		tailX[i] = prevX;
		// set the tails x coordinate of position i equal to the previouse x coordinate.
		tailY[i] = prevY;

		// set the previouse x position equal to the previouse coordinate of previouse 2 x.
		prevX = prev2X;
		// set the previouse x position equal to the previouse coordinate of previouse 2 x.
		prevY = prev2Y;
	}

	// Switch statement to check which direction the snake is traveling 
	// and adjust the position on the X and Y axis acordingly.
	switch (direction)
	{
		// If UP is detected as the current position, then decrease y.
		case UP:
			y--;
			break;
		// If LEFT is detected as the current position, then decrease x.
		case LEFT:
			x--;
			break;
		// If DOWN is detected as the current position, then increase y.
		case DOWN:
			y++;
			break;
		// If RIGHT is detected as the current position, then increase x.
		case RIGHT:
			x++;
			break;
	}

	// Checks if the snake at any time touches the game walls.
	if (x > width || x < 0 || y > height || y < 0)
	{
		// gameOver equals true.
		gameOver = true;
	}

	// Used to allow the snake to wrap the game board, I.e. will not die if it hits the wall
	// horizontally instead of dying on impact.
	if (x >= width)
	{
		// set x equal to 0.
		x = 0;
	} 

	// if x is less than 0.
	else if (x < 0)
	{
		// set x equal to the width of the game board minus 1.
		x = width - 1;
	}

	// Used to allow the snake to wrap the game board, I.e. will not die if it hits the ceiling or floor
	// vertically instead of dying on impact.
	if (y >= width)
	{
		// set y equal to 0.
		y = 0;
	}

	// if y is less than 0.
	else if (y < 0)
	{
		// set x equal to the width of the game board minus 1.
		y = width - 1;
	}

	// For loop to check if i is equal to nTail I.e. length of the tail.
	for (int i = 0; i < nTail; i++)
	{
		// If the tails x coordinate and the tails y coordinate is equal 
		// to the position of the head coordinate.
		if (tailX[i] == x && tailY[i] == y)
		{
			// gameOver is true as a collision was detected.
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		// Plus 10 on the score.
		score += 10;
		// Sets the spawn for the fruits x position to random devided by the width, ensures it never spawns outside of the game window.
		fruitX = rand() % width;
		// Sets the spawn for the fruits y position to random devided by the height, ensures it never spawns outside of the game window.
		fruitY = rand() % height;

		// Increase the tail size.
		nTail++;
	}
}

// Main
int main()
{
	//Initialize the setup method.
	Setup();

	// while gameOver is not true, I.e. a game is ongoing
	while (!gameOver)
	{
		// Initialise the Draw method.
		Draw();
		// Initialise the Input method.
		Input();
		// Initialise the Logic method.
		Logic();

		// Using the windows library to allow sleep, I.e. slow the game slightly
		// as mentioned in the include notes, this will introduce more flikering in the command line.
		// Sleep(10);
	}
	
	// return 0, I.e. end state.
	return 0;
}