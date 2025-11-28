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

struct Tree {
    int N;
    const int LOG = 20;
    vector<vector<int>> adj;
    vector<int> sub, vis, val, pow2;
    vector<array<int, 2>> cnt;
    ll ans = 0;
    
    Tree(int n) : N(n), adj(N), sub(N), vis(N, 0), val(N), cnt(LOG, {0, 0}), pow2(LOG) {
        pow2[0] = 1;
        for(int i = 1; i < LOG; i++) 
            pow2[i] = (pow2[i - 1] << 1);
    }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int dfs_sub(int u, int p) {
        sub[u] = 1;
        for(int &v : adj[u])
            if(v != p && !vis[v])
                sub[u] += dfs_sub(v, u);
        return sub[u];
    }

    int cen(int u, int p, int n) {
        for(int &v : adj[u])
            if(v != p && !vis[v] && sub[v] > n / 2)
                return cen(v, u, n);
        return u;
    }

    ll solve() {
        ans = accumulate(all(val), 0LL);
        dfs_cen(0);
        return ans;
    }

    void dfs_cen(int u) {
        int c = cen(u, -1, dfs_sub(u, -1));
        vis[c] = 1;

        for(int &v : adj[c]){
            if(!vis[v]){
                dfs(v, c, val[c], 0);
                dfs(v, c, 0, 1);
            }
        }

        for(int i = 0; i < LOG; i++)
            for(int k = 0; k < 2; k++)
                cnt[i][k] = 0;
        
        for(int &v : adj[c]) if(!vis[v]) dfs_cen(v);
    }

    int bit(int x, int i) {
        return (x >> i) & 1;
    }

    void dfs(int u, int p, int x, bool t) {
        x ^= val[u];

        if(!t){
            ans += x;
            for(int i = 0; i < LOG; i++)
                ans += 1LL * pow2[i] * cnt[i][!bit(x, i)];
        } else {
            for(int i = 0; i < LOG; i++)
                cnt[i][bit(x, i)]++;
        }

        for(int &v : adj[u])
            if(v != p && !vis[v])
                dfs(v, u, x, t);
    }
};

int main() {

    FastIO();
    int n; cin >> n;
    Tree tree(n);

    for(int &a : tree.val) cin >> a;

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    cout << tree.solve() << endl;
    
    return 0;
}

