#include "rateLimiter.h"
#include <chrono>
#include <gtest/gtest.h>
#include <string>
#include <thread>
#include <vector>

TEST(RateLimiterTest, SimpleNoRefill) {

  RateLimiterStrategy *r =
      new FixedWindowRateLimiter(10, 4); // 4 requests per 10 seconds
  string userOne = "user1";
  int allowedRequests = 0;
  for (int i = 0; i < 7; ++i) {
    if (r->allow(userOne)) {
      ++allowedRequests;
    }
  }

  EXPECT_EQ(allowedRequests, 4);
}

TEST(RateLimiterTest, SimpleWithWait) {
  RateLimiterStrategy *r =
      new FixedWindowRateLimiter(10, 4); // 4 requests per 10 seconds
  string userOne = "user1";
  int allowedRequests = 0;
  for (int i = 0; i < 7; ++i) {
    if (r->allow(userOne)) {
      ++allowedRequests;
    } else {
      this_thread::sleep_for(chrono::duration(chrono::seconds(10)));
    }
  }

  EXPECT_EQ(allowedRequests, 6);
}

// TO RUN THIS TEST ONLY: ./main --gtest_filter=SimpleWithThreads
// TO Remove thread safety remove lock_guard from fixedWindow.cpp and this test
// will fail
TEST(RateLimiterTest, SimpleWithThreads) {
  int j = 10000;
  while (j--) {
    RateLimiterStrategy *r =
        new FixedWindowRateLimiter(10000, 4); // 4 requests per 10000 seconds
    string userOne = "user1";
    atomic<int> allowedRequests = 0;

    vector<thread> threads;
    for (int i = 0; i < 8; ++i) {
      threads.emplace_back([&]() {
        if (r->allow(userOne)) {
          allowedRequests++;
        }
      });
    }

    for (auto &t : threads) {
      t.join();
    }

    ASSERT_EQ(allowedRequests, 4);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
