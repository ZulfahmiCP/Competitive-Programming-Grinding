#include <bits/stdc++.h>

#define fi first 
#define se second 
#define ll long long 
#define pb push_back
#define ppb pop_back 
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'

using namespace std;

void FastIO() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

struct AhoCorasick {
    static const int K = 26;
    struct Node {
        vector<int> word, occ;
        int next[K], fail = -1, cnt = 0, dep = 0;

        Node() {fill(next, next + K, -1);}

        int &operator[](char c) {assert('a' <= c && c <= 'z'); return next[c - 'a'];}
    };

    int N;
    vector<Node> trie;
    vector<vector<int>> adj, occ;

    AhoCorasick() : trie(1), N(0) {}

    void insert(const string &s) {
        int x = 0;

        for(char c : s) {
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

        for(char c = 'a'; c <= 'z'; c++){
            if(trie[x][c] != -1){
                trie[trie[x][c]].fail = x;
                bfs.push(trie[x][c]);
            } else {
                trie[x][c] = 0;
            }
        }

        while(!bfs.empty()){
            x = bfs.front();
            bfs.pop();

            for(char c = 'a'; c <= 'z'; c++){
                if(trie[x][c] != -1){
                    trie[trie[x][c]].fail = trie[trie[x].fail][c];
                    bfs.push(trie[x][c]);
                } else {
                    trie[x][c] = trie[trie[x].fail][c];
                }
            }
        }

        adj.resize(sz(trie));
        for(int i = 1; i < sz(trie); i++)
            adj[trie[i].fail].pb(i);
    }

    void search(const string &s) {
        int x = 0, n = sz(s);
        occ.resize(N);

        for(int i = 0; i < n; i++){
            x = trie[x][s[i]];
            trie[x].occ.pb(i);
        }

        function<void(int)> dfs = [&](int u) -> void {
            for(const int &v : adj[u]){
                dfs(v);
                trie[u].occ.insert(trie[u].occ.end(), all(trie[v].occ));
            }

            for(const int &w : trie[u].word)
                for(int &pos : trie[u].occ)
                    occ[w].pb(pos);
        };

        dfs(0);
    }
} ac;

int main() {

    FastIO();
    int n; cin >> n;
    string s; cin >> s;

    int m; cin >> m;
    vector<string> T(m);

    for(auto &t : T){
        cin >> t;
        ac.insert(t);
    }

    ac.build();
    ac.search(s);

    vector<vector<int>> pos(n + 1);

    for(int i = 0; i < m; i++){
        for(int j : ac.occ[i]){
            pos[j + 1].pb(sz(T[i]));
        }
    }

    vector<ll> dp(n + 1, 0);

    for(int i = 1; i <= n; i++){
        dp[i] = dp[i - 1];
        for(int j : pos[i])
            if(i >= j)
                dp[i] = max(dp[i], dp[i - j] + 1LL * j * j);
    }

    cout << *max_element(all(dp)) << endl;

    return 0;
}