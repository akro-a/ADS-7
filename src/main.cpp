// src/main.cpp

#include "train.h"
#include <iostream>
#include <chrono>
#include <random>

// Мы измеряем для n = 100, 200, …, 2000:
//   • getOpCount() – число «шагов» (переходов по next) при подсчёте длины.
//   • «настенные» микросекунды, потраченные на getLength().
// Для каждого n три сценария: “off”, “on”, “rand”.
// Выводим CSV: n,scenario,ops,time_micro

int main() {
  std::mt19937 generator(2025);       // генератор с фиксированным сидом
  std::uniform_int_distribution<int> dist(0, 1);

  const int MAX_N = 2000;
  const int STEP = 100;

  std::cout << "n,scenario,ops,time_micro\n";

  for (int n = STEP; n <= MAX_N; n += STEP) {
    // 1) Сценарий «off»: все лампочки выключены
    {
      Train train;
      for (int i = 0; i < n; ++i) {
        train.addCar(false);
      }
      auto t_start = std::chrono::steady_clock::now();
      int length = train.getLength();
      auto t_end = std::chrono::steady_clock::now();
      auto elapsed = 
        std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
      std::cout << n << ",off," << train.getOpCount() << "," << elapsed << "\n";
    }

    // 2) Сценарий «on»: все лампочки включены
    {
      Train train;
      for (int i = 0; i < n; ++i) {
        train.addCar(true);
      }
      auto t_start = std::chrono::steady_clock::now();
      int length = train.getLength();
      auto t_end = std::chrono::steady_clock::now();
      auto elapsed = 
        std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
      std::cout << n << ",on," << train.getOpCount() << "," << elapsed << "\n";
    }

    // 3) Сценарий «rand»: случайное распределение лампочек
    {
      Train train;
      for (int i = 0; i < n; ++i) {
        bool state = (dist(generator) == 1);
        train.addCar(state);
      }
      auto t_start = std::chrono::steady_clock::now();
      int length = train.getLength();
      auto t_end = std::chrono::steady_clock::now();
      auto elapsed = 
        std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
      std::cout << n << ",rand," << train.getOpCount() << "," << elapsed << "\n";
    }
  }

  return 0;
}
