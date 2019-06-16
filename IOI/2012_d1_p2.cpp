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

using namespace std;

const int INF = 1e9+10;
const int MAXN = 1000*100*10+10;
const int MAXVAL = 1e9+10;

vi g[MAXN];
vector<ii> edges;
int n;

int parent[MAXN];
struct DSU{
	DSU(int n){
		//parent = new int[n];
		FOR(i,n)parent[i] = i;
	}
	inline int find(int a){
		if(parent[a] != a)parent[a] = find(parent[a]);
		return parent[a];
	}
	inline void merge(int a,int b){
		int pa = find(a);
		int pb = find(b);
		parent[pa] = pb;
	}
	
};	

void Init(int N){
	n = N;//gdsu = new DSU(n);
}



void Link(int a,int b){
	g[a].pb(b);
	g[b].pb(a);
	edges.pb({a,b});
}

inline bool isCritical(int x){
	DSU dsu(n);
	int deg[n];
	FOR(i,n)deg[i] = 0;

	for(auto e : edges){
		if(e.ff == x or e.ss == x)continue;
		deg[e.ff]++;
		deg[e.ss]++;
		if(dsu.find(e.ff) == dsu.find(e.ss)){

			return 0;
		}
		dsu.merge(e.ff,e.ss);
	}
	FOR(i,n)if(deg[i] > 2)return 0;
	return 1;
}

int CountCritical(){

	// check first if there is atleast 1 node of degree 2 or more.
		
	vector<ii> all;
	FOR(i,n){
		all.pb({g[i].size(),i});
	}
	sort(all.begin(), all.end());
	reverse(all.begin(), all.end());
	int ctr = 0;

	
	if(all[0].ff > 2){
		set<int> impNodes;
		if(all[0].ff >= 4){
			return isCritical(all[0].ss);
		}else{
			int csk = 0;
			FOR(i,min(n,7)){
				if(g[i].size() == 3)csk++;
			}
			if(csk <= 2){
				impNodes.insert(all[0].ss);
				impNodes.insert(all[1].ss);
				//ctr += isCritical(all[0].ss);
				//ctr += isCritical(all[1].ss);
				for(auto x : g[all[0].ss])impNodes.insert(x);
				for(auto x : g[all[1].ss])impNodes.insert(x);

				for(auto x:impNodes)ctr += isCritical(x);

			}else{
				FOR(i,min(10,n)){
					ctr += isCritical(all[i].ss);
				}		
			}
		}
		
		return ctr;
	}else{
		
		//cout << "yaya" << endl;
		
		DSU dsu(n);
		for(auto e:edges){
			if(dsu.find(e.ff) != dsu.find(e.ss))dsu.merge(e.ff,e.ss);
		}
	
		int ed[n];
		int nd[n];
		FOR(i,n)ed[i] = nd[i] = 0;
		for(auto e:edges){
			ed[dsu.find(e.ff)]++;
		}
		FOR(i,n)nd[dsu.find(i)]++;
		// find how many components have cycles 
		vi vv;
		FOR(i,n){
			if(nd[i] > 0 and ed[i] >= nd[i]){
				vv.pb(nd[i]);
			}
		}
		//cout << vv.size() << endl;
		if(vv.size() > 1){
			//while(1);
			return 0;
		}else if(vv.size() == 1){
			return vv[0];
		}else{
			return n;
		}
	}

	/*	
	FOR(i,n){
		ctr += isCritical(i);
	}*/
	
}
/*
int main(){
	Init(7);
	cout << CountCritical() << endl;
	Link(1,2);
	cout << CountCritical() << endl;
	Link(0,5);
	cout << CountCritical() << endl;
	Link(0,2);
	cout << CountCritical() << endl;
	Link(3,2);
	cout << CountCritical() << endl;
	Link(3,5);
	cout << CountCritical() << endl;
	Link(3,4);
	cout << CountCritical() << endl;
	

	return 0;
}*/

