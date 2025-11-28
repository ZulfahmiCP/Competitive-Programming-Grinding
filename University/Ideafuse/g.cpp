#include <bits/stdc++.h>

#define fi first 
#define se second 
#define ll long long 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define uniq(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'
#define ttm template
#define ttp typename

using namespace std;
ttm<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}

ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cm = 1;}cerr<<"]\n";}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

template<const int &M = MOD> struct modi {
    int v;

    modi(ll x = 0) {if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x;}

    modi& operator+=(const modi &b){v += b.v; if (v >= M) v -= M; return *this;}
    modi& operator*=(const modi &b){v = (ll)v * b.v % M; return *this;}
        
    friend modi operator+(const modi &a, const modi &b){return modi(a) += b;}
    friend modi operator*(const modi &a, const modi &b){return modi(a) *= b;}
};
using mint = modi<>;

struct Matrix {
    int N, M;
    vector<vector<mint>> Mat;

    Matrix(const vector<vector<int>> mat) : N(sz(mat)), M(sz(mat[0])) {
        Mat.resize(N, vector<mint>(M));
        for(int i = 0; i < N; i++)  
            for(int j = 0; j < M; j++)
                Mat[i][j] = mint(mat[i][j]);
    }

    Matrix(int n, int m, int x = 0) : N(n), M(m), Mat(N, vector<mint>(M, x)) {}

    Matrix& operator*=(const Matrix& A) {
        Matrix prod(N, A.M); assert(M == A.N);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < A.M; j++)
                for(int k = 0; k < M; k++)
                    prod[i][j] += Mat[i][k] * A.Mat[k][j];
        return *this = prod;
    }

    friend Matrix operator*(const Matrix &a, const Matrix &b) { return Matrix(a) *= b; }

    friend Matrix power(Matrix A, ll B) {
        Matrix C(A.N, A.M); assert(A.N == A.M);
        
        for(int i = 0; i < A.N; i++)
            C[i][i] = 1;

        for(; B > 0; A *= A, B >>= 1)
            if(B & 1) C *= A;

        return C;
    }

    vector<mint>& operator[](int i) {
        return Mat[i];
    }
};

int result(const Matrix &A, const Matrix &B, ll n) {
    int x = A.N;
    if(n == 0) return 1;
    auto C = power(A, n) * B;
    return (C[0][0] + C[2][0]).v;
}

int main() {

    FastIO();
    ll n; cin >> n;
    Matrix base(vector<vector<int>>{
        {1, 0, 1},
        {1, 0, 0},
        {0, 1, 0}
    });
    Matrix A(vector<vector<int>>{{1}, {1}, {0}});

    cout << result(base, A, n - 1) << endl;

    return 0;
}

