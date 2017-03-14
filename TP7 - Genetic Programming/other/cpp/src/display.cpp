#include "display.hpp"

void warning(std::string label) {
  std::cout << BYELLOW << label << NOFOR << std::endl;
}
void alert(std::string label) {
  std::cout << BRED << label << NOFOR << std::endl;
}
void ok(std::string label) {
  std::cout << BGREEN << label << NOFOR << std::endl;
}

void progress(int n, int tot) {
  if (n == tot) {
    std::cout << "\r[====================] (" << tot << "/" << tot << ")"
              << std::endl;
    return;
  }
  std::cout << "\r[";
  for (int i = 0; i < 20; i++) {
    if (i > 20 * double(n) / tot) {
      std::cout << " ";
    } else {
      std::cout << "=";
    }
  }
  std::cout << "] (" << n << "/" << tot << ")" << std::flush;
}
