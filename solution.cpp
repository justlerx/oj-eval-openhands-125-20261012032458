#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class DSU {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    DSU(int n) : parent(n), rank(n, 0) {
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
        if (px == py) return;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

struct Constraint {
    int i, j, e;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<Constraint> constraints;
        vector<int> variables;
        variables.reserve(n * 2);
        constraints.reserve(n);
        
        for (int k = 0; k < n; k++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);
            constraints.push_back({i, j, e});
            variables.push_back(i);
            variables.push_back(j);
        }
        
        // Coordinate compression
        sort(variables.begin(), variables.end());
        variables.erase(unique(variables.begin(), variables.end()), variables.end());
        
        unordered_map<int, int> compress;
        compress.reserve(variables.size());
        for (size_t idx = 0; idx < variables.size(); idx++) {
            compress[variables[idx]] = idx;
        }
        
        DSU dsu(variables.size());
        
        // Process equality constraints first
        for (const auto& cons : constraints) {
            if (cons.e == 1) {
                int ci = compress[cons.i];
                int cj = compress[cons.j];
                dsu.unite(ci, cj);
            }
        }
        
        // Check inequality constraints
        bool possible = true;
        for (const auto& cons : constraints) {
            if (cons.e == 0) {
                int ci = compress[cons.i];
                int cj = compress[cons.j];
                if (dsu.same(ci, cj)) {
                    possible = false;
                    break;
                }
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}