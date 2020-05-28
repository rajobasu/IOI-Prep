/*
Try all possible values of cyclic shifts. Then greedily calculate how many type1 changes are required. 
total : O(n);
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
#include <chrono>
#include <random>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<ll,ll>
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

#define endl '\n'

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,a,b;ll x,y;
	string s;
	cin >> n >> a >> b >> x >> y;
	cin >> s;
	int ctr = 0;
	FOR(i,n)if(s[i] == '+')ctr++;
	int k = n + b - a - 2*ctr;
	k /= 2;
	
	ll res = 2e9;


	int dp[n];
	int mndp[n];
	int mn = a;
	FOR(i,n){
		if(s[i] == '+')mn++;
		else mn--;
		dp[i] = mn;
		mndp[i] = mn;
		if(i > 0)mndp[i] = min(mndp[i],mndp[i-1]);
	}

	int delta = 0;
	int newm = 0;
	FOR(i,n){
		int changeNeeded = (abs(min(newm,min(0,delta+mndp[n-i-1]))) + 1)/2;

		if(k > 0){
			if(changeNeeded > k){
				changeNeeded += changeNeeded - k;
			}else{
				changeNeeded = k;
			}
		}
		else changeNeeded += changeNeeded-k;

		res = min(res,i*y + abs(changeNeeded)*x);
		if(s[n-i-1] == '+')delta++;
		else delta--;
		newm = min(0,delta);
	}
	cout << res << endl;


	return 0;
}