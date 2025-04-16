#include "singleton.h"
#include <chrono>
#include <thread>
using namespace this_thread;

Singleton *Singleton::singleton_ = nullptr;
Singleton *Singleton::pinstance_ = nullptr;

mutex Singleton::mutex_;

Singleton *Singleton::GetInstance(const string &value) {
  if (!pinstance_) {
    mutex_.lock();
    if (!pinstance_) {
      pinstance_ = new Singleton(value);
    }
    mutex_.unlock();
  }
  return pinstance_;
}

void Singleton::value() { cout << " ->" << value_ << endl; }

void Thread(const string &value) {
  sleep_for(chrono::milliseconds(1000));
  Singleton *instance = Singleton::GetInstance(value);
  instance->value();
}

int main() {
  thread t1(Thread, "FOO");
  thread t2(Thread, "BAR");
  t1.join();
  t2.join();
  return 0;
}
