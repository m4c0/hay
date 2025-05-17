#pragma leco tool

import hay;

#include <stdio.h>
#include <stdlib.h>

// Windows-specific usage example
class PWSTR {};
void CoDelete(PWSTR) {}
PWSTR CoAlloc() { return {}; }
void CoSomething(PWSTR) {}

template<typename T> T ident(T t) { return t; }

int main() {
  using file = hay<FILE *, fopen, fclose>;
  fputs("ok", file { "out/test.txt", "w" });

  using pwstr = hay<PWSTR, ident<PWSTR>, CoDelete>;
  CoSomething(pwstr { CoAlloc() });

  using malloced = hay<void *, malloc, free>;
  printf("%p\n", static_cast<void *>(malloced { 100 }));
}
