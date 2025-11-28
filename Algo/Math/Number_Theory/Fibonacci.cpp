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

/*
Property of Fibonacci Sequence
 - The last digit has a cycle of length 60.
 - F[n] % m has a cycle of at most 6m.
 - F[m] * F[n + 1] - F[m - 1] * F[n] = (-1)^n * F[m - n]
 - F[m] * F[n] + F[m - 1] * F[n - 1] = F[m + n - 1]
 - F[m] * F[n + 1] + F[m - 1] * F[n] = F[m + n]
 - F[n - 1] * F[n + 1] - F[n] * F[n] = (-1)^n
 - F[n + k] = F[k] * F[n + 1] + F[k - 1] * F[n]
 - F[2 * n] = F[n] * (F[n + 1] * F[n - 1])
 - F[n * k] is multiple of F[n]
 - If F[n] | F[m] ==> n | m
 - gcd(F[m], F[n]) = F[gcd(m, n)]
 - n is fibonacci <==> (5 * n^2 + 4) or (5 * n^2 - 4) is a perfect square
 - Any three consecutive fib are pairwise coprime
 - define f = sqrt(5) ==> F[n] = 1/f( ((1 + f) / 2) ^ n - ((1 - f) / 2) ^ n )

Series
 - F[1]^2 + ... + F[n]^2 = F[n] * F[n + 1]
 - F[1] + F[2] + ... + F[n] = F[n + 2] - 1
 - F[1] + F[3] + ... + F[2n - 1] = F[2n]
 - F[2] + F[4] + ... + F[2n] = F[2n + 1] - 1
 - F[n] = 276601605(691504013^n - 308495997^n) (mod 1e9 + 9)
*/

// return {F[n], F[n + 1]}
pair<int, int> fib (int n) {
    if(!n) return {0, 1};

    auto p = fib(n >> 1);
    int a = (p.fi * (2 * p.se - p.fi)) % MOD;
    int b = (p.fi * p.fi + p.se * p.se) % MOD;
    
    if(n & 1) return {b, (a + b) % MOD};
    else return {a, b};
}

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
