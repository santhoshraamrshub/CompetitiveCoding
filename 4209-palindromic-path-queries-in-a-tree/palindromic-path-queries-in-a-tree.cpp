class Solution {
    int n;
    vector<vector<int>> adj;
    string s_val;
    vector<int> parent, depth, heavy, head, pos;
    vector<int> tree;
    int cur_pos;

    int dfs(int u, int p, int d) {
        parent[u] = p;
        depth[u] = d;
        int size = 1, max_c_size = 0;
        for (int v : adj[u]) {
            if (v != p) {
                int c_size = dfs(v, u, d + 1);
                size += c_size;
                if (c_size > max_c_size) {
                    max_c_size = c_size;
                    heavy[u] = v;
                }
            }
        }
        return size;
    }

    void decompose(int u, int h) {
        head[u] = h;
        pos[u] = cur_pos++;
        if (heavy[u] != -1)
            decompose(heavy[u], h);
        for (int v : adj[u]) {
            if (v != parent[u] && v != heavy[u])
                decompose(v, v);
        }
    }

    void build(int node, int start, int end) {
        if (start == end) {
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] ^ tree[2 * node + 1];
    }

    void update_tree(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid)
            update_tree(2 * node, start, mid, idx, val);
        else
            update_tree(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] ^ tree[2 * node + 1];
    }

    int query_tree(int node, int start, int end, int l, int r) {
        if (r < start || end < l)
            return 0;
        if (l <= start && end <= r)
            return tree[node];
        int mid = (start + end) / 2;
        return query_tree(2 * node, start, mid, l, r) ^ query_tree(2 * node + 1, mid + 1, end, l, r);
    }

    int query_path(int u, int v) {
        int res = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]])
                swap(u, v);
            res ^= query_tree(1, 0, n - 1, pos[head[v]], pos[v]);
            v = parent[head[v]];
        }
        if (depth[u] > depth[v])
            swap(u, v);
        res ^= query_tree(1, 0, n - 1, pos[u], pos[v]);
        return res;
    }

public:
    vector<bool> palindromePath(int n_nodes, vector<vector<int>>& edges, string s, vector<string>& queries) {
        n = n_nodes;
        s_val = s;
        adj.assign(n, vector<int>());
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        parent.assign(n, -1);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        cur_pos = 0;

        dfs(0, -1, 0);
        decompose(0, 0);

        tree.assign(4 * n, 0);
        for (int i = 0; i < n; ++i) {
            int mask = 1 << (s[i] - 'a');
            update_tree(1, 0, n - 1, pos[i], mask);
        }

        vector<bool> ans;
        for (const string& q : queries) {
            if (q[0] == 'u') {
                int space1 = q.find(' ', 7);
                int u = stoi(q.substr(7, space1 - 7));
                char c = q.back();
                s_val[u] = c;
                int mask = 1 << (c - 'a');
                update_tree(1, 0, n - 1, pos[u], mask);
            } else {
                int space1 = q.find(' ', 6);
                int space2 = q.find(' ', space1 + 1);
                int u = stoi(q.substr(6, space1 - 6));
                int v = stoi(q.substr(space1 + 1));
                
                int mask = query_path(u, v);
                if ((mask & (mask - 1)) == 0) {
                    ans.push_back(true);
                } else {
                    ans.push_back(false);
                }
            }
        }
        return ans;
    }
};