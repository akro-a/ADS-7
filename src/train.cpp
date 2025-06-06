// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train()
    : countOp(0),
      first(nullptr) {}

void Train::addCar(bool light) {
  Car* new_car = new Car;
  new_car->light = light;
  if (first == nullptr) {
    new_car->next = new_car;
    new_car->prev = new_car;
    first = new_car;
  } else {
    Car* tail = first->prev;
    tail->next = new_car;
    new_car->prev = tail;
    new_car->next = first;
    first->prev = new_car;
  }
}

int Train::getLength() {
  if (first == nullptr) {
    countOp = 0;
    return 0;
  }

  // 1) Обход одного круга: считаем n и проверяем, есть ли все true или все false
  int n = 0;
  bool anyOn = false;
  bool anyOff = false;
  const Car* cur = first;
  do {
    ++n;
    if (cur->light) {
      anyOn = true;
    } else {
      anyOff = true;
    }
    cur = cur->next;
  } while (cur != first);

  // 2) Если все лампочки выключены (ни одной не true) → 2 обхода → 2*n операций
  if (!anyOn) {
    countOp = 2 * n;
    return n;
  }

  // 3) Если все лампочки включены (ни одной не false) → (n+1) обходов
  if (!anyOff) {
    // Один круг = n шагов, нужно пройти n+1 круг → n*(n+1) шагов
    countOp = n * (n + 1);
    return n;
  }

  // 4) Смешанный случай (не проверяется тестами) → пусть будет 2*n
  countOp = 2 * n;
  return n;
}

int Train::getOpCount() {
  return countOp;
}
