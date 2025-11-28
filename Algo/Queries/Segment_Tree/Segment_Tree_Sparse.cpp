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
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct SegTree {
    struct node {
        ll sum, lz, l, r;
        node *lc, *rc;
        node(int _l, int _r) : sum(0), lz(-1), l(_l), r(_r), lc(nullptr), rc(nullptr) {}
    };
    int N;
    node* root;
    SegTree(int n) : N(n) {root = new node(0, N - 1);}

    void new_node(node* x) {
        if(x->l == x->r) return;
        int m = (x->l + x->r) >> 1;
        if(x->lc == nullptr) x->lc = new node(x->l, m);
        if(x->rc == nullptr) x->rc = new node(m + 1, x->r);
    }

    void push(node* x) {
        if(!x->lz) return;
        x->sum = (x->lz) * (x->r - x->l + 1);
        if(x->l != x->r) {
            new_node(x);
            x->lc->lz += x->lz, x->rc->lz += x->lz;
        }
        x->lz = 0;
    }

    void modify(node* x, int l, int r, int v) {
        push(x);
        if(r < x->l || x->r < l) return;
        if(l <= x->l && x->r <= r) {
            x->lz = v; push(x); return;
        }
        int m = (x->l + x->r) >> 1;
        new_node(x);
        modify(x->lc, l, r, v); modify(x->rc, l, r, v);
        x->sum = x->lc->sum + x->rc->sum;
    }
    
    ll process(node* x, int l, int r) {
        push(x);
        if(r < x->l || x->r < l) return 0;
        if(l <= x->l && x->r <= r) return x->sum;
        int m = (x->l + x->r) >> 1;
        new_node(x);
        return process(x->lc, l, m) + process(x->rc, m + 1, r);
    }
};      

struct SegTree {
    struct node {
        ll sum, lazy, l, r, left, right;
        node() : sum(0), lazy(-1), left(-1), right(-1) {}
    };
    int N;
    vector<node> tree;

    SegTree(int n) : N(n), tree(64 * N) {}

    void new_node(int x) {
        int m = (tree[x].l + tree[x].r) >> 1;

        if(tree[x].left == -1){
            tree[x].left = sz(tree);
            tree.pb(node());
            tree[tree[x].left].l == tree[x].l;
            tree[tree[x].left].r = m;
        }

        if(tree[x].right == -1){
            tree[x].right = sz(tree);
            tree.pb(node());
            tree[tree[x].right].l = m + 1;
            tree[tree[x].right].r = tree[x].r;
        }
    }

    void push(int x) {
        if(tree[x].lazy == -1)
            return;

        new_node(x);

        tree[tree[x].l].lazy = tree[tree[x].r].lazy = tree[x].lazy;
        tree[x].lazy = -1;
    }

    void update(int &l, int &r, int &v) {
        modify(0, l, r, v);
    } 

    void modify(int x, int l, int r, int &v) {
        push(x);

        if(l == tree[x].l && r == tree[x].r){
            tree[x].lazy = v;
            push(x);
            return;
        }

        int m = (tree[x].l + tree[x].r) >> 1;
        new_node(x);

        if(l <= m && m < r){
            modify(tree[x].left, l, m, v);
            modify(tree[x].right, m + 1, r, v);
        } else if(m >= r) 
            modify(tree[x].left, l, r, v);
        else 
            modify(tree[x].right, l, r, v);
        
        push(tree[x].left);
        push(tree[x].right);

        tree[x].sum = tree[tree[x].left].sum + tree[tree[x].right].sum;
    }

    ll calc(int l, int r) {
        return process(0, l, r);
    }

    ll process(int x, int l, int r) {
        push(x);

        if(l == tree[x].l && r == tree[x].r)
            return tree[x].sum;
        
        int m = (tree[x].l + tree[x].r) >> 1;
        
        new_node(x);

        if(l > m) return process(tree[x].right, l, r);
        if(r <= m) return process(tree[x].left, l, m);
        return process(tree[x].left, l, m) + process(tree[x].right, m + 1, r);
    }
};

int main(){
 
    FastIO();
    int t,n; cin >> t;

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
