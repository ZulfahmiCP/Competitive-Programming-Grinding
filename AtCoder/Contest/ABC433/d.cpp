#include <bits/stdc++.h>

#define fi first 
#define se second 
#define ll long long 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define uniq(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'
#define ttm template
#define ttp typename

using namespace std;
ttm<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
#ifndef ONLINE_JUDGE
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}
ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<"[ ";for(auto v:c){prd(v);cerr<<' ';}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<"[ ";for(auto v:c){cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cerr<<' ';}cerr<<"]\n";}
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

int cnt(int x) {
    int c = 0;
    while(x > 0) c++, x /= 10;
    return c;
}

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m; cin >> n >> m;
    vector<ll> A(n), B(n), pow10(11, 0);

    for(int i = 0; i < n; i++){
        cin >> A[i];
        B[i] = cnt(A[i]);
        A[i] %= m;
    }

    pow10[0] = 1;
    for(int i = 1; i < 11; i++)
        pow10[i] = 10LL * pow10[i-1] % m;

    map<pair<int, int>, int> mp;
    ll ans = 0;

    for(int i = 0; i < n; i++)
        mp[{B[i], (m - A[i]) % m}]++;

    for(int i = 0; i < n; i++){
        for(int j = 1; j < 11; j++){
            int x = A[i] * pow10[j] % m;
            assert(x >= 0 && x < m);
            if(mp.find({j, x}) != mp.end())
                ans += mp[{j, x}];
        }
    }

    // cnt(A[j]) = jumlah digit di A[j]
    // f(A[i], A[j]) =  A[i] * cnt(A[j]) + A[j]
    // cnt(A[j]) = x
    // A[i] * x + A[j] = 0
    // A[i] * x = -A[j] % m
    // A[j] = -A[i] * x (-A[i] * cnt(A[j]), cnt(A[j]))
    // M = 10
    // 10 100 0
    // (0, 2) (0, 3) 

    cout << ans << endl;
    
    return 0;
}
