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

map<char, int> mp {
    {'A', 0}, {'U', 1}, {'G', 2}, {'C', 3}  
};

struct TriePref {
    static const int K = 4;
    struct Node {
        int next[K];
        int mn = INF;
        int mx = -1;

        Node() {fill(next, next + K, -1);}

        int &operator[](char c) {assert('A' <= c && c <= 'Z'); return next[mp[c]];}
    };

    vector<Node> trie;

    TriePref() : trie(1) {} 

    void insert(const string &s, int j) {
        int x = 0;

        for(char c : s){
            if(trie[x][c] == -1){
                trie[x][c] = sz(trie);
                trie.pb(Node());
            }

            x = trie[x][c];
            trie[x].mx = max(trie[x].mx, j);
            trie[x].mn = min(trie[x].mn, j);
        }
    }

    pair<int, int> get(const string &s) {
        int x = 0;
        
        for(char c : s){
            if(trie[x][c] == -1)
                return {INF, INF};
            x = trie[x][c];
        }

        return {trie[x].mn, trie[x].mx};
    }
} trie1;

struct TrieSuff {
    static const int K = 4;
    struct Node {
        int next[K];
        vector<int> id;

        Node() {fill(next, next + K, -1);}

        int &operator[](char c) {assert('A' <= c && c <= 'Z'); return next[mp[c]];}
    };

    vector<Node> trie;

    TrieSuff() : trie(1) {} 

    void insert(const string &s, int j) {
        int x = 0;

        for(char c : s){
            if(trie[x][c] == -1){
                trie[x][c] = sz(trie);
                trie.pb(Node());
            }

            x = trie[x][c];
            trie[x].id.pb(j);
        }
    }

    int get(const string &s, int l, int r) {
        int x = 0;
        
        for(char c : s){
            if(trie[x][c] == -1)
                return 0;
            x = trie[x][c];
        }

        l = lower_bound(all(trie[x].id), l) - trie[x].id.begin();
        r = upper_bound(all(trie[x].id), r) - trie[x].id.begin();

        return r - l;
    }
} trie2;

int main() {

    FastIO();
    int n, q; cin >> n >> q;
    vector<string> S(n);

    for(auto &s : S) cin >> s;

    sort(all(S));

    for(int i = 0; i < n; i++){
        trie1.insert(S[i], i);
        reverse(all(S[i]));
        trie2.insert(S[i], i);
    }

    string s,t;
    for(int i = 0; i < q; i++){
        cin >> s >> t;
        reverse(all(t));

        auto [l, r] = trie1.get(s);

        cout << trie2.get(t, l, r) << endl;
    }
    
    return 0;
}
