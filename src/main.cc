#include "infint.hpp"

using T = unsigned char;

int main() {
  struct InfInt<T>
    x({255, 255}),
    y(255);

  x = x + y;
  x.print();

  x = x + 3;
  x.print();

  x = x + 255;
  x.print();

  x = y * 2;
  x.print();

  return 0;
}
