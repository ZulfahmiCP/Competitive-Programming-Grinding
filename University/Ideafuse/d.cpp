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

vector<pair<int, int>> factor(int n) {
    vector<pair<int, int>> fac;
    for(ll i = 2; i * i <= n; i++){
        if(n % i) continue;
        fac.pb({i, 0});
        while(!(n % i))
            n /= i, fac.back().se++;
    }
    if(n > 1) fac.pb({n, 1});
    return fac;
}

int main() {

    FastIO();
    string s; cin >> s;
    reverse(all(s));
    int n; cin >> n;
    int ans = 0;

    for(int i = 0; i < n; i++){
        int x; cin >> x;
        ans = __gcd(ans, x);
    }

    auto fac = factor(ans);

    auto valid = [&](int x) -> bool {
        ll sum = 0;

        for(ll i = 0, ten = 1; i < sz(s); i++){
            sum += ten * (s[i] - '0');
            sum %= x;
            ten = ten * 10 % x;
        }

        return !sum;
    };

    for(auto &[p, a] : fac){
        int q = 1; 
        for(int i = 0; i < a; i++) q *= p;

        while(q > 1 && !valid(q)) 
            q /= p, a--;
    }

    vector<pair<int, int>> res;

    for(auto &[p, a] : fac){
        if(!a) continue;
        res.pb({p, a});
    }

    if(res.empty()){
        cout << "1";
    } else {
        for(auto &[p, a] : res){
        cout << p;
        if(a > 1) cout << '^' << a;
        cout << ' ';
        }
    }

    cout << endl;
    
    return 0;
}

/*
123456789123456789123456789
3
6 24 15

5000
4
250000000 37500000 125000000 500000000

*/
