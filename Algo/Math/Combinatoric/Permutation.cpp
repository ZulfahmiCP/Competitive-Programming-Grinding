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
template<typename T, typename U>void prd(const pair<T, U>& value);
template<typename T, typename... Args>void prd(const T& value, Args... args);
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

template <typename T>
struct Fenwick {
    int N;
    vector<T> bit;
 
    Fenwick(int n = 0, bool fill = 0) : N(n), bit(N + 1, 0) {
        if(fill) for(int i = 0; i < N; i++)
            update(i, 1);
    }

    void update(int i, int v) {
        for(i++; i <= N; i += i & -i) 
            bit[i] += v;
    }
 
    T calc(int i) {
        T sum = 0;
        for(i++; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }
 
    T calc(int l, int r) {
        return calc(r) - calc(l - 1);
    }
};

template<const int &M = MOD>
struct mod_int {
    int val;

    mod_int(ll v = 0) {if(v < 0) v = v % M + M; if(v >= M) v %= M; val = v;}

    friend mod_int power(mod_int a, ll b){mod_int c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend mod_int power(const mod_int &a, const mod_int b){return power(a, b.val);}
    friend mod_int inv(const mod_int &a){return power(a, M - 2);}

    mod_int& operator+=(const mod_int &b){val += b.val; if (val >= M) val -= M; return *this;}
    mod_int& operator-=(const mod_int &b){val -= b.val; if (val < 0) val += M; return *this;}
    mod_int& operator*=(const mod_int &b){val = (ll)val * b.val % M; return *this;}
    mod_int& operator/=(const mod_int &b){return *this *= inv(b);}
    mod_int& operator++(){val = val == M - 1 ? 0 : val + 1; return *this;}
    mod_int& operator--(){val = val == 0 ? M - 1 : val - 1; return *this;}
    mod_int operator++(int){mod_int a = *this; ++*this; return a;}
    mod_int operator--(int){mod_int a = *this; --*this; return a;}

    friend mod_int operator!(const mod_int &a){return a.val != 0;}
    friend mod_int operator-(const mod_int &a){return 0 - a;}
    friend mod_int operator+(const mod_int &a, const mod_int &b){return mod_int(a) += b;}
    friend mod_int operator-(const mod_int &a, const mod_int &b){return mod_int(a) -= b;}
    friend mod_int operator*(const mod_int &a, const mod_int &b){return mod_int(a) *= b;}
    friend mod_int operator/(const mod_int &a, const mod_int &b){return mod_int(a) /= b;}
    
    friend bool operator==(const mod_int &a, const mod_int &b){return a.val == b.val;}
    friend bool operator!=(const mod_int &a, const mod_int &b){return a.val != b.val;}
    friend bool operator>=(const mod_int &a, const mod_int &b){return a.val >= b.val;}
    friend bool operator<=(const mod_int &a, const mod_int &b){return a.val <= b.val;}
    friend bool operator>(const mod_int &a, const mod_int &b){return a.val > b.val;}
    friend bool operator<(const mod_int &a, const mod_int &b){return a.val < b.val;}
    
    friend std::ostream& operator<<(std::ostream& os, const mod_int &a){return os << a.val;}
    friend std::istream& operator>>(std::istream& is, mod_int &a){return is >> a.val; a = mod_int(a.val);}
};
using mint = mod_int<>;

struct Permutation {
    Fenwick<ll> fenwick;

    ll order(vector<ll> A) {
        ll N = sz(A), K = 1;
        vector<ll> fact(N + 1);

        fact[0] = 1;
        for(int i = 1; i <= N; i++)
            fact[i] = fact[i - 1] * i;
        
        fenwick = Fenwick<ll>(N + 1);
        for(ll &a : A) a--;
        reverse(all(A));

        for(int i = 0; i < N; i++){
            K += fact[i] * fenwick.calc(A[i]);
            fenwick.update(A[i], 1);
        }

        return K;
    }

    vector<ll> kth_perm(ll N, ll K) {
        fenwick = Fenwick<ll>(N, 1);
        vector<ll> A(N);

        A[N - 1] = K - 1;
        for(int i = N - 1; i > 0; i--){
            A[i - 1] += A[i] / (N - i);
            A[i] %= (N - i);
        }

        A[0] %= N;

        for(int i = 0; i < N; i++){
            A[i] = bin_search(1, N, A[i] + 1);
            fenwick.update(A[i] - 1, -1);
        }

        return A;
    }

    int bin_search(int l, int r, ll x) {
        if(l >= r) return r;
        int m = (l + r) >> 1;
        return (fenwick.calc(m - 1) >= x ? bin_search(l, m, x) : 
                                           bin_search(m + 1, r, x));
    }
} perm;

ll fact(int n) {
    ll f = 1;
    for(int i = n; i > 1; i--){
        if(f * i > 1e8) break;
        f *= i;
    }
    return f;
}

int main(){
 
    FastIO();
    int n; cin >> n;
    vector<ll> P(n);
    iota(all(P), 1);

    for(ll k = 1; k <= fact(n); k++){
        auto A = perm.kth_perm(n, k);
        for(int i = 0; i < n; i++)
            assert(A[i] == P[i]);
        assert(k == perm.order(A));
        // debug(A);
        // debug(P);
        // debug(k, perm.order(A));newl;
        next_permutation(all(P));
    }

    debug("SOLVE");

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& value){cerr<<"(";prd(value.first);cerr<<", ";prd(value.second);cerr<<")";}
template<typename T, typename... Args>void prd(const T& value, Args... args){prd(value);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr << "]\n";}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c) { for (const auto &v : c) debug(v); cerr << '\n';}
