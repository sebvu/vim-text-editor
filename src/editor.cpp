#include <fstream>
#include <ncurses.h>
#include <vector>

int main(int argc, char *argv[]) {

  // initialize the screen
  // sets up memory and clears the screen
  initscr();
  keypad(stdscr, TRUE); // enable keypad mode on curr window
  noecho();             // doesn't echo clicking random keys

  constexpr int MIN_X = 3;
  constexpr int MIN_Y = 0;
  int curr_x, curr_y, ch;
  curr_x = MIN_X; // this is col dumb jester
  curr_y = MIN_Y; // this is row dumb jester
  std::vector<std::string> lines = {""};

  do {
    clear(); // clears current window (stdscr)

    // calculating relative line numbers
    for (int i = 0; i < lines.size(); i++) {
      int rel = i - curr_y; // relative line pos
      if (i == curr_y) {
        mvprintw(i, 0, "%2d %s", 0, lines[i].c_str());
      } else {
        mvprintw(i, 0, "%2d %s", abs(rel), lines[i].c_str());
      }
    }

    move(curr_y, curr_x);
    refresh();

    ch = getch();

    // movement rules
    switch (ch) {
    case KEY_LEFT: // left arrow
      if (curr_x > MIN_X)
        curr_x -= 1;
      break;
    case KEY_UP: // up arrow
      if (curr_y > MIN_Y)
        curr_y -= 1;
      break;
    case KEY_DOWN: // down arrow
      if (curr_y < lines.size() - 1)
        curr_y += 1;
      break;
    case KEY_RIGHT: // right arrow
      if (curr_x < lines[curr_y].size() + MIN_X)
        curr_x += 1;
      break;
    case KEY_BACKSPACE: // backspace
      if (curr_x > MIN_X) {
        lines[curr_y].pop_back();
        curr_x -= 1;
        // delch();
      } else if (curr_y > MIN_Y) { // append curr line to prev line. no action
                                   // if at 0th y line
        lines[curr_y - 1] += lines[curr_y];
        lines.erase(lines.begin() + curr_y);
        curr_y -= 1;
      }
      break;
    case '\n': // append new line with enter
      lines.push_back("");
      curr_y += 1;
      curr_x = MIN_X;
      break;
    default:
      // addch(ch);
      lines[curr_y].push_back('a');
      curr_x += 1;
      // getyx(stdscr, curr_y, curr_x); // update y, x to ncurses' real cursor pos
      break;
    }
  } while (ch != KEY_BTAB);

  endwin();
  // deallocated memory and ends ncurses

  return 0;
}
