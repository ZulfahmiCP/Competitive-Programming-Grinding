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

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, q; cin >> n >> q;
    
    vector<ll> x(n), y(n), id(n);

    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        id[i] = i;
    }

    // y > 0 -> kuadran 1 & 2, y < 0 -> kuadran 3 & 4
    auto kuadran = [&](int i) {
        return y[i] > 0 || (y[i] == 0 && x[i] > 0);
    };

    auto val = [&](int a, int b) {
        return x[a] * y[b] - y[a] * x[b];
    };

    sort(all(id), [&](ll &a, ll &b){
        return kuadran(a) == kuadran(b) ? val(a, b) > 0 : kuadran(a);
    });

    vector<int> pos(n), line;
    pos[id[0]] = 0;
    line.pb(1);

    int k = 0;

    for(int i = 1, u,v; i < n; i++){
        u = id[i], v = id[i-1];

        if(kuadran(u) == kuadran(v) && val(u, v) == 0){
            line[k]++;
        } else {
            line.pb(1);
            k++;
        }

        pos[u] = k;
    }

    k = sz(line);
    vector<int> sum(k); 

    sum[0] = line[0];
    for (int i = 1; i < k; i++) 
        sum[i] = sum[i - 1] + line[i];

    while(q--){
        int a, b; cin >> a >> b, a--; b--;
        int l = pos[a], r = pos[b];

        if(l == r) 
            cout << line[l] << "\n";
        else if(l > r) 
            cout << sum[l] - (r ? sum[r - 1] : 0) << "\n";
        else 
            cout << sum[l] + (sum[k - 1] - sum[r - 1]) << "\n";
    }
    
    return 0;
}
