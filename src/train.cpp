//Copyriht 2022 NNTU-CS

#include "train.h"
#include <cstddef>  // для nullptr

// Конструктор: создаём «пустой» поезд
Train::Train() : countOp(0), first(nullptr) {}

// Метод addCar(bool): добавляет один вагон в кольцевой список.
// Если first == nullptr, новый вагон сам на себя указывает.
// Иначе вставляем newCar сразу перед first (в конец цикла).
void Train::addCar(bool light) {
  // Выделяем узел «Car» со значением light
  Car* newCar = new Car;
  newCar->light = light;
  newCar->next = newCar;
  newCar->prev = newCar;

  if (first == nullptr) {
    first = newCar;
  } else {
    // Получим последний вагон (тот, чей next указывает на first)
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

// Метод getLength(): обходит поезда, считая вагоны.
// Каждый раз, когда делаем current = current->next, увеличиваем countOp.
// Возвращаем общее число вагонов. Если поезд пуст, возвращаем 0.
int Train::getLength() {
  countOp = 0;
  if (first == nullptr) {
    return 0;
  }
  // Считаем хотя бы один вагон (first сам по себе)
  int len = 1;
  Car* current = first->next;
  while (current != first) {
    ++len;
    ++countOp;        // учёт шага по next
    current = current->next;
  }
  return len;
}

// Метод getOpCount(): возвращает число переходов, накопленных выше.
int Train::getOpCount() {
  return countOp;
}
