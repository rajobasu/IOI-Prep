/*
SOLUTION: Simple dp[index at first string][index at second index].
COMPLEXITY: O(N^2)
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
const ll INF = 100000000000000;
const int MAXN = 1000001;

ll dist(ii a,ii b){
	ll x = a.ff - b.ff;
	ll y = a.ss - b.ss;

	return x*x + y*y;
}

#define cin fin
#define cout fout

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("radio.in");
	fout.open("radio.out");


	int n,m;
	cin >> n >> m;
	ii a,b;
	cin >> a.ff >> a.ss >> b.ff >> b.ss;
	string s1,s2;
	cin >> s1 >> s2;
	

	ii loc1[n+1];
	ii loc2[m+1];


	FOR(i,n){
		loc1[i] = a;
		if(s1[i] == 'N')a.ss++;
		if(s1[i] == 'S')a.ss--;
		if(s1[i] == 'E')a.ff++;
		if(s1[i] == 'W')a.ff--;
	}
	loc1[n] = a; 

	FOR(i,m){
		loc2[i] = b;
		if(s2[i] == 'N')b.ss++;
		if(s2[i] == 'S')b.ss--;
		if(s2[i] == 'E')b.ff++;
		if(s2[i] == 'W')b.ff--;
	}
	loc2[m] = b;

	ll dp[n+1][m+1];
	FOR(i,n+1){
		FOR(j,m+1)dp[i][j] = 0;
	}
	FOR(i,n+1){
		FOR(j,m+1){
			if(i == 0 and j == 0)continue;
			dp[i][j] = INF;
			
			if(i > 0) dp[i][j] = min(dp[i][j],dp[i-1][j]);
			if(j > 0) dp[i][j] = min(dp[i][j],dp[i][j-1]);
			if(i > 0 and j > 0) dp[i][j] = min(dp[i][j],dp[i-1][j-1]);
			dp[i][j] += dist(loc1[i],loc2[j]);
		}
	}


	cout << dp[n][m] << endl;
}
