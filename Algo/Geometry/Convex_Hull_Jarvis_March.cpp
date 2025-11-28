

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

int sign(ll m) {return (m ? (m > 0 ? 1 : -1) : 0);}

struct point {
    ll x, y;

    point() : x(0), y(0) {}
    point(int a, int b) : x(a), y(b) {}

    point& operator+=(const point &b) {x += b.x, y += b.y; return *this;}
    point& operator-=(const point &b) {x -= b.x, y -= b.y; return *this;}
    point& operator*=(const int &b) {x *= b, y *= b; return *this;}
    point& operator/=(const int &b) {x /= b, y /= b; return *this;}

    friend point operator-(const point &a){return point(-a.x, -a.y);}
    friend point operator+(const point &a, const point &b){return point(a) += b;}
    friend point operator-(const point &a, const point &b){return point(a) -= b;}
    friend point operator*(const point &a, const int &b){return point(a) *= b;}
    friend point operator/(const point &a, const int &b){return point(a) /= b;}
    friend ll operator*(const point &a, const point &b){return a.x * b.y - a.y * b.x;}

    friend bool operator==(const point &a, const point &b){return a.x == b.x && a.y == b.y;}
    friend bool operator!=(const point &a, const point &b){return !(a == b);}
    friend bool operator>=(const point &a, const point &b){return a > b || a == b;}
    friend bool operator<=(const point &a, const point &b){return a < b || a == b;}
    friend bool operator>(const point &a, const point &b){return !(a <= b);}
    friend bool operator<(const point &a, const point &b){return (a.x < b.x) || (a.x == b.x && a.y < b.y);}

    // return 0 if cross, -1 left side, 1 right side
    int cross(const point &p, const point &q) {return sign((p - (*this)) * (q - (*this)));}
    double dist(const point &p) {return abs(x - p.x) + abs(y - p.y);}
    double distance(const point &p) {return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));}
    bool pl_intersect(point &p, point &q) {
        if(p.cross((*this), q) != 0) return 0;
        return (min(p.x, q.x) <= (*this).x && (*this).x <= max(p.x, q.x))
            && (min(p.y, q.y) <= (*this).y && (*this).y <= max(p.y, q.y));
    }

    friend ostream& operator<<(ostream &os, const point &a){return os << a.x << a.y;}
    friend istream& operator>>(istream &is, point &a){return is >> a.x >> a.y;}
};

struct ConvexHull {
    int N;
    vector<point> points;

    ConvexHull(int n) : N(n) {}

    void add(int x, int y) {
        points.pb({x, y});
    }

    int orientation(const point& p, const point& q, const point& r) const {
        int v = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        return (v == 0) ? 0 : (v > 0) ? 1 : -1;
    }

    vector<point> find() {
        if(N < 3) return points;  // Convex hull is not possible with less than 3 points

        int pos = 0;
        for(int i = 1; i < N; i++)
            if(points[i] < points[pos])
                pos = i;

        sort(all(points), [this, pos](const point& a, const point& b) {
            if(a == points[pos]) return true;
            if(b == points[pos]) return false;
            int o = orientation(points[pos], a, b);
            if(!o) return (a.x + a.y < b.x + b.y);
            return (o == -1);
        });

        vector<point> hull;
        int p = pos, q;
        do {
            hull.pb(points[p]);
            q = (p + 1) % N;
            for(int i = 0; i < N; i++)
                if(orientation(points[p], points[i], points[q]) == -1)
                    q = i;
            p = q;
        } while(p != pos);

        return hull;
    }
};

int main() {



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
