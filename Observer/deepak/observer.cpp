#include <bits/stdc++.h>
using namespace std;

class IObserver {
public:
  virtual ~IObserver() {};
  virtual void OnUpdate(const string &message_from_subject) = 0;
};

class ISubject {
public:
  virtual ~ISubject() {};
  virtual void subscribe(IObserver *i) = 0;
  virtual void unsubscribe(IObserver *i) = 0;
  virtual void Notify() = 0;
};

class Subject : ISubject {
private:
  list<IObserver *> list_observers_;
  std::string message_;

public:
  ~Subject() { cout << "GoodBye, I was the subject \n"; }
  void subscribe(IObserver *i) { list_observers_.push_back(i); }
  void unsubscribe(IObserver *i) { list_observers_.remove(i); }

  void Notify() {
    auto it = list_observers_.begin();
    cout << "Number of observers " << list_observers_.size() << "\n";
    while (it != list_observers_.end()) {
      (*it)->OnUpdate(message_);
      ++it;
    }
  }

  void UpdateMessage(const string updatedMessage) {
    this->message_ = updatedMessage;
    cout << "New message - " << updatedMessage << "\n";
    Notify();
  }
};

class Observer : IObserver {
private:
  static int observers_count_;
  string message_from_subject_;
  Subject &subject_;
  int number_;

public:
  Observer(Subject &subject) : subject_(subject) {
    std::cout << "Hi, I'm the Observer \"" << ++Observer::observers_count_
              << "\".\n";
    this->number_ = Observer::observers_count_;
    this->subject_.subscribe(this);
  }
  virtual ~Observer() { cout << "I was the observer : " << number_ << "\n"; }

  void OnUpdate(const string &messageFromSubject) {
    message_from_subject_ = messageFromSubject;
    cout << "Observer " << this->number_ << " new message received - "
         << this->message_from_subject_ << "\n";
  }

  void removeAsObserver() {
    cout << "Observer " << this->number_ << " unsubscribed " << "\n";
    this->subject_.unsubscribe(this);
  }
};

int Observer::observers_count_ = 0;

void clientCode() {
  Subject *subject = new Subject;
  Observer *observer1 = new Observer(*subject);
  Observer *observer2 = new Observer(*subject);
  Observer *observer3 = new Observer(*subject);
  Observer *observer4;
  Observer *observer5;

  subject->UpdateMessage("Hello World! : D");
  observer3->removeAsObserver();

  subject->UpdateMessage("the weather is hot today! :p");
  observer4 = new Observer(*subject);

  observer2->removeAsObserver();
  observer5 = new Observer(*subject);

  subject->UpdateMessage("My new car is great! ;)");
  observer3->removeAsObserver();

  observer4->removeAsObserver();
  observer1->removeAsObserver();
  observer5->removeAsObserver();
  subject->UpdateMessage("No subscriber for this message");

  delete observer5;
  delete observer4;
  delete observer3;
  delete observer2;
  delete observer1;
  delete subject;
}

int main() {
  clientCode();
  return 0;
}
