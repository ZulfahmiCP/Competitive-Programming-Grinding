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

// Kalau keyword tidak unik, gunakan map 
struct AhoCorasick {
    static const int K = 27;
    struct Node {
        vector<int> word, occ;
        int next[K], fail = -1, cnt = 0, dep = 0;

        Node(){fill(next, next + K, -1);}

        int& operator[](char c){assert('a' <= c && c <= '{'); return next[c - 'a'];}
    };

    int N;
    vector<Node> trie;
    vector<vector<int>> adj;

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

        for(char c = 'a'; c <= '{'; c++){
            if(trie[x][c] != -1){
                trie[trie[x][c]].fail = x;
                bfs.push(trie[x][c]);
            } else 
                trie[x][c] = 0;
        }

        while(!bfs.empty()){
            x = bfs.front();
            bfs.pop();
            
            for(char c = 'a'; c <= '{'; c++){
                if(trie[x][c] != -1){
                    trie[trie[x][c]].fail = trie[trie[x].fail][c];
                    bfs.push(trie[x][c]);
                } else 
                    trie[x][c] = trie[trie[x].fail][c];
            }
        }

        adj.resize(sz(trie));
        for(int i = 1; i < sz(trie); i++)
            adj[trie[i].fail].pb(i);
    }

    vector<int> count(const string &s) {
        int x = 0, n = sz(s);
        vector<int> cnt(N, 0);

        for(char c : s){
            x = trie[x][c];
            trie[x].cnt++;
        }

        function<int(int)> dfs = [&](int u) -> int {
            int res = trie[u].cnt;
            for(int &v : adj[u])
                res += dfs(v);
            for(int &w : trie[u].word)
                cnt[w] = res;
            return res;
        };

        dfs(0);

        x = 0;
        
        for(char c : s){
            x = trie[x][c];
            trie[x].cnt--;
        }

        return cnt;
    }
} ac;

int main() {

    FastIO();
    int n; cin >> n;
    vector<string> S(n);

    for(auto &s : S) cin >> s;

    int m; cin >> m;
    vector<string> T(m);

    for(auto &t : T){
        cin >> t;
        ac.insert(t);
    }

    ac.build();

    string s1, s2;
    for(auto &s : S){
        s1 += s;
        s2 += s + '{';
    }

    vector<int> occ1 = ac.count(s1);
    vector<int> occ2 = ac.count(s2);

    for(int i = 0; i < m; i++)  
        cout << occ1[i] - occ2[i] << endl;
    
    return 0;
}
