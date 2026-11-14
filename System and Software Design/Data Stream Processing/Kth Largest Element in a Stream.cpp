/*
Problem statement: Kth Largest Element in a Stream

Design a data structure that tracks the kth largest element in a stream of
integers, counting duplicate values as separate elements.

Implement the KthLargest class:
- KthLargest(int k, vector<int>& nums): Initialize with a positive integer k
  and the initial stream values in nums.
- int add(int val): Append val to the stream and return its kth largest value.

Each call to add is guaranteed to leave at least k elements in the stream.
*/

#include <iostream>
#include <set>
#include <vector>

using namespace std;

class KthLargest
{
public:
    multiset<int> st;
    int capacity;
    void balance()
    {
        while (st.size() > capacity)
        {
            st.erase(st.begin());
        }
    }
    KthLargest(int k, vector<int> &nums)
    {
        capacity = k;
        for (auto v : nums)
            st.insert(v);
        balance();
    }

    int add(int val)
    {
        st.insert(val);
        balance();

        return *st.begin();
    }
};

int main() {
    vector<int> nums = {4, 5, 8, 2};
    KthLargest stream(3, nums);

    cout << stream.add(3) << endl;  // 4
    cout << stream.add(5) << endl;  // 5
    cout << stream.add(10) << endl; // 5
    cout << stream.add(9) << endl;  // 8
    cout << stream.add(4) << endl;  // 8

    return 0;
}

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
