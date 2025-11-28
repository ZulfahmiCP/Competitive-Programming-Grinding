#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'

using namespace std;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& x);
template<typename T, typename... A>void prd(const T& x, A... a);
template<typename... A>void debug(A... a);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);
void fail() {debug("DONE"); exit(0);}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;

void FastIO();

#define lc(x) (x << 1)
#define rc(x) (x << 1) | 1

struct SegTree {
    struct node {
        ll sum = 0, lz = 0;
    };

    int N;
    vector<int> arr;
    vector<node> tree;

    SegTree(int n) : N(n), arr(N), tree(4 * N) {}

    node pull(node a, node b) {
        return {
            a.sum + b.sum
        };
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x].sum = arr[l];
            return;
        }

        int m = (l + r) >> 1;

        build(lc(x), l, m);
        build(rc(x), m + 1, r);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }

    void push(int x, int l, int r) {
        if(!tree[x].lz)
            return;

        tree[x].sum += tree[x].lz * (r - l + 1);

        if(l != r){
            tree[lc(x)].lz += tree[x].lz;
            tree[rc(x)].lz += tree[x].lz;
        }

        tree[x].lz = 0;
    }

    void update(int l, int r, ll v) {
        modify(1, 0, N - 1, l, r, v);
    }

    void modify(int x, int l, int r, int ql, int qr, ll v) {
        push(x, l, r);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            tree[x].lz = v;
            push(x, l, r);
            return;
        }

        int m = (l + r) >> 1;

        modify(lc(x), l, m, ql, qr, v);
        modify(rc(x), m + 1, r, ql, qr, v);
        tree[x] = pull(tree[lc(x)], tree[rc(x)]);
    }

    ll calc(int l, int r) {
        return process(1, 0, N - 1, l, r).sum;
    }

    node process(int x, int l, int r, int ql, int qr) {
        push(x, l, r);

        if(l > qr || ql > r)
            return node();

        if(ql <= l && r <= qr)
            return tree[x];

        int m = (l + r) >> 1;

        return pull(process(lc(x), l, m, ql, qr),   
                    process(rc(x), m + 1, r, ql, qr));
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    SegTree seg(n);

    for(int i = 0, t,l,r,v; i < q; i++){
        cin >> t >> l >> r;

        if(t == 1){
            cin >> v;
            seg.update(l, r - 1, v);
        } else 
            cout << seg.calc(l, r - 1) << '\n';
    }

    return 0;
}
 
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
template<typename T, typename... A>void prd(const T& x, A... a){prd(x);cerr<<", ";prd(a...);}
template<typename... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
