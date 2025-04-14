#include "singleton.h"
using namespace this_thread;

Singleton *Singleton::pinstance_{nullptr};
mutex Singleton::mutex_;

/**
 * Static methods should be defined outside the class.
 */
Singleton *Singleton::GetInstance(const string &value) {
  /**
   * This is a safer way to create an instance. instance = new Singleton is
   * dangeruous in case two instance threads wants to access at the same time
   */
  if (!Singleton::pinstance_) {
    Singleton::mutex_.lock();
    if (!Singleton::pinstance_) {
      Singleton::pinstance_ = new Singleton(value);
    }
    Singleton::mutex_.unlock();
  }
  return Singleton::pinstance_;
}

void Singleton::SomeBusinessLogic() {}

void ThreadFoo() {
  // Following code emulates slow initialization.
  sleep_for(chrono::milliseconds(1000));
  Singleton *singleton = Singleton::GetInstance("FOO");
  cout << singleton->value() << "\n";
}

void ThreadBar() {
  // Following code emulates slow initialization.
  sleep_for(chrono::milliseconds(1000));
  Singleton *singleton = Singleton::GetInstance("BAR");
  cout << singleton->value() << "\n";
}

int main() {
  cout << "If you see the same value, then singleton was reused (yay!\n"
       << "If you see different values, then 2 singletons were created "
          "(booo!!)\n\n"
       << "RESULT:\n";
  thread t1(ThreadFoo);
  thread t2(ThreadBar);
  thread t3(ThreadBar);
  thread t4(ThreadBar);
  thread t5(ThreadBar);
  thread t6(ThreadBar);
  thread t7(ThreadBar);
  thread t8(ThreadBar);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
}
