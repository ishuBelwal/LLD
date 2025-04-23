#include <bits/stdc++.h>
#include <cstdio>

using namespace std;

class IObserver {
public:
  virtual ~IObserver() {};
  virtual void OnMessage(string message) = 0;
};

class IPublisher { // aka the Subject
public:
  virtual ~IPublisher() {};
  virtual void subscribe(IObserver *ob) = 0;
  virtual void unSubscribe(IObserver *ob) = 0;
  virtual void Notify() = 0;
};

class Publisher : public IPublisher {
private:
  string name = "Utkarsh";
  list<IObserver *> observerList;
  string message;

public:
  ~Publisher() { cout << "Good Bye I was the Publisher : " << name; }

  void subscribe(IObserver *ob) { observerList.push_back(ob); }

  void unSubscribe(IObserver *ob) { observerList.remove(ob); }

  void Notify() {

    printf("Total %zu Observers to Update.\n", observerList.size());

    for (list<IObserver *>::iterator it = observerList.begin();
         it != observerList.end(); ++it) {
      (*it)->OnMessage(message);
    }
  }

  void onUpdate(string message_) {
    this->message = message_;
    printf("Publisher %s received message %s\n", this->name.c_str(),
           this->message.c_str());
    Notify();
  }
};

class Observer : public IObserver {
private:
  int name_;
  static int nameCounter_;
  Publisher &publisher_;

public:
  ~Observer() { printf("Good Bye I was the observer %d\n", name_); }
  Observer(Publisher &publisher) : publisher_(publisher) {
    this->name_ = nameCounter_++;
    printf("Hi!! I am the new observer %d\n", this->name_);
    publisher_.subscribe(this);
  }

  void OnMessage(string message) {
    printf("Observer %d received message -> %s\n", this->name_,
           message.c_str());
  }
};

int Observer::nameCounter_ = 1;

int main() {
  Publisher *pub = new Publisher();

  Observer *ob1 = new Observer(*pub);
  Observer *ob2 = new Observer(*pub);
  Observer *ob3 = new Observer(*pub);
  Observer *ob4 = new Observer(*pub);
  Observer *ob5;
  Observer *ob6;

  pub->onUpdate("First Message");
  pub->unSubscribe(ob1);
  delete ob1;
  ob5 = new Observer(*pub);
  ob6 = new Observer(*pub);

  pub->onUpdate("Second Message");

  pub->unSubscribe(ob4);
  delete ob4;
  pub->unSubscribe(ob3);
  delete ob3;
  pub->unSubscribe(ob2);
  delete ob2;

  pub->onUpdate("Good Bye Observers!!");

  pub->unSubscribe(ob5);
  delete ob5;
  pub->unSubscribe(ob6);
  delete ob6;

  delete pub;

  return 0;
}
