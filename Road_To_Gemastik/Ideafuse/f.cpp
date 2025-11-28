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
    int T,n,p; cin >> T;

    for(int tc = 1; tc <= T; tc++){
        cin >> n >> p;
        vector<int> A(n);

        for(int &a : A) cin >> a, a = !a;

        // if(n == 1){
        //     cout << "Case #" << tc << ": " << min(1, p + (!A[0])) << endl;
        //     continue;
        // }

        for(int i = 0; i < n; i++)
            A.pb(A[i]);

        n <<= 1;

        int ans = 0;
        vector<int> pref(n + 1, 0);

        for(int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + A[i];

        for(int i = 1; i <= n; i++){
            int l = i, r = n - 1, m;

            while(r - l > 1){
                m = (l + r) >> 1;
                if(pref[m] - pref[i - 1] <= p)
                    l = m;
                else 
                    r = m;
            }

            if(pref[r] - pref[i - 1] <= p)
                l = r;

            if(pref[l] - pref[i - 1] <= p)
                ans = max(ans, min(n / 2, l - i + 1));
        }
        
        cout << "Case #" << tc << ": " << ans << endl;
    }
    
    return 0;
}

