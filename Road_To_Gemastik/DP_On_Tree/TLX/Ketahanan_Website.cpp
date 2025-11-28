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
    vector<vector<int>> adj;
    vector<bool> vis, good;
    vector<int> deg;

    Tree(int n) : N(n), adj(N), vis(N, 0), good(N, 0), deg(N, 0) {}

    void add_edge(int u, int v) {
        adj[v].pb(u);
        deg[u]++;
        if(!u) good[v] = 1;
    }

    int solve() {
        int ans = 0;

        for(int u = 1; u < N; u++)
            if(!deg[u] && dfs(u))
                ans++;
        
        return ans;
    }

    int dfs(int u) {
        if(vis[u]) return 0;
        vis[u] = 1;
        if(good[u]) return 1;
        for(int &v : adj[u])
            if(dfs(v))
                return 1;
        return 0;
    }
};

int main() {

    FastIO();
    int n; cin >> n;
    Tree tree(n);

    for(int u = 0; u < n; u++){
        int k; cin >> k;

        while(k--){
            int v; cin >> v, v--;
            tree.add_edge(u, v);
        }
    }

    cout << tree.solve() << endl;
    
    return 0;
}
/*
7
2 2 3
1 5
2 4 5
0
2 6 7
0
0
*/
