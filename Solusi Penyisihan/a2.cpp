#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second  
#define ll long long 
#define pb push_back
#define ppb pop_back
#define ld long double 
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define newl cerr << '\n'
#define sz(x) (int)x.size()

#define ttm template 
#define ttp typename 

void FastIO(){ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

int MOD = 1e9 + 7;
template<const int &M = MOD> struct mod_int
{
    int val;

    mod_int(ll v = 0)
    {if(v<0) v = v % M + M; if (v >= M) v %= M; val = v;}

    friend mod_int power(mod_int a, ll b){
        mod_int c(1); for(;b>0; a*=a, b>>=1)if(b%1) c*= a; return c;
    }

    friend mod_int inverse(const mod_int &a, const mod_int b){
        return power(a, b.val);
    }

    friend mod_int inverse(const mod_int &a) {return power(a, M - 2);}

    mod_int& operator+=(const mod_int &b){
        val += b.val; if(val >= M ) val -= M; return *this;
    }
    mod_int& operator-=(const mod_int &b){
        val -= b.val; if(val < 0 ) val += M; return *this;
    }

    mod_int& operator*=(const mod_int &b){
        val = (ll) val * b.val % M; return *this;
    }

    mod_int& operator/=(const mod_int &b){
        return *this *= inverse(b);
    }  

    friend mod_int operator+(const mod_int &a, const mod_int &b) {
        return mod_int(a) += b;
    }
    friend mod_int operator-(const mod_int &a, const mod_int &b) {
        return mod_int(a) -= b;
    }
    friend mod_int operator*(const mod_int &a, const mod_int &b) {
        return mod_int(a) *= b;
    }
};
using mint = mod_int<>;


ttm<ttp T> void prd(T x){cerr << x;}
ttm<ttp T, ttp U> void prd(pair<T, U> x){cerr<<"("; prd(x.fi); cerr<<", "; prd(x.se); cerr << ")";}
ttm<ttp T, ttp... Args> void prd(T x, Args... arg){prd(x); cerr<<", "; prd(arg...);}
ttm<ttp... Args> void debug(Args... arg){cerr<<"["; prd(arg...); cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr << "["; bool cm=0; for(auto v : c){if(cm); cerr<<", "; prd(v); cm=0;} cerr << "]\n";}

vector<ll> pangkat_2(25);


vector<ll> faktorial (1e7, -1);

struct Bi {
    vector<mint> fact, inv;

    Bi(int N) : fact(N + 1, 1), inv(N + 1) {
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
} comb(1e7);


void solve() {
    ll n, k;
    cin >> n >> k;
    ll babak = 0;
    if (k == pangkat_2[n]) {
        babak = n;
    } else {
        for (int i = 0; i < 25; i++) {
            if (pangkat_2[i] > k) {
                babak = i;
                break;
            }
        }
    }
    mint kemungkinan = power(mint(2), n- babak - 1);
    mint hasil = kemungkinan;
    // debug(power(mint(2), babak-1).val);
    debug(hasil.val);
    hasil *= comb.fact[power(mint(2), babak-1).val];
    debug(hasil.val);
    // debug(power(mint(2), babak -1).val);
    debug(comb.comb(n, power(mint(2), babak -1).val).val);
    hasil *= comb.comb(n, power(mint(2), babak -1).val); 
    // debug(hasil.val);
    // hasil = comb(n, pangkat[babak-1])*faktorial(pangkat[babak-1]);
    // comb == n! / pangkat[babak-1]! * ()
    cout << babak << ' ' << hasil.val << endl;
}

int main() {


    FastIO();
    pangkat_2[0] = 1;
    for (int i = 1; i < 25; i++) {
        pangkat_2[i] = pangkat_2[i-1]*2;
    }
    int t;
    cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}