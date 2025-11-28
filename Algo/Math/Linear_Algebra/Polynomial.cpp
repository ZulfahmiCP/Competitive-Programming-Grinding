#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <complex>
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
const double PI = acos(-1.0);

void FastIO();

using cd = complex<double>;

void fft(vector<cd>& A, bool inv) {
    int N = sz(A);

    for(int i = 1, j = 0, bit; i < N; i++){
        bit = N >> 1;
        for(; j & bit; bit >>= 1) 
            j ^= bit;
        j ^= bit;

        if(i < j) 
            swap(A[i], A[j]);
    }

    for(int k = 2; k <= N; k <<= 1){
        double angle = 2 * PI / k * (inv ? -1 : 1);
        cd wlen(cos(angle), sin(angle)), w;

        for(int i = 0; i < N; i += k) {
            w = 1;
            for(int j = 0; j < (k >> 1); j++){
                cd u = A[i + j], v = A[i + j + (k >> 1)] * w;
                A[i + j] = u + v, A[i + j + (k >> 1)] = u - v;
                w *= wlen;
            }
        }
    }

    if(inv) for(auto &a : A) a /= N;
}

vector<ll> multiply(const vector<ll>& A, const vector<ll>& B) {
    int N = 1;
    while(N <= max(sz(A), sz(B))) N <<= 1;
    N <<= 1;

    vector<cd> FA(all(A)), FB(all(B));

    FA.resize(N);FB.resize(N);
    fft(FA, 0); fft(FB, 0);
    for(int i = 0; i < N; ++i) 
        FA[i] *= FB[i];
    fft(FA, 1);

    vector<ll> ans(sz(A) + sz(B));

    for(int i = 0; i < sz(ans); i++) 
        ans[i] = round(FA[i].real());

    while(!ans.back()) ans.ppb();

    return ans;
}

struct poly {
    int N;
    vector<ll> P;

    poly(int n, int x = 0) : N(n), P(N, x) {}
    poly(const vector<ll>& arr) : P(arr), N(sz(P)) {}

    poly& operator+=(const poly &Q) {
        if(N > Q.N) P.resize(N = Q.N);
        for(int i = 0; i < N; i++) P[i] += Q[i];
        return *this;
    }
    poly& operator-=(const poly &Q) {
        if(N > Q.N) P.reserve(N = Q.N);
        for(int i = 0; i < N; i++) P[i] -= Q[i];
        return *this;
    }
    poly& operator*=(const poly &Q) {
        return (*this) = poly(multiply(P, Q.P));
    }

    friend poly operator+(const poly &P, const poly &Q) {return poly(P) += Q;}
    friend poly operator-(const poly &P, const poly &Q) {return poly(P) -= Q;}
    friend poly operator*(const poly &P, const poly &Q) {return poly(P) *= Q;}

    friend bool operator==(const poly &A, const poly &B) {return A.N == B.N && A.P == B.P;}
    friend bool operator!=(const poly &A, const poly &B) {return !(A == B);}

    friend poly power(poly A, ll B) {poly C(1, 1); for(;B > 0;A *= A,B >>= 1)if(B & 1)C *= A;return C;}
    friend poly deriv(poly A) {
        if(A.N == 1) return poly(0);
        poly B(A.N - 1);

        for(int i = 1; i < A.N; i++)
            B[i] = A[i - 1] * i;
        
        return B;
    }

    ll& operator[](int i) {return P[i];}
    const ll operator[](int i) const {return P[i];}

    friend ostream& operator<<(ostream& os, const poly &A){for(ll x : A.P) os << x << ' '; return os;}
};

int main() {

    FastIO();
    poly a({1, 2, 3});
    int n; cin >> n;
    cout << power(a, n);

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
