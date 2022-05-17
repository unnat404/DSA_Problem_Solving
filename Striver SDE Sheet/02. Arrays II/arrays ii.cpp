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
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<pair<int,int>> v;
        for(auto x:intervals){
            v.push_back({x[0],0});//0:start
            v.push_back({x[1],1});//1:end
        }
        sort(v.begin(),v.end());
        // for(auto x:v) cout<<x.first<<" "<<x.second<<"\n";
        int i,open=-1,start,end=-1,j=0;
        vector<vector<int>> ans;
        for(i=0;i<v.size();i++){
            if(open==-1 && end<v[i].first){
                start = v[i].first;open=1;
            }
            else if(open>=1){
                if(v[i].second==0) open++;
                else open--;
                if(open==0){
                    end=v[i].first;open=-1;
                    ans.push_back({start,end});j++;
                }
            }
        }
        return ans;
    }
};
//=====================================================================================================
// 3) Leetcode 
//=====================================================================================================
// 4) Leetcode 
//=====================================================================================================
// 5) Leetcode 
//=====================================================================================================

//=====================================================================================================
