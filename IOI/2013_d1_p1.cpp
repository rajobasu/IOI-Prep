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

#include "dreaming.h"

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

const int MAXN = 1e5 + 10;

int dist[MAXN];
bool vis[MAXN];
vv<ii> g[MAXN];
vi now;

void dfs(int node,int p = -1){
	now.pb(node);
	for(auto e : g[node]){
		if(e.ff == p)continue;
		dfs(e.ff,node);
	}
}

void dfsdist(int node,int p = -1){
	vis[node] = 1;
	for(auto e:g[node]){
		if(e.ff == p)continue;
		dist[e.ff] = e.ss + dist[node];
		dfsdist(e.ff,node);
	}
}

int ans; 
vi path;
void dfs2(int node,int target,int p=-1){
	if(node == target){
		// we now process our path variable
		ans = dist[target];
		//cout << node << " " << target << " : " << dist[target] << endl;
		int sum = 0;
		for(auto e:path){
			sum += e;
		//	cout << sum << " [] ";
			ans = min(ans,max(sum,dist[target]-sum));
		}
		//cout << endl;
	}
	for(auto e : g[node]){
		if(e.ff == p)continue;
		path.pb(e.ss);
		dfs2(e.ff,target,node);
		path.pop_back();
	}
}

int travelTime(int n,int m,int l,int a[],int b[],int t[]){
	if(m == 0){
		if(n == 1)return 0;
		if(n == 2)return l;
		return 2*l;
	}
	if(m == 1){
		if(n == 2)return t[0];
		if(n == 3)return l+t[0];
		return max(l+t[0], 2*l);
	}
	// lets prove lemma 1
	vector<int> t2;
	FOR(i,m){
		g[a[i]].pb({b[i],t[i]});
		g[b[i]].pb({a[i],t[i]});
	}
	//cout << "bleh" << endl;
	int MXD = 0;
	FOR(i,n){
		if(vis[i])continue;
		// this is a new component.
		now.clear();
	//	cout << i << endl;
		dfs(i);
		dist[i] = 0;
		dfsdist(i);
		int mxd = 0;
		int ele = now[0];
		for(auto e : now){
			if(dist[e] > mxd){
				mxd = dist[e];
				ele = e;
			}
		}
		dist[ele] = 0;
		dfsdist(ele);
		for(auto e:now){
			MXD = max(MXD,dist[e]);
		}
		mxd = 0;
		int elec = ele;
		for(auto e : now){
			if(dist[e] > mxd){
				mxd = dist[e];
				ele = e;
			}
		}
	//	cout << elec << " " << ele << endl;
		
		path.clear();
		dfs2(elec,ele);
		t2.pb(ans);
		continue;
	/*	for(auto e : now){
			cout << e << " ";
		}
		*/
	//	cout << "ok" << endl;
		int mn = -1;
		for(auto e:now){
		//	cout << e << endl;
			dist[e] = 0;
			dfsdist(e);
			int mx = 0;
			FOR(j,now.size()){
				mx = max(mx,dist[now[j]]);
			}

			if(mn == -1)mn = mx;
			else mn = min(mn,mx);
		}
		//cout << endl;
		t2.pb(mn);
	}



	// this is the 18 pnts substask, will be useful later.
	/*
	for(auto e : t2){
		cout << e << " ";
	}
	cout << endl;
	*/
	sort(t2.begin(), t2.end());
	reverse(t2.begin(), t2.end());
	/*
	for(auto e : t2){
		cout << e << " ";
	}
	cout << endl;
	*/
	if(t2.size() == 1)return MXD;
	int mx = (t2[0] + l + t2[1]);
	//cout << mx << endl;
	if(t2.size() == 2)return max(MXD,mx);
	//while(1);
	mx = max(t2[1] + l + l + t2[2],mx);
	return max(MXD,mx);
}

int ma1in(){
	int n = 12;
	int m = 8;
	int l = 2;
	int a[8] = {0,8,2,5,5,1,1,10};
	int b[8] = {8,2,7,11,1,3,9,6};
	int t[8] = {4,2,4,3,7,1,5,3};
	cout << travelTime(n,m,l,a,b,t) << endl;


	return 0;
}