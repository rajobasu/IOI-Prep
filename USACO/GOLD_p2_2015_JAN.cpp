/*
SOLUTION: Select all upper and lower boundaries, and do a linear scan for the left and right boundaries.
COMPLEXITY: nlogn + n^3
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

using namespace std;

const int INF = 1000000000;

#define cin fin
#define cout fout

const int MAXN = 1<<21;
int dp[MAXN]; // denotes that time dp[mask] time range = [DP[mask]...L] has already been covered.
	

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("movie.in");
	fout.open("movie.out");
	int n,l;
	cin >> n >> l;
	int sz[n];vector<int> times[n];
	FOR(i,n){
		cin >> sz[i];
		int c;
		cin >> c;
		while(c--){
			int a;
			cin >> a;
			times[i].pb(a);
		}
	}
	// input done	
	FOR(i,1<<n)dp[i] = l+1;
	FOR(mask, 1 << n){
		if(mask == 0)continue;
		FOR(i,n){	
			if((mask&(1<<i))>0){// try placing i in the first slot.
				int loc = lower_bound(times[i].begin(), times[i].end() , dp[mask^(1<<i)] - sz[i]) - times[i].begin();
				if(loc != times[i].size()){
					dp[mask] = min(dp[mask],times[i][loc]);
				}
			}
		}
	}
	int best = 100;
	FOR(mask,1<<n){
		int cnt = 0;
		FOR(i,n)if((mask&(1<<i))>0)cnt++;
		if(dp[mask] == 0){
			best = min(best,cnt);
		}
	}	
	if(best == 100){
		cout << -1 << endl;
	}else{
		cout << best << endl;
	}

	return 0;
}