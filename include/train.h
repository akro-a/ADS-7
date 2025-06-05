// Copyright 2025
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

#include <cstddef>

class Train {
 private:
  struct Car {
    bool light;
    Car* next;
    Car* prev;
    // Конструктор “по-умолчанию” для нового вагона:
    explicit Car(bool light_init) : light(light_init), next(this), prev(this) {}
  };

  Car* first_;    // “Вход” в замкнутый список вагонов (первый вагон)
  int count_op_;  // Сколько “шагов” (переходов по next) сделал getLength()

 public:
  // Конструктор/деструктор:
  Train();
  ~Train();

  // Добавить один вагон в поезд (lamp = начальное состояние лампочки):
  void addCar(bool lamp);

  // Обойти все вагоны по кругу, посчитать их число.
  // При каждом переходе current = current->next
  // увеличиваем count_op_. Возвращает общее число вагонов.
  int getLength();

  // После вызова getLength() возвращает, сколько раз мы переходили по next;
  // если getLength() не вызывался, возвращает 0.
  int getOpCount() const;
};

#endif  // INCLUDE_TRAIN_H_

