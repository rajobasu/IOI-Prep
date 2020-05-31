/*
SOlution: maintain maxheap of alternating path on bipartite graph from odd and even vertex.
APIO 2007 Backup same solution. 
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
#define iii pair<ll,ii>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
//#define mp make_pair
#define vv vector
#define endl '\n'
 
using namespace std;

const ll INF = 1e18;
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
 
	int n;
	cin >> n;
	int arr[n];
	FOR(i,n)cin >> arr[i];
 
	set<iii, greater<iii> > all;
	map<ii,ll> values;


	int beforeLink[n];
	int afterLink[n];
	FOR(i,n){
		beforeLink[i] = i-1;
		afterLink[i]=i+1;
		values[{i,i+1}] = arr[i];
		all.insert({arr[i],{i,i+1}});
	}
	ll cost = 0;
	FOR(i,(n+1)/2){
		iii item = *(all.begin());
		
		cost += item.ff;
		all.erase(item);

		if(item.ss.ff > 0){
			ll acost = values[{beforeLink[item.ss.ff],item.ss.ff}];
			all.erase({acost,{beforeLink[item.ss.ff],item.ss.ff}});
		}else{
			ll bcost = values[{item.ss.ss,afterLink[item.ss.ss]}];
			all.erase({bcost,{item.ss.ss,afterLink[item.ss.ss]}});
			beforeLink[afterLink[item.ss.ss]] = item.ss.ff;
			afterLink[item.ss.ff] = afterLink[item.ss.ss];

			iii nc = {-INF, {item.ss.ff,afterLink[item.ss.ss]}};
			values[nc.ss] = nc.ff;
			all.insert(nc);
			cout << cost << endl;
			continue;
		}
		if(item.ss.ss < n){
			ll bcost = values[{item.ss.ss,afterLink[item.ss.ss]}];
			all.erase({bcost,{item.ss.ss,afterLink[item.ss.ss]}});
		}else{
			ll acost = values[{beforeLink[item.ss.ff],item.ss.ff}];
			all.erase({acost,{beforeLink[item.ss.ff],item.ss.ff}});
			beforeLink[item.ss.ss] = beforeLink[item.ss.ff];
			afterLink[beforeLink[item.ss.ff]] = item.ss.ss;

			iii nc = {-INF, {beforeLink[item.ss.ff],item.ss.ss}};
			values[nc.ss] = nc.ff;
			all.insert(nc);
			cout << cost << endl;
			continue;
		}

		if(item.ss.ff > 0 and item.ss.ss < n){
			ll acost = values[{beforeLink[item.ss.ff],item.ss.ff}];
			ll bcost = values[{item.ss.ss,afterLink[item.ss.ss]}];
			beforeLink[afterLink[item.ss.ss]] = beforeLink[item.ss.ff];
			afterLink[beforeLink[item.ss.ff]] = afterLink[item.ss.ss];

			iii nc = {acost + bcost - item.ff, {beforeLink[item.ss.ff],afterLink[item.ss.ss]}};
			values[nc.ss] = nc.ff;
			all.insert(nc);
		}
		cout << cost << endl;
	}
 
	return 0;
}