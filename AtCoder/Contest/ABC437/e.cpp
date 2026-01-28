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

struct Graph {
    struct node {
        int y, len;
    };  
    int N;
    vector<node> A;
    vector<vector<int>> adj;
    vector<int> par, ans;

    Graph(int n) : N(n+1), adj(n+1), A(n+1), par(n+1, -1) {
        A[0] = {0, 0};
    }

    void add_edge(int i, int x, int y) {
        adj[x].pb(i);
        A[i] = {y, A[x].len + 1};
    }

    void solve() {
        dfs_par(0);

        for(int u = 0; u < N; u++){
            sort(all(adj[u]), [&](int a, int b) {
                if(A[a].y == A[b].y) return a < b;
                return A[a].y < A[b].y; 
            });
        }

        dfs({0});
        assert(sz(ans) == N);
        // deb(ans);
    }

    void dfs_par(int u) {
        for(int &v : adj[u]){
            if(v == par[u]) continue;
            par[v] = u;
            dfs_par(v);
        }
    }

    void dfs(vector<int> nodes){
        for(int &u : nodes) ans.pb(u);
        
        vector<int> next;

        for(int &u : nodes)
            for(int &v : adj[u])
                if(v != par[u])
                    next.pb(v);

        sort(all(next), [&](int a, int b) {
            if(A[a].y == A[b].y) return a < b;
            return A[a].y < A[b].y;
        });

        vector<int> trav;

        for(int i = 0; i < sz(next); i++){
            trav.pb(next[i]);
            if(i + 1 == sz(next) || A[next[i]].y != A[next[i+1]].y){
                dfs(trav);
                trav.clear();
            } 
        }

        assert(trav.empty());
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n; cin >> n;
    Graph graph(n);

    for(int i = 1, x,y; i <= n; i++){
        cin >> x >> y;
        graph.add_edge(i, x, y);
    }

    graph.solve();

    for(int i = 1; i <= n; i++)
        cout << graph.ans[i] << ' ';
    
    return 0;
}
