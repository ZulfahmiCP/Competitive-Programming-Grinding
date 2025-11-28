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
    static const int K = 26;
    struct Node {
        int next[K], time = -1, word = 0, pref = 0;

        Node() {fill(next, next + K, 0);}

        int& operator[](char c) { assert('a' <= c && c <= 'z'); return next[c - 'a']; }
    };

    int N, last = 1, ver = 0;
    vector<Node> trie;
    vector<int> rt;

    Trie(int n, int m) : N(n), trie(1), rt(m + 1) {
        rt[0] = 1;
    }

    int clone(int i) {
        int j = sz(trie);
        trie.pb(Node());
        if (i != 0) trie[j] = trie[i];
        return j;
    }

    void insert(const string& s, int t) {
        assert(t + 1 < sz(rt));
        int x = clone(last);
        rt[t + 1] = last = x;

        trie[x].pref++;

        for (char c : s) {
            trie[x][c] = clone(trie[x][c]);
            x = trie[x][c];
            trie[x].pref++;
            trie[x].time = t;
        }

        trie[x].word++;
    }

    int count(int l, int r, const string& s) {
        int xr = rt[r + 1], xl = rt[l];
        for (char c : s) {
            if(trie[trie[xr][c]].pref - trie[trie[xl][c]].pref == 0)
                return 0;
            xr = trie[xr][c], xl =  trie[xl][c];
        }
        return trie[xr].word - trie[xl].word;
    }

    void del(int x, int t) {
        if(!x || trie[x].time != t) return;
        for(char c = 'a'; c <= 'z'; c++)
            del(trie[x][c], t);
        trie[x] = Node();
    }

    void remove() {
        assert(ver > 0);
        del(rt[ver], ver - 1);
        rt[ver--] = 0;
        last = ver > 0 ? rt[ver] : 1;
    }

    int lcp(int l, int r, const string& s) {
        int xr = rt[r + 1], xl = rt[l], ans = 0;

        int total = trie[xr].pref - trie[xl].pref;
        if(!total) return 0;
        
        for (char c : s) {
            int cnt = trie[trie[xr][c]].pref - trie[trie[xl][c]].pref;
            if(cnt != total) break;
            ans++;
            xr = trie[xr][c];
            xl = trie[xl][c];
        }
        
        return ans;
    }
};

int main(){
 
    FastIO();


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
