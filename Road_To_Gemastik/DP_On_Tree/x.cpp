#include <bits/stdc++.h>
using namespace std;

// map<pair<int, int>, int> dp;

// int cari(int a, int b) {
//   if (a < b) return 0;
//   if (a % b == 0) return a/b;
//     if (dp.find({a, b}) == dp.end()) {
//         // cout << a << ' ' << b << ' ' << (a/b)*(b-1) +((a-1)%b) << ' ' << cari((a/b)*(b-1) +((a-1)%b), b) << endl;
//         dp[{a, b}] = cari ((a/b)*(b-1) +((a-1)%b), b); 
//     }
//     return dp[{a, b}];
// }

int cari(int a, int b) {
    if(a < b) return 0;
    if(!(a % b)) return a / b;
    return cari((a / b) * (b - 1) + (a - 1) % b, b);
}

// (ab - a) / b + (a - 1) % b == a
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}

int main() {
    FastIO();    
  int n, a, k, hasil = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> k;
    hasil ^= cari(a, k);
  }
  // cout << cari(5, 2) << endl;
  if (hasil == 0) {
    cout << "Aoki";
  } else {
    cout << "Takahashi";
  }
}