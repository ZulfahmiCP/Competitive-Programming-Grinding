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
    static const int LOG = 20;
    struct Node {
        int next[2];
        int time = -1;
        int cnt = 0;

        Node() {fill(next, next + 2, 0);}

        int &operator[](int i) {assert(0 <= i && i < 2); return next[i];}
    };

    int N, last_root = 1;
    vector<Node> trie;
    vector<int> roots; 

    Trie(int n, int m) : N(n), trie(2), roots(m + 1) {
        roots[0] = 1;
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
        int x = clone(last_root);
        roots[t + 1] = last_root = x;

        for(int i = LOG; i >= 0; i--){
            int c = (v >> i) & 1;
            
            trie[x][c] = clone(trie[x][c]);

            x = trie[x][c];
            trie[x].time = t;
            trie[x].cnt++;
        }
    }

    int cnt_greater_than(int l, int r, int v, int u) {
        int ans = 0, xr = roots[r + 1], xl = roots[l];

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
    int t,n; cin >> t;

    while(t--){
        cin >> n;
        vector<int> A(n), L(n), R(n);
        Trie trie(n, n);
        stack<int> st;

        for(int i = 0; i < n; i++){
            cin >> A[i];
            trie.insert(A[i], i);
        }

        for(int i = 0; i < n; i++){
            while(!st.empty() && A[st.top()] < A[i])
                st.pop();
            L[i] = st.empty() ? 0 : st.top() + 1;
            st.push(i);
        }

        while(!st.empty()) st.pop();

        for(int i = n - 1; i >= 0; i--){
            while(!st.empty() && A[st.top()] <= A[i])
                st.pop();
            R[i] = st.empty() ? n - 1 : st.top() - 1;
            st.push(i);
        }

        ll ans = 0;

        for(int m = 0, l,r; m < n; m++){
            l = L[m], r = R[m];

            if(m - l > r - m){
                for(int i = m; i <= r; i++)
                    ans += 1LL * trie.cnt_greater_than(l, m, A[i], A[m]) * A[m];
            } else {
                for(int i = l; i <= m; i++)
                    ans += 1LL * trie.cnt_greater_than(m, r, A[i], A[m]) * A[m];
            }
        }

        cout << ans << endl;
    }
    
    return 0;
}
