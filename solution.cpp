#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class DSU {
private:
    vector<int> parent;
    
public:
    DSU(int n) : parent(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px != py) {
            parent[py] = px;
        }
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<pair<int, int>> equal_pairs;
        vector<pair<int, int>> unequal_pairs;
        equal_pairs.reserve(n);
        unequal_pairs.reserve(n);
        
        vector<int> variables;
        variables.reserve(n * 2);
        
        for (int k = 0; k < n; k++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);
            variables.push_back(i);
            variables.push_back(j);
            if (e == 1) {
                equal_pairs.push_back({i, j});
            } else {
                unequal_pairs.push_back({i, j});
            }
        }
        
        // Coordinate compression
        sort(variables.begin(), variables.end());
        variables.erase(unique(variables.begin(), variables.end()), variables.end());
        
        unordered_map<int, int> compress;
        compress.reserve(variables.size() * 2);
        for (int idx = 0; idx < (int)variables.size(); idx++) {
            compress[variables[idx]] = idx;
        }
        
        DSU dsu(variables.size());
        
        // Process equality constraints
        for (const auto& pair : equal_pairs) {
            int ci = compress[pair.first];
            int cj = compress[pair.second];
            dsu.unite(ci, cj);
        }
        
        // Check inequality constraints
        bool possible = true;
        for (const auto& pair : unequal_pairs) {
            int ci = compress[pair.first];
            int cj = compress[pair.second];
            if (dsu.same(ci, cj)) {
                possible = false;
                break;
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}