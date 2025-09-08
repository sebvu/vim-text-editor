#include <ncurses.h>

int main(int argc, char *argv[]) {
  // initializes the screen
  // sets up memory and clears the screen
  initscr();

  int x, y;
  x = y = 2;

  // move cursor to specified move(y, x) position
  move(y, x);

  // prints a string(const char *) to a window
  printw("hellooooo world!");

  // refreshes screen to match what's in memory
  refresh();

  // wait for user input, returns int value of that key
  int c = getch();

  x = y = 10;
  move(y, x);

  printw("value pressed is %d", c);

  getch(); // to make program wait

  endwin();
  // deallocated memory and ends ncurses

  return 0;
}
