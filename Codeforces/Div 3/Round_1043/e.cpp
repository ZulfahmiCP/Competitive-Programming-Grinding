#include <bits/stdc++.h>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'
#define endl '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);
void fail() {debug("DONE"); exit(0);}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;

void FastIO();

int main(){
 
    FastIO();
    int t,n,m,q; cin >> t;
    while(t--){
        cin >> n >> m >> q;
        vector<ll> A(n), B(m);

        for(ll &x : A) cin >> x;
        for(ll &x : B) cin >> x;

        sort(All(A));
        sort(All(B));

        for(int i = 1; i < n; i++)
            A[i] += A[i - 1];
        for(int i = 1; i < m; i++)
            B[i] += B[i - 1];

        for(int i = 0, x,y,z; i < q; i++){
            cin >> x >> y >> z;

            if(x == 0 && y == 0){
                cout << "0\n";
                continue;
            }

            if(z == 0){
                cout << "0\n";
                continue;
            }

            x = min(x, z);
            y = min(y, z);

            if(x == 0){
                cout << B[y - 1] << endl;
                continue;
            }

            if(y == 0){
                cout << A[x - 1] << endl;
                continue;
            }

            ll ans = 0;
            
            auto valx = [&](int a) -> ll {
                int b = min(z - a, y);
                if(!b) return A[a - 1];
                if(!a) return B[b - 1];
                return A[a - 1] + B[b - 1];
            };
            
            int l = -1, r = x;
            while(r - l > 1){
                int k = (l + r) >> 1;
                if(valx(k) >= valx(k + 1))
                    r = k;
                else 
                    l = k;
            }

            // debug(x, r, valx(r));
            ans = max(ans, valx(r));

            auto valy = [&](int b) -> ll {
                int a = min(z - b, x);
                if(!a) return B[b - 1];
                if(!b) return A[a - 1];
                return A[a - 1] + B[b - 1];
            };
            
            l = -1, r = y;
            while(r - l > 1){
                int k = (l + r) >> 1;
                if(valy(k) >= valy(k + 1))
                    r = k;
                else 
                    l = k;
            }

            // debug(y, r, valy(r));
            ans = max(ans, valy(r));
            
            cout << ans << endl;
        }
    }

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
