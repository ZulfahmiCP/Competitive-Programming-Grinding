#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int R, C, M;
vector<int> vis[36];
vector<pair<int, int>> left_states, right_states;

void precompute_visibility() {
    for (int i = 0; i < R * C; i++) {
        int r = i / C, c = i % C;
        vis[i].clear();
        
        // Check 4 directions, up to 2 cells away
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        for (int d = 0; d < 4; d++) {
            for (int dist = 1; dist <= 2; dist++) {
                int nr = r + dr[d] * dist;
                int nc = c + dc[d] * dist;
                
                if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    vis[i].push_back(nr * C + nc);
                }
            }
        }
    }
}

bool can_place(int pos, int mask) {
    for (int v : vis[pos]) {
        if (mask & (1 << v)) return false;
    }
    return true;
}

void solve_half(int start, int end, int mask, int count) {
    if (start == end) {
        if (start <= R * C / 2) {
            left_states.push_back({count, mask});
        } else {
            right_states.push_back({count, mask});
        }
        return;
    }
    
    // Don't place spy at current position
    solve_half(start + 1, end, mask, count);
    
    // Try to place spy at current position
    if (can_place(start, mask)) {
        solve_half(start + 1, end, mask | (1 << start), count + 1);
    }
}

bool compatible(int left_mask, int right_mask, int mid) {
    // Check if spies from left and right halves can see each other
    for (int i = 0; i < mid; i++) {
        if (!(left_mask & (1 << i))) continue;
        
        for (int j = mid; j < R * C; j++) {
            if (!(right_mask & (1 << (j - mid)))) continue;
            
            // Check if spy at i can see spy at j
            for (int v : vis[i]) {
                if (v == j) return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> R >> C >> M;
    int B; cin >> B;
    
    precompute_visibility();
    
    int total = R * C;
    int mid = total / 2;
    
    // Solve left half
    solve_half(0, mid, 0, 0);
    
    // Solve right half  
    solve_half(mid, total, 0, 0);
    
    long long result = 0;
    map<int, vector<int>> left_by_count;
    
    // Group left states by count
    for (int i = 0; i < left_states.size(); i++) {
        left_by_count[left_states[i].first].push_back(i);
    }
    
    // For each right state, find compatible left states
    for (auto& [right_count, right_mask] : right_states) {
        int need = M - right_count;
        if (left_by_count.count(need)) {
            for (int idx : left_by_count[need]) {
                int left_mask = left_states[idx].second;
                if (compatible(left_mask, right_mask, mid)) {
                    result = (result + 1) % MOD;
                }
            }
        }
    }
    
    cout << result << "\n";
    
    return 0;
}