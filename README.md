# Terminal-Based-Snake-Game-In-CPP
A game known as snake written completely in C++, please note this version is in the terminal, although a GUI could be created for it.

For the ability to wrap the game board, I.e. you don't die when hitting the walls, floor or ceiling comment out

// Checks if the snake at any time touches the game walls.
// ! Comment me out to have wrap ability in the game, I.e. you don't die when you hit a wall !
if (x > width || x < 0 || y > height || y < 0)
{
  // gameOver equals true.
  gameOver = true;
}

And uncomment these two statements

// Used to allow the snake to wrap the game board, I.e. will not die if it hits the wall
// horizontally instead of dying on impact.
// ! Comment me out to not have wrap ability in the game, I.e. you die when you hit a wall !
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
// ! Comment me out to not have wrap ability in the game, I.e. you die when you hit a wall !
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

These can all be found in the Logic method between lines 273 and 311.
