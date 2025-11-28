#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct Trie {
    static const int K = 26;

    struct Node {
        array<int, K> next;
        bool is_word;
        string pref;

        Node(string pref = "", bool is_word = false) : pref(pref), is_word(is_word) {
            fill(all(next), -1);
        }

        int& operator[](int i){assert(0 <= i && i < K); return next[i];}
        int& operator[](char c){assert('a' <= c && c <= 'z'); return next[c - 'a'];}
    };

    vector<Node> trie;

    Trie() : trie(1) {}

    void insert(string &s) {
        int n = sz(s), u = 0, v;

        for(int i = 0, p; i < n; i += p){
            if(trie[u][s[i]] == -1){
                trie[u][s[i]] = sz(trie);
                trie.pb(Node(suffix(s, i), true));
                break;
            }

            u = trie[u][s[i]];
            p = LCP(suffix(s, i), trie[u].pref);

            if(p == sz(trie[u].pref)) continue;

            v = sz(trie);
            trie.pb(Node(suffix(trie[u].pref, p), trie[u].is_word));
            trie[v].next = trie[u].next;
            fill(all(trie[u].next), -1);
            trie[u][trie[v].pref[0]] = v;
            trie[u].pref = prefix(trie[u].pref, p);
            trie[u].is_word = i + p == n;
        }
    }

    bool search(const string &s) {
        int n = sz(s), u = 0;

        for(int i = 0, p; i < n;){
            if(trie[u][s[i]] == -1)
                return 0;

            u = trie[u][s[i]];
            p = LCP(suffix(s, i), trie[u].pref);

            i += p;
            if(i == n) 
                return trie[u].is_word;
        }

        return 0;
    }

    // return s[0:i - 1]
    string prefix(const string &s, int i) {
        return s.substr(0, i);
    }

    // return s[i:n - 1]
    string suffix(const string &s, int i) {
        return s.substr(i, sz(s) - i);
    }

    int LCP(const string &s, const string &t) {
        int i = 0;
        while(i < min(sz(s), sz(t)) && s[i] == t[i])
            i++;
        return i;
    }
} trie;

int main() {

    FastIO();


    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
