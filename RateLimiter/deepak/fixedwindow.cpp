#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
#include <thread>
#include <unordered_map>
using namespace std;

class RateLimiterStrategy {
public:
  virtual bool allow(string userId) = 0;
};

struct User {
  string userId;
  int window = 0;
  int requestProcessed = 0;
  User(string userId) { this->userId = userId; }
};

class FixedWindowStrategy : public RateLimiterStrategy {
private:
  int requestsPerWindow;
  int windowSizeInSeconds;
  unordered_map<string, User *> userMap;

public:
  FixedWindowStrategy(int requestPerWindow, int windowSizeInSeconds) {
    this->requestsPerWindow = requestPerWindow;
    this->windowSizeInSeconds = windowSizeInSeconds;
  }
  bool allow(string userId) {
    if (!userMap.count(userId)) {
      userMap[userId] = new User(userId);
    }

    auto epoch = chrono::system_clock::now().time_since_epoch();
    int currWindow = chrono::duration_cast<chrono::seconds>(epoch).count() /
                     windowSizeInSeconds;

    auto user = userMap[userId];

    cout << "User - " << userId << " ,currWindow: " << currWindow
         << " , User window - " << user->window << "\n";
    if (user->window != currWindow) {
      user->window = currWindow;
      user->requestProcessed = 0;
    }

    cout << " User requestProcessed: " << user->requestProcessed << "\n";

    if (user->requestProcessed >= requestsPerWindow) {
      return false;
    }

    ++user->requestProcessed;
    return true;
  }
};

int main() {
  RateLimiterStrategy *r = new FixedWindowStrategy(4, 10);
  string userId = "user1";
  string userId2 = "user2";
  assert(r->allow(userId));
  assert(r->allow(userId2));
  assert(r->allow(userId));
  assert(r->allow(userId2));
  assert(r->allow(userId));
  assert(r->allow(userId2));
  assert(r->allow(userId));
  assert(!r->allow(userId));

  std::this_thread::sleep_for(chrono::seconds(10));
  assert(r->allow(userId));
  assert(r->allow(userId2));
  assert(r->allow(userId2));
  assert(r->allow(userId2));
  assert(r->allow(userId2));
  assert(!r->allow(userId2));
}
