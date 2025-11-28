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

struct Fenwick {
    int N;
    vector<ll> bit;

    Fenwick(int n) : N(n), bit(N + 1, 0) {}

    void update(int i, ll v) {
        for(;i <= N; i += i & -i)
            bit[i] += v;
    }

    ll calc(int i) {
        ll sum = 0;
        for(;i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }

    ll calc(int l, int r) {
        return calc(r) - calc(l - 1);
    }
};

int main() {

    FastIO();
    int n,q; cin >> n >> q;
    vector<int> A(n);

    for(int &a : A) cin >> a;

    set<int> st;
    Fenwick fen1(n), fen2(n);

    auto update = [&](int k, int v) {
        assert(1 <= k && k <= n);
        fen1.update(k, v);
        fen2.update(k, 1LL * v * k);
    };

    for(int i = 0, j = 0; i < n; i = ++j){
        while(j + 1 < n && A[i] == A[j + 1])    
            j++;
        
        st.insert(j);
        update(j - i + 1, A[j]);
    }

    st.insert(n);

    auto pos = [&](int i) -> int {
        if(i < 0 || i >= n) return -1;
        auto p = st.upper_bound(i);
        assert(p != st.begin());
        p--;
        return *p;
    };

    for(int i = 0, t,j,x,k,l; i < q; i++){
        cin >> t;

        if(t == 1){
            cin >> j >> x, j--;

            if(A[j] == x) continue;

            set<int> id = {pos(j - 1), pos(j), pos(j + 1)};

            id.erase(-1);

            

            A[j] = x;
            if(j > 0 && A[j - 1] == A[j] && j < n - 1 && A[j + 1] == A[j]){
                k = pos(j);
                l = *st.upper_bound(j);
                update(l - k, A[j]);
            } else if(j > 0 && A[j - 1] == A[j]) {
                k = pos(j);
                l = j + 1;
                update(l - k, A[j]);
            } else if(j < n - 1 && A[j + 1] == A[j]) {
                k = j - 1;
                l = pos(j);
                update(l - k, A[j]);
            } else {
                update(1, A[j]);
            }
        } else {
            cin >> k;
            cout << (fen2.calc(k, n) - fen1.calc(k, n) * (k - 1)) * k << endl;
        }
    }
    
    return 0;
}

