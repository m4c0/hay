#pragma once

template<typename T, auto C, auto D>
class hay {
  T m_t;

public:
  constexpr hay(auto &&... args) : m_t { (*C)(args...) } {}
  constexpr ~hay() { (*D)(m_t); }

  constexpr hay(const hay &) = delete;
  constexpr hay(hay &&) = delete;
  constexpr hay & operator=(const hay &) = delete;
  constexpr hay & operator=(hay &&) = delete;

  constexpr operator       T  () const { return m_t; }
  constexpr operator       T &()       { return m_t; }
  constexpr operator const T &() const { return m_t; }
  constexpr operator       T *()       { return &m_t; }
  constexpr operator const T *() const { return &m_t; }

  constexpr const T & operator->() const { return m_t; }
  constexpr       T & operator->()       { return m_t; }
};
template<typename T, auto D>
struct hay<T, nullptr, D> : hay<T, [](T t) { return t; }, D> {
};
