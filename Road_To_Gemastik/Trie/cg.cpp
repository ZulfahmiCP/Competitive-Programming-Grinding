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

struct AhoCorasick {
    static const int K = 26;
    struct Node {
        vector<int> word, occ;
        int next[K], fail = -1, cnt = 0, dep = 0;

        Node(){fill(next, next + K, -1);}

        int& operator[](int i){assert(0 <= i && i < K); return next[i];}
        int& operator[](char c){assert('a' <= c && c <= 'z'); return next[c - 'a'];}
    };

    int N;
    vector<Node> trie;
    vector<vector<int>> adj, occ;
    vector<int> cnt;

    AhoCorasick() : trie(1), N(0) {}

    void insert(const string &s) {
        int x = 0;

        for(const char &c : s){
            if(trie[x][c] == -1){
                trie[x][c] = sz(trie);
                trie.pb(Node());
            }

            trie[trie[x][c]].dep = trie[x].dep + 1;
            x = trie[x][c];
        }

        trie[x].word.pb(N++);
    }

    void build() {
        int x = 0;
        trie[0].fail = 0;
        queue<int> bfs;

        for(int i = 0; i < K; i++){
            if(trie[x][i] != -1){
                trie[trie[x][i]].fail = x;
                bfs.push(trie[x][i]);
            } else 
                trie[x][i] = 0;
        }

        while(!bfs.empty()){
            x = bfs.front();
            bfs.pop();
            
            for(int i = 0; i < K; i++){
                if(trie[x][i] != -1){
                    trie[trie[x][i]].fail = trie[trie[x].fail][i];
                    bfs.push(trie[x][i]);
                } else 
                    trie[x][i] = trie[trie[x].fail][i];
            }
        }

        adj.resize(sz(trie));
        for(int i = 1; i < sz(trie); i++)
            adj[trie[i].fail].pb(i);
    }

    void search(const string &s, bool sorted = false) {
        int x = 0, n = sz(s);
        occ.resize(n + 1);

        for(int i = 0; i < n; i++) {
            x = trie[x][s[i]];
            trie[x].occ.pb(i); 
        }

        function<void(int)> dfs = [&](int u) -> void {
            for(const int &v : adj[u]) {
                dfs(v);
                trie[u].occ.insert(trie[u].occ.end(), all(trie[v].occ));
            }

            for(const int &w : trie[u].word) 
                for(int pos : trie[u].occ) 
                    occ[pos + 1].pb(w);
        };

        dfs(0);
        if(sorted) for(int i = 1; i <= n; i++)
            sort(all(occ[i]));
    }
};

int main(){
 
    FastIO();
    int T,n,m,p; cin >> T;
    string t;
    for(int tc = 1; tc <= T; tc++){
        cin >> m >> p;
        vector<pair<string, int>> S(m);
        AhoCorasick ac;
        
        for(auto &[s, x] : S){
            cin >> s >> x;
            ac.insert(s);
        }

        ac.build();

        cin >> t;
        n = sz(t);
        ac.search(t);

        vector<ll> dp(n + 1, 0);

        for(int i = 1; i <= n; i++){
            dp[i] = dp[i - 1] - p;
            for(int &j : ac.occ[i])
                dp[i] = max(dp[i], dp[i - sz(S[j].fi)] + S[j].se);
        }
        
        cout << "Case " << tc << ": " << dp[n] << endl;
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
