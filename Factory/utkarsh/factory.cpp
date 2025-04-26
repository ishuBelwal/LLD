
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

class Pizza { // aka the Product
public:
  virtual ~Pizza() {};
  virtual void bakePizza() = 0;
};

class FarmHousePizza : public Pizza {
  void bakePizza() { cout << "Baking your FarmHouse Pizza" << endl; }
};

class VolcanoCheese : public Pizza {
  void bakePizza() { cout << "Baking your VolcanoCheese Pizza" << endl; }
};

class PaneerPizza : public Pizza {
  void bakePizza() { cout << "Baking your Paneer Pizza" << endl; }
};

class CornPizza : public Pizza {
  void bakePizza() { cout << "Baking your Corn Pizza" << endl; }
};

class PizzaStore { // aka the Creator
public:
  string name;
  virtual ~PizzaStore() {};
  virtual Pizza *createPizza(string name) = 0;
  virtual void printName() {
    printf("Hello! Welcome to %s store\n", name.c_str());
  };

  void orderPizza(string name) {
    Pizza *pizza =
        this->createPizza(name); // this doesn't care about the type of Pizza
                                 // it's decoupled from the product creation
    this->printName();
    pizza->bakePizza();
  }
};

class DominosPizzaStore : public PizzaStore {
public:
  DominosPizzaStore(string name_) { this->name = name_; }
  ~DominosPizzaStore() {
    printf("GoodBye!! %s is closing\n", this->name.c_str());
  }

  Pizza *createPizza(string pizzaName_) {
    if (pizzaName_ == "FarmHouse") {
      return new FarmHousePizza();
    } else if (pizzaName_ == "VolcanoCheese") {
      return new VolcanoCheese();
    }

    return nullptr;
  }
};

class PizzaHutPizzaStore : public PizzaStore {
public:
  PizzaHutPizzaStore(string name_) { this->name = name_; };
  ~PizzaHutPizzaStore() {
    printf("GoodBye!! %s is closing\n", this->name.c_str());
  }

  Pizza *createPizza(string pizzaName_) {
    if (pizzaName_ == "Paneer") {
      return new PaneerPizza();
    } else if (pizzaName_ == "Corn") {
      return new CornPizza();
    }

    return nullptr;
  }
};

int main() {
  PizzaStore *dominosPizzaStore = new DominosPizzaStore("Dominos");
  PizzaStore *pizzaHutPizzaStore = new PizzaHutPizzaStore("PizzaHut");

  dominosPizzaStore->orderPizza("FarmHouse");
  cout << "--------------------------------------------------------------------"
          "---\n";
  pizzaHutPizzaStore->orderPizza("Paneer");
  cout << "--------------------------------------------------------------------"
          "---\n";
  dominosPizzaStore->orderPizza("VolcanoCheese");
  cout << "--------------------------------------------------------------------"
          "---\n";
  delete dominosPizzaStore;
  cout << "--------------------------------------------------------------------"
          "---\n";
  pizzaHutPizzaStore->orderPizza("Corn");
  cout << "--------------------------------------------------------------------"
          "---\n";
  delete pizzaHutPizzaStore;
  cout << "--------------------------------------------------------------------"
          "---\n";

  return 0;
}
