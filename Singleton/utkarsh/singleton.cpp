#include "singleton.h"
#include <chrono>
#include <thread>

Singleton *Singleton::singleton = nullptr;
Singleton *Singleton::pinstance_ = nullptr;
mutex Singleton::mutex_;

Singleton *Singleton::GetInstance(string &value) {

  if (Singleton::pinstance_ == nullptr) {
    Singleton::mutex_.lock();
    if (Singleton::pinstance_ == nullptr) {
      Singleton::pinstance_ = new Singleton(value);
    }
    Singleton::mutex_.unlock();
  }

  return Singleton::pinstance_;
}

void Singleton::showValue() { cout << " -> " << value << endl; }

void ThreadFoo(string value) {
  sleep_for(chrono::milliseconds(1000));
  Singleton *singleton = Singleton::GetInstance(value);
  singleton->showValue();
}

int main() {

  thread t1(ThreadFoo, "FOO");
  thread t2(ThreadFoo, "BAR");
  t1.join();
  t2.join();

  return 0;
}
