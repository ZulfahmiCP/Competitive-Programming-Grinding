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

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T> using ordmulset = tree<T, null_type, 
less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n,k; cin >> n >> k;
    vector<int> ans(3);
    
    for(int l = 0; l < 3; l++){
        vector<int> A(n);

        for(int &a : A) cin >> a;

        ordmulset<int> ms;

        int med = 0;

        for(int i = 0, j = 0; i + k - 1 < n; i++){
            while(j - i < k)
                ms.insert(A[j++]);
            
            med = max(med, *ms.find_by_order(k/2));
            ms.erase(ms.find_by_order(ms.order_of_key(A[i])));
        }

        ans[l] = med;
    }

    sort(all(ans));
    cout << ans[1] << endl;

    return 0;
}
