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
#include <complex>
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
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
using cd = complex<double>;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename K, typename V>void debug(const map<K, V>& c);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;
const double PI = acos(-1.0);

void FastIO();

void fft(vector<cd>& A, bool inv) {
    int N = sz(A);

    for(int i = 1, j = 0, bit; i < N; i++){
        bit = N >> 1;
        for(; j & bit; bit >>= 1) 
            j ^= bit;
        j ^= bit;

        if(i < j) 
            swap(A[i], A[j]);
    }

    for(int k = 2; k <= N; k <<= 1){
        double angle = 2 * PI / k * (inv ? -1 : 1);
        cd wlen(cos(angle), sin(angle)), w;

        for(int i = 0; i < N; i += k) {
            w = 1;
            for(int j = 0; j < (k >> 1); j++){
                cd u = A[i + j], v = A[i + j + (k >> 1)] * w;
                A[i + j] = u + v, A[i + j + (k >> 1)] = u - v;
                w *= wlen;
            }
        }
    }

    if(inv) for(auto &a : A) a /= N;
}

string multiply(const string& A, const string& B) {
    int N = 1;
    while(N <= max(sz(A), sz(B))) N <<= 1;
    N <<= 1;

    vector<cd> FA(N), FB(N);

    for(int i = 0; i < sz(A); i++)
        FA[i] = cd(A[sz(A) - i - 1] - '0', 0);
    for(int i = 0; i < sz(B); i++)
        FB[i] = cd(B[sz(B) - i - 1] - '0', 0);

    fft(FA, 0); fft(FB, 0);
    for(int i = 0; i < N; ++i) 
        FA[i] *= FB[i];
    fft(FA, 1);

    string ans;
    int car = 0;
    for(int i = 0, d; i < N; i++){
        d = round(FA[i].real()) + car;
        ans += char(d % 10 + '0');
        car = d / 10;
    }

    while(sz(ans) > 1 && ans.back() == '0')
        ans.ppb();
    reverse(all(ans));

    return ans;
}

struct bint {
    string val;
    int dig;
    bool pos;

    /*----Constructor----*/

    bint() : dig(0), pos(1) {}
    bint(const char *v) : bint(string(v)) {}
    bint(ll v) : bint(to_string(v)) {}
    bint(int v) : bint(to_string(v)) {}
    bint(string v) {
        pos = v[0] != '-', dig = sz(v);
        if(v[0] != '+' && v[0] != '-') val = v;
        else val = v.substr(1), dig--;
        strip_lz(val);
    }

    /*----Arithmatic Operation----*/

    bint& operator+=(const bint &b) {
        bint res;
        if(pos && !b.pos){
            res = b; res.pos = 1; 
            return (*this = *this - res);
        } else if(!pos && b.pos) {
            res = *this; res.pos = 1; 
            return (*this = -(res - b));
        }


        auto [A, B] = get_lam(val, b.val);
        short c = 0, s;
        for(int i = sz(A) - 1; i >= 0; i--){
            s = A[i] - '0' + B[i] - '0' + c;
            res.val += char((s % 10) + '0');
            c = s / 10;
        }

        reverse(all(res.val));

        if(c) res.val = to_string(c) + res.val;
        if(!pos && !res.is_zero()) res.pos = 0;
        res.dig = sz(res.val);
        return (*this = res);  
    }
    bint& operator-=(const bint &b) {
        bint res;
        if(pos && !b.pos){
            res = b; res.pos = 1; 
            return (*this = *this + res);
        } else if(!pos && b.pos) {
            res = *this; res.pos = 1; 
            return (*this = -(res + b));
        }

        string A = b.val, B = val;
        res.pos = !b.pos;
        if(abs(*this) > abs(b)){
            swap(A, B);
            res.pos = pos;
        }

        add_lz(B, sz(A) - sz(B));

        for(int i = sz(A) - 1, j, diff; i >= 0; i--){
            diff = A[i] - B[i];
            if(diff < 0){
                for(j = i - 1; j >= 0; j--){
                    if(A[j] != '0'){
                        A[j]--;
                        break;
                    }
                }

                j++;
                while(j != i) A[j++] = '9';
                diff += 10; 
            }

            res.val += char(diff + '0');
        }
        
        reverse(all(res.val));
        strip_lz(res.val);
        if(res.is_zero()) res.pos = 1;
        res.dig = sz(res.val);
        return *this = res;
    }
    bint& operator*=(const bint &b) {
        auto mult = multiply(val, b.val);
        if(pos != b.pos) mult = "-" + mult;
        return *this = bint(mult);
    }
    bint& operator/=(const bint &oth) {
        bint a = abs(*this), b = abs(oth);

        assert(oth != 0);
        if(a < b) return *this = bint();
        if(oth == 1) return *this;
        if(oth == -1) return *this = -(*this); 

        bint q;
        if(a <= LLONG_MAX && b <= LLONG_MAX) q = stoll(a.val) / stoll(b.val);
        else if(is_pow_ten(b.val)) q.val = a.val.substr(0, a.dig - b.dig + 1);
        else if(a == b) q = 1;
        else {
            q.val = "";    
            bint c, c_quo, c_rem;
            c_rem.val = a.val.substr(0, b.dig - 1);
            int c_idx = b.dig - 1;
            while(c_idx < a.dig){
                c.val = c_rem.val.append(1, a.val[c_idx++]);
                while(c < b){
                    q.val += "0";
                    if(c_idx >= a.dig) break;
                    c.val.append(1, a.val[c_idx++]);
                }

                if(c == b) q.val += "1", c_rem = 0;
                else if(c > b) {
                    strip_lz(c.val);
                    tie(c_quo, c_rem) = divide(c, b);
                    q.val += c_quo.val;
                }
            }
        }

        strip_lz(q.val);
        q.pos = (pos == oth.pos);
        q.dig = sz(q.val);
        return *this = q;
    }
    bint& operator%=(const bint &oth) {
        bint a = abs(*this), b = abs(oth);
        
        assert(b != 0 && oth.pos);
        if(b == 1 || b == a) return *this = bint();

        bint rem;
        if(a <= LLONG_MAX and b <= LLONG_MAX) rem = stoll(a.val) % stoll(b.val);
        else if(a < b) rem = a;
        else if(is_pow_ten(oth.val)) rem.val = a.val.substr(a.dig - oth.dig - 1);
        else rem = a - (a / b) * b;
        strip_lz(rem.val);

        rem.pos = this->pos;
        if(rem.is_zero()) rem.pos = 1;
        if(!pos) rem += oth;
        return (*this = rem);
    }

    /*----Comparison----*/

    bint& operator++(){return *this = *this + 1;}
    bint& operator--(){return *this = *this - 1;}
    bint operator++(int){bint a = *this; ++*this; return a;}
    bint operator--(int){bint a = *this; --*this; return a;}

    friend bint operator-(const bint &a){bint b = a; b.pos = !b.pos; return b;}
    friend bint operator!(const bint &a){return a.val != "0";}
    friend bint operator+(const bint &a, const bint &b){return bint(a) += b;}
    friend bint operator-(const bint &a, const bint &b){return bint(a) -= b;}
    friend bint operator*(const bint &a, const bint &b){return bint(a) *= b;}
    friend bint operator/(const bint &a, const bint &b){return bint(a) /= b;}
    friend bint operator%(const bint &a, const bint &b){return bint(a) %= b;}
    
    friend bool operator==(const bint &a, const bint &b){return a.pos == b.pos && a.dig == b.dig && a.val == b.val;}
    friend bool operator!=(const bint &a, const bint &b){return !(a == b);}
    friend bool operator>=(const bint &a, const bint &b){return !(a < b);}
    friend bool operator<=(const bint &a, const bint &b){return (a < b || a == b);}
    friend bool operator>(const bint &a, const bint &b){return !((a < b || a == b));}
    friend bool operator<(const bint &a, const bint &b){
        if(a.pos != b.pos) return !a.pos;
        if(!a.pos) return -a > -b;
        if(a.dig == b.dig) return a.val < b.val;
        return a.dig < b.dig;
    }

    /*----Math Function----*/

    friend bint abs(const bint &a){bint b = a; b.pos = 1; return b;}
    static bint big_pow_ten(int b){return bint("1" + string(b, '0'));}
    friend bint gcd(const bint &a, const bint &b) {return b == 0 ? a : gcd(b % a, a);}
    friend bint lcm(const bint &a, const bint &b) {return a == 0 || b == 0 ? 0 : a * b / gcd(a, b);}
    friend bint power(bint a, ll b){bint c("1");for(;b > 0;a *= a,b >>= 1)if(b & 1)c *= a;return c;}
    friend bint power(const bint &a, bint b){return power(a, b.to_long_long());}
    friend bint sqrt(const bint &a) {
        assert(a.pos);
        if(a == 0) return 0;
        if(a < 4) return 1;
        if(a < 9) return 2;
        if(a < 16) return 3;

        bint prev = -1, cur = big_pow_ten(a.dig / 2 - 1);
        while(abs(cur - prev) > 1)
            prev = cur, cur = (a / prev + prev) / 2;
        return cur;
    }
        
    friend pair<bint, bint> divide(const bint& div_end, const bint& div) {
        bint q = 1, rem, temp = div;
        while(temp < div_end) q++, temp += div;
        if(temp > div_end) q--, rem = div_end - (temp - div);
        return {q, rem};
    }
    
    pair<string, string> get_lam(const string& v1, const string& v2) {
        string A = v2, B = v1;
        if(sz(v1) > sz(v2) || (sz(v1) == sz(v2) && v1 > v2)) 
            swap(A, B);
        add_lz(B, sz(A) - sz(B));
        return {A, B};
    }

    /*----Numerical Function----*/
    
    bool is_zero(){return dig == 1 && val == "0";}
    bool is_valid_num(const string& v) {for(char c : v) if(c < '0' || c > '9') return 0; return 1;}
    bool is_pow_ten(const string &v) {if(v[0] != '1') return 0; for(int i = 1; i < sz(v); i++) if(v[i] != 0) return 0; return 1;}
    void strip_lz(string& v) {int i; for(i = 0; i < sz(v); i++) if(v[i] != '0') break; i == sz(v) ? v = "0" : v = v.substr(i);}
    void add_lz(string& v, int i) {v = string(i, '0') + v;}
    void add_tz(string& v, int i) {v += string(i, '0');}

    string to_str() {return (pos ? "-" : "") + val;}
    int to_int() {return stoi(val);}
    ll to_long_long() {return stoll(val);}

    friend istream& operator>>(istream& in, bint& a) {string input; in >> input; a = bint(input); return in;}
    friend ostream& operator<<(ostream& out, const bint& a) {if(!a.pos) out << '-'; out << a.val; if(!a.dig) out << 0; return out;}
};

int main(){
 
    FastIO();
    bint a, b; cin >> a >> b;
    cout << a % b << '\n';

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
