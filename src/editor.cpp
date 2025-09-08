#include <ncurses.h>

int main(int argc, char *argv[]) {
  // initialize the screen
  // sets up memory and clears the screen
  initscr();

  keypad(stdscr, TRUE); // enable keypad mode on curr window

  int x, y, c;
  x = y = 0;

  move(y, x);
  refresh();

  do {
    c = getch();
    // printw("%d", c);

    switch (c) {
    case KEY_LEFT: // left arrow
      if (x > 0)
        x -= 1;
      break;
    case KEY_UP: // up arrow
      if (y > 0)
        y -= 1;
      break;
    case KEY_DOWN: // down arrow
      y += 1;
      break;
    case KEY_RIGHT: // right arrow
      x += 1;
      break;
    case KEY_BACKSPACE: // backspace
      if (x > 0) {
        x -= 1;
        move(y, x);
        delch();
      }
      break;
    default:
      addch(c);
      getyx(stdscr, y, x); // update y, x to ncurses' real cursor pos
      break;
    }
    move(y, x);
    refresh();
  } while (c != 999); // just filler c
  endwin();
  // deallocated memory and ends ncurses

  return 0;
}
