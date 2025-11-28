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

// Link(x, y): Connect node x to node y.
// Cut(x, y): Remove the edge between node x and node y.
// Connected(x, y): Check if node x and node y are in the same tree

struct Node {
    Node *left, *right, *par;
    bool rev;
    int val, sum;
    
    Node(int v) : val(v), sum(v), left(nullptr), right(nullptr), par(nullptr), rev(false) {}
};

typedef Node *vertex;

struct LCT {
    int N, M;
    vector<vertex> nodes;

    LCT(int n) : N(n), M(N) {
        for(int u = 0; u < N; u++)
            nodes.pb(new Node(u));
    }

    void make_root(vertex node) {
        access(node);
        node->rev ^= 1;
    }
    
    void add_edge(int u, int v) {link(nodes[u], nodes[v]);}
    void link(vertex x, vertex y) {
        make_root(x);
        if(!connected(x, y)) M--;
        x->par = y;
    }
    
    void remove_edge(int u, int v) {cut(nodes[u], nodes[v]);}
    void cut(vertex x, vertex y) {
        make_root(x);
        access(y);
        if(y->left == x && !x->right){
            y->left = y->left->par = nullptr;
            update(y);
            M++;
        }
    }
    
    bool connected(int u, int v) {return connected(nodes[u], nodes[v]);}
    bool connected(vertex x, vertex y) {
        make_root(x);
        access(y);
        return x == y || x->par;
    }

    void update(vertex node) {
        if(!node) return;
        node->sum = node->val;
        if(node->left) node->sum += node->left->sum;
        if(node->right) node->sum += node->right->sum;
    }
    
    void push(vertex node) {
        if(!node || !node->rev) return;
        swap(node->left, node->right);
        if(node->left) node->left->rev ^= 1;
        if(node->right) node->right->rev ^= 1;
        node->rev = 0;
    }
    
    void rotate(vertex node) {
        Node *p = node->par, *gp = p->par;

        if(p->left == node){
            p->left = node->right;
            if(node->right) node->right->par = p;
            node->right = p;
        } else {
            p->right = node->left;
            if(node->left) node->left->par = p;
            node->left = p;
        }

        p->par = node, node->par = gp;

        if(gp) gp->left == p ? gp->left = node : gp->right = node;
        update(p); update(node);
    }
    
    void splay(vertex node) {
        while(node->par){
            Node *p = node->par, *gp = p->par;
            if (gp) push(gp);
            push(p);push(node);

            if(gp){
                bool zigzig = (gp->left == p) == (p->left == node);
                rotate(zigzig ? p : node);
            } 
            rotate(node);
        }
    }
    
    vertex access(vertex node) {
        vertex last = nullptr;
        for(vertex y = node; y; y = y->par){
            splay(y);
            y->right = last;
            update(y);
            last = y;
        }
        
        splay(node);
        return last;
    }
};

int main() {

    FastIO();
    int n,m,q; cin >> n >> m >> q;
    LCT tree(n);

    for(int i = 0, u, v; i < m; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    cout << tree.M << ' ';

    int t,u,v;
    while(q--){
        cin >> t >> u >> v, u--, v--;
        t == 1 ? tree.add_edge(u, v) : tree.remove_edge(u, v);
        cout << tree.M << ' ';
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
