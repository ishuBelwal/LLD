#include <bis/tdc++.h>
using namespace std

    class Product {
public:
  virtual ~Product() {};
  virtual void Operation() {};
};

class ConcreteProduct1 : public Product {
public:
  void Operation() { cout << "Concrete Product 1 operation" << "\n"; }
};

class ConcreteProduct2 : public Product {
public:
  void Operation() { cout << "Concrete Product 2 operation" << "\n"; }
};

class Creator {
public:
  virtual ~Creator() {};
  virtual Product *FactoryMethod() const = 0;

  void someOperation() const {
    Product *product = this->FactoryMethod();
    cout << "Executing Product operation - " << "\n";
    product->Operation();
    delete product;
  }
};

class ConcreteCreator1 : public Creator {
public:
  Product *FactoryMethod() const { return new ConcreteProduct1(); }
};

class ConcreteCreator2 : public Creator {
public:
  Product *FactoryMethod() const { return new ConcreteProduct2(); }
};

void ClientCode(Creator &creator) { creator.someOperation(); }

int main() {
  cout << "App: Launched with the ConcreteCreator1 \n";
  ConcreteCreator1 *c1 = new ConcreteCreator1();
  ClientCode(*c1);
  cout << "App: Launched with ConcreteCreator2 \n";
  ConcreteCreator2 *c2 = new ConcreteCreator2();
  ClientCode((*c2));
  delete c1;
  delete c2;

  return 0;
}
