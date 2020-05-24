/*
Maintain all the i/2 states as separate. also maintain the prev, to calculate the
next row (here, we maitained preprev as well but its not needed). Each of those pointers
will move along at half the speed as the previous pointer (Pointer0 is actually calculating the 
new value of the dp[i] that we are trying to calculate). Thus we maintain logn pointers where the
ith pointer moves at half the speed of the (i-1)th pointer. This way, at any moment we only need
to store 3*logn rows, which is sufficient to calculate our next state. (Note that we move forward
each pointer only when its previous pointer is being recalculated and for that, the current pointer
also needs to move forward).

dp[.][.] is just a buffer for the first few values. 

*/


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
//#define int short
#define vi vector<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
#define mp make_pair
#define vv vector
#define endl '\n'

#include "ckuclib.h"

using namespace std;

const int MAXN = 1e3+5;
const int MAXE = 24;
ll dp[MAXN+4][MAXE+4];



inline int gete(int j){
	return ((j)>23)?23:(j);
}

deque<pair<pair<int,ll*>,pair<ll*,ll*> > > vals;// {currentID,currentarr}, {prevarr,preprevarr}


void calcRow(int i, int valIND){
	// we have to calculate index^th row. For that we need index-1,index-2, index-index/2 rows;
	// first we check if index-index/2 row was updated or not. if not, we recurse;

	if(valIND == vals.size()){
		// this is at the beginning
		ll* row = new ll[MAXE];
		FOR(j,MAXE){
			row[j] = dp[i-1][gete(j+1)] + jedno(i);
			row[j] = min(row[j],dp[i-2][j] + dwa(i)); 
			if(j>0) row[j] = min(row[j],dp[i -i/2][j-1]+polowa(i));	
		}
		ll* prev = new ll[MAXE];
		FOR(j,MAXE)prev[j] = dp[i-1][j];

		ll* preprev = new ll[MAXE];
		FOR(j,MAXE)preprev[j] = dp[i-2][j];

		vals.pb(mp(mp(i,row),mp(prev,preprev)));
		return;
	}

	if(vals[valIND].ff.ff == i){
		// means this row is already created. so return;
		return;
	}

	// that means this row needs to be updated
	// just ensure that the needed rows are created;

	if((i-i/2) < MAXN){
		// that means the halfrow is inbuilt and no recalc is needed;
		auto x = vals[valIND];
		ll* row = new ll[MAXE];
		FOR(j,MAXE){
			row[j] = x.ff.ss[gete(j+1)] + jedno(i);
			row[j] = min(row[j],x.ss.ff[j] + dwa(i));
			if(j > 0)row[j] = min(row[j],dp[i-i/2][j-1] + polowa(i));
		}
		delete[] x.ss.ss;
		vals[valIND] = mp(mp(i,row),mp(x.ff.ss,x.ss.ff));
		return;
	}
	// means halfrow should be created.
	calcRow(i-i/2,valIND+1);

	auto x = vals[valIND];
	ll* row = new ll[MAXE];
	FOR(j,MAXE){
		row[j] = x.ff.ss[gete(j+1)] + jedno(i);
		row[j] = min(row[j],x.ss.ff[j] + dwa(i));
		if(j > 0)row[j] = min(row[j],vals[valIND+1].ff.ss[j-1] + polowa(i));

	}
	delete[] x.ss.ss;
	vals[valIND] = mp(mp(i,row),mp(x.ff.ss,x.ss.ff));	
}

int main(){
	int n = dajn();
	int e = daje();

	FORE(i,1,n){

		if(i<MAXN){
			FOR(j,MAXE){
				dp[i][j] = dp[i-1][gete(j+1)] + jedno(i);
				if(i>1) dp[i][j] = min(dp[i][j],dp[i-2][j] + dwa(i)); 
				if(j>0 and i>1) dp[i][j] = min(dp[i][j],dp[i-i/2][j-1]+polowa(i));	
			}

		}else{
			calcRow(i,0);
		}
	}
	if(n < MAXN){
		odpowiedz(dp[n][gete(e)]);
	}
	else odpowiedz(vals[0].ff.ss[gete(e)]);

	return 0;
}
