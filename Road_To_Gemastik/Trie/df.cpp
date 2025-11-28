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
    int N, cur = 1, LOG = 20;
    vector<array<int, 2>> trie;
    vector<int> cnt;

    Trie(int n) : N(n), trie(LOG * N), cnt(LOG * N) {}

    void insert(int v) {
        for(int i = LOG, x = 1, c; i >= 0; i--){
            c = (v >> i) & 1;
            if(!trie[x][c])
                trie[x][c] = ++cur;
            
            x = trie[x][c];
            cnt[x]++;
        }
    }

    void remove(int v) {
        for(int i = LOG, x = 1, c; i >= 0; i--){
            c = (v >> i) & 1;
            x = trie[x][c];
            cnt[x]--;
        }
    }

    int max_xor(int v, int u) {
        int ans = 0, x = 1;

        for(int i = LOG; i >= 0 && x; i--){
            int cv = (v >> i) & 1;
            int cu = (u >> i) & 1;

            if(!cu){
                if(trie[x][cv ^ 1])
                    ans += cnt[trie[x][cv ^ 1]];
                x = trie[x][cv];
            } else {
                x = trie[x][cv ^ 1];
            }
        }

        return ans;
    }
};

const int MX = 1e5 + 5;
const int B = 700;

struct MO {
    struct que {
        int l, r, x;
        bool operator<(const que &oth) const {
            return make_pair(l / B, r) < make_pair(oth.l / B, r);
        }
    };

    int N;
    ll cnt = 0;
    vector<int> arr;
    vector<que> queries;
    Trie trie;

    MO(int n) : N(n), arr(N), trie(N) {}
    
    void add_query(int l, int r, int x) {
        queries.pb({l, r, x});
    }

    void add(int i, int m) {
        cnt += trie.max_xor(arr[i], m);
        trie.insert(arr[i]);
    }

    void remove(int i, int m) {
        trie.remove(arr[i]);
        cnt -= trie.max_xor(arr[i], m);
    }

    ll solve() {
        ll res = 0;

        if(queries.empty()) return 0;
        sort(all(queries));

        int L = queries[0].l, R = queries[0].l - 1;

        for(auto &[l, r, x] : queries){
            // cnt = 0;

            while(L > l) add(--L, x);
            while(L < l) remove(L++, x);
            while(R < r) add(++R, x); 
            while(R > r) remove(R--, x);

            debug(x, l+1, r+1, cnt);
            res += cnt * x;
        }

        return res;
    }
};

int main() {

    FastIO();
    int t,n; cin >> t;

    while(t--){
        cin >> n;
        vector<int> A(n);

        for(int &a : A) cin >> a;

        MO mo(n);

        mo.arr = A;

        vector<int> left(n), right(n);
        stack<int> st;

        for(int i = 0; i < n; i++){
            while(!st.empty() && A[st.top()] < A[i])
                st.pop();
            left[i] = st.empty() ? 0 : st.top() + 1;
            st.push(i);
        }

        while(!st.empty()) st.pop();

        for(int i = n - 1; i >= 0; i--){
            while(!st.empty() && A[st.top()] <= A[i])
                st.pop();
            right[i] = st.empty() ? n - 1 : st.top() - 1;
            st.push(i);
        }

        debug(A); debug(left); debug(right);

        for(int i = 0; i < n; i++)
            if(left[i] != right[i])
                mo.add_query(left[i], right[i], A[i]);

        cout << mo.solve() << endl;
    }
    
    return 0;
}
