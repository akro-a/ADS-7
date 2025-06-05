// Copyright 2025
#ifndef ADS7_TRAIN_H_
#define ADS7_TRAIN_H_

#include <cstddef>

namespace ads7 {

class Train {
 private:
  struct Car {
    bool light;
    Car* next;
    Car* prev;
    Car(bool light_init) : light(light_init), next(this), prev(this) {}
  };

  Car* first_;
  int count_op_;

 public:
  Train();
  ~Train();

  void addCar(bool light);

  int getLength();

  int getOpCount() const;
};

}  

#endif 

