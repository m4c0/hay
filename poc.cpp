#pragma leco tool
#define _CRT_SECURE_NO_WARNINGS // Because Windows

import hay;

#include <stdio.h>
#include <stdlib.h>

// Windows-specific usage example
class WSTR {};
using PWSTR = WSTR *;
void CoDelete(PWSTR) {}
void CoSomething(PWSTR *) {}

int main() {
  using file = hay<FILE *, fopen, fclose>;
  fputs("ok", file { "out/test.txt", "w" });

  using pwstr = hay<PWSTR, nullptr, CoDelete>;
  pwstr pw { nullptr };
  CoSomething(pw);

  using malloced = hay<void *, malloc, free>;
  printf("%p\n", static_cast<void *>(malloced { 100 }));

  struct cls { void fn() {} };
  hay<cls *, nullptr, [](cls * n) { delete n; }> obj { new cls() };
  obj->fn();
}
