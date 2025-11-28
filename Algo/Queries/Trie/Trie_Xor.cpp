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
#include <bset>
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

template<typename T> struct Trie {
    int N, cur = 1;
    const int LOG = 31;
    vector<array<int, 2>> trie;
    vector<int> cnt;

    Trie(int n) : N(n), trie(LOG * N, 0), cnt(LOG * N, 0) {
        insert(0);
    }
    Trie(const vector<T> &arr) : Trie(sz(arr)) {
        for(T &a : arr) insert(a);
    }

    void insert(T x) {
        for(int i = LOG, k = 1, b; i >= 0; i--){
            b = (x >> i) & 1;
            if(!trie[k][b]) 
                trie[k][b] = ++cur;
            k = trie[k][b];
            cnt[k]++;
        }
    }

    void remove(T x) {
        for(int i = LOG, k = 1, b; i >= 0; i--){
            b = (x >> i) & 1;
            k = trie[k][b];
            cnt[k]--;
        }
    }

    T max_xor(T x) {
        T ans = 0;

        for(int i = LOG, k = 1, b; i >= 0; i--){
            b = (x >> i) & 1;
            ans <<= 1;
            
            if(cnt[trie[k][b ^ 1]] > 0 && trie[k][b ^ 1]) 
                ans++, k = trie[k][b ^ 1];
            else 
                k = trie[k][b];
        }

        return ans;
    }

    T min_xor(T x) {
        T ans = 0;

        for(int i = LOG, k = 1, b; i >= 0; i--){
            b = (x >> i) & 1;
            ans <<= 1;
            
            if(cnt[trie[k][b]] > 0 && trie[k][b]) 
                k = trie[k][b];
            else 
                ans++, k = trie[k][b ^ 1];
        }

        return ans;
    }

    T count(T x, T y) { // count `a` s.t. a ^ x < y
        T ans = 0;

        for(int i = LOG, k = 1; i >= 0 && k; i--){
            int xb = (x >> i) & 1;
            int yb = (y >> i) & 1;

            if(yb){
                if(trie[k][xb]) 
                    ans += cnt[trie[k][xb]];
                k = trie[k][xb ^ 1];
            } else {
                k = trie[k][xb];
            }
        }

        return ans;
    }

    T count_greater_than_k(T x, T y) {
        T ans = 0;

        for(int i = LOG, k = 1; i >= 0 && k; i--){
            int xb = (x >> i) & 1;
            int yb = (y >> i) & 1;

            if(!yb){
                if(trie[k][xb ^ 1])
                    ans += cnt[trie[k][xb ^ 1]];
                k = trie[k][xb];
            } else {
                k = trie[k][xb ^ 1];
            }
        }

        return ans;
    }

    T mex() {
        T ans = 0, k = 1;

        for(int i = LOG, b; i >= 0 && k; i--){
            b = (lz >> i) & 1;

            if(trie[k][b] && sub[trie[k][b]] == (1 << i)){
                ans |= (1 << i);
                k = trie[k][b ^ 1];
            } else {
                k = trie[k][b];
            }
        }

        return ans;
    }
};

int main(){
 
    FastIO();
    int q, x; cin >> q;
    char op;
    Trie<int> trie(2e5);

    while(q--){
        cin >> op >> x;
        if(op == '+') trie.insert(x);
        else if(op == '-') trie.remove(x);
        else cout << trie.max_xor(x) << '\n';
    }

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
