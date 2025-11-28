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
    int n,k; cin >> n >> k;
    vector<ll> A(n);
    map<ll, ll> cnt;
    cnt[0] = 1;

    for(int i = 0; i < n; i++){
        cin >> A[i];
        A[i] -= k;
        if(i) A[i] += A[i - 1];
        cnt[A[i]]++;
    }

    ll ans = 0;

    for(auto [p, c] : cnt)
        ans += c * (c - 1) / 2;

    cout << ans << endl;

    int q; cin >> q;

    for(ll i = 0, j,x; i < q; i++){
        char op; cin >> op >> j >> x, j--;

        if(op == 'L'){
            ans -= (--cnt[A[j - 1]]);
            if(!cnt[A[j - 1]])
                cnt.erase(A[j - 1]);
            A[j - 1] += x;
            ans += (cnt[A[j - 1]]++);
        } else {
            ans -= (--cnt[A[j]]);
            if(!cnt[A[j]])
                cnt.erase(A[j]);
            A[j] -= x;
            ans += (cnt[A[j]]++);
        }

        cout << ans << endl;
    }
    
    return 0;
}

