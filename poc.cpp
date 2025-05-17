#pragma leco tool

import hay;

#include <stdio.h>

int main() {
  using file = hay<FILE *, fopen, fclose>;

  fputs("ok", file { "out/test.txt", "w" });
}
