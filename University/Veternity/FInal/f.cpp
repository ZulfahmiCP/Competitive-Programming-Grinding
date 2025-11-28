#include <bits/stdc++.h>

#define fi first 
#define se second 
#define ll long long 
#define pb push_back
#define ppb pop_back 
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'

using namespace std;

void FastIO() {ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);}

const int MOD = 1e9 + 7;

template<const int &M = MOD> struct modi {
    int v;

    modi(ll x = 0) { if(x < 0) x = x % M + M; if(x >= M) x %= M; v = x; }

    modi operator+=(const modi &b) {v += b.v; if(v >= M) v -= M; return *this;}
    modi operator-=(const modi &b) {v -= b.v; if(v < 0) v += M; return *this;}
    modi operator*=(const modi &b) {v = (ll)v * b.v % M; return *this;}

    friend modi operator+(const modi &a, const modi &b) {return modi(a) += b;}
    friend modi operator-(const modi &a, const modi &b) {return modi(a) -= b;}
    friend modi operator*(const modi &a, const modi &b) {return modi(a) *= b;}
};
using mint = modi<>;

struct Matrix {
    int N, M;
    vector<vector<mint>> Mat;

    Matrix() {}
    Matrix(vector<vector<int>> ma) : N(sz(ma)), M(sz(ma[0])) {
        Mat.resize(N, vector<mint>(M));

        for(int i = 0; i < N; i++)
            for(int j = 0; j < M; j++)
                Mat[i][j] = mint(ma[i][j]);
    }

    Matrix(int n, int m, int x = 0) : N(n), M(m), Mat(N, vector<mint>(M, x)) {}
    
    Matrix &operator*=(const Matrix &A) {
        Matrix prod(N, A.M); assert(M == A.N);

        for(int i = 0; i < N; i++)
            for(int j = 0; j < A.M; j++)
                for(int k = 0; k < M; k++)
                    prod[i][j] += Mat[i][k] * A.Mat[k][j];

        return *this = prod;
    }

    friend Matrix operator*(const Matrix &a, const Matrix &b) {return Matrix(a) *= b;}
    vector<mint>& operator[](int i) { return Mat[i]; }
};

struct SegTree {
    int N;
    vector<Matrix> tree, mat;

    SegTree(int n) : N(n), mat(N), tree(4 * N) {}

    #define lc(x) (x << 1)
    #define rc(x) (x << 1) | 1

    void build() {
        build(1, 0, N - 1);
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = mat[l];
            return;
        }

        int m = (l + r) >> 1;
        build(lc(x), l, m);
        build(rc(x), m + 1, r);
        tree[x] = tree[lc(x)] * tree[rc(x)];
    }

    void update(int j, Matrix ma) {
        modify(1, 0, N - 1, j, ma);
    }

    void modify(int x, int l, int r, int j, Matrix &ma) {
        if(l == r){
            tree[x] = ma;
            return;
        }

        int m = (l + r) >> 1;
        j <= m ? modify(lc(x), l, m, j, ma) : modify(rc(x), m + 1, r, j, ma);
        tree[x] = tree[lc(x)] * tree[rc(x)];
    } 

    pair<int, int> solve(Matrix base) {
        Matrix res = tree[1];
        res *= base;
        return {res[0][0].v, res[2][0].v};
    }
};

int main() {

    FastIO();
    int n,q; cin >> n >> q;
    SegTree seg(n - 1);

    vector<vector<int>> A1 = {
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
    };

    vector<vector<int>> A2 = {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0}
    };

    vector<vector<int>> A3 = {
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0}
    };

    Matrix base1(A1), base2(A2), base3(A3);

    for(int i = 0; i < n - 1; i++)
        seg.mat[i] = base1;

    seg.build();

    Matrix basea({
        {1},
        {0},
        {0},
        {0}
    });    

    Matrix baseb({
        {0},
        {0},
        {1},
        {0}
    });   
    
    Matrix basec({
        {1},
        {0},
        {1},
        {0}
    });

    auto base = basea;

    auto ans = seg.solve(base);
    cout << ans.fi << ' ' << ans.se << endl;

    for(int i = 0, j,t; i < q; i++){
        cin >> j >> t, j -= 2;

        if(j == -1){
            if(!t) base = basea;
            else if(t == 1) base = baseb;
            else base = basec;
        } else {
            if(!t) seg.update(j, base1);
            else if(t == 1) seg.update(j, base2);
            else seg.update(j, base3);
        } 

        ans = seg.solve(base);
        cout << ans.fi << ' ' << ans.se << endl;
    }

    return 0;
}