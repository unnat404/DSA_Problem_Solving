// ==================================================================================================
#include <bits/stdc++.h>
using namespace std;
// ==================================================================================================
// 1) Leetcode 48. Rotate Image :: https://leetcode.com/problems/rotate-image
class Solution {
public:
// -------------------------------------------------------------------

    /*
     * clockwise rotate
     * first reverse up to down, then swap the symmetry 
     * 1 2 3     7 8 9     7 4 1
     * 4 5 6  => 4 5 6  => 8 5 2
     * 7 8 9     1 2 3     9 6 3
    */
    void rotate(vector<vector<int> > &matrix) {
        reverse(matrix.begin(), matrix.end());
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = i + 1; j < matrix[i].size(); ++j)
                swap(matrix[i][j], matrix[j][i]);
        }
    }
// -------------------------------------------------------------------
    /*
     * anticlockwise rotate
     * first reverse left to right, then swap the symmetry
     * 1 2 3     3 2 1     3 6 9
     * 4 5 6  => 6 5 4  => 2 5 8
     * 7 8 9     9 8 7     1 4 7
    */
    void anti_rotate(vector<vector<int> > &matrix) {
        for (auto vi : matrix) reverse(vi.begin(), vi.end());
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = i + 1; j < matrix[i].size(); ++j)
                swap(matrix[i][j], matrix[j][i]);
        }
    }
// -------------------------------------------------------------------

};

//=====================================================================================================
// 2) Leetcode 56. Merge Intervals :: https://leetcode.com/problems/merge-intervals/

//--------------------------------------------------------------------
// Approach #1 : Graph & connected components 
// Time complexity : O(n^2) , Space : O(n*n)
// https://leetcode.com/problems/merge-intervals/solution/
//--------------------------------------------------------------------
// Approach #2 : Sorting(better) (Implementation #1)
// Time complexity : O(n log n) , Space : O(n)
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<pair<int,int>> v;
        for(auto x:intervals){
            v.push_back({x[0],0});//0:start
            v.push_back({x[1],1});//1:end
        }
        sort(v.begin(),v.end());//sort all points(start & end :: included with marking 0/1)
        // for(auto x:v) cout<<x.first<<" "<<x.second<<"\n";
        int i,open=-1,start,end=-1;
        vector<vector<int>> ans;
        for(i=0;i<v.size();i++){
            if(open==-1 && end<v[i].first){// new interval starts ; 
                // 2nd condition to ensure next interval's start is greater than previous interval's end 
                start = v[i].first;
                open=1;// open -> stores no. of intervals(/braces) opened
            }
            else if(open>=1){
                if(v[i].second==0) open++;// new interval opening found => belongs to same merged interval
                else open--;
                if(open==0){// when no of open braces/intervals = no of close braces/intervals
                    // => this merged interval comes to an end
                    end=v[i].first;
                    open=-1;
                    ans.push_back({start,end});// push merged interval
                }
            }
        }
        return ans;
    }
};

// Approach #2 : Sorting (Implementation #2)
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged;
        for (auto interval : intervals) {
            // if the list of merged intervals is empty or if the current
            // interval does not overlap with the previous, simply append it.
            if (merged.empty() || merged.back()[1] < interval[0]) {
                merged.push_back(interval);
            }
            // otherwise, there is overlap, so we merge the current and previous
            // intervals.
            else {
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }
        return merged;
    }
};
//=====================================================================================================
// 3) Leetcode 88. Merge Sorted Array :: https://leetcode.com/problems/merge-sorted-array
// NOTE: key to the soln is to start filling the numbers from the back, as then there will be no intersection bw 2 elements of nums1
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int a,b,i,j,k;
        i=m+n-1,a=m-1,b=n-1;
        while(a>=0 && b>=0){
            if(nums1[a]>=nums2[b]) nums1[i--]=nums1[a--];
            else nums1[i--]=nums2[b--];
        }
        while(b>=0){
            nums1[i--]=nums2[b--];
        }        
    }
};
/*
This code relies on the simple observation that once all of the numbers from nums2 have been merged into nums1,
the rest of the numbers in nums1 that were not moved are already in the correct place.
*/

/*
[1,4,6,0,0,0]
3
[2,5,6]
3
*/
//=====================================================================================================
// 4) Leetcode 287. Find the Duplicate Number :: https://leetcode.com/problems/find-the-duplicate-number/
/*
Constraints:
1 <= n <= 105
nums.length == n + 1
1 <= nums[i] <= n
All the integers in nums appear only once except for precisely one integer which appears two or more times.
*/

// Approach #1
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        //approach 2: O(n) : simple summation of first n no.s
        int sum=0,n=nums.size();
        for(const auto& x:nums) sum+=x;
        n--;
        return sum-((n*(n+1))/2);
        
        //approach 1: O(n log n) : sort & traversal will do  {for genral constriants[sort + binary search]}
        
        // FOOD FOR THOUGHT: more general approach kya hoga if:  1 <= nums[i] <= n : this cosition is not given 
    }
};

/* 
**NOTE: See Shadab's soln :: https://github.com/Shadab2/SDE_Sheet/blob/master/DAY2/duplicate_number.java

Approach #2 
use 0th index to set all numbers to their respective place

Approach #3
modifying the array so that arr[index] should contains index+1 num , if its'
already there more than once return it

*/
//=====================================================================================================
// 5) https://www.interviewbit.com/problems/repeat-and-missing-number-array/ 
//=====================================================================================================
// 6) https://www.codingninjas.com/codestudio/problems/count-inversions_615
//=====================================================================================================
