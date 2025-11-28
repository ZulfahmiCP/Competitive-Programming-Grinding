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
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

template<const int &M = MOD> struct modi {
    int v;

    modi(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}

    friend modi power(modi a, ll b){modi c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend modi power(const modi &a, const modi b){return power(a, b.v);}
    friend modi inverse(const modi &a){return power(a, M - 2);}

    modi& operator+=(const modi &b){v += b.v; if (v >= M) v -= M; return *this;}
    modi& operator-=(const modi &b){v -= b.v; if (v < 0) v += M; return *this;}
    modi& operator*=(const modi &b){v = (ll)v * b.v % M; return *this;}
    modi& operator/=(const modi &b){return *this *= inverse(b);}

    friend modi operator-(const modi &a){return 0 - a;}
    friend modi operator+(const modi &a, const modi &b){return modi(a) += b;}
    friend modi operator-(const modi &a, const modi &b){return modi(a) -= b;}
    friend modi operator*(const modi &a, const modi &b){return modi(a) *= b;}
    friend modi operator/(const modi &a, const modi &b){return modi(a) /= b;}
    
    friend bool operator==(const modi &a, const modi &b){return a.v == b.v;}
    friend bool operator!=(const modi &a, const modi &b){return a.v != b.v;}
    friend bool operator>=(const modi &a, const modi &b){return a.v >= b.v;}
    friend bool operator<=(const modi &a, const modi &b){return a.v <= b.v;}
    friend bool operator>(const modi &a, const modi &b){return a.v > b.v;}
    friend bool operator<(const modi &a, const modi &b){return a.v < b.v;}
    
    friend ostream& operator<<(ostream& os, const modi &a){return os << a.v;}
    friend istream& operator>>(istream& is, modi &a){return is >> a.v; a = modi(a.v);}
};
using mint = modi<>;

struct Binomial {
    vector<vector<mint>> C;
    vector<mint> fact, inv;

    Binomial(int N, int M) : C(N + 1, vector<mint>(M + 1, 0)) {
        for(int i = 0; i <= N; i++)
            for(int j = 0; j <= min(i, M); j++)
                C[i][j] = (!j || j == i ? 1 : C[i - 1][j - 1] + C[i - 1][j]);
    }

    Binomial(int N) : fact(N + 1), inv(N + 1) {
        fact[0] = 1;
        for(int i = 1; i <= N; i++)
            fact[i] = fact[i - 1] * i;
            
        inv[N] = inverse(fact[N]);
        for(int i = N - 1; i >= 0; i--)
            inv[i] = inv[i + 1] * (i + 1);
    }

    mint comb(int A, int B) {
        if(!B) return 1; 
        if(A < B) return 0;
        return fact[A] * inv[A - B] * inv[B];
    }

    mint perm(int A, int B) {
        if(!B) return 1; 
        if(A < B) return 0;
        return fact[A] * inv[A - B];
    }

    mint perm_rep(const vector<int> &A) {
        return perm_rep(accumulate(all(A), 0), A);
    }

    mint perm_rep(int A, const vector<int> &B) {
        mint res = fact[A];
        for(const int &b : B)
            res *= inv[b];
        return res;
    }

    mint comb_rep(int A, int B) {
        return comb(A + B - 1, A);
    }

    // return the # of solution in O(N)
    // x[1] + ... + x[n] = s, l <= x[i] <= r
    mint comb_rep_range(int n, int s, int l, int r) {
        if (s < l * n) return 0;

        s -= l * n, r -= l;
        mint ans = 0;

        for(int k = 0; k <= n; k++){
            mint cur = comb(s - k - k * r + n, n) * comb(n, k);
            ans += (k & 1 ? -cur : cur);
        }

        return ans;
    }

    mint catalan(int n) {
        return (n & 1 ? 0 : comb(n, n / 2) / (n / 2 + 1));
    }

    vector<mint>& operator[](int i) {
        assert(0 <= i && i < sz(C));
        return C[i];
    }

    mint operator()(int A, int B) {
        return comb(A, B);
    }
} comb(1e5);

int main(){
 
    FastIO();
    /* Property of Binomial Coefficient
     - C[n][k] = C[n][k - 1]
     - C[n][k] = C[n - 1][k - 1] + C[n][k - 1]
     - C[n][k] = (n / k) * C[n - 1][k - 1]

     - C[n][0] + C[n][1] + ... + C[n][n] = 2^n
     - C[0][k] + C[1][k] + ... + C[n][k] = C[n + 1][k + 1]
     - C[n][0] + C[n + 1][1] + ... + C[n + m][m] = C[n + m + 1][m]
     - (C[n][0])^2 + (C[n][1])^2 + ... + (C[n][n])^2 = C[2 * n][n]
     - C[n][1] + 2 * C[n][2] + ... + n * C[n][n] = n * 2 ^ (n - 1)
     - C[n][0] + C[n - 1][1] + ... + C[0][n] = F[n + 1]
    */

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
