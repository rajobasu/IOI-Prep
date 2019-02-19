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
#define ii pair<ll,ll>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>

using namespace std;

const ll INF = 10000000000000000;
const int MAXN = 1<<21;
ll dp[MAXN];
ll subsetsum[MAXN];

#define cout fout
#define cin fin
	
int main(){

	ifstream fin;
	ofstream fout;
	fin.open("guard.in");
	fout.open("guard.out");

	int n,h;
	cin >> n >> h;
	pair<ll,pll> all[n];
	FOR(i,n)cin >> all[i].ff >> all[i].ss.ff >> all[i].ss.ss;
	FOR(mask,1<<n){
		ll sum = 0;
		FOR(i,n)if((mask&(1<<i))>0)sum += all[i].ss.ff;
		subsetsum[mask] = sum;
	}
	dp[0] = INF;
	FOR(mask,1<<n){
		if(mask == 0)continue;
		dp[mask] = -INF;
		FOR(i,n){
			if((mask&(1<<i))>0 and subsetsum[mask^(1<<i)] <= all[i].ss.ss){
				dp[mask] = max(dp[mask],min(all[i].ss.ss - subsetsum[mask^(1<<i)], dp[mask^(1<<i)]));
			}
		}
	}
	ll best = -1;
	FOR(mask, 1<<n){
		ll hh = 0;
		if(mask == 0)continue;
		FOR(i,n)if((mask&(1<<i))>0)hh += all[i].ff;
		if(hh >= h){
			best = max(best,dp[mask]);
		}
	}
	if(best == -1){
		cout << "Mark is too tall" << endl;
	}else{
		cout << best << endl;
	}
	return 0;
}

