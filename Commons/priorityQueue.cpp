

#include <functional>
#include <iostream>
#include <ostream>
#include <queue>
#include <random>
#include <vector>
using namespace std;

int generateRandomNumber(int lower, int upper) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(lower, upper);
  return dist(gen);
}

// Min Heap (By Default it's Max Heap)
void MinHeap() {
  priority_queue<int, vector<int>, greater<>> pq;
  for (int i = 0; i < 10; ++i) {
    pq.push(generateRandomNumber(1, 100));
  }
  cout << "Min Heap \n";
  while (!pq.empty()) {
    cout << pq.top() << ' ';
    pq.pop();
  }
  cout << endl;
}

//-----------------------------------------------------------------------------------//
class Person {
public:
  string name;
  int age;

  bool operator<(const Person &p) const {
    return this->name < p.name;
  } // Prefer overloading <
    // If > then use greater<>()
};

class PersonComp {
public:
  bool operator()(const Person &p1, const Person &p2) {
    return p1.age < p2.age;
  }
};

void PQPerson() {
  priority_queue<Person> namePQ; // uses operator<
  priority_queue<Person, vector<Person>, PersonComp>
      agePQ; // uses custom comparator
  namePQ.push(Person{"Utkarsh", 27});
  namePQ.push(Person{"Deepak", 26});
  namePQ.push(Person{"Ashish", 28});
  namePQ.push(Person{"Rahul", 28});
  namePQ.push(Person{"Utkarsh", 29});
  cout << "Persons Max Heap By Name\n";
  while (!namePQ.empty()) {
    cout << namePQ.top().name << ' ' << namePQ.top().age;
    cout << endl;
    namePQ.pop();
  }

  agePQ.push(Person{"Utkarsh", 27});
  agePQ.push(Person{"Deepak", 26});
  agePQ.push(Person{"Ashish", 28});
  agePQ.push(Person{"Rahul", 28});
  agePQ.push(Person{"Utkarsh", 29});
  cout << "Persons Max Heap By Age\n";
  while (!agePQ.empty()) {
    cout << agePQ.top().name << ' ' << agePQ.top().age;
    cout << endl;
    agePQ.pop();
  }
}

int main() {
  MinHeap();
  PQPerson();
  return 0;
}
