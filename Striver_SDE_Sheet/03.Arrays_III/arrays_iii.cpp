// =====================================================================================================================================
/*
Question List :: Day 3 :: Arrays III


*/
// =====================================================================================================================================
#include <bits/stdc++.h>
using namespace std;
// =====================================================================================================================================
// 1) Leetcode 74. Search a 2D Matrix :: https://leetcode.com/problems/search-a-2d-matrix

// Approach #1: Binary Search : O(log n + log m) = O(log n*m)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // binary search along both row and column
        int rmid,rl,rh,cmid,cl,ch,i,j,n,m,k;
        n=matrix.size(),m=matrix[0].size();
        rl=0,rh=n-1;
        while(rl<=rh){
            rmid=rl+(rh-rl)/2;
            if(target >= matrix[rmid][0] && target <= matrix[rmid][m-1]){
                cl=0,ch=m-1;
                while(cl<=ch){
                    cmid=cl+(ch-cl)/2;
                    if(target==matrix[rmid][cmid]) return true;
                    else if(target > matrix[rmid][cmid]) cl = cmid+1;
                    else ch=cmid-1;
                }
                return false;
            }
            else if(target < matrix[rmid][0]) rh=rmid-1;
            else rl=rmid+1;
        }
        return false;
    }
};

// Approach #2: BST Observation : O(n) approach [COOL SOLN/ Observation]
class Solution {
public:
    // Soln Inspiration: https://leetcode.com/problems/search-a-2d-matrix/discuss/1895837/C%2B%2B-BINARY-SEARCH-TREE-(**)-Explained-with-IMG
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        /* 
        BST Observation: elements on the left are always smaller than the current element, and elements on           the bottom are always greater. It reminds us of the Binary Search Tree!
        Assume: matrix[0][m-1] as root 
        - left child           : matrix[0][(m-1)-1] is always less than the root
        - right(/bottom) child : matrix[0+1][m-1] is always greater than the root       
        Use this property/observation to now traverse the matrix likein a BST to find the element
        */
        
        int i,j,n=matrix.size(),m=matrix[0].size();
        i=0,j=m-1;//root index
        while( i<n && j>=0 ){
            if(target==matrix[i][j]) return true;
            else if(target > matrix[i][j]) i++;
            else j--;
        }
        return false;
    }
};
// =====================================================================================================================================
// 2) Leetcode 50. Pow(x, n) :: Leetcode https://leetcode.com/problems/powx-n/
// Power Exponentiation + Take care of out of bound for -ve powers
class Solution {
public:
    double myPow(double x, int n) {
        // long long p = -1*(long long)n;//type-casting to long long was needed to handle overflow
        if(n<0) return (1/x)*(1/pow(x,-(n+1)));//another way to handle overflow
        if(n<0) return 1/pow(x,p);
        return pow(x,n);
    } 
    double pow(double x,int n){
        // fast exponentiation 
        if(n==1) return x;
        if(n==0) return 1;
        
        // n is odd  : myPow(x,n/2) * myPow(x,n/2) * x
        // n is even : myPow(x,n/2) * myPow(x,n/2)
        double ans=myPow(x,n/2);
        if(n&1) return ans*ans*x;
        else return ans*ans;
    }
};
/* 
1.00000
-2147483648
Line 4: Char 34: runtime error: signed integer overflow: -1 * -2147483648 cannot be represented in type 'int' (solution.cpp)
*/

// =====================================================================================================================================
// 3) Lettcode 169. Majority Element :: https://leetcode.com/problems/majority-element/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int majority=0,count=0,n=nums.size();
        
        //approach 1: moore's voting algorithm
        for(int num : nums){
            if(!count){
                majority=num;
            }
            count += majority==num ? 1 : -1 ;            
        }
        return majority;
        
        
        /* 
        //approach 2 : bit manipulation [NICE APPROACH]
        // if no of occurences of i'th bit > floor(n/2) => include it in the ans 
        for(unsigned int i=0,mask=1;i<32;i++,mask<<=1){
            count=0;
            for(int num : nums){
                if(num & mask) count++;
                // count+= num & mask ? 1:0;
            }
            if(count > n/2){
                majority|=mask;
            }
        }
        return majority;
        */
    }
};
// =====================================================================================================================================
// 4) Leetcode 229. Majority Element II :: https://leetcode.com/problems/majority-element-ii/

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        // extension of moore's voting algo
        // note: there can be AT MAX 2 majority elements :  that appear more than ⌊ n/3 ⌋ times
        // so we take 2 candidates as majority elements and keep updating them
        // note: at last we will have to check if the 2 candidates have freq > ⌊ n/3 ⌋ (as in qn its NOT mentioned that majority element will surely exist) 
        int num1,num2,f1=0,f2=0,n=nums.size();
        num1=num2=1e9+7;//any element not in array
        for(auto x:nums){
            if(num1==x) f1++;
            else if(num2==x) f2++;
            else if(f1==0) num1=x,f1=1;
            else if(f2==0) num2=x,f2=1;
            else f1--,f2--;//x matches neither candidates => decrease both ka freq 
        }
        
        // perform sanity check: if 2 majority elements have freq > ⌊ n/3 ⌋ or not
        f1=f2=0;
        for(auto x:nums){
            if(num1==x) f1++;
            if(num2==x) f2++;
        }
        vector<int> ans;
        if(f1>n/3) ans.push_back(num1);
        if(f2>n/3) ans.push_back(num2);
        return ans;
        
        // note: here the bit manipulation(used in Majority Element I) wont work: freq of set bits technique wont't work:
        // as 2 elements could contribute to a set bit and make its freq > n/3 :
        // but both indivisually can be < n/3 => this gives false positives
    }
};
// =====================================================================================================================================
// 5) 
class Solution {
public:
    int uniquePaths(int m, int n) {
        
        // Approach 1: simple dp problem : has been space optimized
        // O(n*m)
        int i,j,curr=0;
        vector<vector<int>> dp(2,vector<int>(n,1));//first row and first col = 1
        for(i=1;i<m;i++){
            for(j=1;j<n;j++){
                dp[curr^1][j]=dp[curr][j]+dp[curr^1][j-1];                
            }curr^=1;
        }        
        return dp[curr][n-1];
        
        /*
        // Approach 2: combinatorics/math pblm :: finding nCr
        // ans = (n+m-2) C (n-1) = (n+m-2) C (m-1) = (n * n+1 * .... * n+m-2) / (1*2*...*m-1)
        double ans=1;
        for(int i=1;i<m;i++){
            ans=ans*(n+i-1)/i;
        }
        return (int)(ans+0.01);
        */
    }
};
// =====================================================================================================================================
