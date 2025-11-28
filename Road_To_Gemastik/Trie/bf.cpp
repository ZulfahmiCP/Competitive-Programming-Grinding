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
    int N, cur = 1;
    const int LOG = 31; 
    vector<array<int, 2>> trie;
    vector<int> cnt;

    Trie(int n) : N(n), trie(LOG * N), cnt(LOG * N) {}

    void insert(int x){
        for(int i = LOG, k = 1, b; i >= 0; i--){
            b = (x >> i) & 1;
            if(!trie[k][b])
                trie[k][b] = ++cur;
            k = trie[k][b];
            cnt[k]++;
        }
    }

    void remove(int x) {
        for(int i = LOG, k = 1, b; i >= 0; i--){
            b = (x >> i) & 1;
            k = trie[k][b];
            cnt[k]--;
        }
    }

    int max_xor(int x) {
        int ans = 0;

        for(int i = LOG, k = 1, b; i >= 0; i--){
            b = (x >> i) & 1;
            ans <<= 1;

            if(cnt[trie[k][b ^ 1]])
                ans++, k = trie[k][b ^ 1];
            else 
                k = trie[k][b];
        }

        return ans;
    }
};

struct Tree {
    int N;
    vector<vector<int>> adj;
    vector<int> val;
    Trie trie;

    Tree(int n) : N(n), adj(N), val(N), trie(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int solve() {
        return dfs(0, -1);
    }

    int dfs(int u, int p) {
        int ans = trie.max_xor(val[u]);
        trie.insert(val[u]);

        for(int &v : adj[u]){
            if(v == p) continue;
            ans = max(ans, dfs(v, u));
        }

        trie.remove(val[u]);
        return ans;
    }
};

int main(){
 
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
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
template<typename T, typename... A>void prd(const T& x, A... a){prd(x);cerr<<", ";prd(a...);}
template<typename... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
/*
3
4 7 15
1 2
3 1

5
11 3 7 6 14
1 2
2 3
3 4
2 5
*/