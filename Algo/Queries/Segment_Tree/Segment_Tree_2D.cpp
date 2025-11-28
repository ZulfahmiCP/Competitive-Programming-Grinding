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

#define lc(x) (x << 1)
#define rc(x) (x << 1) | 1

struct SegTree2D {
    struct SegTree1D {
        int N;
        vector<int> tree;

        SegTree1D(int n = 0) : N(n), tree(4 * N) {}

        void update_x(int j, int v) {
            update_x(1, 0, N - 1, j, v);
        }

        void update_x(int x, int l, int r, int j, int v) {
            if(l == r){
                tree[x] += v;
                return;
            }
            int m = (l + r) >> 1;
            j <= m ? update_x(lc(x), l, m, j, v) : update_x(rc(x), m + 1, r, j, v);
            tree[x] = tree[lc(x)] + tree[rc(x)];
        }

        int calc_x(int l, int r) {
            return calc_x(1, 0, N - 1, l, r);
        }

        int calc_x(int x, int l, int r, int ql, int qr) {
            if(qr < l || r < ql) return 0;
            if(ql <= l && r <= qr) return tree[x];
            int m = (l + r) >> 1;
            return calc_x(lc(x), l, m, ql, qr) + calc_x(rc(x), m + 1, r, ql, qr);
        }
    };

    int N, M;
    vector<SegTree1D> tree;

    SegTree2D(int n, int m) : N(n), M(m), tree(4 * N) {
        build_y(1, 0, N - 1);
    }

    void build_y(int x, int l, int r) {
        tree[x] = SegTree1D(M);
        if(l == r) return;
        int m = (l + r) >> 1;
        build_y(lc(x), l, m);
        build_y(rc(x), m + 1, r);
    }

    void update(int qr, int qc, ll v) {
        update_y(1, 0, N - 1, qr, qc, v);
    }

    void update_y(int x, int l, int r, int qr, int qc, ll v) {
        if(l == r){
            tree[x].update_x(qc, v);
            return;
        }
        int m = (l + r) >> 1;
        qr <= m ? update_y(lc(x), l, m, qr, qc, v) : update_y(rc(x), m + 1, r, qr, qc, v);
        v = tree[lc(x)].calc_x(qc, qc) + tree[rc(x)].calc_x(qc, qc) - tree[x].calc_x(qc, qc);
        tree[x].update_x(qc, v);
    }

    int calc(int r1, int c1, int r2, int c2) {
        return calc_y(1, 0, N - 1, r1, c1, r2, c2);
    }

    int calc_y(int x, int l, int r, int r1, int c1, int r2, int c2) {
        if(r2 < l || r < r1) return 0;
        if(r1 <= l && r <= r2) return tree[x].calc_x(c1, c2);
        int m = (l + r) >> 1;
        return calc_y(lc(x), l, m, r1, c1, r2, c2) + calc_y(rc(x), m + 1, r, r1, c1, r2, c2);
    }
};

int main() {

    FastIO();
    
    
    return 0;
}

