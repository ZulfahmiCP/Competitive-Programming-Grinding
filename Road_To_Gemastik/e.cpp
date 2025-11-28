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
ttm<ttp T> void prd(T x){cerr<<x;}
ttm<ttp T, ttp U>void prd(pair<T, U> x){cerr<<"(";prd(x.fi);cerr<<", ";prd(x.se);cerr<<")";}
ttm<ttp T, ttp... A>void prd(T x, A... a){prd(x);cerr<<", ";prd(a...);}
ttm<ttp... A> void debug(A... a){cerr << "["; prd(a...);cerr<<"]\n";}
ttm<ttp T> void debug(vector<T> c){cerr<<"[ ";for(auto v:c){prd(v);cerr<<' ';}cerr<<"]\n";}
ttm<ttp T> void debug(vector<vector<T>> c){for(auto v: c)debug(v);cerr<<'\n';}
ttm<ttp K, ttp V> void debug(map<K, V> c){cerr<<"[ ";for(auto v:c){cerr<<'[';prd(v.fi);cerr <<", ";prd(v.se);cerr<<']';cerr<<' ';}cerr<<"]\n";}
#define deb(...) debug(__VA_ARGS__)
#define newl cerr << '\n'
#else 
#define deb(...)
#define newl
#endif

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

int N, S;

struct Sqrt {
    vector<string> block;
    vector<int> rank;

    Sqrt() {}
    Sqrt(string &s) : block(S), rank(S) {
        for(int i = 0; i < N; i++)
            block[i / S] += s[i];
    }

    char &operator[](int i) {assert(i >= 0 && i < N); return block[i / S][i % S];}
};

Sqrt s[3];

bool lessthan(Sqrt &A, Sqrt &B, int L, int R) {
    while(L <= R){
        if(L + S - 1 > R) break;
        if(L % S){
            if(A[L] < B[L]) return 1;
            if(A[L] > B[L]) return 0;
            L++;
        } else {
            if(A.rank[L / S] < B.rank[L / S]) return 1;
            if(A.rank[L / S] > B.rank[L / S]) return 0;
            L += S;
        }
    }

    while(L <= R){
        if(A[L] < B[L]) return 1;
        if(A[L] > B[L]) return 0;
        L++;
    }

    return 0;
}

void swap(Sqrt &A, Sqrt &B, int L, int R) {
    while(L <= R){
        if(L + S - 1 > R) break;
        if(L % S){
            swap(A[L], B[L]);
            L++;
        } else {
            swap(A.block[L / S], B.block[L / S]);
            L += S;
        }
    }
    
    while(L <= R){
        swap(A[L], B[L]);
        L++;
    }
}

void update_rank(int i) {
    i = i / S;
    
    vector<pair<string, int>> ss = {{s[0].block[i], 0}, {s[1].block[i], 1}, {s[2].block[i], 2}};

    sort(all(ss));

    for(int j = 0, r = 0; j < 3; j++){
        if(ss[j].se == 0) s[0].rank[i] = r;
        if(ss[j].se == 1) s[1].rank[i] = r;
        if(ss[j].se == 2) s[2].rank[i] = r;

        if(j < 2 && ss[j].fi != ss[j + 1].fi)
            r++;
    }
}

void sort(int L, int R) {
    for(int _ = 0; _ < 2; _++){
        for(int j = 0, k; j < 2; j++){
            if(lessthan(s[j], s[j + 1], L, R)) continue;
            swap(s[j + 1], s[j], L, R);
            
            k = L;
            update_rank(k);

            k += (S - k % S) % S;

            while(k <= R){
                update_rank(k);
                k += S;
            }
        }
    }
} 

int main() {

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int q; cin >> N >> q;
    S = 700;
    string t;

    for(int i = 0; i < 3; i++){
        cin >> t;
        s[i] = Sqrt(t);
    }

    for(int i = 0; i < N; i += S){
        update_rank(i);
    }

    for(int i = 0, l,r; i < q; i++){
        cin >> l >> r, l--, r--;
        sort(l, r);
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < N; j++)
            cout << s[i][j];
        cout << endl;
    }
    
    return 0;
}
