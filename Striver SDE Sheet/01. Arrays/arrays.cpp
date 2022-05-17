// ==================================================================================================
/*
Question List :: Day 1 :: Arrays
1) *Leetcode 73. Set Matrix Zeroes :: https://leetcode.com/problems/set-matrix-zeroes/
2) Leetcode 118. Pascal's Triangle :: https://leetcode.com/problems/pascals-triangle/
3) *Leetcode 31. Next Permutation :: https://leetcode.com/problems/next-permutation/
4) Leetcode 53. Maximum Subarray:: https://leetcode.com/problems/maximum-subarray/
5) *Leetcode 75. Sort Colors :: https://leetcode.com/problems/sort-colors/
6) Leetcode 121. Best Time to Buy and Sell Stock :: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
*/
// ==================================================================================================
#include <bits/stdc++.h>
using namespace std;
// ==================================================================================================
// 1) Leetcode 73. Set Matrix Zeroes :: https://leetcode.com/problems/set-matrix-zeroes/
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool row_zero=false,col_zero=false;
        //to check if first row contains 0 , first col contains 0
        //if they contain=> they will at last be filled by 0's other wise not
        int n,m,i,j;
        n=matrix.size(),m=matrix[0].size();
        
        //check if first_col is to be made 0 in the end
        for(i=0;i<n;i++){
            if(matrix[i][0]==0){
                col_zero = true; break;
            }
        }
        //check if first_row is to be made 0 in the end
        for(j=0;j<m;j++){
            if(matrix[0][j]==0){
                row_zero = true; break;
            }
        }
        
        //set which row or col need to be made 0 (in first row & column of matrix itself)
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                if(matrix[i][j]==0) matrix[i][0]=matrix[0][j]=0;
            }
        }
        
        // set new 0's
        for(i=1;i<n;i++){
            for(j=1;j<m;j++){
                if(matrix[i][0]==0 || matrix[0][j]==0) matrix[i][j]=0;
            }
        }
        
        // set first row/col 0 
        if(row_zero){
            for(i=0;i<m;i++) matrix[0][i]=0;
        }
        if(col_zero){
            for(i=0;i<n;i++) matrix[i][0]=0;
        }       
    }
};
/*
Note: the trick here is to not get fooled by the newly filled 0's / differentiate bw a newly filled 0 & an old 0

Approach 1: Auxillary Space = O(m+n)
- store x & y co-ordinates in 2 seperate arrays ,or, sets         
- iterate over set of x & make all elements in that row as 0
- do the same for y (columns)

Approach 2: Auxillary Space = O(1)
- the idea remains the same as above, just that instead of using extra space for storing row & column containing 0's we store that info in the first row and first column of the matrix itself
- but there's a catch, what if there's a 0 in either 1st row or 1st column itself ??
- to tackle that we use 2 variables as flags to check if first row/col containg 0's , if yes then at last the first row/col get replaced with 0's

*/
// ==================================================================================================
// 2) Leetcode 118. Pascal's Triangle :: https://leetcode.com/problems/pascals-triangle/
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        int i,j,n=numRows;
        vector<vector<int>> v(n);
        v[0]={1};
        for(i=1;i<n;i++){
            vector<int> t(i+1,1);
            for(j=1;j<i;j++){
                t[j]=v[i-1][j]+v[i-1][j-1];
            }
            v[i]=t;
        }
        return v;
    }
};
// simple brute force kinda soln only
// ==================================================================================================
// 3) Leetcode 31. Next Permutation :: https://leetcode.com/problems/next-permutation/

//Soln 1:
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int left=-1,right=-1,i,j,n=nums.size();
        //below code can be optimized
        for(i=n-2;i>=0 && left==-1;i--){
            for(j=n-1;j>i;j--){
                if(nums[j]>nums[i]){ 
                    left=i,right=j;
                    break;
                }
            }
        }
        
        if(left==-1){
            sort(nums.begin(),nums.end());// sorted in desc => next is asc order sort permuatation
            return;
        }
        
        // swap left & right index elements
        nums[left]=nums[left]+nums[right];
        nums[right]=nums[left]-nums[right];
        nums[left] = nums[left]-nums[right];
        
        // reverse elements to the right of left idx
        sort(nums.begin()+left+1,nums.end());
                          
    }
};
/*
1 4 2 2 1  -> 21124
^     ^
2 1 1 2 4
    ^ ^
2 1 2 1 4
      ^ ^
      4 1

Algo:
- start traversing from right: find a no to their irght which is greater than current element
- swap the greater element & current ewlement's position and sort the array from i+1...n-1 
- if no such element found => sort whole array and return 
- (will reverse work, in place of sort, if yes : why?? -> ans -> yes it will work, think on WHY?)
*/

//Sol 2: (same algo but better implementation & tricks/observations used)
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int peak=-1,i,j,n=nums.size(),gtr;
        //right to left jo ascending order break krra h wo find krna , let its index = k
        for(i=n-1;i>0;i--){
            if(nums[i]>nums[i-1]){
                peak=i-1; break;
            }
        }
        // index k does not exist->simply reverse the list , [k=peak]
        if(peak==-1){
            reverse(nums.begin(),nums.end());
            return;
        }      
        // if index k exists 
        // find rightmost element greater than nums[k] ,let its index be p (p>k && nums[p]>nums[k])
        gtr=peak;//this is important as no guarantee is there of gtr element
        for(i=n-1;i>peak;i--){
            if(nums[i]>nums[peak]){
                gtr=i;break;
            }
        }
        //swap eith greater element
        i=nums[gtr];
        nums[gtr]=nums[peak];
        nums[peak]=i;
        // reverse list to the right of index k
        //(as then it will become ascending from left to right => next permutation)
        reverse(nums.begin()+peak+1,nums.end());    
        
        //::Algorithm::
        //right to left jo ascending order break krra h wo find krna , let its index = k
        // if index k does not exist->simply reverse the list , k=peak        
        // else if index k exists 
        // find rightmost element greater than nums[k] ,let its index be p (p>k && nums[p]>nums[k])
        // reverse list to the right of index k
        //(as then it will become ascending from left to right => next permutation)
        
    }
};
// ==================================================================================================
// 4) Leetcode 53. Maximum Subarray:: https://leetcode.com/problems/maximum-subarray/
// Approach 1: normal dp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //recurrence:: 
        // s(i)=max(a[i]+s(i-1),a[i])
        int i,n=nums.size(),ans;
        if(n==0) return 0;
        vector<int> dp(n+1,0);
        dp[0]=ans=nums[0];
        for(i=1;i<n;i++){
            dp[i]=max(nums[i],nums[i]+dp[i-1]);
            ans=max(ans,dp[i]); //keep running maximum of all dp[i] 's
        }
        return ans;
    }
};
//input :: [-2,1,-3,4,-1,2,1,-5,4]
//dp[i] :: -2 1 -2 4 3 5 6 1 5
//ans = max(dp[i]) = 6
//above code can be space optimized -> kandane's algo
// --------------------------------------------------
// Approach 2: space optimized dp (better)
// Kadane's Algo 
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // space-optimized dp : Kadan's Algo
        int i,j,curr=nums[0],prev=nums[0],n=nums.size(),ans=nums[0];
        // prev : max sum subarray(0....i-1) ending at i-1 idx 
        // curr : max sum subarray(0....i) ending at i idx
        for(i=1;i<n;i++){
            curr = max(nums[i]+prev,nums[i]);// max sum ending at i
            ans=max(ans,curr);// keep running max of possible ans
            prev= curr;// reinitializing prev
        }
        return ans;
    }
};

// ==================================================================================================
// 5) Leetcode 75. Sort Colors :: https://leetcode.com/problems/sort-colors/
class Solution {
public:
    void sortColors(vector<int>& nums) {
        //Approach 2 (1 pass soln) (better)
         int red_end,blue_start,n=nums.size(),i;
        red_end=-1,blue_start=n;
        
        // Terminating condition of loop is vvvvv imp************
        for(i=0;i<blue_start;i++){
            if(nums[i]==0){//red
                swap(nums[++red_end],nums[i]);
            }
            else if(nums[i]==2){//blue
                swap(nums[--blue_start],nums[i]);
                i--;// imp:: we have to re-evaluate for swapped i
            }
        }        
        
        
        // Approach 1 (2 pass)
        
        // int red,white,n=nums.size();
        // red=white=0;//r-0,w-1,b-2
        // for(auto x:nums){
        //     red = x==0 ? red+1:red;
        //     white = x==1 ? white+1:white;
        // }
        // for(int i=0;i<n;i++){
        //     if(i<red) nums[i]=0;
        //     else if(i<red+white) nums[i]=1;
        //     else nums[i]=2;
        // }
    }
};
// ==================================================================================================
// 6) 121. Best Time to Buy and Sell Stock :: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // mx[i]= max(prices[i+1...n-1])
        int buy,sell,profit=0,n=prices.size();
        buy=prices[0];
        for(int i=1;i<n;i++){
            profit=max(profit,prices[i]-buy);
            buy=min(buy,prices[i]);
        }
        return profit;
    }
};
// ==================================================================================================

// ==================================================================================================

// ==================================================================================================

// ==================================================================================================

// ==================================================================================================

// ==================================================================================================

// ==================================================================================================

