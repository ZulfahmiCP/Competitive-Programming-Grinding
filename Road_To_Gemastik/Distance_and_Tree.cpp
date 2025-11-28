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
    int N, K;
    vector<vector<int>> adj;
    vector<int> sub, vis, cnt;
    ll ans = 0;

    Tree(int n, int k) : N(n), K(k), adj(N), sub(N), vis(N, 0), cnt(K + 1, 0) {
        cnt[0] = 1;
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

    void dfs_cen(int u) {
        int c = cen(u, -1, dfs_sub(u, -1));
        vis[c] = 1;

        for(int &v : adj[c]){
            if(!vis[v]){
                dfs(v, c, 1, 0);
                dfs(v, c, 1, 1);
            }
        }

        for(int &v : adj[c])
            if(!vis[v])
                dfs(v, c, 1, 2);

        for(int &v : adj[c]) 
            if(!vis[v])
                dfs_cen(v);
    }

    void dfs(int u, int p, int d, int t) {
        if(d > K) return;

        if(!t) 
            ans += cnt[K - d];
        else if(t == 1) 
            cnt[d]++;
        else 
            cnt[d]--;


        for(int &v : adj[u])
            if(v != p && !vis[v])
                dfs(v, u, d + 1, t);
    }
};

int main() {

    FastIO();
    int n,k; cin >> n >> k;
    Tree tree(n, k);

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.dfs_cen(0);

    cout << tree.ans << endl;
    
    return 0;
}

