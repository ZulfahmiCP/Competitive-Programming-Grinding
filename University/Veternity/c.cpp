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

struct node {
    char c;
    int val, prior, size;
    bool rev;
    ll sum;
    node *l, *r;

    node(int cc) : c(cc), sum(cc), prior(rand()), size(1), l(NULL), r(NULL), rev(0) {}
};

struct Treap {
    node *root;

    int size(node *x) { return x ? x->size : 0; }
    ll suma(node *x) { return x ? x->sum : 0; }

    void insert(char c) {
        merge(root, root, new node(c));
    }

    void pull(node *x) {
        if(!x) return;
        push(x->l), push(x->r);
        x->size = size(x->l) + size(x->r) + 1;
        x->sum = suma(x->l) + suma(x->r) + x->val;
    }

    void push(node *x) {
        if(!x || !x->rev) return;
        x->rev = 0;
        swap(x->l, x->r);
        if(x->l) x->l->rev ^= true;
        if(x->r) x->r->rev ^= true;
    }
    
    void merge(node *&x, node *l, node *r) {
        if(!l || !r){
            x = l ? l : r;
            return;
        }
        
        push(l), push(r);

        if(l->prior < r->prior){
            merge(l->r, l->r, r);
            x = l;
        } else {
            merge(r->l, l, r->l);
            x = r;
        }
        
        pull(x);
    }

    void split(node *x, node *&l, node *&r, int val) {
        if(!x){
            l = r = NULL;
            return;
        }

        push(x);

        if(size(x->l) < val){
            split(x->r, x->r, r, val - size(x->l) - 1);
            l = x;
        } else {
            split(x->l, l, x->l, val);
            r = x;
        }

        pull(x);
    }

    node *a, *b, *c, *d, *e, *f;

    void insert(int i, int x) {
		split(root, a, b, i); 
		auto v = new node(x);
		merge(a, a, v);
		merge(root, a, b);
	}

	void del(int i) {
		split(root, a, b, i);
		split(b, root, b, 1);
		merge(root, a, b);
	}

    void cut(int l, int r) {
		split(root, a, b, l); // a = [0, l - 1], b = [l, n - 1]
		split(b, c, d, r - l + 1); // c = [l, r], d = [r + 1, n - 1]
		merge(root, a, d); /// root = [0, l - 1] + [r + 1, n - 1]
		merge(root, root, c); // root = [0, l - 1] + [r + 1, n - 1] + [l, r]
    }

    char get(int i) {
        split(root, a, b, i);
        split(b, b, c, 1);
        char x = b->c;
        merge(b, b, c);
        merge(root, a, b);
        return x;
    }

    void cyclic(int l, int r, int k) {
        k %= (r - l + 1);
        if(!k) return;
        split(root, a, b, l); // a = [0, l - 1], b = [l, n - 1]
		split(b, c, d, r - l + 1); // c = [l, r], d = [r + 1, n - 1]
        split(c, e, f, k); // e = [l, l + k - 1], f = [l + k, r]
        merge(c, f, e); // c = [l + k, r] + [l, l + k - 1]
        merge(b, a, c); 
        merge(root, b, d);
    }
} treap;

int main(){
 
    FastIO();
    string s; cin >> s;
    int n = sz(s);

    for(int i = 0; i < n; i++)
        treap.insert(i, s[i]);

    int q; cin >> q;

    for(int i = 0, l,r,k; i < q; i++){
        cin >> l >> r >> k, l--, r--;
        treap.cyclic(l, r, k);
    }

    for(int i = 0; i < n; i++)
        cout << treap.get(i);

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
