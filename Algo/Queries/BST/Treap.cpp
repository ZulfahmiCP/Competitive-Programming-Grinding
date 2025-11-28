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
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

// reverse, sum, insert, delete, get

struct node {
    int val, prior, size;
    bool rev;
    ll sum;
    node *l, *r;

    node(int v) : val(v), sum(v), prior(rand()), size(1), l(NULL), r(NULL), rev(0) {}
};

struct Treap {
    node *root;

    int size(node *x) { return x ? x->size : 0; }
    ll suma(node *x) { return x ? x->sum : 0; }

    void insert(int v) {
        merge(root, root, new node(v));
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

    node *a, *b, *c, *d;

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

    void reverse(int l, int r) {
        split(root, a, b, l);  // a = [0, l - 1], b = [l, n - 1]
        split(b, b, c, r - l + 1); // b = 
        if(b) b->rev ^= true;
        merge(root, a, b);
        merge(root, root, c);
    }

    ll sum(int l, int r) {
        return prefix(root, r + 1) - prefix(root, l);
    }

    ll prefix(node *x, int pref) {
        push(x);
        if(!x || !pref) return 0;
        if(size(x) == pref) return suma(x);
        if(pref <= size(x->l)) return prefix(x->l, pref);
        return suma(x->l) + prefix(x->r, pref - size(x->l) - 1) + x->val;
    }

    int get(int i) {
        split(root, a, b, i);
        split(b, b, c, 1);
        int x = b ? b->val : -1;
        merge(b, b, c);
        merge(root, a, b);
        return x;
    }
} treap;

ostream &operator<<(ostream &out, node *x) {
	if (!x) return out;
	out << x->l << ' ' << x->val << ' ' << x->r;
	return out;
}

int main() {

    FastIO();
    int n, q; cin >> n >> q;

    for(int i = 0, x; i < n; i++){
        cin >> x;
        treap.insert(x);
    }

    for(int i = 0, t, l, r; i < q; i++){
        cin >> t >> l >> r, l--, r--;
        
        if(t == 1)
            treap.reverse(l, r);
        else 
            cout << treap.sum(l, r) << '\n';
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
