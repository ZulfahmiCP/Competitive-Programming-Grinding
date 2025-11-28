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

struct Trie {
    struct Node {
        int next[2], time = -1, cnt = 0;

        Node() {fill(next, next + 2, 0);}

        int &operator[](int i) {assert(0 <= i && i < 2); return next[i];}
    };

    int N, LOG = 20, last = 1, ver = 0;
    vector<Node> trie;
    vector<int> rt;

    Trie(int n, int m) : N(n), trie(2), rt(m + 1, 0) {}

    int clone(int i) {
        int j = sz(trie);
        trie.pb(Node());
        if(i) trie[j] = trie[i];
        return j;
    }

    bool go(int i, int l) {
        return (i ? trie[i].time >= l : 0);
    }

    void insert(int v) {
        int t = ver++;
        int x = clone(last);
        rt[t + 1] = last = x;

        for(int i = LOG, c; i >= 0; i--){
            c = (v >> i) & 1;
            trie[x][c] = clone(trie[x][c]);
            x = trie[x][c];
            trie[x].cnt++;
            trie[x].time = t;
        }
    }

    void del(int x, int t) {
        if(!x || !trie[x].time != t) return;
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

            if(go(trie[x][c ^ 1], l))
                ans++, x = trie[x][c ^ 1];
            else 
                x = trie[x][c];
        }

        return ans ^ v;
    }

    int cnt_less_than(int l, int r, int v, int u){
        int ans = 0, xr = rt[r + 1], xl = rt[l];

        for(int i = LOG; i >= 0 && xr; i--){
            int cv = (v >> i) & 1;
            int cu = (u >> i) & 1;

            if(cu){
                int chr = trie[xr][cv], chl = trie[xl][cv];
                ans += (trie[chr].cnt -trie[chl].cnt);
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
};

int main() {

    FastIO();
    int m; cin >> m;
    Trie trie(m, m);

    for(int i = 0; i < m; i++){
        int t; cin >> t;
        int l,r,x;

        if(!t){
            cin >> x;
            trie.insert(x);
        } else if(t == 1) {
            cin >> l >>  r >> x;
            l--, r--;
            cout << trie.max_xor(l, r, x) << endl;
        } else if(t == 2) {
            cin >> x;
            while(x--) trie.remove();
        } else if(t == 3) {
            cin >> l >> r >> x;
            l--, r--;
            cout << trie.cnt_less_than(l, r, 0, x + 1) << endl;
        } else {
            cin >> l >> r >> x;
            l--, r--;
            cout  << trie.kth_smallest_xor(l, r, 0, x) << endl;
        }
    }
    
    return 0;
}
