#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class HashDSU {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    
public:
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
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
        constraints.reserve(n);
        
        for (int k = 0; k < n; k++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);
            constraints.push_back({i, j, e});
        }
        
        HashDSU dsu;
        
        // Process equality constraints first
        for (const auto& cons : constraints) {
            if (cons.e == 1) {
                dsu.unite(cons.i, cons.j);
            }
        }
        
        // Check inequality constraints
        bool possible = true;
        for (const auto& cons : constraints) {
            if (cons.e == 0) {
                if (dsu.same(cons.i, cons.j)) {
                    possible = false;
                    break;
                }
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}