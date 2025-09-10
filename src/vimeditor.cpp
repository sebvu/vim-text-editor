#include "vimeditor.hpp"
#include "ncurses.h"
#include <algorithm>
#include <string>
#include <vector>

VimEditor::VimEditor() {
  modeActions[Mode::NORMAL] = [this](int c) {
    switch (c) {
    case 104: // h
      if (curr_x > MIN_X)
        curr_x -= 1;
      break;
    case 107: // k
      if (curr_y > MIN_Y) {
        curr_y -= 1;
        curr_x =
            std::min(static_cast<int>(lines[curr_y].size()) + MIN_X, curr_x);
      }
      break;
    case 106: // j
      if (curr_y < static_cast<int>(lines.size()) - 1) {
        curr_y += 1;
        curr_x =
            std::min(static_cast<int>(lines[curr_y].size()) + MIN_X, curr_x);
      }
      break;
    case 108: // l
      if (curr_x < static_cast<int>(lines[curr_y].size()) + MIN_X)
        curr_x += 1;
      break;
    case 105: // i INSERT MODE
      mode = Mode::INSERT;
      break;
    default:
      break;
    }
  };

  modeActions[Mode::INSERT] = [this](int c) {
    switch (c) {
    case 27: // esc NORMAL MODE
      mode = Mode::NORMAL;
      break;
    case KEY_BACKSPACE: // backspace
      if (curr_x > MIN_X) {
        lines[curr_y].erase(lines[curr_y].begin() + curr_x - MIN_X - 1);
        curr_x -= 1;
        // delch();
      } else if (curr_y > MIN_Y) { // append curr line to prev line. no action
                                   // if at 0th y line
        curr_x = static_cast<int>(lines[curr_y - 1].size()) + MIN_X;
        lines[curr_y - 1] += lines[curr_y];
        lines.erase(lines.begin() + curr_y);
        curr_y -= 1;
      }
      break;
    case '\n': {
      std::string appStr =
          lines[curr_y].substr(curr_x - MIN_X, lines[curr_y].size());
      lines[curr_y].erase(curr_x - MIN_X, lines[curr_y].size());
      lines.insert(lines.begin() + curr_y + 1, appStr);
      curr_y += 1;
      curr_x = MIN_X;
      break;
    }
    default:
      lines[curr_y].insert(lines[curr_y].begin() + curr_x - MIN_X, ch);
      curr_x += 1;
      break;
    };
  };
  // modeActions[Mode::COMMAND] = [this](int c) {}
  // modeActions[Mode::VISUAL] = [this](int c) {}

  curr_x = MIN_X;
  curr_y = MIN_Y;
  mode = Mode::NORMAL; // default mode

}; // include file loading later

void VimEditor::chHandler(int c) {

  auto it = modeActions.find(mode);
  if (it != modeActions.end()) {
    it->second(c); // execute mode-specific lambda
  }
}

void VimEditor::renderLines() {
  for (int i = 0; i < static_cast<int>(lines.size()) && i < LINES - 2; i++) {
    int rel = i - curr_y; // relative line pos
    if (i == curr_y) {
      mvprintw(i, 0, "%2d %s", i, lines[i].c_str());
    } else {
      mvprintw(i, 0, "%2d %s", abs(rel), lines[i].c_str());
    }
  }
  mvprintw(LINES - 1, 0, "%s", modeToString(mode).c_str()); // printout mode
}

void VimEditor::runEditor() {
  // initialize the screen
  // sets up memory and clears the screen
  initscr();
  keypad(stdscr, TRUE); // enable keypad mode on curr window
  noecho();             // doesn't echo clicking random keys

  set_escdelay(25); // here as a patch solution for delayed esc press

  do {
    clear(); // clears current window (stdscr)

    renderLines();

    move(curr_y, curr_x);
    refresh();

    ch = getch();
    chHandler(ch);

  } while (ch != KEY_BTAB);
}

void VimEditor::endEditor() { endwin(); }

VimEditor::~VimEditor() {}

void VimEditor::loadFile() {}

void VimEditor::saveFile() {}
