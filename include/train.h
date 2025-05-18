// Copyright 2025
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

#include <cstddef>  // std::size_t

class Train {
 public:
  Train() : first_(nullptr), op_count_(0) {}
  ~Train() {
    if (!first_) return;
    auto* cur = first_->next;
    while (cur != first_) {
      auto* next = cur->next;
      delete cur;
      cur = next;
    }
    delete first_;
  }

  // интерфейс, который вызывает main.cpp
  void addCar(bool light_on) { AddCar(light_on); }
  int  getLength()           { return static_cast<int>(GetLength()); }
  int  getOpCount() const    { return static_cast<int>(op_count_);   }

 private:
  struct Car {
    bool light;
    Car* next;
    Car* prev;
  };

  Car* first_;
  std::size_t op_count_;

  void AddCar(bool light_on) {
    Car* c = new Car{light_on, nullptr, nullptr};
    if (!first_) {
      c->next = c->prev = c;
      first_ = c;
      return;
    }
    Car* tail = first_->prev;
    tail->next = c;
    c->prev   = tail;
    c->next   = first_;
    first_->prev = c;
  }

  std::size_t GetLength() {
    if (!first_) return 0;
    op_count_ = 1;            // <‑‑ учитываем «стартовый вход» в первый вагон

    // 1. погасить все лампочки
    for (Car* cur = first_;; cur = cur->next) {
      ++op_count_;
      cur->light = false;
      if (cur->next == first_) break;
    }

    // 2. отметка
    first_->light = true;

    // 3. обход до своей метки
    std::size_t len = 1;
    for (Car* cur = first_->next; !cur->light; cur = cur->next) {
      ++op_count_;
      ++len;
    }
    return len;
  }

  Train(const Train&)            = delete;
  Train& operator=(const Train&) = delete;
};

#endif  // INCLUDE_TRAIN_H_
