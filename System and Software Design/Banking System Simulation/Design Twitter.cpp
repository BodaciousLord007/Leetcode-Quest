/*
Problem statement: Design Twitter

Design a simplified version of Twitter where users can post tweets,
follow/unfollow another user, and see the 10 most recent tweets in the user's
news feed.

Implement the Twitter class:
- Twitter(): Initializes your twitter object.
- void postTweet(int userId, int tweetId): Composes a new tweet with ID tweetId
  by the user userId. Each call to this function will be made with a unique
  tweetId.
- vector<int> getNewsFeed(int userId): Retrieves the 10 most recent tweet IDs in
  the user's news feed. Each item in the news feed must be posted by users who
  the user followed or by the user themself. Tweets must be ordered from most
  recent to least recent.
- void follow(int followerId, int followeeId): The user with ID followerId
  started following the user with ID followeeId.
- void unfollow(int followerId, int followeeId): The user with ID followerId
  started unfollowing the user with ID followeeId.

Example:
Twitter twitter;
twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5).
twitter.getNewsFeed(1);  // User 1's news feed should return [5].
twitter.follow(1, 2);    // User 1 follows user 2.
twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6).
twitter.getNewsFeed(1);  // User 1's news feed should return [6, 5].
twitter.unfollow(1, 2);  // User 1 unfollows user 2.
twitter.getNewsFeed(1);  // User 1's news feed should return [5].
*/

#include <algorithm>
#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Twitter {
public:
  int time;
  unordered_map<int, deque<pair<int, int>>> postByUser;
  unordered_map<int, unordered_set<int>> followingID;

  Twitter() { time = 0; }

  void postTweet(int userId, int tweetId) {
    postByUser[userId].push_back({time, tweetId});
    time++;

    if (postByUser[userId].size() > 10)
      postByUser[userId].pop_front();
  }

  vector<int> getNewsFeed(int userId) {
    vector<pair<int, int>> choice;

    // Self
    for (auto tweet : postByUser[userId])
      choice.push_back(tweet);

    // Non Self
    for (auto id : followingID[userId]) {
      for (auto tweet : postByUser[id])
        choice.push_back(tweet);
    }

    sort(choice.rbegin(), choice.rend());

    vector<int> ans;

    for (auto [t, tweetID] : choice) {
      ans.push_back(tweetID);
      if (ans.size() == 10)
        break;
    }

    return ans;
  }

  void follow(int followerId, int followeeId) {
    followingID[followerId].insert(followeeId);
  }

  void unfollow(int followerId, int followeeId) {
    followingID[followerId].erase(followeeId);
  }
};

int main() {
  Twitter twitter;

  twitter.postTweet(1, 5); // User 1 posts a new tweet (id = 5)

  // User 1's news feed should return [5]
  vector<int> feed1 = twitter.getNewsFeed(1);
  cout << "[";
  for (size_t i = 0; i < feed1.size(); ++i) {
    if (i > 0)
      cout << ", ";
    cout << feed1[i];
  }
  cout << "]" << endl; // [5]

  twitter.follow(1, 2);    // User 1 follows user 2
  twitter.postTweet(2, 6); // User 2 posts a new tweet (id = 6)

  // User 1's news feed should return [6, 5]
  vector<int> feed2 = twitter.getNewsFeed(1);
  cout << "[";
  for (size_t i = 0; i < feed2.size(); ++i) {
    if (i > 0)
      cout << ", ";
    cout << feed2[i];
  }
  cout << "]" << endl; // [6, 5]

  twitter.unfollow(1, 2); // User 1 unfollows user 2

  // User 1's news feed should return [5]
  vector<int> feed3 = twitter.getNewsFeed(1);
  cout << "[";
  for (size_t i = 0; i < feed3.size(); ++i) {
    if (i > 0)
      cout << ", ";
    cout << feed3[i];
  }
  cout << "]" << endl; // [5]

  return 0;
}

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
