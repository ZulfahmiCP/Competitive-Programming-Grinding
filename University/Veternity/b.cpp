#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'

using namespace std;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& x);
template<typename T, typename... A>void prd(const T& x, A... a);
template<typename... A>void debug(A... a);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);
void fail() {debug("DONE"); exit(0);}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct DSU {
    int N;
    vector<int> par, size, mn;
    vector<bool> cen;

    DSU(int n) : N(n), par(N), size(N, 1), mn(N, INF), cen(N, 0) {
        iota(all(par), 0);
        iota(all(mn), 0);
    }

    int find(int u) {
        return u == par[u] ? u : par[u] = find(par[u]);
    }

    bool unite(int u, int v) {
        u = find(u), v = find(v);

        if(u == v)
            return 0;

        if(size[u] < size[v])
            swap(u, v);
        
        par[v] = u;
        size[u] += size[v];
        mn[u] = min(mn[u], mn[v]);
        cen[u] = cen[u] | cen[v];

        return 1;
    }

    bool query(int u, int v) {
        return find(u) == find(v);
    }

    int connected(int u) {
        return size[find(u)];
    }

    int center(int u) {
        return cen[find(u)];
    }

    int mini(int u) {
        return mn[find(u)];
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    DSU dsu(n);
    vector<int> center;

    for(int i = 0; i < n; i++){
        int x; cin >> x;
        dsu.cen[i] = x;
        if(x) center.pb(i);
    }

    for(int i = 0, u,v; i < m; i++){
        cin >> u >> v, u--, v--;
        dsu.unite(u, v);
    }

    vector<pair<int, int>> ans;

    for(int u = n - 1; u >= 0; u--){
        if(dsu.center(u)) continue;
        if(dsu.mini(u) != u) continue;
        int v = lower_bound(all(center), u) - center.begin() - 1;

        for(int j : {v, v + 1, v + 2})
            if(0 <= j && j < sz(center))
                if(v < 0)
                    v = j;
                else if(abs(center[v] - u) > abs(center[j] - u))
                    v = j;

        v = center[v];
        dsu.unite(u, v);
        ans.pb({u, v});
    }

    reverse(all(ans));
    cout << sz(ans) << '\n';
    for(auto &[a, b] : ans) cout << a+1 << ' ' << b+1 << '\n';

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
template<typename T, typename... A>void prd(const T& x, A... a){prd(x);cerr<<", ";prd(a...);}
template<typename... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
