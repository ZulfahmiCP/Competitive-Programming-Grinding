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

struct Trie {
    int N, cur = 1;
    const int LOG = 31;
    vector<array<int, 2>> trie;
    vector<int> cnt;

    Trie() {}
    Trie(int n) : N(n + 1), trie(LOG * N, {0, 0}), cnt(LOG * N, 0) {}

    void insert(int v) {
        for(int i = LOG, x = 1, c; i >= 0; i--){
            c = (v >> i) & 1;
            if(!trie[x][c])
                trie[x][c] = ++cur;
            
            x = trie[x][c];
            cnt[x]++;
        }
    }

    void remove(int v){
        for(int i = LOG, x = 1, c; i >= 0; i--){
            c = (v >> i) & 1;
            x = trie[x][c];
            cnt[x]--;
        }
    }

    int min_xor(int v){
        int x = 1, ans = 0;

        for(int i = LOG, c; i >= 0 && x; i--){
            c = (v >> i) & 1;
            ans <<= 1;

            if(cnt[trie[x][c]])
                x = trie[x][c];
            else 
                ans++, x = trie[x][c ^ 1];
        }

        return ans;
    }

    int max_xor(int v) {
        int x = 1, ans = 0;

        for(int i = LOG, c; i >= 0 && x; i--){
            c = (v >> i) & 1;
            ans <<= 1;

            if(cnt[trie[x][c ^ 1]])
                ans++, x = trie[x][c ^ 1];
            else 
                x = trie[x][c];
        }

        return ans;
    }
};

struct Tree {
    int N;
    vector<vector<pair<int, int>>> adj;
    vector<int> val;
    Trie trie;

    Tree(int n) : N(n), val(N), trie(N), adj(N) {}

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    void build() {
        val[0] = 0;
        dfs(0, -1);
    }

    void dfs(int u, int p){
        for(auto &[v, w] : adj[u]){
            if(v == p) continue;
            val[v] = w ^ val[u];
            dfs(v, u);
        }
    }

    pair<int, int> solve() {
        // debug(val);
        for(int &v : val) trie.insert(v);

        int mn = INF, mx = -INF;

        for(int &v : val){
            trie.remove(v);
            mn = min(mn, trie.min_xor(v));
            mx = max(mx, trie.max_xor(v));
            // debug(trie.min_xor(v), trie.max_xor(v));
            trie.insert(v);
        }

        return {mn, mx};
    }
}; 

int main() {

    FastIO();
    int n; cin >> n;
    Tree tree(n);

    for(int i = 1, u,v,w; i < n; i++){
        cin >> u >> v >> w, u--, v--;
        tree.add_edge(u, v, w);
    }

    tree.build();

    auto [mn, mx] = tree.solve();

    cout << mn << ' ' << mx << endl;
    
    return 0;
}
