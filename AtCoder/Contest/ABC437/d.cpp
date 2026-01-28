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

struct Pref {
    vector<ll> pref;

    Pref(vector<int> &A) : pref(sz(A)) {
        int n = sz(A);
        pref[0] = A[0];
        for(int i = 1; i < n; i++)
            pref[i] = pref[i - 1] + A[i];
    }

    ll operator()(int l, int r) {
        ll sum = pref[r] - (l > 0 ? pref[l-1] : 0);
        return sum % mod;
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m; cin >> n >> m;
    vector<int> A(n), B(m);

    for(int &x : A) cin >> x;
    for(int &x : B) cin >> x;

    sort(all(A));
    sort(all(B));

    if(A[0] < B[0]){
        swap(A, B);
        swap(n, m);
    }

    Pref sum_b(B);

    ll ans = 0;

    for(int i = 0, j = 0; i < n; i++){
        // A[i] >= B[j], j max 
        while(j + 1 < m && A[i] >= B[j+1])
            j++;
        
        if(A[i] >= B[j])
            ans = (ans + (1LL * (j+1) * A[i] % mod) - sum_b(0, j) + mod) % mod;
        
        if(j+1 < m)
            ans = (ans + sum_b(j+1, m-1) - (1LL * (m-j-1) * A[i] % mod) + mod) % mod;
    }

    cout << ans << endl;
    
    return 0;
}
