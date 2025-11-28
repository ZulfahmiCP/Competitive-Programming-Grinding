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
 
const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 2e18 + 7;
const double EPS = 1e-9;
 
void FastIO();
 
int agg(int a, int b) {
    return gcd(a, b);
}
 
struct stack_mono {
    stack<pair<int, int>> st;
 
    pair<int, int> top() {
        return st.top();
    }
 
    void push(int x) {
        int y = st.empty() ? x : agg(top().se, x);
        st.push({x, y});
    }
 
    void pop() {
        st.pop();
    }
 
    int find() {
        return st.top().se;
    };
 
    bool empty() {
        return st.empty();
    }
};
 
struct queue_mono {
    stack_mono in, out;
 
    void push(int x) {
        in.push(x);
    }
 
    void pop() {
        if(out.empty()){
            while(!in.empty()){
                out.push(in.top().fi);
                in.pop();
            }
        }
        out.pop();
    }
 
    int query() {
        if(in.empty()) return out.find();
        if(out.empty()) return in.find();
        return agg(in.find(), out.find());
    }
 
    bool empty() {
        return in.empty();
    }
};
 
int main(){
 
    FastIO();
    ll n, m, l;
    cin >> n >> m >> l;

    vector<vector<ll>> a(m);
    vector<ll> s(m);

    for (ll i = 0; i < m; i++) {
        cin >> s[i];
        for (ll j = 0; j < s[i]; j++) {
            ll k;
            cin >> k;
            a[i].push_back(k);
        }
    }

    vector<int> b(n);
    for (ll i = 0; i < n; i++) {
        b[i] = a[i % m][(i/m) % s[i % m]];
    }

    queue_mono kas;
    ll hasil = 0;
    for (ll i = 0, j = 0; i + l - 1 < n; i++) {
        while(j - i < l)
            kas.push(b[j++]);

        hasil += kas.query();

        kas.pop();
    }
 
    cout << hasil;
    
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