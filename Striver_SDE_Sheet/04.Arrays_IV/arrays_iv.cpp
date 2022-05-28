// =====================================================================================================================================
/*
Question List :: Day 3 :: Arrays IV
1) Leetcode 1. Two Sum :: https://leetcode.com/problems/two-sum/
2) **Leetcode 18. 4Sum :: https://leetcode.com/problems/4sum/
3) *Leetcode 128. Longest Consecutive Sequence :: https://leetcode.com/problems/longest-consecutive-sequence/
4) *GFG : Largest subarray with 0 sum ::https://practice.geeksforgeeks.org/problems/largest-subarray-with-0-sum/1#
5) *https://www.interviewbit.com/problems/subarray-with-given-xor/
6) **Leetcode 3. Longest Substring Without Repeating Characters :: https://leetcode.com/problems/longest-substring-without-repeating-characters/
 

*/
// =====================================================================================================================================
#include <bits/stdc++.h>
using namespace std;
// =====================================================================================================================================
// Leetcode 1. Two Sum :: https://leetcode.com/problems/two-sum/
// Approach 1: efficient one : using maps : O(n)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // using map : O(n log n) (since maps internally take log n time for searching & insertion)
        int i,j,n=nums.size();
        map<int,int> m;
        for(i=0;i<n;i++){
            if(m.find(target-nums[i])!=m.end()){
                return {i,m[target-nums[i]]};
            }
            else m[nums[i]]=i;
        }
        //non-functional return
        return {-1,-1};
    }
};
// =====================================================================================================================================
// Leetcode 18. 4Sum :: https://leetcode.com/problems/4sum
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        // Fix first 2 pointers and use 2Sum soln : O(n^3) ?
        int i,j,k,left,right,remain,n=nums.size(),curr,a,b;
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        for(i=0;i<n-3;i++){
            for(j=i+1;j<n-2;j++){
                remain = target - nums[i] - nums[j];//new target for 2sum
                // cout<<remain<<" ";
                left=j+1,right=n-1;
                
                while(left<right){
                    curr=nums[left]+nums[right];
                    if(curr>remain) right--;
                    else if(curr==remain){
                        ans.push_back({nums[i],nums[j],nums[left],nums[right]});
                        a=nums[left],b=nums[right];
                        while(left<right && nums[left+1]==a) left++;//to avoid duplicates
                        while(left<right && nums[right-1]==b) right--;//to avoid duplicates
                        left++,right--;
                    } 
                    else if(curr<remain) left++;
                }
                a = nums[j];
                while(j+1<n && nums[j+1]==a) j++;//to avoid duplicates
            }
            a=nums[i];
            while(i+1<n && nums[i+1]==a) i++;//to avoid duplicates
        }
        return ans;
    }
};
/*
i/p:
[-3,-2,-1,0,0,1,2,3]
0

o/p:
[[-3,-2,2,3],[-3,-1,1,3],[-3,0,0,3],[-3,0,1,2],[-2,-1,0,3],[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
*/
// =====================================================================================================================================
// 3) Leetcode 128. Longest Consecutive Sequence :: https://leetcode.com/problems/longest-consecutive-sequence
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        /*
        Approach 1: using set
        - store nums in set data structure
        - each time you visit an element mark(/remove) all the consequtive elements for that component (i.e. belonging to same consequtive element's sequence )
        - keep a count of no of elements in the component & keep updating global max component size 
        */
        set<int> s;
        for(auto x:nums){
            s.insert(x);
        }
        int ans=0,tem,j;
        for(auto x:s){
            tem=1,j=x;
            // visit and mark(by deleleting) consequtive elements greater than x (i.e: x+1,x+2,...)
            while(s.find(j+1)!=s.end()){
                s.erase(j+1);// stop accounting for it again 
                j++,tem++;                
            }
            
            // visit and mark(by deleleting) consequtive elements less than x (i.e: x-1,x-2,...)
            j=x;
            while(s.find(j-1)!=s.end()){
                s.erase(j-1);// stop accounting for it again 
                j--,tem++;
            }
            
            s.erase(x);// stop accounting for it again 
            ans=max(ans,tem);
        }
        return ans;
        
        /* 
        Approach 2: union find 
         - edge bw any nodes with differce=1 
         - finding the size of largest component
        */
    }
};
// =====================================================================================================================================
// 4) GFG : Largest subarray with 0 sum ::https://practice.geeksforgeeks.org/problems/largest-subarray-with-0-sum/1#

// { Driver Code Starts
//Initial Template for C++
#include <bits/stdc++.h>
using namespace std;
 // } Driver Code Ends
/*You are required to complete this function*/
class Solution{
    public:
    int maxLen(vector<int>&A, int n)
    {   
        // sum=0 => prefix_sum array has same value at different indexes 
        // find max index difference of each such sum
        map<int,int> m;//{sum,start_idx}
        int ans=0,curr,sum=0;
        
        //edge case (can be handles with if-else also)
        m[0]=-1;// if at any point we get prefix_sum as 0 => that will automaticcaly be the current max length subarray
        
        for(int i=0;i<n;i++){
            sum+=A[i];//stores sum 0...i
            if(m.find(sum)==m.end()){
                m[sum]=i;//insert start_idx at first occurence of that sum
            }
            else{
                ans=max(ans,i-m[sum]);// find length of cu
            }
        }
        return ans;
    }
};
/*
A         : -1  0  1
prefix_sum: -1 -1  0

A         : 11  1  -1
prefix_sum: 11  12 11

*/
// { Driver Code Starts.
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int m;
        cin>>m;
        vector<int> array1(m);
        for (int i = 0; i < m; ++i){
            cin>>array1[i];
        }
        Solution ob;
        cout<<ob.maxLen(array1,m)<<endl;
    }
    return 0; 
}
  // } Driver Code Ends
// =====================================================================================================================================
// 5) https://www.interviewbit.com/problems/subarray-with-given-xor/

int Solution::solve(vector<int> &A, int B) {
    map<int,int> m;//{xor,count}
    int n=A.size(),i,j,curr,need,ans=0,prefix_xor=0;
    for(i=0;i<n;i++){
        prefix_xor^=A[i];
        if(prefix_xor==B){
            ans++;
            if(m.find(0)!=m.end()){
                ans+=m[0];
            }
            if(A[0]==0) ans--;            
        } 
        else{
            // find ans for this using map count
            if(m.find(prefix_xor^B)!=m.end()){
                ans+=m[prefix_xor^B];
            }
        }
        m[prefix_xor]++;//already in sorted order insert hoga
    }
    return ans;
}

// =====================================================================================================================================
// 6) Leetcode 3. Longest Substring Without Repeating Characters :: https://leetcode.com/problems/longest-substring-without-repeating-characters/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // two pointers/sliding window approach
        int left,right,i,j,ans=0,n=s.length();
        map<char,int> m;// set??
        //"...aa" => left = m[s[i]]+1 
        //"dsxa...a" => m[s[i]]+1 
        
        for(i=0,left=0;i<n;i++){
            if(m.find(s[i])!=m.end()){
                left=max(m[s[i]]+1,left);//max bcaz if out of range then no need to change left             
            }
            ans=max(ans,i-left+1);
            // cout<<ans<<" : "<<i<<" - "<<left<<"\n";
            m[s[i]]=i;
        }
        return ans;
    }
};
// =====================================================================================================================================
