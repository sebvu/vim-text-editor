#include <fstream>
#include <ncurses.h>
#include <vector>

int main(int argc, char *argv[]) {
  // initialize the screen
  // sets up memory and clears the screen
  initscr();
  keypad(stdscr, TRUE); // enable keypad mode on curr window
  noecho();             // doesn't echo clicking random keys

  std::vector<std::string> lines = {"", "", "",
                                    "", "", ""}; // line representations

  int curr_x, curr_y, ch;
  curr_x = 2; // this is col dumb jester
  curr_y = 0; // this is row dumb jester

  move(curr_y, curr_x);
  refresh();

  while ((ch = getch()) != KEY_BTAB) {
    clear(); // clears current window (stdscr)

    // calculating relative line numbers
    for (int i = 0; i < (int)lines.size(); i++) {
      int rel = i - curr_y; // relative line pos
      if (i == curr_y) {
        mvprintw(i, 0, "%2d %s", 0, lines[i].c_str());
      } else {
        mvprintw(i, 0, "%2d %s", abs(rel), lines[i].c_str());
      }
    }

    move(curr_y, curr_x);
    refresh();

    // movement rules
    switch (ch) {
    case KEY_LEFT: // left arrow
      if (curr_x > 2)
        curr_x -= 1;
      break;
    case KEY_UP: // up arrow
      if (curr_y > 0)
        curr_y -= 1;
      break;
    case KEY_DOWN: // down arrow
      curr_y += 1;
      break;
    case KEY_RIGHT: // right arrow
      curr_x += 1;
      break;
    case KEY_BACKSPACE: // backspace
      if (curr_x > 2) {
        curr_x -= 1;
        move(curr_y, curr_x);
        delch();
      }
      break;
    default:
      addch(ch);
      getyx(stdscr, curr_y, curr_x); // update y, x to ncurses' real cursor pos
      break;
    }
  }
  endwin();
  // deallocated memory and ends ncurses

  return 0;
}
