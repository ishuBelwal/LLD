#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>

using namespace std;

// Sorting in ASCENDING order
void sortingAscending(vector<int> &vec) {
  sort(vec.begin(), vec.end());
  cout << "Sorting in Ascending order\n";
  for (int i : vec) {
    cout << i << ", ";
  }
  cout << endl;
}

// Sorting in DESCENDING order
void sortingDescending(vector<int> &vec) {
  sort(vec.begin(), vec.end(), greater<>());
  cout << "Sorting in Descending order\n";
  for (int i : vec) {
    cout << i << ", ";
  }
  cout << endl;
}

// Generate random integer within a range (>= C++11)
int generateRandomInteger(int lower, int upper) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(lower, upper);
  return dist(gen);
}

// Generate random integer (old style)
int generateRandomIntegerOld(int lower, int upper) {
  srand(time(nullptr));
  int num = rand() % upper + 1 + lower;
  return num;
}

void testSimpleSorting() {
  int n = 10;
  vector<int> vec(10);
  cout << "Original Array\n";
  for (int i = 0; i < 10; ++i) {
    vec[i] = generateRandomInteger(1, 100);
    cout << vec[i] << ", ";
  }
  cout << endl;
  sortingAscending(vec);
  sortingDescending(vec);
}

//-----------------------------------------------------------------------------------//
// Sorting of Class/Structs
class Person {
public:
  string name;
  int age;
};

bool personAgeComparator(const Person &p1, const Person &p2) {
  if (p1.age == p2.age) {
    return p1.name < p2.name;
  }
  return p1.age < p2.age;
}

vector<Person> testClassSorting() {
  vector<Person> persons;
  persons.push_back(Person{"Utkarsh", 27});
  persons.push_back(Person{"Deepak", 26});
  persons.push_back(Person{"Ashish", 28});
  persons.push_back(Person{"Rahul", 28});
  persons.push_back(Person{"Utkarsh", 29});

  sort(persons.begin(), persons.end(), personAgeComparator);
  cout << "Persons after sorting by age(asc)\n";
  for (Person &p : persons) {
    cout << p.age << " " << p.name << endl;
  }

  auto personNameLambda = [](const Person &p1, const Person &p2) {
    if (p1.name == p2.name) {
      return p1.age > p2.age;
    }
    return p1.name > p2.name;
  };

  sort(persons.begin(), persons.end(), personNameLambda);
  cout << "Persons after sorting by name(desc)\n";
  for (Person &p : persons) {
    cout << p.name << " " << p.age << endl;
  }

  return persons;
}

//-----------------------------------------------------------------------------------//
// Using Lower/Upper Bounds

void findPersonLowerBound(vector<Person> &persons, Person person) {
  vector<Person>::iterator itr =
      lower_bound(persons.begin(), persons.end(), person,
                  [](const Person &p1, const Person &p2) {
                    if (p1.name == p2.name) {
                      return p1.age > p2.age;
                    }
                    return p1.name > p2.name;
                  });
  if (itr == persons.end()) {
    persons.push_back(person);
  } else {
    persons.insert(itr, person);
  }
}

void testLowerUpperBoundsClass() {
  vector<Person> persons = testClassSorting();
  findPersonLowerBound(persons, Person{"Tushar", generateRandomInteger(1, 30)});
  findPersonLowerBound(persons, Person{"Aakash", generateRandomInteger(1, 30)});
  findPersonLowerBound(persons, Person{"Zeta", generateRandomInteger(1, 30)});
  findPersonLowerBound(persons, Person{"Utkarsh", 29});
  findPersonLowerBound(persons, Person{"Deepak", 19});
  cout << "Persons after inserting \n";
  for (Person &p : persons) {
    cout << p.name << " " << p.age << endl;
  }
}

int main() {
  testSimpleSorting();
  testLowerUpperBoundsClass();
}
