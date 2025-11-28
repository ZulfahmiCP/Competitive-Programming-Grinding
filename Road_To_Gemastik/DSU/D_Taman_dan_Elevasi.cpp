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
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}

ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cm = 1;}cerr<<"]\n";}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

struct DSU {
    int N, M;
    vector<int> par, size;

    DSU(int n) : N(n), M(0), par(N), size(N, 1) {
        iota(all(par), 0);
    }

    int find(int u) {
        return u == par[u] ? u : par[u] = find(par[u]);
    }

    void unite(int u, int v) {
        u = find(u), v = find(v);

        if(u == v) return;
        if(size[u] < size[v]) swap(u, v);

        par[v] = u;
        size[u] += size[v];
        M--;
    }
};

int main() {

    FastIO();
    int n,m; cin >> n >> m;
    vector<vector<int>> A(n, vector<int>(m));
    map<int, vector<pair<int, int>>> pos;

    auto get = [&](int i, int j) -> int {
        return i * m + j;
    };

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> A[i][j];
            pos[-A[i][j]].pb({i, j});
        }
    }

    DSU dsu(n * m);
    int ans = 0;

    for(auto [t, arr] : pos){
        for(auto &[i, j] : arr){
            dsu.M++;

            if(i > 0 && A[i-1][j] >= A[i][j]) 
                dsu.unite(get(i-1, j), get(i, j));
            if(j > 0 && A[i][j-1] >= A[i][j])
                dsu.unite(get(i, j-1), get(i, j));
            if(i < n - 1 && A[i+1][j] >= A[i][j])
                dsu.unite(get(i+1, j), get(i, j));
            if(j < m - 1 && A[i][j+1] >= A[i][j])
                dsu.unite(get(i, j+1), get(i, j));
        }

        ans = max(ans, dsu.M);
    }

    cout << ans << endl;
    
    return 0;
}

