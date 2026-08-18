class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
     int n=nums.size();
     int best=nums[0];
     int minval=nums[0];
     int minans=nums[0];
     int ans=nums[0];
     int total=nums[0];
     for(int i=1;i<n;i++){
        best=max(nums[i]+best,nums[i]);
        ans=max(ans,best);
        minval=min(nums[i]+minval,nums[i]);
        minans=min(minans,minval);
        total+=nums[i];
     }
     if(ans<0) return ans;
     return max(ans,total-minans);
    }
};