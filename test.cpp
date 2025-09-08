
#include <ncurses.h>
#include <string>
#include <vector>

int main() {
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);

  std::vector<std::string> lines = {"Line one",   "Line two",  "Line three",
                                    "Line four",  "Line five", "Line six",
                                    "Line seven", "Line eight"};

  int current_line = 0;
  int ch;

  while ((ch = getch()) != 'q') {
    clear();

    // draw each line with relative numbering
    for (int i = 0; i < (int)lines.size(); i++) {
      int rel = i - current_line; // relative to cursor
      if (i == current_line) {
        attron(A_REVERSE); // highlight current line
        mvprintw(i, 0, "%2d %s", 0, lines[i].c_str());
        attroff(A_REVERSE);
      } else {
        mvprintw(i, 0, "%2d %s", abs(rel), lines[i].c_str());
      }
    }

    // handle navigation
    switch (ch) {
    case KEY_UP:
      if (current_line > 0)
        current_line--;
      break;
    case KEY_DOWN:
      if (current_line < (int)lines.size() - 1)
        current_line++;
      break;
    }
  }

  endwin();
  return 0;
}
