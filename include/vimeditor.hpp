#ifndef VIMEDITOR_HPP
#define VIMEDITOR_HPP
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class VimEditor {
private:
  static constexpr int MIN_X = 3;
  static constexpr int MIN_Y = 0;
  int curr_x = MIN_X, curr_y = MIN_Y, ch;
  std::vector<std::string> lines = {""};

  struct EnumClassHash {
    template <typename T> std::size_t operator()(T t) const {
      return static_cast<std::size_t>(t);
    }
  };

  enum class Mode { NORMAL, INSERT, COMMAND, VISUAL };

  std::unordered_map<Mode, std::function<void(int)>, EnumClassHash> modeActions;

  Mode mode;
  static std::string modeToString(Mode m) {
    switch (m) {
    case Mode::NORMAL:
      return "NORMAL";
    case Mode::INSERT:
      return "INSERT";
    case Mode::COMMAND:
      return "COMMAND";
    case Mode::VISUAL:
      return "VISUAL";
    default:
      return "UNKNOWN";
    }
  }

  void chHandler(int c);
  void renderLines();

public:
  VimEditor();
  ~VimEditor();
  void runEditor();
  void endEditor();
  void loadFile();
  void saveFile();
};

#endif
