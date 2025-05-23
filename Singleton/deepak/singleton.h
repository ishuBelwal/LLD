#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class Singleton {

private:
  static Singleton *pinstance_;
  static mutex mutex_;
  Singleton(const string value) : value_(value) {}

protected:
  string value_;
  static Singleton *singleton_;

public:
  Singleton(Singleton &other) = delete;
  void operator=(const Singleton &) = delete;
  void operator=(Singleton &) = delete;

  static Singleton *GetInstance(const string &value);

  void someBuisnessLogin();
  void value();
};
