
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Product {
public:
  vector<string> products;
  void showProduts() {
    for (string &s : products) {
      cout << s << ' ' << endl;
    }
    cout << endl;
  }
};

class Builder {
public:
  virtual ~Builder() {};
  virtual void BuildProductA(string s) = 0;
  virtual void BuildProductB(string s) = 0;
  virtual void BuildProductC(string s) = 0;
};

class ConcreteBuilder : public Builder {
private:
  Product *product;

  void reset() { product = new Product(); }

public:
  ConcreteBuilder() { this->reset(); }

  ~ConcreteBuilder() { delete product; }

  void BuildProductA(string s) override {
    product->products.push_back("Part A " + s);
  }

  void BuildProductB(string s) override {
    product->products.push_back("Part B " + s);
  }

  void BuildProductC(string s) override {
    product->products.push_back("Part C " + s);
  }

  Product *getProduct() {
    Product *currentProduct = this->product;
    this->reset();
    return currentProduct;
  }
};

int main() {
  ConcreteBuilder *builder = new ConcreteBuilder();
  builder->BuildProductA("is a MotherBoard");
  builder->BuildProductB("is a RAM");
  builder->BuildProductC("is a GPU");
  Product *product = builder->getProduct();
  product->showProduts();
  return 0;
}
