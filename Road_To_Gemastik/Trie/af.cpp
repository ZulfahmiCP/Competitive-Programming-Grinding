#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
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

const int K = 10;
vector<int> p(10);

struct Trie {   
    struct Node {
        int next[K], pref = 0;

        Node() {fill(next, next + K, -1);}

        int& operator[](int i){assert(0 <= i && i < K); return next[i];}
        int& operator[](char c){assert('0' <= c && c <= '9'); return next[c - '0'];}
    };

    int N;
    vector<Node> trie;

    Trie() : trie(1), N(0) {}

    void insert(string &s) {
        s = string(19 - sz(s), '0') + s;

        int x = 0;

        for(char c : s){
            if(trie[x][c] == -1){
                trie[x][c] = sz(trie);
                trie.pb(Node());
            }

            x = trie[x][c];
            trie[x].pref++;
        }

        N++;
    }

    int calc(string &s) {
        s = string(19 - sz(s), '0') + s;

        int x = 0, ans = 0;
        bool ld = 1;

        for(char c : s){
            if(x == -1) break;
            if(s == "0") return N;
            if(c != '0') ld = 0;

            if(ld){
                x = trie[x][c];
                continue;
            }

            for(int i : p){
                if(i == (c - '0')) break;
                if(trie[x][i] != -1)
                    ans += trie[trie[x][i]].pref;
            }

            if(trie[x][c] == -1) break;
            x = trie[x][c];
        }

        return ans;
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

    int q; cin >> q;
    for(int i = 0; i < q; i++){
        for(int &j : p) cin >> j;
        cin >> s;
        cout << trie.calc(s) << endl;
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

/*
3
100 20 30
1
0 9 8 7 6 5 4 3 2 1 100
*/