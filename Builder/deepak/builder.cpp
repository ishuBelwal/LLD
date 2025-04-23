#include <bits/stdc++.h>
using namespace std;

class MainClass {
public:
  string part1;
  string part2;
  MainClass() {}
  ~MainClass() { cout << "Good bye I was the main class" << "\n"; }
};

class MainClassBuilder {
private:
  MainClass _mainClass;

public:
  MainClassBuilder() { _mainClass = MainClass(); }

  MainClassBuilder *part1(string part1) {
    _mainClass.part1 = part1;
    return this;
  }

  MainClassBuilder *part2(string part2) {
    _mainClass.part2 = part2;
    return this;
  }

  MainClass build() { return _mainClass; }
};

int main() {
  MainClassBuilder *mainClassBuilder = new MainClassBuilder();
  mainClassBuilder->part1("random part 1")->part2("random part 2");
  MainClass mainClass = mainClassBuilder->build();
  cout << mainClass.part1 << "\n";
  cout << mainClass.part2 << "\n";
}
