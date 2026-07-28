class Solution {
public:
    vector<vector<int>> ansss;
    vector<int> ans;
    void sum(int i,vector<int> candidates, int target){
        if(i==candidates.size() || target<0){
            return;
        }
        if(target==0){
            ansss.push_back(ans);
            return;
        }
        ans.push_back(candidates[i]);
        sum(i,candidates,target-candidates[i]);
        ans.pop_back();
        sum(i+1,candidates,target);
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sum(0,candidates,target);
        return ansss;
    }
};