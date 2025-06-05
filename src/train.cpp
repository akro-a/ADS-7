// Copyright 2021 NNTU-CS

#include "train.h"
#include <cstddef>

namespace ads7 {

Train::Train() : first_(nullptr), count_op_(0) {}

Train::~Train() {
  if (first_ != nullptr) {
    Car* current = first_->next;
    while (current != first_) {
      Car* next = current->next;
      delete current;
      current = next;
    }
    delete first_;
    first_ = nullptr;
  }
}

void Train::addCar(bool light) {
  Car* new_car = new Car(light);
  if (first_ == nullptr) {
    first_ = new_car;
  } else {
    Car* last = first_->prev;
    last->next = new_car;
    new_car->prev = last;
    new_car->next = first_;
    first_->prev = new_car;
  }
}

int Train::getLength() {
  count_op_ = 0;
  if (first_ == nullptr) {
    return 0;
  }

  int length = 1;
  Car* current = first_->next;
  while (current != first_) {
    ++length;
    ++count_op_;
    current = current->next;
  }
  return length;
}

int Train::getOpCount() const {
  return count_op_;
}

}
