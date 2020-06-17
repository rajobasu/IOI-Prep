//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")

#include <stdio.h>     
#include <stdlib.h>    
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <cmath>
#include <set>
#include <stack>
#include <map>
#include <unordered_map>
 
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long 
#define ld long double
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define il pair<int,ll>
#define ii pair<int,int>
#define lii pair<pair<ll,int>,il>
#define iii pair<int,ii>
#define iiii pair<iii,int>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define vv vector
#define endl '\n'
 
using namespace std;

const int MAXN = 2e3+5;
const int INF = 1e8;

int arr[MAXN];
int n,p,q;
         
int dp[MAXN][MAXN];//dp[number of q taken][till index processed] = number of p required
bool check(int w){

    FOR(i,q)FOR(j,n)dp[i][j] = INF;
    FOR(i,q+1){
        int ptr1 = 0;
        int ptr2 = 0;
        FOR(j,n){
            while(arr[ptr1]+w-1 < arr[j])ptr1++;
            int prevInd = ptr1-1;
            if(prevInd == -1){
                dp[i][j] = 1;
            }else{
                dp[i][j] = dp[i][prevInd] + 1;
            }      

            // using a q here
            if(i > 0){
                while(arr[ptr2]+w*2-1<arr[j])ptr2++;
                prevInd = ptr2-1;
                if(prevInd == -1){
                    dp[i][j] = 0;
                }else{
                    dp[i][j] = min(dp[i][j],dp[i-1][prevInd]);
                }
            }                              
        }
    }
    
    return dp[q][n-1] <= p;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> p >> q;

    p = min(n,p);
    q = min(n,q);

    FOR(i,n)cin >> arr[i];
    sort(arr,arr+n);
    int lo = 1;
    int hi = 1e9;
    //cout << check(4) << endl;
    int ans = 1e9;
    while(lo <= hi){
        int mid = (lo+hi)/2;
        if(check(mid)){
            ans = min(ans,mid);
            hi = mid-1;
        }else{
            lo = mid+1;
        }
    }
    cout << ans << endl;

    return 0;
}
