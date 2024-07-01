#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isPos(int moves, vector<int> &nums, vector<int> &changeIndices)
    {
        int n = nums.size();
        int m = changeIndices.size();
        
        vector<int> lastOccurence(n+1, -1);
        for(int i = moves-1; i>=0; i--)
        {
            int ind = changeIndices[i];
            if(lastOccurence[ind] == -1)
            {
                lastOccurence[ind] = i+1;
            }
        }
        
        for(int i = 1; i<=n; i++)
        {
            if(lastOccurence[i] == -1)
                return false;
        }
        
        vector<pair<int,int>> vpr;
        for(int i = 1; i<=n; i++)
        {
            vpr.push_back({lastOccurence[i], i});
        }
        
        sort(vpr.begin(), vpr.end());
        
        
        long long cnt = 0;  
        for(int i = 0; i< vpr.size(); i++)
        {
            int lastInd = vpr[i].first;
            int ind = vpr[i].second;
            int needed = nums[ind-1];
            
            int available = lastInd - 1- cnt;
            if(available >= needed)
            {
                cnt += needed + 1;
            }
            else
                return false;
        }
        
        return true;
    }
    
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size();
        int m = changeIndices.size();
        long long  minNeeded = 0;
        for(int i = 0; i< n ; i++)
        {
            minNeeded += nums[i] + 1;
        }
        
        if(minNeeded > m)
            return -1;
        
        int lo = minNeeded;
        int hi = m;
        // FFFFFTTTTTT, minimum true 
        while(hi - lo > 1)
        {
            int mid = (hi + lo)/2;
            if(isPos(mid, nums, changeIndices))
                hi = mid;
            else
                lo = mid + 1;
        }
        if(isPos(lo, nums, changeIndices))
            return lo;
        if(isPos(hi, nums, changeIndices))
            return hi;
        
        return -1;
    }
};

int main() {
    Solution sol;


    vector<int> nums1 = {2, 2, 0};
    vector<int> changeIndices1 = {2, 2, 2, 2, 3, 2, 2, 1};
    cout << "Example 1: " << sol.earliestSecondToMarkIndices(nums1, changeIndices1) << endl; // Output: 8

    vector<int> nums2 = {1, 3};
    vector<int> changeIndices2 = {1, 1, 1, 2, 1, 1, 1};
    cout << "Example 2: " << sol.earliestSecondToMarkIndices(nums2, changeIndices2) << endl; // Output: 6

    vector<int> nums3 = {0, 1};
    vector<int> changeIndices3 = {2, 2, 2};
    cout << "Example 3: " << sol.earliestSecondToMarkIndices(nums3, changeIndices3) << endl; // Output: -1

    return 0;
}
