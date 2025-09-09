#include "vimeditor.hpp"
#include "ncurses.h"
#include <algorithm>
#include <string>
#include <vector>

VimEditor::VimEditor() {}; // include file loading later

void VimEditor::chHandler(int c) {
  // movement rules
  switch (c) {
  case KEY_LEFT: // left arrow
    if (curr_x > MIN_X)
      curr_x -= 1;
    break;
  case KEY_UP: // up arrow
    if (curr_y > MIN_Y) {
      curr_y -= 1;
      curr_x = std::min(static_cast<int>(lines[curr_y].size()) + MIN_X, curr_x);
    }
    break;
  case KEY_DOWN: // down arrow
    if (curr_y < static_cast<int>(lines.size()) - 1) {
      curr_y += 1;
      curr_x = std::min(static_cast<int>(lines[curr_y].size()) + MIN_X, curr_x);
    }
    break;
  case KEY_RIGHT: // right arrow
    if (curr_x < static_cast<int>(lines[curr_y].size()) + MIN_X)
      curr_x += 1;
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
  case '\n': // append new line with enter
    lines.push_back("");
    curr_y += 1;
    curr_x = MIN_X;
    break;
  default:
    // addch(ch);
    lines[curr_y].insert(lines[curr_y].begin() + curr_x - MIN_X, ch);
    curr_x += 1;
    // getyx(stdscr, curr_y, curr_x); // update y, x to ncurses' real cursor
    // pos
    break;
  }
}

void VimEditor::renderLines() {
  for (int i = 0; i < static_cast<int>(lines.size()); i++) {
    int rel = i - curr_y; // relative line pos
    if (i == curr_y) {
      mvprintw(i, 0, "%2d %s", 0, lines[i].c_str());
    } else {
      mvprintw(i, 0, "%2d %s", abs(rel), lines[i].c_str());
    }
  }
}

void VimEditor::runEditor() {
  // initialize the screen
  // sets up memory and clears the screen
  initscr();
  keypad(stdscr, TRUE); // enable keypad mode on curr window
  noecho();             // doesn't echo clicking random keys

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
