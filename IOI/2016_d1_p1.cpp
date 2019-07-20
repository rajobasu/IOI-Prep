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
#include <unordered_map>
#include <fstream>
#include <complex>
#include <random>
#include <stack>
#include <chrono>
#include <set>

#include "molecules.h"
 
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
 
using namespace std;

const int MAXN = 500000 + 10;

vi find_subset(int l,int u,vi w){
	int n = w.size();
	int lptr = 0;
	vv<ii> ids;
	FOR(i,n)ids.pb({w[i],i});
	sort(ids.begin(), ids.end(),greater<int>());
	ll sum = 0;
	FOR(i,n){
		sum += ids[i].ff;
		if(l <= sum and sum <= u){
			vi t;
			FORE(j,lptr,i){
				t.pb(ids[j].ss);
			}
			sort(t.begin(), t.end());
			return t;
		}
		while(sum > u){
			sum -= ids[lptr++].ff;
			if(lptr > i)break;
		}
	}
	vi x;
	return x;
}