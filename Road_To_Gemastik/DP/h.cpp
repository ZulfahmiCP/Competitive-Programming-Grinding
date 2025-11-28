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

struct SegTree {
    int N;
    vector<int> tree;

    SegTree(int n) : N(n), tree(4 * N, 0) {}

    #define lc(x) (x << 1)
    #define rc(x) (x << 1) | 1
    
    void update(int j, int v) {
        modify(1, 0, N - 1, j, v);
    }

    void modify(int x, int l, int r, int j, int v) {
        if(l == r) {
            tree[x] = v;
            return;
        }

        int m = (l + r) >> 1;
        j <= m ? modify(lc(x), l, m, j, v) : modify(rc(x), m + 1, r, j, v);
        tree[x] = max(tree[lc(x)], tree[rc(x)]);
    }

    int calc(int l, int r) {
        return process(1, 0, N - 1, l, r);
    }

    int process(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) return 0;
        if(ql <= l && r <= qr) return tree[x];
        int m = (l + r) >> 1;
        return max(process(lc(x), l, m, ql, qr), process(rc(x), m + 1, r, ql, qr));
    }
};

int main() {

    FastIO();
    int n; cin >> n;
    vector<int> A(n); 

    for(int &a : A) cin >> a;

    vector<int> L(n), R(n);
    stack<int> st;

    for(int i = 0; i < n; i++){
        L[i] = i;
        while(!st.empty() && A[st.top()] < A[i])
            st.pop();

        L[i] = st.empty() ? 0 : st.top() + 1;
        st.push(i);
    }

    while(!st.empty()) st.pop();

    for(int i = n - 1; i >= 0; i--){
        R[i] = i;
        while(!st.empty() && A[st.top()] < A[i])
            st.pop();

        R[i] = st.empty() ? n - 1 : st.top() - 1;
        st.push(i);
    }

    vector<pair<int, int>> B(n);

    for(int i = 0; i < n; i++)
        B[i] = {A[i], i};
    
    sort(all(B));

    SegTree dp(n);

    int ans = 0;

    for(auto &[a, i] : B){
        dp.update(i, dp.calc(L[i], R[i]) + 1);
        ans = max(ans, dp.calc(i, i));
    }

    cout << ans << endl;

    return 0;
}
