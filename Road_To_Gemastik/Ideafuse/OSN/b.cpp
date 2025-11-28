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
    int N;
    vector<ll> par, size, sum;

    DSU(int n) : N(n), par(N), size(N, 1), sum(N, 0) {
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
        sum[u] += sum[v];
    }

    ll query(int u) {
        return sum[find(u)];
    }
};

const int LOG = 31;

int msb(int x) { return LOG - __builtin_clz(x); }
int get(int x, int i) { return (x >> i) & 1; }

stack<int> group[LOG][LOG];

int main() {

    FastIO();
    int n; cin >> n;
    vector<array<int, 3>> A(n);
    DSU dsu(n);

    for(int i = 0; i < n; i++){
        cin >> A[i][0];
        A[i][2] = i;
    }

    for(int i = 0; i < n; i++)
        cin >> A[i][1];

    sort(all(A));

    for(int i = 0; i < n; i++) dsu.sum[i] = A[i][1];

    for(int i = 0; i < n; i++){
        int bit = msb(A[i][0]);

        for(int j = 0, u,v; j < bit; j++){
            if(get(A[i][0], j)) continue;
            if(group[bit][j].empty()) continue;

            while(sz(group[bit][j]) > 1){
                u = group[bit][j].top();
                group[bit][j].pop();
                v = group[bit][j].top();

                dsu.unite(u, v);
            }

            v = group[bit][j].top();
            dsu.unite(i, v);
        }

        for(int j = 1; j < LOG; j++) if(!get(A[i][0], j)) {
            int k = j - 1;
            while(k > 0 && !get(A[i][0], k))
                k--;

            if(get(A[i][0], k))
                group[j][k].push(i);
        }
    }

    vector<ll> ans(n);

    for(int i = 0; i < n; i++)
        ans[A[i][2]] = dsu.query(i);

    for(ll &a : ans) cout << a << endl; 
    
    return 0;
}

