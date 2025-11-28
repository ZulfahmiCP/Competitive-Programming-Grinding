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

int main() {

    FastIO();
    int n,q; cin >> n >> q;
    vector<int> A(n, 0);

    for(int i = 0; i < n; i++){
        map<ll, int> mpx, mpy, mpz;
        set<array<ll, 3>> st;
        set<int> s;

        for(int j = 0; j < 8; j++){
            ll x,y,z; cin >> x >> y >> z;
            mpx[x]++;
            mpy[y]++;
            mpz[z]++;
            st.insert({x, y, z});
        }

        if(sz(mpx) != 2 || sz(mpy) != 2 || sz(mpz) != 2) continue;

        bool valid = 1;

        for(auto mp : {mpx, mpy, mpz}){
            vector<int> p;
            for(auto [_, a] : mp){
                p.pb(_);
                if(a != 4) valid = 0;
            }

            s.insert(p[1] - p[0]);
        }

        for(auto [p, a] : mpx) if(a != 4) valid = 0;
        for(auto [p, a] : mpy) if(a != 4) valid = 0;
        for(auto [p, a] : mpz) if(a != 4) valid = 0;

        if(sz(st) != 8 || sz(s) != 1) valid = 0;

        A[i] = valid;
    }

    for(int i = 1; i < n; i++) A[i] += A[i - 1];

    for(int i = 0, l,r,ans; i < q; i++){
        cin >> l >> r, l--, r--;
        ans = A[r];
        if(l > 0) ans -= A[l - 1];
        cout << ans << endl;
    }
    
    return 0;
}

