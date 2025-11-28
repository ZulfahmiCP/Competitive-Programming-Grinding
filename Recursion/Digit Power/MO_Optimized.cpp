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

struct Query {
    int l, r, idx;
};

// Mo's algorithm with square root decomposition optimization
int block;
bool cmp(Query a, Query b) {
    if (a.l / block != b.l / block) 
        return a.l / block < b.l / block;
    return (a.l / block & 1) ? a.r < b.r : a.r > b.r;
}

// Pattern recognition system for repeated calculations
class PatternRecognizer {
private:
    map<string, long long> patternCache;
    map<pair<long long, int>, long long> powCache;
    
public:
    long long fastPow(long long base, int exp) {
        auto key = make_pair(base, exp);
        if (powCache.count(key)) return powCache[key];
        
        if (base == 0 && exp == 0) return powCache[key] = 1;
        return powCache[key] = mpow(base, exp);
    }
    
    string makeKey(const vector<int>& digs, int l, int r, int skip) {
        string key = to_string(l) + "," + to_string(r) + "," + to_string(skip) + ":";
        for (int i = l; i <= r; i++) {
            if (i != skip) key += to_string(digs[i]);
        }
        return key;
    }
    
    long long buildWithCache(const vector<int>& digs, int l, int r, int skip) {
        string key = makeKey(digs, l, r, skip);
        if (patternCache.count(key)) return patternCache[key];
        
        long long res = 0;
        for (int i = l; i <= r; i++) {
            if (i == skip) continue;
            res = (res * 10 + digs[i]) % MOD;
        }
        
        return patternCache[key] = res;
    }
    
    void clearCache() {
        if (patternCache.size() > 15000) patternCache.clear();
        if (powCache.size() > 8000) powCache.clear();
    }
};

// Ultimate calculator with all optimizations combined
class UltimateCalculator {
private:
    vector<int> digs;
    PatternRecognizer* pr;
    vector<long long> pw10;
    int n;
    
    // Square root decomposition for range queries
    struct SqrtDecomp {
        vector<long long> blocks;
        vector<vector<long long>> blockData;
        int bsize, bcount;
        
        SqrtDecomp(int n) {
            bsize = sqrt(n) + 1;
            bcount = (n + bsize - 1) / bsize;
            blocks.resize(bcount);
            blockData.resize(bcount);
        }
        
        void addToBlock(int blockIdx, long long val) {
            blocks[blockIdx] = (blocks[blockIdx] + val) % MOD;
            blockData[blockIdx].push_back(val);
        }
        
        long long getBlockSum(int blockIdx) {
            return blocks[blockIdx];
        }
    };
    
public:
    UltimateCalculator(vector<int>& digits) : digs(digits), n(digits.size()) {
        pr = new PatternRecognizer();
        
        pw10.resize(n + 1);
        pw10[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw10[i] = (pw10[i-1] * 10) % MOD;
        }
    }
    
    ~UltimateCalculator() {
        delete pr;
    }
    
    // Optimized f calculation with pattern recognition
    long long getF(int l, int r, int pos) {
        int globalPos = l + pos;
        long long base = pr->buildWithCache(digs, l, r, globalPos);
        return pr->fastPow(base, digs[globalPos]);
    }
    
    // Matrix-based optimization for repetitive patterns
    long long getRangeSumOptimized(int l, int r) {
        int len = r - l + 1;
        
        // Use square root decomposition for very large ranges
        if (len > 500) {
            SqrtDecomp sd(len);
            long long totalSum = 0;
            
            for (int i = 0; i < len; i++) {
                long long val = getF(l, r, i);
                totalSum = (totalSum + val) % MOD;
                
                // Add to appropriate block
                int blockIdx = i / sd.bsize;
                sd.addToBlock(blockIdx, val);
            }
            
            return totalSum;
        }
        
        // Direct computation for smaller ranges
        long long sum = 0;
        for (int i = 0; i < len; i++) {
            sum = (sum + getF(l, r, i)) % MOD;
        }
        
        return sum;
    }
    
    void performMaintenance() {
        pr->clearCache();
    }
};

string s;
int k;
vector<int> digs;
UltimateCalculator* calc;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q;
    cin >> s >> q;
    
    k = s.length();
    block = max(1, (int)(sqrt(k) + sqrt(q) / 10)); // Adaptive block size
    
    digs.resize(k);
    for (int i = 0; i < k; i++) {
        digs[i] = s[i] - '0';
    }
    
    // Initialize ultimate calculator
    calc = new UltimateCalculator(digs);
    
    // Read and process queries
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; queries[i].r--;
        queries[i].idx = i;
    }
    
    // Sort queries for better cache performance
    sort(queries.begin(), queries.end(), cmp);
    
    vector<long long> ans(q);
    
    // Process queries with ultimate optimization
    for (int i = 0; i < q; i++) {
        const auto& query = queries[i];
        ans[query.idx] = calc->getRangeSumOptimized(query.l, query.r);
        
        // Periodic maintenance
        if (i % 3000 == 0) {
            calc->performMaintenance();
        }
    }
    
    // Output results in original order
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    
    delete calc;
    return 0;
}