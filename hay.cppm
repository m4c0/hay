export module hay;

export {
#include "hay.hpp"
}

module :private;

#pragma clang diagnostic ignored "-Wself-move"

static_assert([] {
  hay<bool *> x { new bool { true } };
  x = static_cast<hay<bool *> &&>(x);
  return *static_cast<bool *>(x);
}());
static_assert([] {
  hay<bool *> x { new bool { true } };
  hay<bool *> y = static_cast<hay<bool *> &&>(x);
  return *static_cast<bool *>(y) && !x.data();
}());
