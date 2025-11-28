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

int ask(set<int> &s) {
    if(sz(s) == 1) return 0;
    cout << "? " << sz(s) << ' ';
    for(int a : s) cout << a+1 << ' ';
    cout << endl;
    int res; cin >> res;
    return res;
}

void answer(vector<int> &A) {
    cout << "! ";
    for(int &a : A) cout << a << ' ';
    cout << endl;
}

int main() {

    int t,n; cin >> t;

    while(t--){
        cin >> n;
        vector<int> A(2 * n, 0), pos(n+1, -1);
        set<int> st;

        for(int i = 0, j = 0, k; i < 2 * n; i++){
            k = 0;

            while(j < 2 * n){
                st.insert(j);
                k = ask(st);
                if(k) break;
                j++;
            }

            if(k && j < 2 * n){
                A[j] = k;
                pos[k] = j;
                st.erase(j);
                j++;
            }
        }

        // debug(A);
        // debug(pos);

        st.clear();

        for(int i = 0; i < 2 * n; i++)
            if(A[i])
                st.insert(i);

        assert(sz(st) == n);

        for(int i = 0; i < 2 * n; i++){
            if(A[i]) continue;
            st.insert(i);
            A[i] = ask(st);
            st.erase(i);
        }

        // debug(A);
        answer(A);
    }


    
    return 0;
}

