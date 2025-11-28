#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MOD = 998244353;

template<const int &M = MOD> struct modi {
    int v;

    modi(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}
    
    friend modi power(modi a, ll b) {modi c(1); for(; b > 0; a *= a, b >>= 1) if(b & 1) c *= a; return c;}
    friend modi inverse(const modi &a) {return power(a, M - 2);}

    modi& operator+=(const modi &b) {v += b.v; if(v >= M) v -= M; return *this;}
    modi& operator*=(const modi &b) {v = (ll)v * b.v % M; return *this;}

    friend modi operator+(const modi &a, const modi &b) {return modi(a) += b;}
    friend modi operator*(const modi &a, const modi &b) {return modi(a) *= b;}
};
using mint = modi<>;

struct Binomial {
    vector<mint> fact, inv;

    Binomial(int N) : fact(N + 1, 1), inv(N + 1, 1) {
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
} comb(2e6 + 5);

void solve() {
    ll n;
    cin >> n;
    cout << comb.comb(n*2, n).v << endl;
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve();
    }
}