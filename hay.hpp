#pragma once

template<typename T, auto C = nullptr, auto D = nullptr>
class hay {
  T m_t;

public:
  constexpr hay(auto &&... args) : m_t { (*C)(args...) } {}
  constexpr ~hay() { (*D)(m_t); }

  constexpr hay(const hay &) = delete;
  constexpr hay & operator=(const hay &) = delete;

  constexpr hay(hay && o) : m_t { o.m_t } { o.m_t = T {}; }
  constexpr hay & operator=(hay && o) {
    (*D)(m_t);
    m_t = o.m_t;
    o.m_t = T {};
    return *this;
  }

  constexpr auto & data(this auto && self) { return self.m_t; }

  constexpr operator       T &()       { return m_t; }
  constexpr operator const T &() const { return m_t; }
  constexpr operator       T *()       { return &m_t; }
  constexpr operator const T *() const { return &m_t; }

  constexpr auto & operator->(this auto && self) { return self.m_t; }
};
template<typename T, auto D>
struct hay<T, nullptr, D> : hay<T, [](T t) { return t; }, D> {
};
template<typename T>
struct hay<T, nullptr, nullptr> : hay<T, nullptr, [](T t) { delete t; }> {
};

template<typename T>
struct hay<T[], nullptr, nullptr> : hay<T *,
  [](unsigned n) { return new T[n] {}; },
  [](T * t) { delete[] t; }> {

  constexpr auto & operator[](this auto && self, unsigned i) { return self.data()[i]; }
};
