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
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,int>
#define vv vector

#include "robots.h"

using namespace std;

int a;
int b;
int t;
vi aa;
vi bb;
vv<ii> tt;

inline bool ok(int ans){
	//cout << ans << endl;
	priority_queue<int,vi,less<int> > s;
	int ptr = 0;
	for(auto e : aa){
		while(ptr < t and tt[ptr].ff < e){
			s.push(tt[ptr].ss);
			ptr++;
		}
		int left = ans;
		while(!s.empty() and left > 0){
			s.pop();
			//s.erase(s.begin());
			left--;
		}
	}
	while(ptr < t){
		s.push(tt[ptr].ss);
		ptr++;
	}
	for(auto e: bb){
		int left = ans;
		while(!s.empty() and left > 0){
			if(s.top() >= e)return 0;
			//s.erase(s.begin());
			s.pop();
			left--;
		}
	}
	return s.empty();
	//reverse(bb.begin(), bb.end());
}

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
	a = A;
	b = B;
	t = T;
	FOR(i,a)aa.pb(X[i]);
	FOR(i,b)bb.pb(Y[i]);
	FOR(i,t)tt.pb({W[i],S[i]});

	sort(aa.begin(), aa.end());
	sort(bb.begin(), bb.end());
	reverse(bb.begin(), bb.end());
	sort(tt.begin(), tt.end());

	//cout << endl;

	//cout << ok(3) << endl; 
	int lo = 1;
	int hi = t ;
	if(!ok(t+10))return -1;
	int best = t+10;
	while(lo <= hi){
		if(hi - lo < 3){
			FORE(i,lo,hi){
				if(ok(i)){
					best = min(best,i);
					break;
				}
			}
		}
		int mid = (lo + hi)/2;
		if(ok(mid)){
			best = min(best,mid);
			hi = mid-1;
		}else{
			lo = mid+1;
		}
	}

	return best;
}

int mai1n(){
	int a = 3;
	int b = 2;
	int t = 10;
	int X[3] = {6,2,9};
	int Y[2] = {4,7};
	int W[10] = { 4,8,2,7,1,5,3,8,7,10};
	int S[10] = { 6,5,3,9,8,1,3,7,6,5};
	cout << putaway(a,b,t,X,Y,W,S) << endl;
	return 0;
}



