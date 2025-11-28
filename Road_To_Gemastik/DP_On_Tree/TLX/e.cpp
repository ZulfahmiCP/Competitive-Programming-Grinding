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
    struct Node {
        int next[2], pref = 0;
        
        Node() {fill(next, next + 2, -1);}

        int &operator[](char c) {assert('0' <= c && c <= '1'); return next[c - '0'];}
        int &operator[](int i) {assert(0 <= i && i < 2); return next[i];}
    };

    ll N, dep = 0, ans = 0;
    vector<Node> trie;
    vector<int> cnt;

    Trie(ll n, ll L) : trie(1), N(n), dep(L), cnt(100, 0) {}

    void insert(const string &s) {
        int x = 0;

        for(char c : s){
            if(trie[x][c] == -1){
                trie[x][c] = sz(trie);
                trie.pb(Node());
            }

            x = trie[x][c];
            trie[x].pref++;
        }
    }

    bool solve() {  
        dfs(0, dep);
        for(int i = 0; i < 100; i++)
            if(cnt[i] & 1) 
                return 1;
        return 0;
    }

    ll low(ll x) {
        return __builtin_ctz(x) + 1;
    }

    void dfs(int x, ll d) {
        if(trie[x][0] == -1 && trie[x][1] == -1)
            return;

        if(trie[x][0] == -1){
            cnt[low(d)]++;
        } else {
            dfs(trie[x][0], d - 1);
        }
        
        if(trie[x][1] == -1) {
            cnt[low(d)]++;
        } else {
            dfs(trie[x][1], d - 1);
        }
    }
};

int main() {

    FastIO();
    ll n,l; cin >> n >> l;
    Trie trie(n, l);
    string s;

    for(int i = 0; i < n; i++){
        cin >> s;
        trie.insert(s);
    }

    cout << (trie.solve() ? "Alice" : "Bob") << endl;
    
    return 0;
}

