#include <iostream>
#include <vector>

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;

template<typename T>
struct InfInt {
  InfInt(T x = 0);
  InfInt(const std::vector<T> &);

  struct InfInt operator+(T);
  struct InfInt operator+(struct InfInt&);

  struct InfInt operator*(T);
  struct InfInt operator*(struct InfInt&);

  bool operator<(T);
  bool operator<(struct InfInt&);

  void addAt(uint idx, T x);

  void print() const;

  std::vector<T> parts;
};

template<typename T>
InfInt<T>::InfInt(T x) : parts({x}) {}

template<typename T>
InfInt<T>::InfInt(const std::vector<T> &_parts) : parts(_parts) {}

template<typename T>
struct InfInt<T> InfInt<T>::operator+(T x) {
  struct InfInt<T> res(*this);
  res.addAt(0, x);
  return res;
}

template<typename T>
struct InfInt<T> InfInt<T>::operator+(struct InfInt &other) {
  if (parts.size() < other.parts.size()) // TODO: Is this needed?
    return other + *this;

  struct InfInt<T> res(*this);

  for (uint i = 0; i < other.parts.size(); i++)
    res.addAt(i, other.parts[i]);

  return res;
}

template<typename T>
struct InfInt<T> InfInt<T>::operator*(T x) {
  struct InfInt<T> tmp(x);
  return (*this) * tmp;
}

template<typename T>
struct InfInt<T> InfInt<T>::operator*(struct InfInt &other) {
  struct InfInt<T> res(0);
  for (struct InfInt<T> i(0); i < other; i = i + 1)
    res = res + *this;
  return res;
}

template<typename T>
bool InfInt<T>::operator<(T x) {
  return parts[0] < x && parts.size() == 1;
}

template<typename T>
bool InfInt<T>::operator<(struct InfInt &other) {
  if (parts.size() == other.parts.size()) {
    for (uint i = 0; i < parts.size(); i++) {
      uint idx = parts.size() - i - 1; // Reverse
      if (parts[idx] < other.parts[idx])
        return true;
    }

    return false;
  } else return parts.size() < other.parts.size(); 
}

template<typename T>
void InfInt<T>::addAt(uint idx, T x) {
  if (x == 0) return;
  else if (idx == parts.size()) {
    parts.push_back(x);
    return;
  }

  T y = parts[idx],
    sum = y + x,
    overflow = T(sum < y || sum < x);

  parts[idx] = sum;

  if (overflow != 0)
    addAt(idx + 1, overflow);
}

template<typename T>
void InfInt<T>::print() const {
  for (auto it = parts.rbegin(); it != parts.rend(); ++it)
    std::cout << (ulong)*it << ", "; // NOTE: In base T
  std::cout << std::endl;
}

int main() {
  struct InfInt<uchar> x({255, 255}),
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
