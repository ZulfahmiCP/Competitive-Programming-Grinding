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
 
#ifndef ONLINE_JUDGE
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}
ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<"[ ";for(auto v:c){prd(v);cerr<<' ';}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<"[ ";for(auto v:c){cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cerr<<' ';}cerr<<"]\n";}
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

struct SegTree {
    struct node {
        int go[16];
        node() {fill(go, go + 16, 0);}
    };  
    int N;
    vector<node> tree;

    SegTree(int n) : N(n), tree(4 * N) {} 

    #define lc(x) (x << 1) 
    #define rc(x) (x << 1) | 1

    node pull(node a, node b) {
        node c;
        for(int i = 0; i < 16; i++)
            c.go[i] = b.go[a.go[i]];
        return c;
    }

    void update(int j, char c, int v) {
        modify(1, 0, N - 1, j, c, v);
    }

    void modify(int x, int l, int r, int j, char c, int v) {
        if(l == r){
            for(int i = 0; i < 16; i++){
                if(c == '+')
                    tree[x].go[i] = (v + i) % 16;
                else 
                    tree[x].go[i] = (v ^ i);
            }
            return; 
        }

        int m = (l + r) >> 1;
        j <= m ? modify(lc(x), l, m, j, c, v) : modify(rc(x), m + 1, r, j, c, v);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }

    int calc() {
        return tree[1].go[0];
    }
};

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q; cin >> n >> q;
    SegTree seg(n);

    for(int i = 0; i < n; i++){
        char c; cin >> c;
        int x; cin >> x;
        seg.update(i, c, x);
    }

    for(int i = 0; i < q; i++){
        int j; cin >> j, j--;
        char c; cin >> c;
        int x; cin >> x;
        seg.update(j, c, x);
        cout << seg.calc() << endl;
    }
    
    return 0;
}
