#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
#include <gtest/gtest.h>
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
  mutex mutex_;
  int requestsPerWindow;
  int windowSizeInSeconds;
  unordered_map<string, User *> userMap;

public:
  FixedWindowStrategy(int requestPerWindow, int windowSizeInSeconds) {
    this->requestsPerWindow = requestPerWindow;
    this->windowSizeInSeconds = windowSizeInSeconds;
  }
  bool allow(string userId) {
    lock_guard<mutex> lock(mutex_);
    if (!userMap.count(userId)) {
      userMap[userId] = new User(userId);
    }

    auto epoch = chrono::system_clock::now().time_since_epoch();
    int currWindow = chrono::duration_cast<chrono::seconds>(epoch).count() /
                     windowSizeInSeconds;

    auto user = userMap[userId];

    if (user->window != currWindow) {
      user->window = currWindow;
      user->requestProcessed = 0;
    }

    if (user->requestProcessed >= requestsPerWindow) {
      return false;
    }

    ++user->requestProcessed;
    return true;
  }
};

TEST(FixedWindowStrategyTest, UserLimitTest) {
  RateLimiterStrategy *r = new FixedWindowStrategy(4, 10);
  string userId = "user1";
  int requestCount = 5;
  int requestProcessed = 0;
  for (int i = 0; i < requestCount; i++) {
    if (r->allow(userId)) {
      requestProcessed++;
    }
  }
  EXPECT_EQ(4, requestProcessed);
}

// To enable this testcase remove DISABLE_ prefix from test name
TEST(FixedWindowStrategyTest, DISABLED_WindowResetTest) {
  RateLimiterStrategy *r = new FixedWindowStrategy(4, 10);
  string userId = "user1";
  int requestCount = 9;
  int requestProcessed = 0;
  for (int i = 0; i < 4; i++) {
    if (r->allow(userId)) {
      requestProcessed++;
    }
  }
  this_thread::sleep_for(chrono::seconds(10));
  for (int i = 4; i < requestCount; i++) {
    if (r->allow(userId)) {
      requestProcessed++;
    }
  }
  EXPECT_EQ(8, requestProcessed);
}

TEST(FixedWindowStrategyTest, RequestFromMultipleThreadsTest) {
  int t = 10000;
  while (t-- > 0) {
    RateLimiterStrategy *r = new FixedWindowStrategy(4, 10);
    string userId = "user1";

    vector<thread> threads;
    int numberOfRequests = 8;
    atomic<int> numberOfRequestsAllowed = 0;
    for (int i = 0; i < numberOfRequests; i++) {
      threads.emplace_back(([&] {
        if (r->allow(userId)) {
          numberOfRequestsAllowed++;
        }
      }));
    }

    for (int i = 0; i < numberOfRequests; i++) {
      threads[i].join();
    }

    ASSERT_EQ(4, numberOfRequestsAllowed);
  }
}
