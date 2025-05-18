// Copyright 2025
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

#include <cstddef>  // std::size_t

// Класс‑решение задачи о «поезде с лампочками».
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

  // Добавить вагон с заданным состоянием лампочки.
  void AddCar(bool light_on) {
    Car* c = new Car{light_on, nullptr, nullptr};
    if (!first_) {
      c->next = c->prev = c;
      first_ = c;
      return;
    }
    Car* tail = first_->prev;
    tail->next = c;
    c->prev = tail;
    c->next = first_;
    first_->prev = c;
  }

  // Вычислить длину поезда; во время работы ведётся счётчик операций.
  std::size_t GetLength() {
    if (!first_) return 0;
    op_count_ = 0;

    // Шаг 1: погасить все лампочки (один полный обход).
    for (Car* cur = first_; /*до возврата*/; cur = cur->next) {
      ++op_count_;
      cur->light = false;
      if (cur->next == first_) break;
    }

    // Шаг 2: ставим «метку» – зажигаем лампочку в первом вагоне.
    first_->light = true;

    // Шаг 3: идём вперёд, пока снова не встретим зажжённую лампочку.
    std::size_t len = 1;
    for (Car* cur = first_->next; !cur->light; cur = cur->next) {
      ++op_count_;
      ++len;
    }
    return len;
  }

  // Получить число сделанных шагов.
  std::size_t GetOpCount() const { return op_count_; }

 private:
  struct Car {
    bool light;
    Car* next;
    Car* prev;
  };

  Car* first_;           // точка входа в кольцо
  std::size_t op_count_; // счётчик операций во время GetLength()

  Train(const Train&) = delete;
  Train& operator=(const Train&) = delete;
};

#endif  // INCLUDE_TRAIN_H_
