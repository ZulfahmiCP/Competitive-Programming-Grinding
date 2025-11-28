#include <bits/stdc++.h>
using namespace std;

#define fi first 
#define se second
#define ll long long
#define pb push_back
#define ppb pop_back 
#define pf push_front
#define ppf pop_front
#define all_range(x) (x).begin(), (x).begin()
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'
#define ttm  template
#define ttp typename

#ifndef ONLINE_JUDGE 
ttm<ttp T> void prd(T x) {cerr << x;}
ttm<ttp T, ttp U> void prd(pair<T, U> x) {cerr << "("; prd(x.fi); cerr<<", "; prd(x.se); cerr<<")";}
ttm<ttp T, ttp ... A> void prd(T x, A... a) {prd(x); cerr << ", "; prd(a...); }
ttm<ttp... A> void debug(A... a) {cerr << "["; prd(a...); cerr <<"]\n";}
ttm<ttp T> void debug(vector<T> c) {cerr <<"["; for(auto v : c) debug(v); cerr << '\n';} 
ttm<ttp T> void debug(vector<vector<T>> c) {cerr <<"["; for(auto v : c) debug(v); cerr << '\n';} 
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

struct RMQ {
    int N, LOG;
    vector<vector<int>> tab;
    vector<int> arr, log_tab;

    RMQ(int n) : N(n), LOG(log2(N) + 1), tab(N, vector<int>(LOG)), log_tab(N + 1, 0), arr(N) {}

    void build() {
        for(int i = 2; i <= N; i++)
            log_tab[i] = 1 + log_tab[i >> 1];

        for(int i = 0; i < N; i++)
            tab[i][0] = arr[i];

        for(int j = 1; j < LOG; j++){
            for(int i = 0; i + (1 << j) <= N; i++){
                int tab1 = tab[i][j - 1];
                int tab2 = tab[i + (1 << (j - 1))][j - 1];
                tab[i][j] = min(tab1, tab2);
            }
        }
    }

    ll calc(int l, int r) {
        int k = log_tab[r - l + 1];
        return min(tab[l][k], tab[r - (1 << k) + 1][k]);
    }
};

ll val(ll n) {
    return n * (n + 1) / 2;
}

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll n,k; cin >> n >> k;
    vector<int> A(n);
    vector<ll> pref(n);
    RMQ rmq(n);

    for(auto &a : A) cin >> a;

    pref[0] = A[0];
    for(int i = 1; i < n; i++)
        pref[i] = pref[i - 1] + A[i];

    rmq.arr = A;
    rmq.build();

    ll cur, ans = -1e18;

    for(int i = 0; i + k - 1 < n; i++){
        cur = pref[i + k - 1];
        if(i) cur -= pref[i - 1];

        if(i > 0){
            cur += rmq.calc(0, i - 1) * i;
            cur -= val(i);
        }

        if(i + k < n){
            cur += rmq.calc(i + k, n - 1) * (n - (i + k));
            cur -= val(n - (i + k));
        }

        ans = max(ans, cur);
    }

    cout << ans << endl;
    
    return 0;
}