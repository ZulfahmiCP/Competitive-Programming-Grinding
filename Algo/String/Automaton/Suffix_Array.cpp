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
template<typename K, typename V>void debug(const map<K, V>& c);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct RMQ {
    int N, LOG;
    vector<vector<int>> table;
    vector<int> log_table;

    void build(const vector<int>& arr) {
        N = arr.size();
        LOG = log2(N) + 1;

        table.assign(N, vector<int>(LOG));
        log_table.assign(N + 1, 0);

        for(int i = 2; i <= N; i++)
            log_table[i] = 1 + log_table[i >> 1];

        for(int i = 0; i < N; i++)
            table[i][0] = arr[i];

        for(int j = 1; j < LOG; j++)
            for(int i = 0; i + (1 << j) <= N; i++)
                table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }

    int val(int l, int r){
        int k = log_table[r - l + 1];
        return min(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

struct Suffix {
    int N;
    string S;
    vector<int> P, LCP;
    RMQ rmq;

    Suffix(string s) : N(sz(s)), S(s), P(N), LCP(N) {
        s += '$';
        int n = sz(s), k = 0;
        vector<int> p(n), c(n);
        vector<pair<int, int>> a(n);
        
        for(int i = 0; i < n; i++)  
            a[i] = {s[i], i};
        sort(all(a));

        for(int i = 0; i < n; i++)
            p[i] = a[i].se;
        c[p[0]] = 0;

        for(int i = 1; i < n; i++)
            c[p[i]] = c[p[i - 1]] + (a[i].fi != a[i - 1].fi);
        
        for(; (1 << k) < n; k++) {
            for(int i = 0; i < n; i++)
                p[i] = (p[i] - (1 << k) + n) % n;

            count_sort(p, c);

            vector<int> c_new(n);
            c_new[p[0]] = 0;

            for(int i = 1; i < n; i++){
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
                pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                c_new[p[i]] = c_new[p[i - 1]] + (prev != now);
            }

            c = c_new;
        }

        for(int i = 0; i < N; i++)
            P[i] = p[i + 1];
        rmq.build(P);

        for(int i = 0, j = 0; i < n - 1; i++, j = max(j - 1, 0)){
            while(s[i + j] == s[p[c[i] - 1] + j])
                j++;
            LCP[i] = j;
        }
    }

    bool find(const string &t) {
        int n = sz(t), l = 0, r = N - 1, m;

        for(string suff; l <= r;){
            m = (l + r) >> 1;
            suff = S.substr(P[m], min(N - P[m], n));

            if(sz(suff) == n && suff == t)
                return 1;

            t < suff ? r = m - 1 : l = m + 1;
        }

        return 0;
    }

    int count(const string &t) {
        auto [low, high] = bound(t);
        return high - low + 1;
    }

    int first_pos(const string &t) {
        auto [low, high] = bound(t);
        return low == -1 ? -1 : rmq.val(low, high);
    }

    pair<int, int> bound(const string &t) {
        int n = sz(t), low, high;
        int l = 0, r = N - 1, m;

        for(string suff; l <= r;){
            m = (l + r) >> 1;
            suff = S.substr(P[m], min(N - P[m], n));
            t <= suff ? low = m, r = m - 1 : l = m + 1;
        }

        if(low >= N || S.substr(P[low], n) != t)
            return {-1, -1};

        high = low, l = low + 1, r = N - 1;
        for(string suff; l <= r;){
            m = (l + r) >> 1;
            suff = S.substr(P[m], min(N - P[m], n));
            t >= suff ? high = m, l = m + 1 : r = m - 1;
        }

        return {low, high};
    }

    string suffix(int i) {
        return S.substr(P[i], N - P[i]);
    }

    string lcp(int i) {
        return S.substr(i, LCP[i]);
    }

    void count_sort(vector<int> &p, vector<int> &c) {
        int n = sz(p);
        vector<int> cnt(n, 0), p_new(n), pos(n);

        for(int &x : c)
            cnt[x]++;
        
        pos[0] = 0;
        for(int i = 1; i < n; i++)
            pos[i] = pos[i - 1] + cnt[i - 1];
        
        for(int &x : p){
            p_new[pos[c[x]]] = x;
            pos[c[x]]++;
        }

        p = p_new;
    }
};

int main(){
 
    FastIO();
    string s; cin >> s;
    Suffix suff(s);

    for(int i = 0; i < sz(s); i++)
        debug(i, suff.LCP[i], suff.lcp(i));

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
