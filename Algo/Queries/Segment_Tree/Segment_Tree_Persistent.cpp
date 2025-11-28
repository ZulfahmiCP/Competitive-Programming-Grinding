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
        ll sum;
        node *left, *right;

        node(int v) : sum(v), left(nullptr), right(nullptr) {}
        node(node* l, node* r) : sum(0), left(l), right(r) {
            if(left) sum += left->sum;
            if(right) sum += right->sum;
        }
    };
    int N;
    vector<node*> root;
    vector<int> arr;

    SegTree(int n) : N(n), arr(N) {}
    SegTree(const vector<int>& A) : N(sz(A)), arr(A) {
        build();
    }

    void build() {
        root.pb(build(0, N - 1));
    }

    node* build(int l, int r) {
        if(l == r) return new node(arr[l]);
        int m = (l + r) >> 1;
        return new node(build(l, m), build(m + 1, r));
    }

    void update(int k, int j, int v) {
        root[k] = modify(root[k], 0, N - 1, j, v);
    }

    node* modify(node* x, int l, int r, int j, int v) {
        if(l == r) return new node(v);
        int m = (l + r) >> 1;
        return (j <= m ? new node(modify(x->left, l, m, j, v), x->right)
                       : new node(x->left, modify(x->right, m + 1, r, j, v)));
    }

    void copy(int k) {
        root.pb(root[k]);
    }

    ll calc(int k, int l, int r) {
        return process(root[k], 0, N - 1, l, r);
    }

    ll process(node* x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql)
            return 0;

        if(ql <= l && r <= qr)
            return x->sum;

        int m = (l + r) >> 1;
        return process(x->left, l, m, ql, qr) + 
               process(x->right, m + 1, r, ql, qr);
    }
};

int main() {

    FastIO();
    int n,q; cin >> n >> q;
    SegTree seg(n);

    for(int &a : seg.arr)
        cin >> a;
    seg.build();

    for(int i = 0, t, l, r, j, v, k; i < q; i++){
        cin >> t >> k, k--;

        if(t == 1){
            cin >> j >> v, j--;
            seg.update(k, j, v);
        } else if(t == 2) {
            cin >> l >> r, l--, r--;
            cout << seg.calc(k, l, r) << '\n';
        } else 
            seg.copy(k);
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
