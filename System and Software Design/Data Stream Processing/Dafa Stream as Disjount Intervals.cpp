/*
Problem statement: Data Stream as Disjoint Intervals

Given a stream of non-negative integers, summarize all distinct values seen
so far as sorted, disjoint inclusive intervals. Merge adjacent intervals.

Implement the SummaryRanges class:
- SummaryRanges(): Initialize an empty data stream.
- void addNum(int value): Add value to the stream. Duplicates have no effect.
- vector<vector<int>> getIntervals(): Return the current intervals [start, end]
  sorted by start in ascending order.

Example: Adding 1, 3, 7, 2, 6 produces these successive summaries:
[[1, 1]]
[[1, 1], [3, 3]]
[[1, 1], [3, 3], [7, 7]]
[[1, 3], [7, 7]]
[[1, 3], [6, 7]]
*/

#include <iostream>
#include <iterator>
#include <map>
#include <vector>

using namespace std;

class SummaryRanges {
    map<int, int> intervals;

public:
    SummaryRanges() = default;

    void addNum(int value) {
        auto right = intervals.upper_bound(value);
        auto left = intervals.end();

        if (right != intervals.begin()) {
            left = prev(right);
            if (left->second >= value) return;
        }

        bool joinsLeft = left != intervals.end() &&
                         static_cast<long long>(left->second) + 1 == value;
        bool joinsRight = right != intervals.end() &&
                          static_cast<long long>(value) + 1 == right->first;

        if (joinsLeft && joinsRight) {
            left->second = right->second;
            intervals.erase(right);
        } else if (joinsLeft) {
            left->second = value;
        } else if (joinsRight) {
            int end = right->second;
            intervals.erase(right);
            intervals.emplace(value, end);
        } else {
            intervals.emplace(value, value);
        }
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> result;
        result.reserve(intervals.size());
        for (const auto& interval : intervals) {
            result.push_back({interval.first, interval.second});
        }
        return result;
    }
};

int main() {
    SummaryRanges stream;
    vector<int> values = {1, 3, 7, 2, 6};

    for (int value : values) {
        stream.addNum(value);
        auto intervals = stream.getIntervals();

        cout << "[";
        for (size_t i = 0; i < intervals.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << "[" << intervals[i][0] << ", " << intervals[i][1] << "]";
        }
        cout << "]" << endl;
    }

    return 0;
}
