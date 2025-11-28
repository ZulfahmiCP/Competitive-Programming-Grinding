#pragma GCC optimize("O3", "Ofast", "unroll-loops")
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <deque>
#include <climits>
#include <cmath>
#include <numeric>
#include <string>
#include <bitset>
#include <assert.h>
#include <iomanip>
using namespace std;

template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

// template <typename T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #include <bits/stdc++.h>
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// #define getrand(l, r) uniform_int_distribution<int>(l, r)(rng)

const long long infl = 1e18 + 1;
const int inf = 1e9 + 1;
const int mod1 = 1e9 + 7;
const int mod2 = 998244353;
const long double eps = 1e-7;
const int mod = mod2;

int add(int a, int b) { return (a + b) % mod; }
int sub(int a, int b) { return (a - b + mod) % mod; }
int mul(int a, int b) { return (int)((long long)a * b % mod); }
int pwr(int a, int b = mod - 2)
{
  int res = 1;
  for (; b > 0; b >>= 1, a = mul(a, a))
    if (b & 1)
      res = mul(res, a);
  return res;
}
template <typename T>
bool chmax(T &a, T b)
{
  if (b > a)
  {
    a = b;
    return true;
  }
  return false;
}
template <typename T>
bool chmin(T &a, T b)
{
  if (b < a)
  {
    a = b;
    return true;
  }
  return false;
}

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define SZ(x) (int)x.size()
#define vec vector
#define dbg(x) cout << (#x) << " : " << x << endl;
using ll = long long;
using ull = unsigned long long;

void solve()
{
  int n;
  cin >> n;
  vec<pair<int, int>> a(n);
  for(auto &[f, s]: a)
    cin >> f >> s;
  int mx = 0;
  for(auto [f, s]: a)
    chmax(mx, f);
  auto rec = [&](auto self, int i, int j, int k) -> int
  {
    if(j % k == 0)
      return j / k;
    if(j < k)
      return 0;
    // if(j < k * 1ll * k)
    //   return (j - k - 1) % 2;
    return self(self, i, j - j / k - 1, k);
  };
  int res = 0;
  for(int i = 0; i < n; i++)
    res ^= rec(rec, i, a[i].first, a[i].second);
  cout << (res ? "Takahashi" : "Aoki");
}

/*    /\_/\
 *   (= ._.)
 *   / >  \>
 */

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  while(t--)
  {
    solve();
    cout << (t ? "\n" : "");
  }
}