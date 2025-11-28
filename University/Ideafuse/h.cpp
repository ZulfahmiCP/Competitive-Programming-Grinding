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
#define ttp tyname

using namespace std;
ttm<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;


int main() {

    FastIO();
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<int, int>> task(n);
        for(int i = 0; i < n; i++){
            cin >> task[i].first >> task[i].second;
        }

        int pagi = 180, sore = 300;
        int fi_idle = 0, se_idle = 0;

        int cur = 0;
        bool cek_pagi = true;
        
        for(int i = 0; i < n; i++){   
            int ty = task[i].first;
            int d = task[i].second;

            if(cek_pagi){
                if(cur + d > pagi){
                    int idle_pagi = pagi - cur;
                    fi_idle += idle_pagi;
                    se_idle += idle_pagi;
                    cek_pagi = false;
                    cur = 0;
                }
            }

            int sisa = cek_pagi ? (pagi - cur) : (sore - cur);
            int waktu = min(d, sisa);
            
            if(ty == 0) se_idle += waktu;
            else fi_idle += waktu;

            cur += waktu;

            if(!cek_pagi && cur >= sore){
                break;
            }
        }
        cout << fi_idle + se_idle << endl;
    }
    return 0;

}