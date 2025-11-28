#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
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
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

using lint = __uint128_t; // up to 2^127 or 10^38
using Long = unsigned long long;
using Int = unsigned int;

lint read() {
    lint x = 0;
    string s; cin >> s;
    for(char &c : s)
        if(isdigit(c))
            x = 10 * x + (c - '0');
    return s[0] == '-' ? -x : x;
}

void print(lint x) {
    if(x < 0){cout << '-';x = -x;}
    if(x > 9) print(x / 10);
    cout << char(x % 10 + '0');
}

// Compute DIV_COUNT(i) 1...N in O(cbrt(N))
// It is also equal to floor(N / i) 1...N
// takes ~100 ms for n = 1e18 

lint div_num_sum(Long n) {
    auto out = [n] (Long x, Int y) {
        return x * y > n;
    };

    auto cut = [n] (Long x, Int dx, Int dy) {
        return lint(x) * x * dy >= lint(n) * dx;
    };

    const Long sn = sqrtl(n);
    const Long cn = pow(n, 0.34); //cbrtl(n);

    Long x = n / sn;
    Int y = n / x + 1;
    lint ans = 0;

    stack<pair<Int, Int>> st;
    st.emplace(1, 0);
    st.emplace(1, 1);

    while (true) {
        auto [lx, ly] = st.top();
        st.pop();

        while(out(x + lx, y - ly)){
            ans += x * ly + Long(ly + 1) * (lx - 1) / 2;
            x += lx, y -= ly;
        }

        if (y <= cn) break;
        Int rx = lx, ry = ly;

        while(true){
            tie(lx, ly) = st.top();
            if(out(x + lx, y - ly)) break;
            rx = lx, ry = ly;
            st.pop();
        }
        while(true){
            Int mx = lx + rx, my = ly + ry;
            if (out(x + mx, y - my)) 
                st.emplace(lx = mx, ly = my);
            else {
                if (cut(x + mx, lx, ly)) break;
                rx = mx, ry = my;
            }
        }
    }

    for(--y; y > 0; --y) 
        ans += n / y;
    return ans * 2 - sn * sn;
}

int main() {
  
    FastIO();
    ll n; cin >> n;
    print(div_num_sum(n));

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
