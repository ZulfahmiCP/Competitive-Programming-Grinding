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


struct Trie {
    static const int LOG = 20;
    struct Node {
        int next[2];
        int time = -1;
        int cnt = 0;

        Node() {fill(next, next + 2, 0);}

        int &operator[](int i) {assert(0 <= i && i < 2); return next[i];}
    };

    int N, last_root = 0;
    vector<Node> trie;
    vector<int> rt; 

    Trie() {}
    Trie(int n, int m) : N(n), trie(2), rt(m + 1) {
        rt[0] = 1;
    }

    int clone(int i) {
        int j = sz(trie);
        trie.pb(Node());
        if(i) trie[j] = trie[i];
        return j;
    }

    bool go(int i, int l) {
        return (i ? trie[i].time >= l : 0);
    }

    void insert(int v, int t, int p) {
        int x = clone(rt[p]);
        rt[t] = x;

        for(int i = LOG; i >= 0; i--){
            int c = (v >> i) & 1;
            
            trie[x][c] = clone(trie[x][c]);

            x = trie[x][c];
            trie[x].time = t;
            trie[x].cnt++;
        }
    }
    
    int kth_smallest_xor(int u, int v, int l, int p, int x, int k) {
        int ans = 0;
        int xu = rt[u], xv = rt[v], xl = rt[l], xp = rt[p];
        // debug(make_pair(u, rt[u]), make_pair(v, rt[v]), make_pair(l, rt[l]), make_pair(p, rt[p]));

        for(int i = LOG; i >= 0 ; i--){
            int c = (x >> i) & 1;
            int cnt = trie[trie[xu][c]].cnt + trie[trie[xv][c]].cnt 
                    - trie[trie[xl][c]].cnt - trie[trie[xp][c]].cnt ;
            // debug(cnt, k, trie[trie[xu][c]].cnt, trie[trie[xv][c]].cnt, trie[trie[xl][c]].cnt, trie[trie[xp][c]].cnt);

            if(k <= cnt){
                xu = trie[xu][c];
                xv = trie[xv][c];
                xl = trie[xl][c];
                xp = trie[xp][c];
            } else {
                ans |= (1 << i);
                k -= cnt; 
                xu = trie[xu][c ^ 1];
                xv = trie[xv][c ^ 1];
                xl = trie[xl][c ^ 1];
                xp = trie[xp][c ^ 1];
            }
        }
        return ans;
    }
};

struct LCA {
    int N, K, cur = 0;
    vector<vector<int>> par, adj; 
    vector<int> val, dep, pos; 
    Trie trie;  

    LCA(int n) : N(n + 1), K(log2(N) + 1), par(N, vector<int>(K, 0)),
                 val(N), dep(N), adj(N), pos(N, 0), trie(N, N) {}

    void add_edge(int u, int v){
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build(int root = 1) {
        par[root][0] = 0;
        dfs(root);

        for(int d = 1; d < K; d++)
            for(int u = 1; u < N; u++)
                if(par[u][d - 1] != -1)
                    par[u][d] = par[par[u][d - 1]][d - 1];
    }

    void dfs(int u) {
        eliminate(adj[u], par[u][0]);
        pos[u] = ++cur;
        trie.insert(val[u], pos[u], pos[par[u][0]]);

        for(const int &v : adj[u]){
            par[v][0] = u, dep[v] = dep[u] + 1;
            dfs(v);
        }
    }

    int lca(int u, int v) {
        if(dep[u] < dep[v]) swap(u, v); 

        int g = dep[u] - dep[v];
        for(int d = 0; d < K; d++) 
            if((g >> d) & 1)
                u = par[u][d];

        if(u == v) return u;

        for(int d = K - 1; d >= 0; d--) 
            if(par[u][d] != par[v][d])
                u = par[u][d], v = par[v][d];

        return par[u][0]; 
    }

    int solve(int u, int v, int x, int k) {
        int l = lca(u, v), p = par[l][0];
        // debug(make_pair(u, pos[u]), make_pair(v, pos[v]), make_pair(l, pos[l]), make_pair(p, pos[p]));
        return trie.kth_smallest_xor(pos[u], pos[v], pos[l], pos[p], x, k);
    }
};


int main(){
 
    FastIO();
    int n; cin >> n;
    LCA tree(n);

    for(int i = 1; i <= n; i++)
        cin >> tree.val[i];

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v;
        tree.add_edge(u, v);
    }

    tree.build();

    int q; cin >> q;

    for(int i = 0, u,v,x,k; i < q; i++){
        cin >> u >> v >> k >> x;
        cout << tree.solve(u, v, x, k) << endl;
    }

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
