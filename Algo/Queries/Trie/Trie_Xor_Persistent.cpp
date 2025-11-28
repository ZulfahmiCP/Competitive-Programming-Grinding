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

struct Trie {
    static const int LOG = 30;
    struct Node {
        int next[2];
        int time = -1;
        int cnt = 0;

        Node() {fill(next, next + 2, 0);}

        int &operator[](int i) {assert(0 <= i && i < 2); return next[i];}
    };

    int N, last = 1, ver = 0;
    vector<Node> trie;
    vector<int> rt; 

    Trie(int n, int m) : N(n), trie(2), rt(m + 1) {
        rt[0] = 1;
    }

    int clone(int i) {
        int j = sz(trie);
        trie.pb(Node());
        if(i != 0) trie[j] = trie[i];
        return j;
    }

    bool go(int i, int l) {
        return (i ? trie[i].time >= l : 0);
    }

    void insert(int v, int t) {
        assert(t + 1 < sz(rt));
        int x = clone(last);
        rt[t + 1] = last = x;

        for(int i = LOG; i >= 0; i--){
            int c = (v >> i) & 1;
            
            trie[x][c] = clone(trie[x][c]);

            x = trie[x][c];
            trie[x].time = t;
            trie[x].cnt++;
        }
    }

    void del(int x, int t) {
        if(!x || trie[x].time != t) return;
        del(trie[x][0], t);
        del(trie[x][1], t);
        trie[x] = Node();
    }

    void remove() {
        assert(ver > 0);
        del(rt[ver], ver - 1);
        rt[ver--] = 0;
        last = ver > 0 ? rt[ver] : 1;
    }
    
    int max_xor(int l, int r, int v) {
        int ans = 0, x = rt[r + 1];

        for(int i = LOG, c; i >= 0; i--){
            c = (v >> i) & 1;
            ans <<= 1;

            if(go(trie[x][c ^ 1], l)){
                ans++;
                x = trie[x][c ^ 1];
            } else {
                x = trie[x][c];
            }
        }
        return ans;
    }

    int min_xor(int l, int r, int v) {
        int ans = 0, x = rt[r + 1];

        for(int i = LOG, c; i >= 0; i--){
            c = (v >> i) & 1;
            ans <<= 1;
            
            if(go(trie[x][c], l)){
                x = trie[x][c];
            } else {
                ans++;
                x = trie[x][c ^ 1];
            }
        }
        return ans;
    }

    int cnt_less_than(int l, int r, int v, int u) {
        int ans = 0, xr = rt[r + 1], xl = rt[l];

        for(int i = LOG; i >= 0 && xr; i--){
            int cv = (v >> i) & 1, cu = (u >> i) & 1;
            
            if(cu){
                int chr = trie[xr][cv], chl = trie[xl][cv];
                ans += (trie[chr].cnt - trie[chl].cnt);
                xr = trie[xr][cv ^ 1], xl = trie[xl][cv ^ 1];
            } else {
                xr = trie[xr][cv], xl = trie[xl][cv];
            }
        }
        
        return ans;
    }

    int kth_smallest_xor(int l, int r, int v, int k) {
        int ans = 0, xr = rt[r + 1], xl = rt[l];

        for(int i = LOG; i >= 0; i--){
            int c = (v >> i) & 1;
            int cnt = trie[trie[xr][c]].cnt - trie[trie[xl][c]].cnt;

            if(k <= cnt){
                xr = trie[xr][c], xl = trie[xl][c];
            } else {
                k -= cnt;
                ans |= (1 << i);
                xr = trie[xr][c ^ 1], xl = trie[xl][c ^ 1];
            }
        }
        
        return ans;
    }

    int cnt_greater_than(int l, int r, int v, int u) {
        int ans = 0, xr = rt[r + 1], xl = rt[l];

        for(int i = LOG; i >= 0 && xr; i--){
            int cv = (v >> i) & 1, cu = (u >> i) & 1;

            if(!cu){
                int chr = trie[xr][cv ^ 1], chl = trie[xl][cv ^ 1];
                ans += (trie[chr].cnt - trie[chl].cnt);
                xr = trie[xr][cv], xl = trie[xl][cv];
            } else {
                xr = trie[xr][cv ^ 1], xl = trie[xl][cv ^ 1];
            }
        }

        return ans;
    }
};

int main() {
    FastIO();
    int n, q;
    cin >> n >> q;
    
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    Trie pt(n, n);
    for (int i = 0; i < n; ++i) {
        pt.insert(a[i], i);
    }

    for(int i = 0; i < q; i++) {
        int l, r, x;
        cin >> x >> l >> r;
        l--; 
        r--;
        cout << pt.max_xor(r, x, l) << endl;
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
