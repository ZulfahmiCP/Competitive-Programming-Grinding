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

#ifndef ONLINE_JUDGE
// Di lokal, kita definisikan semua fungsi implementasi
ttm<ttp T> void _prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void _prd(pair<T, U> x){cerr<<"(";_prd(x.fi);cerr<<", ";_prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void _prd(T x, A... a){_prd(x);cerr<<", ";_prd(a...);}

ttm<ttp... A> void _debug(A... a){cerr << "["; _prd(a...);cerr<<"]\n";}
ttm<ttp T> void _debug(vector<T> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";_prd(v);cm=1;}cerr<<"]\n";}
ttm<ttp T> void _debug(vector<vector<T>> c){for(auto v: c)_debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void _debug(map<K, V> c){cerr<<'[';bool cm=0;for(auto v:c){if(cm)cerr<<", ";cerr<<'[';_prd(v.fi);cerr <<", ";_prd(v.se);cerr<<']';cm = 1;}cerr<<"]\n";}

// Kita buat macro untuk memanggil fungsi-fungsi di atas
#define debug(...) _debug(__VA_ARGS__)
#define newl cerr << '\n'

#else 
// Di ONLINE_JUDGE, kita buat semua macro ini menjadi KOSONG
#define debug(...)
#define newl

#endif

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    int n = 3;
    string s = "rawr";
    double f = 5.67;
    pair<int, int> p = {1, 2};
    debug(n, f, s, p);
    
    vector<int> A = {10, 20, 30};
    debug(A);
    
    return 0;
}

