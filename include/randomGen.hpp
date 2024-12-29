#pragma once
#include <random>

class Randor {
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> distrib;

public:
  Randor() : gen(rd()), distrib(0, 0) {}
  void setX(int x) { distrib = std::uniform_int_distribution<>(0, x); }
  int getRandom() { return distrib(gen); }
};
