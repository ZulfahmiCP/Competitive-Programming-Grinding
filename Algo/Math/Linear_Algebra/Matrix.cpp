#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>

#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template<typename T>void prd(const T& x);
template<typename T, typename U>void prd(const pair<T, U>& val);
template<typename T, typename... Args>void prd(const T& val, Args... args);
template<typename... Args>void debug(Args... args);
template<typename T>void debug(const set<T>& c);
template<typename T>void debug(const vector<T>& c);
template<typename T>void debug(const vector<vector<T>> &c);
template<typename K, typename V>void debug(const map<K, V>& c);

const int MOD = 1e9 + 7;
const int mod = 998244353;
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct Matrix {
    int N;
    double determinant, rank;
    vector<vector<double>> M;

    Matrix(int n) : N(n), M(N, vector<double>(N)) {}
    Matrix(const vector<vector<double>> &Mat) : N(sz(Mat)), M(Mat) {}

    Matrix& operator+=(const Matrix &B) {
        assert(N == B.N);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                M[i][j] += B.M[i][j];
        return (*this);
    }

    Matrix& operator-=(const Matrix &B) {
        assert(N == B.N);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                M[i][j] -= B.M[i][j];
        return (*this);
    }

    Matrix& operator*=(const Matrix& B) {
        Matrix prod(N); assert(N == B.N);
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                for(int k = 0; k < N; k++)
                    prod[i][j] += M[i][k] * B.M[k][j];
        return *this = prod;
    }

    friend Matrix operator+(const Matrix &a, const Matrix &b) { return Matrix(a) += b; }
    friend Matrix operator-(const Matrix &a, const Matrix &b) { return Matrix(a) -= b; }
    friend Matrix operator*(const Matrix &a, const Matrix &b) { return Matrix(a) *= b; }

    void computer_determinant() {
        determinant = 1;
        for(int i = 0, k; i < N; i++){
            k = i;
            for(int j = i + 1; j < N; j++)
                if(abs(M[j][i]) > abs (M[k][i]))
                    k = j;

            if(abs(M[k][i]) < EPS){
                determinant = 0;
                break;
            }

            swap(M[i], M[k]);

            if(i != k)
                determinant = -determinant;
            determinant *= M[i][i];

            for(int j = i + 1; j < N; j++)
                M[i][j] /= M[i][i];

            for(int j = 0; j < N; j++)
                if(j != i && abs(M[j][i]) > EPS)
                    for(int k = i + 1; k < N; k++)
                        M[j][k] -= M[i][k] * M[j][i];
        }
    }

    void compute_rank(){
        vector<bool> used(N, 0);
        rank = 0;

        for(int i = 0, j; i < N; i++){
            for(j = 0; j < N; j++)
                if(!used[j] && abs(M[j][i]) > EPS)
                    break;

            if(j == N) continue;

            rank++;
            used[j] = 1;
            
            for(int k = i + 1; k < N; k++)
                M[j][k] /= M[j][i];

            for(int k = 0; k < N; ++k)
                if(k != j && abs(M[k][i]) > EPS)
                    for(int p = i + 1; p < N; ++p)
                        M[k][p] -= M[j][p] * M[k][i];
        }
    }

    vector<double>& operator[](int i) {
        return M[i];
    }
};

int main(){
 
    FastIO();
    

    return 0;
}
 
void FastIO(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
template<typename T> void prd(const T& x){cerr<<x;}
template<typename T, typename U>void prd(const pair<T, U>& val){cerr<<"(";prd(val.fi);cerr<<", ";prd(val.se);cerr<<")";}
template<typename T, typename... Args>void prd(const T& val, Args... args){prd(val);cerr<<", ";prd(args...);}
template<typename... Args> void debug(Args... args){cerr << "["; prd(args...);cerr<<"]\n";}
template<typename T> void debug(const set<T>& c){cerr<<'[';bool cm=0;for(const auto& st:c){if(cm)cerr<<", ";prd(st);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<T>& c){cerr<<'[';bool cm=0;for(const auto& v:c){if(cm)cerr<<", ";prd(v);cm=1;}cerr<<"]\n";}
template<typename T> void debug(const vector<vector<T>> &c){for(const auto &v: c)debug(v);cerr<<'\n';}
template<typename K, typename V> void debug(const map<K, V>& c){cerr<<'[';bool cm=0;for(auto[k, v]:c){if(cm)cerr<<", ";cerr<<'[';prd(k);cerr <<", ";prd(v);cerr<<']';cm = 1;}cerr<<"]\n";}
