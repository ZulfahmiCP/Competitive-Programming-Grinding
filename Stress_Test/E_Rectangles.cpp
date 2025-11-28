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

struct SP2D {
private:
    int n, m;
    vector<vector<ll>> initial_grid;
    vector<tuple<int, int, int, int, ll>> queries;

public:
    SP2D(const vector<vector<ll>>& grid) {
        if (!grid.empty()) {
            this->n = grid.size();
            this->m = grid[0].size();
            this->initial_grid = grid;
        } else {
            this->n = 0;
            this->m = 0;
        }
    }

    void update(int r1, int c1, int r2, int c2, ll val) {
        queries.emplace_back(r1, c1, r2, c2, val);
    }

    vector<vector<ll>> solve() {
        vector<vector<ll>> H(n, vector<ll>(m, INFL));

        for (const auto& q : queries) {
            int r1, c1, r2, c2;
            ll val;
            tie(r1, c1, r2, c2, val) = q;
            for (int j = c1; j <= c2; ++j) {
                if (j < m) {
                    H[r1][j] = min(H[r1][j], val);
                }
            }
        }

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                H[i][j] = min(H[i][j], H[i - 1][j]);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                H[i][j] = min(H[i][j], H[i][j - 1]);
            }
        }

        vector<vector<ll>> final_grid = initial_grid;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                final_grid[i][j] = min(final_grid[i][j], H[i][j]);
            }
        }

        return final_grid;
    }
};


int main() {

    FastIO();
    int t,n,m; cin >> t;

    while(t--){
        cin >> n >> m;
        vector<vector<int>> A(n, vector<int>(m));
        bool swp = 0;

        for(int i = 0; i < n; i++){
            string s; cin >> s;
            for(int j = 0; j < m; j++)
                A[i][j] = s[j] - '0';
        }
        
        if(n > m){
            vector<vector<int>> B(m, vector<int>(n));

            for(int j = 0; j < m; j++)
                for(int i = 0; i < n; i++)
                    B[j][i] = A[i][j];

            A = B;
            swp = 1;
            swap(n, m);
        }

        SP2D sp(vector<vector<ll>>(n, vector<ll>(m, INFL)));

        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                vector<int> P;

                for(int k = 0; k < m; k++)
                    if(A[i][k] && A[j][k])
                        P.pb(k);

                // debug(i, j);
                // debug(P);

                for(int k = 0; k < sz(P) - 1; k++){
                    ll area = 1LL * (j - i + 1) * (P[i+1] - P[i] + 1);
                    sp.update(i, P[i], j, P[i+1], area);
                    debug(i, P[i], j, P[i+1], area);
                }
                    
            }
        }

        auto ans = sp.solve();

        debug(ans);
        if(swp){
            vector<vector<ll>> B(m, vector<ll>(n));

            for(int j = 0; j < m; j++)
                for(int i = 0; i < n; i++)
                    B[j][i] = ans[i][j];

            ans = B;
        }

        // for(auto &a : ans){
        //     for(auto &x : a) cout << x << ' ';
        //     cout << endl;
        // }
    }
    
    return 0;
}

