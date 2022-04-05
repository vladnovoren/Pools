#include "pool.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

void TestSpeed() {
  srand(time(NULL));

  std::vector<size_t> to_connect(8000000);
  for (size_t i = 0; i < 8000000; ++i) {
    to_connect[i] = rand() % 12000000;
  }

  Pool::Reserve(12000000);
  std::vector<Pool> pools(12000000);

  for (size_t i = 0; i < 12000000; ++i) {
    pools[i].AddWater(1);
  }

  auto at_begin = std::chrono::steady_clock::now();
  for (size_t i = 0; i < 8000000; ++i) {
    pools[i].Connect(pools[to_connect[i]]);
  }
  auto at_end = std::chrono::steady_clock::now();

  std::chrono::duration<double> dur = at_end - at_begin;
  std::cout << "connect time: " << dur.count() << '\n';
}

void TestPour1() {
  Pool pool1(10), pool2(20), pool3(30);
  assert(pool1.Measure() == 10 && pool2.Measure() == 20 && pool3.Measure() == 30);

  pool1.Connect(pool2);
  assert(pool1.Measure() == 15 && pool2.Measure() == 15 && pool3.Measure() == 30);

  pool2.AddWater(60);
  assert(pool1.Measure() == 45 && pool2.Measure() == 45 && pool3.Measure() == 30);

  pool3.Connect(pool2);
  assert(pool1.Measure() == 40 && pool2.Measure() == 40 && pool3.Measure() == 40);

  pool3.AddWater(30);
  assert(pool1.Measure() == 50 && pool2.Measure() == 50 && pool3.Measure() == 50);
}

void TestPour2() {
  Pool::Reserve(100);
  std::vector<Pool> pools(100);

  for (size_t i = 0; i < 100; ++i) {
    pools[i].AddWater(i);
  }

  for (size_t i = 1; i < 100; ++i) {
    pools[i].Connect(pools[i - 1]);
    if (2 * pools[i].Measure() != i) {
      printf("test pour2 failed\n");
    }
  }
}


int main() {
  TestSpeed();
  TestPour1();
  TestPour2();
  return 0;
}