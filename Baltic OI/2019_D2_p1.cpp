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
#include <fstream>
#include <complex>
#include <stack>
#include <set>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define vv vector
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>

using namespace std;

const int INF = 1e9;
const int MAXN = 301;

int dp[MAXN*MAXN];

int main(){
	int n,m,k;
	cin >> n >> m >> k;
	int a[n];int b[m];
	FOR(i,n)cin >> a[i];
	FOR(i,m)cin >> b[i];
	int x = 0;
	FOR(i,n){
		if(a[i] < k){
			cout << "Impossible" << endl;
			return 0;
		}
		x += a[i];
	}
	FOR(i,MAXN*MAXN)dp[i] = -INF;
	dp[0] = 0;

	FOR(i,m){
		for(int h = MAXN*MAXN-1;h >= 0;h--){
			if(h < b[i])continue;
			dp[h] = max(dp[h] , dp[h-b[i]] + min(n,b[i]));
		}
	}
	int diff = INF;
	FOR(i,MAXN*MAXN){
		if(i < x)continue;
		if(dp[i] < n*k)continue;
		diff = min(diff,abs(x-i));
		break;
	}	
	if(diff >= INF){
		cout << "Impossible" << endl;
	}else
	cout << diff << endl;
	return 0;
}