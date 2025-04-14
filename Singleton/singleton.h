#include <bits/stdc++.h>
#include <mutex>
using namespace std;
/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class Singleton {

  /**
   * The Singleton's constructor should always be private to prevent direct
   * construction calls with the `new` operator.
   */
private:
  static Singleton *pinstance_;
  static mutex mutex_;

protected:
  Singleton(const std::string value) : value_(value) {}

  static Singleton *singleton_;

  std::string value_;

public:
  /**
   * Singletons should not be cloneable.
   */
  Singleton(Singleton &other) = delete;
  /**
   * Singletons should not be assignable.
   */
  // TODO : not understood the requirement of const yet, working without const
  // as well as per current understanding
  void operator=(const Singleton &) = delete;
  void operator=(Singleton &) = delete;
  /**
   * This is the static method that controls the access to the singleton
   * instance. On the first run, it creates a singleton object and places it
   * into the static field. On subsequent runs, it returns the client existing
   * object stored in the static field.
   */

  static Singleton *GetInstance(const std::string &value);
  /**
   * Finally, any singleton should define some business logic, which can be
   * executed on its instance.
   */
  void SomeBusinessLogic();

  std::string value() const { return value_; }
};
