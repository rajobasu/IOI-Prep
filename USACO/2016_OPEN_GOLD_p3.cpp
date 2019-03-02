/*
SOLUTION: same as plat p3 2016
COMPLEXITY: O(100*n)
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
const int MAXN = 262150;
const int MAXK = 80;
    
ll dp[MAXK][MAXN];
int arr[MAXN];


int main(){
    ifstream fin;
    ofstream fout;
    
    #define cin fin
    #define cout fout
    fin.open("248.in");
    fout.open("248.out");
    
    int n;
    cin >> n;
    FOR(i,n)cin >> arr[i];
    FOR(j,MAXK)FOR(i,MAXN)dp[j][i] = -1;

    FOR(k,MAXK){
        FOR(i,n){
            if(arr[i] == k){
                dp[k][i] = i+1;
            }else if(k > 0 and dp[k-1][i] != -1){
                dp[k][i] = dp[k-1][dp[k-1][i]];
            }
        }
    }
    int mx = 0;
    FOR(j,MAXK)FOR(i,n)if(dp[j][i] != -1)mx = max(mx,j);
    cout << mx << endl;
   
    return 0;
}
