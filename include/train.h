// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
  struct Car {
    bool light;            // состояние лампочки
    Car* next;
    Car* prev;
  };
  int countOp;            // счётчик шагов (переходов по next)
  Car* first;             // указатель на первый вагон в цикле

 public:
  Train();
  void addCar(bool light);   // добавить вагон с начальным состоянием лампочки
  int getLength();           // вычислить длину поезда
  int getOpCount();          // вернуть число переходов (из getLength)
};

#endif  // INCLUDE_TRAIN_H_
