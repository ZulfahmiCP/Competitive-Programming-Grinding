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

template<const int &M = mod> struct modi {
    int v;

    modi(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}

    modi& operator+=(const modi &b) {v += b.v; if(v >= M) v -= M; return *this;}
    modi& operator*=(const modi &b) {v = (ll)v * b.v % M; return *this;}
    
    friend modi operator+(const modi &a, const modi &b) { return modi(a) += b;}
    friend modi operator*(const modi &a, const modi &b) { return modi(a) *= b;}
};
using mint = modi<>;

struct Tree {
    int N, K;
    vector<vector<int>> adj;
    vector<vector<mint>> dp;
    vector<int> ord;
    mint ans;

    Tree(int n, int k) : N(n), K(k), adj(N), ord(N), ans(1), dp(N, vector<mint>(K, 0)) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
    }

    int solve() {
        if(!check(0, -1)) return 0;
        dfs({0});
        return ans.v;
    }

    bool check(int u, int mx) {
        if(ord[u] < mx) return false; 
        mx = max(ord[u], mx);
        for(int &v : adj[u])
            if(!check(v, mx)) return false;
        return true;
    }

    void dfs(vector<int> nodes) {
        vector<int> next;

        for(int &u : nodes)
            for(int &v : adj[u])
                next.pb(v);

        if(next.empty()) return;

        sort(all(next), [&](int a, int b) {
            return ord[a] < ord[b];
        });

        nodes.clear();

        int M = sz(next);

        for(int i = 0; i < K; i++) dp[next[0]][i] = 1;

        for(int i = 0, u, v; i < M; i++){
            v = next[i];
            nodes.pb(v);

            if(i > 0){
                u = next[i - 1];

                for(int j = 1; j < K; j++)
                    dp[v][j] = dp[u][j - 1];

                if((ord[u] + 1 == ord[v]) && (u < v)){
                    for(int j = 0; j < K; j++)  
                        dp[v][j] += dp[u][j];
                }
            }

            if(i + 1 == M || ord[v] + 1 != ord[next[i + 1]] || v > next[i + 1]){
                dfs(nodes);
                nodes.clear();
            }
        }

        ans *= accumulate(all(dp[next[M - 1]]), mint(0));

    }
};

int main() {

    FastIO();
    int n,k; cin >> n >> k;
    Tree tree(n, k);

    for(int u = 1, p; u < n; u++){
        cin >> p, p--;
        tree.add_edge(p, u);
    }

    for(int o = 0, u; o < n; o++){  
        cin >> u, u--;
        tree.ord[u] = o;
    }

    cout << tree.solve() << endl;
    
    return 0;
}

/*
2 5
1
1 2
*/