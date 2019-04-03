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
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ii pair<long double,long double>
#define ll long long int
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;
//using namespace __gnu_pbds;

const int MOD = 1000000009;
const int INF = 1e9;
const int MAXN = 3000000;

#define cin fin
#define cout fout

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("nochange.in");
	fout.open("nochange.out");

	int n,k;
	cin >> k >> n;
	ll coins[k];
	FOR(i,k)cin >> coins[i];
	ll arr[n];
	FOR(i,n)cin >> arr[i];
	ll pref[n];
	pref[0] = arr[0];
	FOR(i,n-1)pref[i+1] = pref[i] + arr[i+1];
	int dp[1<<k];
		
	FOR(i,1<<k)dp[i] = -1;
	ll best = -1;
	FOR(mask,1<<k){
		int cnt = __builtin_popcount(mask);
		int submask = mask;
		FOR(i,k){
			if((submask&(1<<i)) > 0){
					// let this element be the last element.
				int lp = dp[submask^(1<<i)];
				ll val = coins[i];
				if(lp != -1){
					val += pref[lp];
				}
				int ind = upper_bound(pref,pref+n,val+1) - pref;
				dp[submask] = max(dp[submask],ind-1);
			}
		}
		if(dp[submask] >= n-1){
			ll sum = 0;
			FOR(i,k){
				if((mask&(1<<i)) == 0)sum += coins[i];
			}
			best= max(best, sum);
		}
	}
	//FOR(i,1<<k)cout << dp[i] << " ";cout << endl;
	cout << best << endl;
	
	return 0;
}
