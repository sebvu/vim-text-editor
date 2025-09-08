#include <ncurses.h>

int main(int argc, char *argv[]) {
  // initialize the screen
  // sets up memory and clears the screen
  initscr();

  int x, y, c;
  x = y = 0;

  move(y, x);
  refresh();

  do {
    c = getch();
    // printw("%d", c);

    switch (c) {
    case 97: // a
      if (x > 0)
        x -= 1;
      break;
    case 119: // w
      if (y > 0)
        y -= 1;
      break;
    case 115: // s
      y += 1;
      break;
    case 100: // d
      x += 1;
      break;
    case 127: // backspace
      delch();
      break;
    default:
      break;
    }
    move(y, x);
    refresh();
  } while (c != 10); // backspace
  endwin();
  // deallocated memory and ends ncurses

  return 0;
}
