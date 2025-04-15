#ifndef SINGLETON_H
#define SINGLETON_H

#include <bits/stdc++.h>
#include <mutex>

using namespace std;
using namespace this_thread;
using namespace chrono;

class Singleton {
private:
  static Singleton *pinstance_;
  static mutex mutex_;

protected:
  static Singleton *singleton;
  string value;

public:
  Singleton(string value_) : value(value_) {}

  Singleton(Singleton &other) = delete;
  void operator=(const Singleton &) = delete;
  void showValue();

  static Singleton *GetInstance(string &value);
};

#endif
