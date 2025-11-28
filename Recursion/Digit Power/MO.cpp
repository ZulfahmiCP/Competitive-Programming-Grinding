#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;

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

// MO's Algorithm
struct Query {
    int l, r, idx;
};

int block;
bool cmp(Query a, Query b) {
    if (a.l / block != b.l / block) 
        return a.l / block < b.l / block;
    return (a.l / block & 1) ? a.r < b.r : a.r > b.r;
}

string n;
int k;
vector<int> digs;
vector<long long> f; // Precomputed f(N, i) values
long long curSum = 0;

// 

// Add element at position pos to current window
void add(int pos) {
    curSum = (curSum + f[pos]) % MOD;
}

// Remove element at position pos from current window  
void remove(int pos) {
    curSum = (curSum - f[pos] + MOD) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q;
    cin >> n >> q;
    
    k = n.length();
    block = sqrt(k) + 1; // Block size for MO
    
    digs.resize(k);
    for (int i = 0; i < k; i++) {
        digs[i] = n[i] - '0';
    }
    
    // Precompute all f(N, i) values
    f.resize(k);
    
    // Memoization for expensive modpow operations
    map<pair<long long, int>, long long> memo;
    
    auto calcPow = [&](long long base, int exp) -> long long {
        auto key = make_pair(base, exp);
        if (memo.count(key)) return memo[key];
        
        if (base == 0 && exp == 0) return memo[key] = 1;
        return memo[key] = mpow(base, exp);
    };
    
    // Compute f(N, i) for each position i
    for (int i = 0; i < k; i++) {
        long long num = 0;
        
        // Build number without digit at position i
        for (int j = 0; j < k; j++) {
            if (j == i) continue;
            num = (num * 10 + digs[j]) % MOD;
        }
        
        f[i] = calcPow(num, digs[i]);
    }
    
    // Read and sort queries using MO's algorithm
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; queries[i].r--; // Convert to 0-indexed
        queries[i].idx = i;
    }
    
    sort(queries.begin(), queries.end(), cmp);
    
    vector<long long> ans(q);
    int curL = 0, curR = -1;
    
    // Process queries using MO's algorithm
    for (auto& query : queries) {
        int l = query.l, r = query.r;
        
        // Extend right boundary
        while (curR < r) {
            curR++;
            add(curR);
        }
        
        // Shrink right boundary
        while (curR > r) {
            remove(curR);
            curR--;
        }
        
        // Extend left boundary
        while (curL > l) {
            curL--;
            add(curL);
        }
        
        // Shrink left boundary
        while (curL < l) {
            remove(curL);
            curL++;
        }
        
        ans[query.idx] = curSum;
    }
    
    // Output answers in original order
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}