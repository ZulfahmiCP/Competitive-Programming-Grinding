#include <bits/stdc++.h>
using namespace std;

#define fi first 
#define se second
#define ll long long
#define pb push_back
#define ppb pop_back 
#define pf push_front
#define ppf pop_front
#define all_range(x) (x).begin(), (x).begin()
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'
#define ttm  template
#define ttp typename

#ifndef ONLINE_JUDGE 
ttm<ttp T> void prd(T x) {cerr << x;}
ttm<ttp T, ttp U> void prd(pair<T, U> x) {cerr << "("; prd(x.fi); cerr<<", "; prd(x.se); cerr<<")";}
ttm<ttp T, ttp ... A> void prd(T x, A... a) {prd(x); cerr << ", "; prd(a...); }
ttm<ttp... A> void debug(A... a) {cerr << "["; prd(a...); cerr <<"]\n";}
ttm<ttp T> void debug(vector<T> c) {cerr <<"["; for(auto v : c) debug(v); cerr << '\n';} 
ttm<ttp T> void debug(vector<vector<T>> c) {cerr <<"["; for(auto v : c) debug(v); cerr << '\n';} 
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    
    return 0;
}