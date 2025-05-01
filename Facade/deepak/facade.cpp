#include <bits/stdc++.h>
using namespace std;

class Subsytem1 {
public:
  void operation1() { cout << "Subsytem1 operation - 1\n"; }
  void operation2() { cout << "Subsytem1 operation - 2\n"; }
};

class Subsytem2 {
public:
  void operation1() { cout << "Subsytem2 operation - 1\n"; }
  void operation2() { cout << "Subsytem2 operation - 2\n"; }
};

class Facade {
private:
  Subsytem1 *_subsystem1;
  Subsytem2 *_subsystem2;

public:
  Facade(Subsytem1 *subsytem1, Subsytem2 *subsytem2) {
    this->_subsystem1 = subsytem1 ? subsytem1 : new Subsytem1();
    this->_subsystem2 = subsytem2 ? subsytem2 : new Subsytem2;
  }

  void doFacadeOpeartion1() {
    cout << "Facade opartion 1 \n";
    _subsystem1->operation1();
    _subsystem2->operation2();
  }

  void doFacadeOpeartion2() {
    cout << "Facade opartion 2 \n";
    _subsystem2->operation1();
    _subsystem1->operation2();
  }
};

int main() {
  Subsytem1 *sub1 = new Subsytem1();
  Subsytem2 *sub2 = new Subsytem2();
  Facade facade = Facade(sub1, sub2);
  facade.doFacadeOpeartion1();
  facade.doFacadeOpeartion2();
  delete sub1;
  delete sub2;
}
