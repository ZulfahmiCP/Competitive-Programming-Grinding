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
template<typename T>void debug(const multiset<T>& c);
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
    static const int K = 26;
    struct Node {
        int next[K];
        bool word = 0;
        multiset<int> dep;

        Node() {fill(next, next + K, -1);}

        int &operator[](char c) {assert('a' <= c && c <= 'z'); return next[c - 'a'];} 

        void merge(Node &a) {
            if(sz(dep) < sz(a.dep))
                swap(dep, a.dep);

            for(const auto &d : a.dep)
                dep.insert(d);

            a.dep.clear();
        }
    };

    vector<Node> trie;

    Trie() : trie(1) {}

    void insert(const string &s) {
        int x = 0;

        for(char c : s) {
            if(trie[x][c] == -1){
                trie[x][c] = sz(trie);
                trie.pb(Node());
            }

            x = trie[x][c];
        }

        trie[x].word = 1;
    }

    ll solve() {
        dfs(0, 0);
        // debug(trie[0].dep);
        return accumulate(all(trie[0].dep), 0LL);
    }

    void dfs(int x, int d) {
        for(char c = 'a'; c <= 'z'; c++){
            if(trie[x][c] == -1) continue;
            dfs(trie[x][c], d + 1);
            trie[x].merge(trie[trie[x][c]]);
        }

        if(trie[x].word){
            trie[x].dep.insert(d);
        } else if(d) {
            trie[x].dep.erase(prev(trie[x].dep.end()));
            trie[x].dep.insert(d);
        }
    }
} trie;

int main(){
 
    FastIO();
    int n; cin >> n;
    string s;

    for(int i = 0; i < n; i++){
        cin >> s;
        trie.insert(s);
    }

    cout << trie.solve() << endl;

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
template<typename T, typename... A>void prd(const T& x, A... a){prd(x);cerr<<", ";prd(a...);}
template<typename... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
template<typename T> void debug(const multiset<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
