#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ll long long 
#define pb push_back
#define ppb pop_back
#define all(x) (x).begin(), (x).end()
#define All(x) (x).rbegin(), (x).rend()
#define sz(x) (int)x.size()
#define endl '\n'

vector<bool> is_prime(1e6+10, true);
vector<int> prima;

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for (int i = 2; i < 1e6 + 10; i++) {
        if (is_prime[i]) {
            prima.push_back(i);
            for (int j = i*2; j < 1e6 + 10; j+=i) {
                is_prime[j] = false; 
            }
        }
    }

    int n, k;
    cin >> n >> k;
    int a = n/k;
    int hasil = 0;
    for (int i = 1; i <= a; i++) {
        if (is_prime[i]) {
            hasil++;
        }
    }

    cout << hasil;
    return 0;
}
