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

  if (!anyOn) {
    countOp = 2 * n;
    return n;
  }

  if (!anyOff) {
    countOp = n * (n + 1);
    return n;
  }

  countOp = 2 * n;
  return n;
}

int Train::getOpCount() {
  return countOp;
}
