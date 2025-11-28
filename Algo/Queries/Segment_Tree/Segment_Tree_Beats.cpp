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


// Update : min=, max=, +=, =
// Query : sum, max, min
// If we have lz_eq, no other pushes should be made. They're all combined together in lz_eq.
// Otherwise we first apply lz_sum and then min= and max= pushes (in any order btw).

struct SegTree {
    struct node {
        ll sum, max, smax, min, smin;
        int maxc, minc;
        ll lz_sum = 0, lz_eq = -1;
    };

    int N;
    vector<int> arr;
    vector<node> tree;

    SegTree(int n) : N(n), arr(N), tree(4 * N) {}

    void pull(int x) {
        int l = 2 * x + 1, r = 2 * x + 2;

        tree[x] = {
            tree[l].sum + tree[r].sum,
            max(tree[l].max, tree[r].max),
            max(tree[l].smax, tree[r].smax),
            min(tree[l].min, tree[r].min),
            min(tree[l].smin, tree[r].smin),
            0, 0
        };
        
        for(int y : {l, r}){
            if(tree[x].max == tree[y].max) tree[x].maxc += tree[y].maxc;
            else tree[x].smax = max(tree[x].smax, tree[y].max);

            if(tree[x].min == tree[y].min) tree[x].minc += tree[y].minc;
            else tree[x].smin = min(tree[x].smin, tree[y].min);
        }
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = {arr[l], arr[l], -INFL, arr[l], INFL, 1, 1};
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);
        pull(x);
    }
 
    void push_eq(int x, int l, int r, ll v) {
        tree[x] = {v * (r - l + 1), v, -INFL, v, INFL, r - l + 1, r - l + 1, 0, v};
    }
 
    void push_min(int x, int l, int r, ll v) {
        if(tree[x].min >= v){
            push_eq(x, l, r, v);
        } else if (tree[x].max > v) {
            if(tree[x].smin == tree[x].max)
                tree[x].smin = v;
            tree[x].sum -= (tree[x].max - v) * tree[x].maxc;
            tree[x].max = v;
        }
    }
 
    void push_max(int x, int l, int r, ll v) {
        if(tree[x].max <= v){
            push_eq(x, l, r, v);
        } else if (tree[x].min < v) {
            if(tree[x].smax == tree[x].min)
                tree[x].smax = v;
            tree[x].sum += (v - tree[x].min) * tree[x].minc;
            tree[x].min = v;
        }
    }
 
    void push_sum(int x, int l, int r, ll v) {
        if(tree[x].min == tree[x].max){
            push_eq(x, l, r, tree[x].min + v);
            return;
        } 

        tree[x].max += v;
        if(tree[x].smax != -INFL) 
            tree[x].smax += v;

        tree[x].min += v;
        if(tree[x].smin != INFL)
            tree[x].smin += v;

        tree[x].sum += (r - l + 1) * v;
        tree[x].lz_sum += v;
    }
 
    void push(int x, int l, int r) {
        if(l == r) 
            return;

        int m = (l + r) >> 1;

        if(tree[x].lz_eq != -1){
            push_eq(2 * x + 1, l, m, tree[x].lz_eq);
            push_eq(2 * x + 2, m + 1, r, tree[x].lz_eq);
            tree[x].lz_eq = -1;
            return;
        } 

        push_sum(2 * x + 1, l, m, tree[x].lz_sum);
        push_sum(2 * x + 2, m + 1, r, tree[x].lz_sum);
        tree[x].lz_sum = 0;

        push_min(2 * x + 1, l, m, tree[x].max);
        push_min(2 * x + 2, m + 1, r, tree[x].max);

        push_max(2 * x + 1, l, m, tree[x].min);
        push_max(2 * x + 2, m + 1, r, tree[x].min);
    }
 
    void modify_min(int x, int l, int r, int ql, int qr, int v) {
        if(qr < l || r < ql || tree[x].max <= v) 
            return;

        if(ql <= l && r <= qr && tree[x].smax < v){
            push_min(x, l, r, v);
            return;
        }

        int m = (l + r) >> 1;

        push(x, l, r);
        modify_min(2 * x + 1, l, m, ql, qr, v);
        modify_min(2 * x + 2, m + 1, r, ql, qr, v);
        pull(x);
    }
 
    void update_min(int ql, int qr, int v) {
        modify_min(0, 0, N - 1, ql, qr, v);
    }
 
    void modify_max(int x, int l, int r, int ql, int qr, int v) {
        if(qr < l || r < ql || tree[x].min >= v) 
            return;

        if(ql <= l && r <= qr && tree[x].smin > v){
            push_max(x, l, r, v);
            return;
        }

        int m = (l + r) >> 1;

        push(x, l, r);
        modify_max(2 * x + 1, l, m, ql, qr, v);
        modify_max(2 * x + 2, m + 1, r, ql, qr, v);
        pull(x);
    }
 
    void update_max(int ql, int qr, int v) {
        modify_max(0, 0, N - 1, ql, qr, v);
    }
 
    void modify_eq(int x, int l, int r, int ql, int qr, int v) {
        if(qr < l || r < ql) 
            return;

        if(ql <= l && r <= qr){
            push_eq(x, l, r, v);
            return;
        }

        int m = (l + r) >> 1;

        push(x, l, r);
        modify_eq(2 * x + 1, l, m, ql, qr, v);
        modify_eq(2 * x + 2, m + 1, r, ql, qr, v);
        pull(x);
    }
 
    void update_eq(int ql, int qr, int v) {
        modify_eq(0, 0, N - 1, ql, qr, v);
    }
 
    void modify_sum(int x, int l, int r, int ql, int qr, int v) {
        if(qr < l || r < ql) 
            return;

        if(ql <= l && r <= qr){
            push_sum(x, l, r, v);
            return;
        }

        int m = (l + r) >> 1;

        push(x, l, r);
        modify_sum(2 * x + 1, l, m, ql, qr, v);
        modify_sum(2 * x + 2, m + 1, r, ql, qr, v);
        pull(x);
    }
 
    void update_sum(int ql, int qr, int v) {
        modify_sum(0, 0, N - 1, ql, qr, v);
    }
 
    ll process_sum(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) 
            return 0;

        if(ql <= l && r <= qr) 
            return tree[x].sum;

        int m = (l + r) >> 1;
        push(x, l, r);

        return process_sum(2 * x + 1, l, m, ql, qr) + 
               process_sum(2 * x + 2, m + 1, r, ql, qr);
    }
 
    ll calc_sum(int ql, int qr) {
        return process_sum(0, 0, N - 1, ql, qr);
    }
 
    ll process_min(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) 
            return INF;

        if(ql <= l && r <= qr) 
            return tree[x].min;

        int m = (l + r) >> 1;
        push(x, l, r);

        return min(process_min(2 * x + 1, l, m, ql, qr), 
                   process_min(2 * x + 2, m + 1, r, ql, qr));
    }
 
    ll calc_min(int ql, int qr) {
        return process_min(0, 0, N - 1, ql, qr);
    }
 
    ll process_max(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) 
            return -INF;

        if(ql <= l && r <= qr) 
            return tree[x].max;

        int m = (l + r) >> 1;
        push(x, l, r);

        return max(process_max(2 * x + 1, l, m, ql, qr), 
                   process_max(2 * x + 2, m + 1, r, ql, qr));
    }
 
    ll calc_max(int l, int r) {
        return process_max(0, 0, N - 1, l, r);
    }
};
 
int main() {
    
    FastIO();
    int n; cin >> n;
    SegTree seg(n);
    
    for(int &a : seg.arr)
        cin >> a;
    seg.build(0, 0, n - 1);

    int q,t,l,r,v; cin >> q;
    while(q--){
        cin >> t >> l >> r, l--, r--;

        if(t == 1){
            cin >> v;
            seg.update_min(l, r, v);
        } else if(t == 2) {
            cin >> v;
            seg.update_sum(l, r, v);
        } else 
            cout << seg.calc_sum(l, r) << '\n';
    }
    
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
