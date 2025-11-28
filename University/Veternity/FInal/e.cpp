#include <bits/stdc++.h>
#define sz(x) (int)x.size()
#define ll long long 
using namespace std;

vector<int> good = {2, 3, 4, 5, 7, 8, 9};
ll dp[20][3][5][2][2];

struct DIGIT_DP {
    vector<int> dig;

    ll answer(int n, int a, int b, bool s, bool t) {
        if(n == sz(dig)) return s == 0;
        if(dp[n][a][b][s][t] != -1) return dp[n][a][b][s][t];

        int m = t ? dig[n] : 9;
        ll res = 0;

        for(int d : good){
            if(d > m) break;
        }
    }
};  

int main() {


    
    return 0;
}
