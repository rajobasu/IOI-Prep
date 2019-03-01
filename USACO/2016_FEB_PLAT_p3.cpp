/*
SOLUTION: Simple DnC dp. note that there was a problem where i started the loop in solve() from j=mid, which gave TLE
Its a common error ig, that is to be avoided.
COMPLEXITY: O(N*N*K*logn)
*/

#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <cmath>
#include <queue>
#include <string>
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define ld long double

using namespace std;

const int MOD = 1000000007;
const ll INF = 1000000000000000;
const int MAXN = 1001;
const int MAXK = 8;
    
ll dp[MAXK][MAXN];
int arr[MAXN];

ll cst[MAXN];// cost to go to the end
ll pref[MAXN];// the prefix over cst;
ll npref[MAXN];// the normal prefix
int n;
void prec(){
    FOR(i,n){
        cst[i] = arr[i]*(n-i-1);
        if(i == 0)pref[i] = cst[i];
        else pref[i] = pref[i-1] + cst[i];
        if(i == 0)npref[i] = arr[i];
        else npref[i] = npref[i-1] + arr[i];
    }
}


ll costCalc(int l,int r){
    int k = n-r-1;
    ll tot = pref[r] - ((l>0)?pref[l-1]:0);
    ll ntot = npref[r] - ((l>0)?npref[l-1]:0);
    return tot - ntot*(k);
}

inline void solve(int k,int l,int r,int vl,int vr){
    if(r < l)return;
    int mid = (l+r)/2;
    ll sum = 0;
    int optj = 0;
    ll mn = INF;
    for(int j = min(mid,vr);j>=vl;j--){
        sum = costCalc(j,mid);
        if(mn >= dp[k-1][j-1] + sum){
            optj = j;
            mn = dp[k-1][j-1] + sum;
        }
        dp[k][mid] = mn;
    }
    solve(k,l,mid-1,vl,optj);
    solve(k,mid+1,r,optj,vr);
}




inline void cyclicShift(int* arr,int n){
    int v = arr[0];
    FOR(i,n-1)arr[i] = arr[i+1];
    arr[n-1] = v;
}

int main(){
    ifstream fin;
    ofstream fout;
    
    #define cin fin
    #define cout fout
    fin.open("cbarn.in");
    fout.open("cbarn.out");
    
    int k;
    cin >> n >> k;
    FOR(i,n)cin >> arr[i];
    
    reverse(arr,arr+n);
    ll cost = INF;
    ll curr,sum;
    FOR(nnnn,n){ // starting location
        prec();
        FOR(i,MAXK)FOR(j,MAXN)dp[i][j] = INF;
        FOR(_k,k+1){
            if(_k == 0)continue;
            if(_k == 1){
                curr = 0;
                sum = 0;
                FOR(i,n){
                    sum += curr;
                    curr += arr[i];

                    dp[_k][i] = sum;
                }
            }else{
                solve(_k,0,n-1,0,n-1);
            }
        }
        cost = min(cost,dp[k][n-1]);
        cyclicShift(arr,n);
    }
   

    cout << cost << endl;

    return 0;
}
