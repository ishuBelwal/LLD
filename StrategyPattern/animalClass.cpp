#include <iostream>

using namespace std;

class Animal {
protected:
  string name;

public:
  Animal(string n) : name(n) {}
  virtual void speak() = 0;
  virtual void walk() = 0;
  virtual ~Animal() {}
};

class Dog : public Animal {
public:
  Dog() : Animal("") {}
  Dog(string name) : Animal(name) {}
  void speak() override { cout << name << " Dog Barks: woof woof\n"; }
  void walk() override { cout << name << " Dog walks on four legs \n"; }
};

class Duck : public Animal {
public:
  Duck() : Animal("") {}
  Duck(string name) : Animal(name) {}
  void speak() override { cout << name << " Duck Quacks: quack quack \n"; }
  void walk() override { cout << name << " I swim not walk \n"; }
};

class AnimalPlay {
public:
  void speak(Animal *animal) {
    animal->speak();
    cout << endl;
  }

  void walk(Animal *animal) {
    animal->walk();
    cout << endl;
  }
};

int main() {
  AnimalPlay obj;

  while (true) {
    int i;
    cin >> i;
    if (i == 0) {
      break;
    }
    string name;
    cin >> name;

    switch (i) {
    case 1: {
      Animal *dog = new Dog(name);
      obj.speak(dog);
      obj.walk(dog);
      delete dog;
      break;
    }
    case 2: {
      Animal *duck = new Duck(name);
      obj.speak(duck);
      obj.walk(duck);
      delete duck;
      break;
    }
    }
  }
  return 0;
}
