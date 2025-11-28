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
    static const int K = 26;
    struct Node {
        int next[K];
        bool pref[2];

        Node() {fill(next, next + K, -1); fill(pref, pref + 2, 0);}

        bool empty(){
            for(int i = 0; i < K; i++)
                if(next[i] != -1) return 0;
            return 1;
        }

        int &operator[](char c) {assert('a' <= c && c <= 'z'); return next[c - 'a'];}
    };

    vector<Node> trie;

    Trie() : trie(1) {}

    void insert(const string &s, bool a) {
        int x = 0;
        trie[x].pref[a] = 1;

        for(char c : s){
            if(trie[x][c] == -1){
                trie[x][c] = sz(trie);
                trie.pb(Node());
            }

            x = trie[x][c];
            trie[x].pref[a] = 1;
        }
    }

    bool ans() {
        return dp(0, 1);
    }

    bool dp(int x, bool d) {
        if(d && !trie[x].pref[0]) return 1;
        if(!d && !trie[x].pref[1]) return 0;

        for(char c = 'a'; c <= 'z'; c++){
            if(trie[x][c] == -1) continue;
            if(d && dp(trie[x][c], d ^ 1)) return 1;
            if(!d && !dp(trie[x][c], d ^ 1)) return 0;
        }

        return !d;
    }
} trie;

int main() {

    FastIO();
    int n; cin >> n;
    string s;

    for(int i = 0; i < n; i++){
        cin >> s;
        trie.insert(s, 1);
    }

    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> s;
        trie.insert(s, 0);
    }

    cout << (trie.ans() ? "Nina" : "Emilija") << endl;
    
    return 0;
}
