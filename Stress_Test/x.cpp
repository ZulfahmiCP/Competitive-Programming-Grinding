#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int ones = 0;
        int first = -1;
        int last = -1;
        for(int i = 30;i>=0;i--){
            if((n & (1 << i))!=0){
                ones++;
                if(first==-1) first = i;
                last = i;
            }
        }
        vector<int> nums;
        for(int i = first;i>=last;i--){
            if((n & (1 << i))!=0){
                nums.push_back(1);
            }
            else nums.push_back(0);
        }
        bool pall = true;
        for(int i = 0;i<nums.size();i++){
            if(nums[i]!=nums[nums.size()-1-i]){
                pall = false;
                break;
            }
        }
    if(ones%2==0 && pall){
        cout<<"YES"<<endl;
    }
    else cout<<"NO"<<endl;
    }
}