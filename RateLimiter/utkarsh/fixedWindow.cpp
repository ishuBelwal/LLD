#include "rateLimiter.h"
#include <chrono>
#include <mutex>

FixedWindowRateLimiter::FixedWindowRateLimiter(int windowDuration_,
                                               int maximumRequests_)
    : windowDuration(windowDuration_), maximumRequests(maximumRequests_) {}

bool FixedWindowRateLimiter::allow(string userID) {
  lock_guard<mutex> lock_guard(mutex_);

  if (userMap.count(userID) == 0) {
    userMap.insert({userID, new User(userID)});
  }

  auto now = chrono::system_clock::now().time_since_epoch();

  long long window =
      chrono::duration_cast<chrono::seconds>(now).count() / windowDuration;

  if (userMap[userID]->currentWindow != window) {
    userMap[userID]->requestsProcessed = 0;
    userMap[userID]->currentWindow = window;
  }

  if (userMap[userID]->requestsProcessed < maximumRequests) {
    userMap[userID]->requestsProcessed++;
    return true;
  }

  return false;
}
