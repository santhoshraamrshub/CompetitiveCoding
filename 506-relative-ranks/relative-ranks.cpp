class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
     priority_queue<pair<int,int>> v;
     for(int i=0;i<score.size();i++)   {
        v.push({score[i],i});
     }
     vector<string> ans(score.size(),"");
     ans[v.top().second]="Gold Medal";
     v.pop();
     if(!v.empty()){
     ans[v.top().second]="Silver Medal";
     v.pop();
     }
     if(!v.empty()){
     ans[v.top().second]="Bronze Medal";
     v.pop();
     }
     int rank=4;
     while(!v.empty()){
        ans[v.top().second]=to_string(rank);
     v.pop();
     rank++;
     }
     return ans;
    }
};