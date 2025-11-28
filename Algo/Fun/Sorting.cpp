#include <bits/stdc++.h>
using namespace std;

void bubble_sort(vector<int> &A) {
    int n = A.size();

    for(int i = 0; i < n; i++)
        for(int j = 1; j < n; j++)
            if(A[j] < A[j - 1])
                swap(A[j - 1], A[j]);
}

void insertion_sort(vector<int> &A) {
    int n = A.size();

    for(int i = 1, j, k; i < n; i++){
        j = i - 1, k = A[i];
        while(j >= 0 && A[j] > k)
            A[j + 1] = A[j--];
        A[j + 1] = k;
}

void selection_sort(vector<int> &A) {
    int n = A.size();

    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++)
            if(A[j] < A[i])
                swap(A[i], A[j]);
    }
}

// arr = {7, 4, 6, 5, 8, 1, 2, 3}
// merge_sort(arr, 0, 7)
// merge_sort(arr, 0, 3)
// merge_sort(arr, 0, 1) -> left = arr[0]

vector<int> merge_sort(vector<int> &A, int l, int r) {
    if(l == r)
        return {A[l]};
    
    int m = (l + r) / 2;

    vector<int> left = merge_sort(A, l, m);
    vector<int> right = merge_sort(A, m + 1, r);

    vector<int> res;
    int kiri = 0, kanan = 0;
    while(kiri < left.size() && kanan < right.size()){
        if(left[kiri] < right[kanan]){
            res.push_back(left[kiri]);
            kiri++;
        } else {
            res.push_back(right[kanan]);
            kanan++;
        }
    }

    while(kiri < left.size()){
        res.push_back(left[kiri]);
        kiri++;
    }

    while(kanan < right.size()){
        res.push_back(right[kanan]);
        kanan++;
    }

    return res;
}
/*
res [1, 2, 3, 4, 5, 6]
                 l                  
left [1, 4, 5, 6] 
               r
right = [2, 3, 7, 8]
[4, 6] and [1, 5] || [2, 8] and [3, 7]

*/



int main() {

    

    return 0;
}