#include "vimeditor.hpp"
#include <fstream>

int main(int argc, char *argv[]) {

  VimEditor editor = VimEditor();

  editor.runEditor();

  return 0;
}
