#include <iostream>
#include <ostream>
using namespace std;

class AbstractProductA {
public:
  virtual ~AbstractProductA() { cout << "Deleting Product A" << endl; }
  virtual string UsefulFunctionA() const = 0;
};

class ConcreteProductA1 : public AbstractProductA {
public:
  string UsefulFunctionA() const override {
    return "UsefulFunctionA1 for Product - A1";
  }
};

class ConcreteProductA2 : public AbstractProductA {
public:
  string UsefulFunctionA() const override {
    return "UsefulFunctionA2 for Product - A2";
  }
};

class AbstractProductB {
public:
  virtual ~AbstractProductB() { cout << "Deleting Product B" << endl; }
  virtual string UsefulFunctionB() const = 0;
  virtual string AnotherUsefulFunctionB(const AbstractProductA &a) const = 0;
};

class ConcreteProductB1 : public AbstractProductB {
public:
  string UsefulFunctionB() const override {
    return "UsefulFunctionB1 for Product - B1";
  }

  string AnotherUsefulFunctionB(const AbstractProductA &a) const override {
    return "AnotherUsefulFunctionB1 works with " + a.UsefulFunctionA();
  }
};

class ConcreteProductB2 : public AbstractProductB {
public:
  string UsefulFunctionB() const override {
    return "UsefulFunctionB2 for Product - B2";
  }

  string AnotherUsefulFunctionB(const AbstractProductA &a) const override {
    return "AnotherUsefulFunctionB2 works with " + a.UsefulFunctionA();
  }
};

class AbstractFactory {
public:
  virtual ~AbstractFactory() { cout << "Deleting Abstract Factory \n"; }
  virtual AbstractProductA *createProductA() = 0;
  virtual AbstractProductB *createProductB() = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
  AbstractProductA *createProductA() override {
    return new ConcreteProductA1();
  }
  AbstractProductB *createProductB() override {
    return new ConcreteProductB1();
  }
};

class ConcreteFactory2 : public AbstractFactory {
public:
  AbstractProductA *createProductA() override {
    return new ConcreteProductA2();
  }
  AbstractProductB *createProductB() override {
    return new ConcreteProductB2();
  }
};

void clientCode(AbstractFactory *factory) {
  AbstractProductA *productA = factory->createProductA();
  AbstractProductB *productB = factory->createProductB();
  cout << productA->UsefulFunctionA() << endl;
  cout << productB->AnotherUsefulFunctionB(*productA) << endl;
  delete productA;
  delete productB;
}

int main() {
  AbstractFactory *factoryA = new ConcreteFactory1();
  clientCode(factoryA);
  delete factoryA;
  factoryA = new ConcreteFactory2();
  clientCode(factoryA);
  delete factoryA;
  return 0;
}
