class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        // Build adjacency list: u -> list of (v, weight)
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        // State: (weight, node, count)
        // We use a min-heap priority queue
        priority_queue<tuple<long long, int, int>, 
                       vector<tuple<long long, int, int>>, 
                       greater<tuple<long long, int, int>>> pq;

        // Distances: dist[node][count]
        // count goes from 1 to k
        vector<vector<long long>> dist(n, vector<long long>(k + 1, LLONG_MAX));

        // Start from node 0 with count 1 and weight 0
        int start_count = 1;
        dist[0][start_count] = 0;
        pq.push({0, 0, start_count});

        while (!pq.empty()) {
            auto [w, u, count] = pq.top();
            pq.pop();

            if (w > dist[u][count]) continue;
            if (u == n - 1) return w;

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                int next_count = (labels[u] == labels[v]) ? (count + 1) : 1;

                if (next_count <= k) {
                    if (w + weight < dist[v][next_count]) {
                        dist[v][next_count] = w + weight;
                        pq.push({w + weight, v, next_count});
                    }
                }
            }
        }

        long long ans = LLONG_MAX;
        for (int c = 1; c <= k; ++c) {
            ans = min(ans, dist[n - 1][c]);
        }

        return ans == LLONG_MAX ? -1 : ans;
    }
};