#include <bits/stdc++.h>
using namespace std;

class AbstractProductA {
public:
  virtual ~AbstractProductA() { cout << "Delete Product A \n"; }
  virtual std::string UsefulFunctionA() const = 0;
};

class ConcreateProductA1 : public AbstractProductA {
public:
  string UsefulFunctionA() const {
    return "UsefulFunctionA1 for Product - ProductA1";
  }
};

class ConcreateProductA2 : public AbstractProductA {
public:
  string UsefulFunctionA() const {
    return "UsefulFunctionA2 for Product - ProductA2";
  }
};

class AbstractProductB {
public:
  virtual ~AbstractProductB() { cout << "Delete Product B \n"; }
  virtual string UseFulFunctionB() const = 0;
  virtual string UsefulAnotherFunctionB(const AbstractProductA &a) const = 0;
};

class ConcreateProductB1 : public AbstractProductB {
public:
  string UseFulFunctionB() const {
    return "UserfulFunctionB1 for Product - ProductB1";
  }
  string UsefulAnotherFunctionB(const AbstractProductA &a) const {
    return "UsefulAnotherFunctionB1 works with " + a.UsefulFunctionA();
  }
};

class ConcreateProductB2 : public AbstractProductB {
public:
  string UseFulFunctionB() const {
    return "UserfulFunctionB for Product - ProductB2";
  }
  string UsefulAnotherFunctionB(const AbstractProductA &a) const {
    return "UsefulAnotherFunctionB works with " + a.UsefulFunctionA();
  }
};

class AbstractFactory {
public:
  virtual ~AbstractFactory() { cout << "Delete Abstract Factory \n"; }
  virtual AbstractProductA *createProductA() const = 0;
  virtual AbstractProductB *createProductB() const = 0;
};

class ConcreteAbstractFactory1 : public AbstractFactory {
public:
  ~ConcreteAbstractFactory1() { cout << "Delete Concrete Abstract Factory 1"; }
  AbstractProductA *createProductA() const override {
    return new ConcreateProductA1();
  }
  AbstractProductB *createProductB() const override {
    return new ConcreateProductB1();
  }
};

class ConcreteAbstractFactory2 : public AbstractFactory {
public:
  ~ConcreteAbstractFactory2() { cout << "Delete Concrete Abstract Factory 2"; }
  AbstractProductA *createProductA() const override {
    return new ConcreateProductA2();
  }
  AbstractProductB *createProductB() const override {
    return new ConcreateProductB2();
  }
};

void ClientCode(AbstractFactory &factory) {
  const AbstractProductA *productA = factory.createProductA();
  const AbstractProductB *productB = factory.createProductB();
  cout << productA->UsefulFunctionA() << "\n";
  cout << productB->UsefulAnotherFunctionB(*productA);
  delete productA;
  delete productB;
}

int main() {
  cout << "Starting application with family of products of 1 " << "\n";
  ConcreteAbstractFactory1 factory1;
  ClientCode(factory1);
  cout << "Starting application with family of products of 2 " << "\n";
  ConcreteAbstractFactory2 factory2;
  ClientCode(factory2);
}
