// Copyright 2025 ADS-7.2

#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "train.h"

int main() {


  const int max_n = 2000;
  const int step = 100;
  std::mt19937 rng(42);

  std::cout << "n,scenario,op_count,time_micro\n";
  for (int n = step; n <= max_n; n += step) {
    {
      ads7::Train train;
      for (int i = 0; i < n; ++i) {
        train.addCar(false);
      }
      auto start = std::chrono::high_resolution_clock::now();
      int len = train.getLength();
      auto end = std::chrono::high_resolution_clock::now();
      long long duration =
          std::chrono::duration_cast<std::chrono::microseconds>(end - start)
              .count();
      std::cout << n << ",off," << train.getOpCount() << "," << duration
                << "\n";
    }

    {
      ads7::Train train;
      for (int i = 0; i < n; ++i) {
        train.addCar(true);
      }
      auto start = std::chrono::high_resolution_clock::now();
      int len = train.getLength();
      auto end = std::chrono::high_resolution_clock::now();
      long long duration =
          std::chrono::duration_cast<std::chrono::microseconds>(end - start)
              .count();
      std::cout << n << ",on," << train.getOpCount() << "," << duration
                << "\n";
    }

    {
      ads7::Train train;
      for (int i = 0; i < n; ++i) {
        bool light = (rng() & 1);
        train.addCar(light);
      }
      auto start = std::chrono::high_resolution_clock::now();
      int len = train.getLength();
      auto end = std::chrono::high_resolution_clock::now();
      long long duration =
          std::chrono::duration_cast<std::chrono::microseconds>(end - start)
              .count();
      std::cout << n << ",rand," << train.getOpCount() << "," << duration
                << "\n";
    }
  }

  return 0;
}
