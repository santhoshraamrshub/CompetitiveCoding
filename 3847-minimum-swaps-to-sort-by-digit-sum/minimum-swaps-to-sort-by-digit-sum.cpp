class Solution {
private:
    int digitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = {nums[i], i};
        }

        sort(arr.begin(), arr.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            int sumA = 0, tempA = a.first;
            while (tempA > 0) { sumA += tempA % 10; tempA /= 10; }
            
            int sumB = 0, tempB = b.first;
            while (tempB > 0) { sumB += tempB % 10; tempB /= 10; }

            if (sumA != sumB) return sumA < sumB;
            return a.first < b.first;
        });

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; ++i) {
            if (visited[i] || arr[i].second == i) continue;

            int cycleSize = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = arr[j].second;
                cycleSize++;
            }
            if (cycleSize > 1) {
                swaps += (cycleSize - 1);
            }
        }

        return swaps;
    }
};