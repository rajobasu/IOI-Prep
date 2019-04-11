/*
SOLUTION: DP, however note that its useless to covert a -1 to a 0. 
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
#include <unordered_map>
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<int,int>
#define il pair<int,ll>
#define li pair<ll,int>
#define x ff
#define y ss
#define lii pair<ll,pair<int,int> > 
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const int MOD = 1000000009;
const int INF = 1e9;
const int MAXN = 500*500+1;


bool check(int* arr,int k){
	int arr2[k];FOR(i,k)arr2[i] = arr[i];
	sort(arr2,arr2+k);
	int mx = 0;
	FOR(i,k){
		mx = max(mx,arr2[i]);
		if(mx <= i)return true;
	}
	return false;
}


int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    int arr[n];
    FOR(i,n)cin >> arr[i];
    int dp[n][3];
    dp[0][0] = dp[0][1] = dp[0][2] = INF;
    dp[0][arr[0]+1] = 0;

    FORE(i,1,n-1){
    	if(arr[i] == -1){
    		dp[i][0] = dp[i-1][0];
    		dp[i][1] = INF;
    		dp[i][2] = dp[i-1][2] + 2;
    	}else if(arr[i] == 0){
    		dp[i][0] = dp[i-1][0] + 1;
    		dp[i][1] = min(dp[i-1][0],dp[i-1][1]);
    		dp[i][2] = dp[i-1][2] + 1;
    	}else{
    		dp[i][0] = dp[i-1][0] + 2;
    		dp[i][1] = dp[i-1][0] + 1;
    		dp[i][2] = min(dp[i-1][0],min(dp[i-1][1],dp[i-1][2]));
    	}
    }
	int val = min(dp[n-1][0],min(dp[n-1][1],dp[n-1][2]));
	if(val >= INF){
		cout << "BRAK" << endl;
	}else{
		cout << val << endl;
	}
	return 0;
}
