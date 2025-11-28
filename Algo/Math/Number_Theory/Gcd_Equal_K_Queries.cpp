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
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void prd(const T& x);
template <typename T, typename U>
    void prd(const pair<T, U>& value);
template <typename T, typename... Args>
    void prd(const T& value, Args... args);
template <typename... Args>
    void debug(Args... args);
template <typename K, typename V>
    void debug(const map<K, V>& cont);
template <typename T>
    void debug(const set<T>& cont);
template <typename T>
    void debug(const vector<T>& cont);
template <typename T>
    void debug(const vector<vector<T>> &cont);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

template<const int &M = MOD>
struct mod_int {
    int val;

    mod_int(ll v = 0) {if(v < 0) v = v % M + M; if(v >= M) v %= M; val = v;}

    friend mod_int power(mod_int a, ll b){mod_int c(1);for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend mod_int power(const mod_int &a, const mod_int b){return power(a, b.val);}
    friend mod_int inverse(const mod_int &a){return power(a, M - 2);}

    mod_int& operator+=(const mod_int &b){val += b.val; if (val >= M) val -= M; return *this;}
    mod_int& operator-=(const mod_int &b){val -= b.val; if (val < 0) val += M; return *this;}
    mod_int& operator*=(const mod_int &b){val = (ll)val * b.val % M; return *this;}
    mod_int& operator/=(const mod_int &b){return *this *= inv(b);}
    mod_int& operator++(){val = val == M - 1 ? 0 : val + 1; return *this;}
    mod_int& operator--(){val = val == 0 ? M - 1 : val - 1; return *this;}
    mod_int operator++(int){mod_int a = *this; ++*this; return a;}
    mod_int operator--(int){mod_int a = *this; --*this; return a;}

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
    friend std::istream& operator>>(std::istream& is, mod_int &a){return is >> a.val;}
};
using mint = mod_int<>;

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

    int comb(int A, int B) {
        if(A < B) return 0;
        return (fact[A] * inv[A - B] * inv[B]).val;
    }

    int perm(int A, int B) {
        if(A < B) return 0;
        return (fact[A] * inv[A - B]).val;
    }

    int perm_rep(int A, const vector<int> &B) {
        mint res = fact[A];
        for(const int &b : B)
            res *= inv[b];
        return res.val;
    }

    int comb_rep(int A, int B) {
        return comb(A + B - 1, B);
    }

    vector<mint>& operator[](int i) {
        assert(0 <= i && i < sz(C));
        return C[i];
    }
};

struct GCD_CNT {
    int MX; 
    vector<int> cnt, ans;
    Binomial C;

    GCD_CNT(int mx = 1e6) : MX(mx), cnt(MX + 1, 0), ans(MX + 1, 0), C(MX) {}

    void add(int x) {
        cnt[x]++;
    }

    void solve(int k = 2) {
        for(int i = 1; i <= MX; i++){
            for(int j = i; j <= MX; j += i)
                ans[i] += cnt[j];
            ans[i] = C.comb(ans[i], k);
        }

        for(int i = MX; i > 0; i--)
            for(int j = 2 * i; j <= MX; j += i)
                ans[i] -= ans[j];
    }

    int& operator[](int i) {
        assert(1 <= i && i <= MX);
        return ans[i];
    }
};

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

    int n; cin >> n;
    GCD_CNT g;

    for(int i = 0, a; i < n; i++){
        cin >> a;
        g.add(a);
    }

    g.solve();
    cout << g[1] << '\n';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& value){ cerr << "("; prd(value.first); cerr << ", "; prd(value.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& value, Args... args){prd(value); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
