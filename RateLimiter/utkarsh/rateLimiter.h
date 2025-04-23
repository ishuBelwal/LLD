#ifndef RATELIMITER_H
#define RATELIMITER_H

#include <mutex>
#include <string>
#include <unordered_map>
using namespace std;

class RateLimiterStrategy {
public:
  virtual bool allow(string userID) = 0;
};

struct User {
  string userID;
  int requestsProcessed;
  int currentWindow;
  User(string userID_) : userID(userID_) {}
};

class FixedWindowRateLimiter : public RateLimiterStrategy {
private:
  int windowDuration;
  int maximumRequests;
  unordered_map<string, User *> userMap;
  mutex mutex_;

public:
  FixedWindowRateLimiter(int windowDuration_, int maximumRequests_);
  bool allow(string userID);
};

#endif
