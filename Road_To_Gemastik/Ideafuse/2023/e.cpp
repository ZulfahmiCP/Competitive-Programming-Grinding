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
    int T,n,k; cin >> T;

    for(int tc = 1; tc <= T; tc++){
        cin >> n >> k, k--;
        vector<int> A(n), B(n), C(n);

        for(int &a : A) cin >> a;

        for(int i = 0; i < n; i++){
            B[i] = A[i] > A[k];
            if(i) B[i] += B[i - 1];
        }

        for(int i = 0; i < n; i++){
            C[i] = A[i] < A[k];
            if(i) C[i] += C[i - 1];
        }

        int ans = 1;
        map<int, set<int>> mp;

        mp[0].insert(0);

        for(int i = 0; i < k; i++)
            mp[B[i] - C[i]].insert(B[i]);

        for(int i = k, j; i < n; i++){
            j = B[i] - C[i];
            if(mp.find(j) != mp.end()){
                int p = *mp[j].begin();
                ans = max(ans, (B[i] - p) * 2 + 1);
            }
        }

        cout << "Case #" << tc << ": " << ans << endl;
    }
    
    return 0;
}

// A[x] : y < x
// B[x] : y > x
// A[x] == B[x]
// A[x] - B[x] = 0
// 10 7 12 8 9 6 
// 1  1  2 2 3 3    
// 0  1  1 1 1 2
