// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "train.h"

int main() {
  // Набор размеров поезда, для которых будем проводить эксперимент
  std::vector<int> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

  // Генератор случайных состояний лампочек
  std::mt19937 engine(42);
  std::uniform_int_distribution<int> dist(0, 1);

  // Выводим CSV-заголовок: n, операци_выкл, операци_вкл, операци_случай, время_выкл_ms, время_вкл_ms, время_случай_ms
  std::cout << "n,ops_off,ops_on,ops_rand,time_off_ms,time_on_ms,time_rand_ms\n";

  for (int n : sizes) {
    // случай 1: все лампочки выключены
    Train train_off;
    for (int i = 0; i < n; ++i) {
      train_off.addCar(false);
    }
    auto start_off = std::chrono::high_resolution_clock::now();
    int len_off = train_off.getLength();
    auto end_off = std::chrono::high_resolution_clock::now();
    int ops_off = train_off.getOpCount();
    auto duration_off = std::chrono::duration_cast<std::chrono::milliseconds>(end_off - start_off).count();

    // случай 2: все лампочки включены
    Train train_on;
    for (int i = 0; i < n; ++i) {
      train_on.addCar(true);
    }
    auto start_on = std::chrono::high_resolution_clock::now();
    int len_on = train_on.getLength();
    auto end_on = std::chrono::high_resolution_clock::now();
    int ops_on = train_on.getOpCount();
    auto duration_on = std::chrono::duration_cast<std::chrono::milliseconds>(end_on - start_on).count();

    // случай 3: распределение лампочек случайное
    Train train_rand;
    for (int i = 0; i < n; ++i) {
      bool light = (dist(engine) == 1);
      train_rand.addCar(light);
    }
    auto start_rand = std::chrono::high_resolution_clock::now();
    int len_rand = train_rand.getLength();
    auto end_rand = std::chrono::high_resolution_clock::now();
    int ops_rand = train_rand.getOpCount();
    auto duration_rand = std::chrono::duration_cast<std::chrono::milliseconds>(end_rand - start_rand).count();

    // Выводим одну строчку с результатами для текущего n
    std::cout << n << ","
              << ops_off << "," << ops_on << "," << ops_rand << ","
              << duration_off << "," << duration_on << "," << duration_rand << "\n";
  }

  return 0;
}
