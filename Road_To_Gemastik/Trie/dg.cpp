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
    const int LOG = 20;
    struct Node {
        int next[2];
        int cnt = 0;

        Node() {fill(next, next + 2, 0);}

        int &operator[](int i) {assert(0 <= i && i < 2); return next[i];}
    };

    vector<Node> trie;
    
    Trie() : trie(2) {}

    void insert(int v) {
        for(int i = LOG, x = 1, c; i >= 0; i--){
            c = (v >> i) & 1;
            if(!trie[x][c]){
                trie[x][c] = sz(trie);
                trie.pb(Node());
            }
            x = trie[x][c];
            trie[x].cnt++;
        }
    }

    int greater_xor_cnt(int v, int u) {
        int ans = 0, x = 1;

        for(int i = LOG; i >= 0 && x; i--){
            int cv = (v >> i) & 1;
            int cu = (u >> i) & 1;

            if(!cu){
                if(trie[x][cv ^ 1])
                    ans += trie[trie[x][cv ^ 1]].cnt;
                x = trie[x][cv];
            } else {
                x = trie[x][cv ^ 1];
            }
        }

        return ans;
    }

    int size() {
        return sz(trie);
    }
};

int main() {

    FastIO();
    int t,n; cin >> t;

    while(t--){
        cin >> n;
        vector<int> A(n), L(n), R(n);

        for(int &a : A) cin >> a;

        stack<int> st;

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
        map<pair<int, int>, int> who;
        vector<Trie> tries;

        for(int i = 0; i < n; i++)
            who[{L[i], R[i]}] = i;

        function<int(int, int)> solve = [&](int l, int r) -> int {
            int x = sz(tries);
            tries.pb(Trie());
            
            if(l > r) return x;

            assert(who.find({l, r}) != who.end());

            int m = who[{l, r}];
            
            if(l == r){
                tries[x].insert(A[m]);
                return x;
            }
            
            int lc = solve(L[m], m - 1);
            int rc = solve(m + 1, R[m]);
            
            if(m - L[m] > R[m] - m){
                swap(x, lc);

                tries[x].insert(A[m]);
                
                for(int i = m; i <= R[m]; i++)
                    ans += 1LL * tries[x].greater_xor_cnt(A[i], A[m]) * A[m];

                for(int i = m + 1; i <= R[m]; i++)
                    tries[x].insert(A[i]);
            } else {    
                swap(x, rc);

                tries[x].insert(A[m]);

                for(int i = m; i >= L[m]; i--)
                    ans += 1LL * tries[x].greater_xor_cnt(A[i], A[m]) * A[m];

                for(int i = m - 1; i >= L[m]; i--)
                    tries[x].insert(A[i]);
            }

            return x;
        };

        solve(0, n - 1);

        cout << ans << endl;
    }
    
    return 0;
}
