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
    point rev() {return {y, x};}
    friend point rev(const point &p) {return {p.y, p.x};}

    friend ostream& operator<<(ostream &os, const point &a){return os << a.x << ' ' << a.y;}
    friend istream& operator>>(istream &is, point &a){return is >> a.x >> a.y;}
};

struct point_hash {size_t operator()(const point& p) const {return hash<int>()(p.x) ^ hash<int>()(p.y);}};

struct line {
    point p, q;

    line() : p(0, 0), q(0, 0) {}
    line(int x1, int y1, int x2, int y2) : p(x1, y1), q(x2, y2) {}
    line(const point &a, const point &b) : p(a), q(b) {}

    int cross(point &r) {return r.cross(p, q);}
    bool pl_intersect(point &r) {return r.pl_intersect(p, q);}
    friend bool intersect(line a, line b) {
        if((a.q - a.p) * (b.q - b.p)){
            for(int i = 0, s, t; i < 2; i++){
                s = a.p.cross(a.q, b.p);
                t = a.p.cross(a.q, b.q);
                if(max(s, t) < 0 || min(s, t) > 0)
                    return 0;
                swap(a, b);
            }
            return 1;
        }

        if(a.p.cross(a.q, b.p))
            return 0;
        
        for(int i = 0; i < 2; i++){
            if(max(a.p.x, a.q.x) < min(b.p.x, b.q.x) ||
               max(a.p.y, a.q.y) < min(b.p.y, b.q.y))
            return 0;
            swap(a, b);
        }

        return 1;
    }

    bool vertical() {return p.x == q.x;}
    bool horizontal() {return p.y == q.y;}

    friend ostream& operator<<(ostream &os, const line &a){return os << a.p << ' ' << a.p;}
    friend istream& operator>>(istream &is, line &a){return is >> a.p >> a.q;}
};

struct polygon {
    int N;
    vector<point> points;

    polygon() {}
    polygon(int n) : N(n), points(N) {}
    polygon(const vector<point> &pts) : N(sz(pts)), points(pts) {}

    void add(const point &p) {
        if(!points.empty())
            points.ppb();
        points.pb(p); 
        points.pb(points[0]);
        N++;
    }

    ll area() {
        ll zone = 0;
        points.pb(points[0]);

        for(int i = 0; i < N; i++)
            zone += (points[i].x * points[i + 1].y) - 
                    (points[i].y * points[i + 1].x);
        
        return abs(zone);
    }

    // return -1 if boundary, 1 if inside, 0 if outside
    int pos(point &p) {
        int cnt = 0;
        bool bound = 0;

        for(int i = 0, j = 1; i < N; i++, j++){
            if(p.pl_intersect(points[i], points[j]))
                return -1;
            cnt += (points[i].x <= p.x && p.x < points[j].x && p.cross(points[i], points[j]) < 0
                 || points[j].x <= p.x && p.x < points[i].x && p.cross(points[j], points[i]) < 0);
        }

        return (cnt & 1);
    }

    // return the number of points where their coordinates 
    // is int and is inside and on the boundary of polygon
    pair<ll, ll> lattice_points() {
        ll bound = 0;

        for(int i = 0, j = 1; i < N; i++, j++){
            if(points[j].x == points[i].x) 
                bound += abs(points[j].y - points[i].y);
            else if(points[j].y == points[i].y)
                bound += abs(points[j].x - points[i].x);
            else 
                bound += gcd(abs(points[j].x - points[i].x), abs(points[j].y - points[i].y));
        }

        return {(area() - bound + 2) / 2, bound};
    }

    friend ostream& operator<<(ostream &os, const polygon &pol){for(auto &p : pol.points) os << p << '\n'; return os;}
    friend istream& operator>>(istream &is, polygon &pol){for(auto &p : pol.points) is >> p; pol.points.pb(pol.points[0]); return is;}
};

struct SweepLine {
    struct Event {
        point p;
        int type, id;
        Event(const point& p, int type, int id) : p(p), type(type), id(id) {}
        bool operator<(const Event& e) const {
            return (p.x != e.p.x ? p.x < e.p.x : type < e.type);
        }
    };

    int N;
    vector<line> lines;
    set<int> active;
    vector<Event> events;

    SweepLine(int n) : N(n), lines(N) {} 

    bool intrsct(int i, int j) {
        return intersect(lines[i], lines[j]);
    }

    bool run() {
        for(int i = 0; i < N; i++){
            if(lines[i].p > lines[i].q) 
                swap(lines[i].p, lines[i].q);
            events.pb(Event(lines[i].p, 0, i));
            events.pb(Event(lines[i].q, 1, i));
        }

        sort(all(events));

        for(const auto& event : events){
            int id = event.id;
            if (event.type == 0) {  
                auto it = active.lower_bound(id);
                if (it != active.end() && intrsct(id, *it)) return 1;
                if (it != active.begin() && intrsct(id, *prev(it))) return 1;
                active.insert(it, id);
            } else {  
                auto it = active.find(id);
                if (it != active.end()) {
                    if (next(it) != active.end() && it != active.begin() && intrsct(*prev(it), *next(it))) return 1;
                    active.erase(it);
                }
            }
        }
        return false;
    }
};

int main() {
    
    FastIO();
    int n,m; cin >> n >> m;
    SweepLine sl(m);

    for(auto &l : sl.lines)
        cin >> l;

    cout << (sl.run() ? "There is an intersection.\n" : "No intersections.\n");

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
