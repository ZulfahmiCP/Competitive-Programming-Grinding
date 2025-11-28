#include <bits/stdc++.h>

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
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct Trie {
    static const int K = 26;
    struct Node {
        int next[26], word = 0, pref = 0;

        Node(){fill(next, next + K, -1);}

        bool empty() {
            for(int i = 0; i < K; i++)
                if(next[i] != -1) return 0;
            return 1;
        }

        int& operator[](char c){assert('a' <= c && c <= 'z'); return next[c - 'a'];}
    };

    int N;
    vector<Node> trie; 

    Trie() : trie(1), N(0) {}

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

        trie[x].word++;
    }

    bool search(const string &s) {
        int x = 0;

        for(char c : s){
            if(trie[x][c] == -1)
                return 0;
            x = trie[x][c];
        }

        return trie[x].word > 0;
    }

    int pref_cnt(const string &s) {
        int x = 0;

        for(char c : s){
            if(trie[x][c] == -1)
                return 0;
            x = trie[x][c];
        }

        return trie[x].pref;
    }

    void remove(const string& s) {
        remove(0, s, 0);
    }

    bool remove(int x, const string& s, int d) {
        trie[x].pref--;

        if(d == sz(s)) 
            trie[x].word--;
        else if(remove(trie[x][s[d]], s, d + 1)) 
            trie[x][s[d]] = -1;
        
        return (x != 0 && trie[x].pref == 0);
    }

    int lcp(const string &s) {
        int x = 0, ans = 0;

        for(char c : s){
            if(trie[x][c] == -1)
                break;
            x = trie[x][c];
            if(trie[x].pref == 1)
                break;
            ans++;
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
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
