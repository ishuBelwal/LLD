
#include <iostream>
#include <string>
using namespace std;

class SubSystem1 {
public:
  string initSubsystem() { return "Init SubSystem One"; }

  string executeSubsystem() { return "Executing Sub System One"; }
};

class SubSystem2 {
public:
  string initSubsystem() { return "Init SubSystem Two"; }

  string executeSubsystem() { return "Executing Sub System Two"; }
};

class Facade {
  SubSystem1 *subSytem1_;
  SubSystem2 *subSytem2_;

public:
  Facade(SubSystem1 *subSystem1, SubSystem2 *subSystem2)
      : subSytem1_(subSystem1), subSytem2_(subSystem2) {};

  ~Facade() {
    cout << "Adios Amigo!!" << endl;
    delete subSytem1_;
    delete subSytem2_;
  }

  void operationInit() {
    cout << subSytem1_->initSubsystem() << endl;
    cout << subSytem2_->initSubsystem() << endl;
  }

  void operationExecute() {
    cout << subSytem1_->executeSubsystem() << endl;
    cout << subSytem2_->executeSubsystem() << endl;
  }
};

int main() {
  Facade *facade = new Facade(new SubSystem1(), new SubSystem2());
  facade->operationInit();
  facade->operationExecute();
  delete facade;
  return 0;
}
