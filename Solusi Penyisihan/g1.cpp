#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second  
#define ll long long 
#define pb push_back
#define ppb pop_back
#define ld long double 
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define newl cerr << '\n'
#define sz(x) (ll)x.size()

#define ttm template 
#define ttp typename 

void FastIO(){ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

ttm<ttp T> void prd(T x){cerr << x;}
ttm<ttp T, ttp U> void prd(pair<T, U> x){cerr<<"("; prd(x.fi); cerr<<", "; prd(x.se); cerr << ")";}
ttm<ttp T, ttp... Args> void prd(T x, Args... arg){prd(x); cerr<<", "; prd(arg...);}
ttm<ttp... Args> void debug(Args... arg){cerr<<"["; prd(arg...); cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr << "["; bool cm=0; for(auto v : c){if(cm) cerr<<", "; prd(v); cm=1;} cerr << "]\n";}

struct RMQ {
    ll N,LOG;
    vector<vector<int>> tab;
    vector<int> arr, log_tab;

    RMQ(ll n = 0) : N(n), LOG(log2(N) + 1), tab(N, vector<int>(LOG)), log_tab(N + 1, 0), arr(N) {}

    void build() {
        for(ll i = 2; i <= N; i++)
            log_tab[i] = 1 + log_tab[i >> 1];

        for(ll i = 0; i < N; i++)
            tab[i][0] = arr[i];

        for(ll j = 1; j < LOG; j++){
            for(ll i = 0; i + (1 << j) <= N; i++){
                tab[i][j] = __gcd(tab[i][j - 1], tab[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    ll calc(ll l, ll r) {
        ll k = log_tab[r - l + 1];
        return __gcd(tab[l][k], tab[r - (1 << k) + 1][k]);
    }
};

int main() {

    FastIO();
    ll n, m, l;
    cin >> n >> m >> l;

    vector<vector<ll>> a(m);
    vector<ll> s(m);

    for (ll i = 0; i < m; i++) {
        cin >> s[i];
        for (ll j = 0; j < s[i]; j++) {
            ll k;
            cin >> k;
            a[i].push_back(k);
        }
    }

    vector<int> b(n);
    for (ll i = 0; i < n; i++) {
        b[i] = a[i % m][(i/m) % s[i % m]];
    }

    RMQ kas(n);
    ll hasil = 0;
    kas.arr = b;
    kas.build();
    for (ll i = 0; i + l - 1 < n; i++) {
        hasil += kas.calc(i, i+l -1);
    }
 
    cout << hasil;
    return 0;
}