#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long mpow(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

struct SqrtDecomp {
    vector<long long> arr, blocks;
    int n, bsz;
    
    SqrtDecomp(vector<long long>& a) {
        n = a.size();
        bsz = sqrt(n) + 1;
        arr = a;
        blocks.assign((n + bsz - 1) / bsz, 0);
        
        // Build blocks
        for (int i = 0; i < n; i++) {
            blocks[i / bsz] = (blocks[i / bsz] + arr[i]) % MOD;
        }
    }
    
    long long query(int l, int r) {
        long long res = 0;
        
        // Handle left partial block
        while (l <= r && l % bsz != 0) {
            res = (res + arr[l]) % MOD;
            l++;
        }
        
        // Handle complete blocks
        while (l + bsz - 1 <= r) {
            res = (res + blocks[l / bsz]) % MOD;
            l += bsz;
        }
        
        // Handle right partial block
        while (l <= r) {
            res = (res + arr[l]) % MOD;
            l++;
        }
        
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string n;
    int q;
    cin >> n >> q;
    
    int k = n.length();
    vector<int> digs(k);
    for (int i = 0; i < k; i++) {
        digs[i] = n[i] - '0';
    }
    
    // Precompute all f(N, i) values with memoization
    vector<long long> f(k);
    map<pair<long long, int>, long long> memo;
    
    auto calcPow = [&](long long base, int exp) -> long long {
        auto key = make_pair(base, exp);
        if (memo.count(key)) return memo[key];
        
        if (base == 0 && exp == 0) return memo[key] = 1;
        return memo[key] = mpow(base, exp);
    };
    
    for (int i = 0; i < k; i++) {
        long long num = 0;
        
        // Build number without digit at position i
        for (int j = 0; j < k; j++) {
            if (j == i) continue;
            num = (num * 10 + digs[j]) % MOD;
        }
        
        f[i] = calcPow(num, digs[i]);
    }
    
    // Build SQRT decomposition structure
    SqrtDecomp sd(f);
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--; // Convert to 0-indexed
        
        cout << sd.query(l, r) << "\n";
    }
    
    return 0;
}