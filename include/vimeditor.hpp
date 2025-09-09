#ifndef VIMEDITOR_HPP
#define VIMEDITOR_HPP
#include "ncurses.h"
#include <string>
#include <vector>

class VimEditor {
private:
  static constexpr int MIN_X = 3;
  static constexpr int MIN_Y = 0;
  int curr_x = MIN_X, curr_y = MIN_Y, ch;
  std::vector<std::string> lines = {""};

  void chHandler(char c);

  void renderLines();

  void runWindow();

  void endWindow();

public:
  VimEditor();
  ~VimEditor();
  void loadFile();
  void saveFile();
};

#endif
