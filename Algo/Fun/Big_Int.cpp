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
#define Int unsigned int 
#define Long unsigned long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) (x).erase(unique(all(x)), (x).end());
#define all_range(x) sort(all(x)), (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void prd(const T& x);
template <typename T, typename U>
    void prd(const pair<T, U>& value);
template <typename T, typename... Args>
    void prd(const T& value, Args... args);
template <typename... Args>
    void debug(Args... args);
template <typename K, typename V>
    void debug(const map<K, V>& cont);
template <typename T>
    void debug(const set<T>& cont);
template <typename T>
    void debug(const vector<T>& cont);
template <typename T>
    void debug(const vector<vector<T>> &cont);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct bint {
    string val;
    char sign;
    int dig;

    bint() : val("0"), sign('+') {}
    bint(const ll v) : bint(to_string(v)) {}
    bint(const string &v) {
        if(v[0] == '-') val = v.substr(1), sign = '-';
        else val = v, sign = '+';
    }

    int to_int() {return stoi(val);}
    ll to_ll() {return stoll(val);}

    bint& operator+=(const bint &b){
        if(this->sign == '-' && b.sign == '+') return *this = -(b - *this);

        string sum;
        for(int i = dig - 1, j = b.dig - 1, carry = 0, ds; i >= 0 || j >= 0 || carry; i--, j--){
            ds = carry;
            if(i >= 0) ds += val[i] - '0';
            if(j >= 0) ds += val[j] - '0';
            sum += (ds % 10) + '0';
            carry = ds / 10;
        }
        reverse(all(sum));
        return *this = bint(sum);
    }
    bint& operator-=(const bint &b){}
    bint& operator*=(const bint &b){}
    bint& operator/=(const bint &b){}
    bint& operator++(){}
    bint& operator--(){}
    bint operator++(int){bint a = *this; ++*this; return a;}
    bint operator--(int){bint a = *this; --*this; return a;}

    friend bint operator!(const bint &a){return a.dig == 1 && a.val == "0";}
    friend bint operator-(bint a){a.sign = (a.sign == '+' ? '-' : '+'); return a;}
    friend bint operator+(const bint &a, const bint &b){return bint(a) += b;}
    friend bint operator-(const bint &a, const bint &b){return bint(a) -= b;}
    friend bint operator*(const bint &a, const bint &b){return bint(a) *= b;}
    friend bint operator/(const bint &a, const bint &b){return bint(a) /= b;}
    
    friend bool operator==(const bint &a, const bint &b){return a.sign == b.sign && a.dig == b.dig && a.val == b.val;}
    friend bool operator!=(const bint &a, const bint &b){return !(a == b);}    
    friend bool operator>(const bint &a, const bint &b){return !(a.sign == '-' && b.sign == '+') && a.val > b.val;}
    friend bool operator<(const bint &a, const bint &b){return !(a > b);}
    friend bool operator>=(const bint &a, const bint &b){return a > b || a == b;}
    friend bool operator<=(const bint &a, const bint &b){return a < b || a == b;}

    friend std::ostream& operator<<(std::ostream& os, const bint &a){return os << a.val;}
    friend std::istream& operator>>(std::istream& is, bint &a){return is >> a.val; a = bint(a.val);}
};

int main(){
 
    FastIO();
    ll v = 1;
    bint a = v;
    bint b = a;

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& value){ cerr << "("; prd(value.first); cerr << ", "; prd(value.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& value, Args... args){prd(value); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
