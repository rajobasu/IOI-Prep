/*
SOLUTION: same as edi.
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
#include <unordered_map>
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ii pair<int,int>
#define ll long long int
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const int MOD = 1000000009;
const int INF = 1e9;
const int MAXN = 200001;

#define cin fin
#define cout fout

class DSU{
	int parent[MAXN];
	public : 
	DSU(){
		FOR(i,MAXN)parent[i] = i;
	}
	inline int find(int n){
		if(parent[n] != n)parent[n] = find(parent[n]);
		return parent[n];
	}
	inline void merge(int a,int b){
		int pa = find(a);
		int pb = find(b);
		parent[pa] = pb;
	}
};



int n,m,k,q;
vector<ii>* g;
vector<piil> edges;
int* color;
int PTR;
int par[MAXN];
int parCost[MAXN];


map<int,multiset<int> >  mps[MAXN];
multiset<int> sts[MAXN];

inline void dfs(int node,int p){
	par[node] = p;
	//cout << " NODE: " << node << endl;
	for(auto& child:g[node]){
		if(child.ff == p)continue;
		mps[node][color[child.ff]].insert(child.ss);
		parCost[child.ff] = child.ss;
		dfs(child.ff,node);
	}
}
inline void erase(multiset<int>& ms, int val){
	ms.erase(ms.lower_bound(val));
}


int main(){
	ifstream fin;
	ofstream fout;
	fin.open("grass.in");
	fout.open("grass.out");
	//FOR(i,MAXN)mps[i].reserve(1024),mps[i].max_load_factor(0.10);
	cin >> n >> m >> k >> q;
	g = new vector<ii>[n];
	color = new int[n];
	FOR(i,m){
		int a,b,c;
		cin >> a >> b >> c;
		a--;b--;
		edges.pb(mp(c,mp(a,b)));
	//	g[a].pb(mp(a,c));
	//	g[b].pb(mp(b,c));
	}
	FOR(i,n)cin >> color[i];
	sort(edges.begin(), edges.end());
	DSU dsu;
	FOR(i,edges.size()){
		if(dsu.find(edges[i].ss.ff) == dsu.find(edges[i].ss.ss))continue;
		g[edges[i].ss.ff].pb(mp(edges[i].ss.ss,edges[i].ff));
		g[edges[i].ss.ss].pb(mp(edges[i].ss.ff,edges[i].ff));
		dsu.merge(edges[i].ss.ff, edges[i].ss.ss);
	}
	// MST has been created. 
	// make the initial segment tree.
	dfs(0,-1);
	// now precess the queries.
	
	multiset<int> all;
	int ctr = 0;
	FOR(i,n){
		//int ans = min(segtree[i].query(0,color[i]-1), segtree[i].query(color[i]+1,MAXN));
		for(pair<const int,multiset<int> >& s:mps[i]){
			ctr++;
			if(s.ss.size() == 0)continue;
			if(s.ff == color[i])continue;

			sts[i].insert(*s.ss.begin());
		}
		if(sts[i].size() != 0)all.insert(*sts[i].begin());
	}
	if(ctr > 3*n)return 0;
	//cout << *all.begin() << endl;
	FOR(i,q){
		int a,b;
		cin >> a >> b;
		a--;
		if(color[a] == b){
			cout << *all.begin() << endl;
			continue;
		}
		if(par[a] != -1){
			if(sts[par[a]].size() != 0)erase(all,*sts[par[a]].begin());
			
			if(color[par[a]] != color[a])
				erase(sts[par[a]],*mps[par[a]][color[a]].begin());

			if(mps[par[a]][b].size() != 0 and color[par[a]] != b)
				erase(sts[par[a]],*mps[par[a]][b].begin());
			
			erase(mps[par[a]][color[a]],parCost[a]);
			mps[par[a]][b].insert(parCost[a]);
			
			if(mps[par[a]][color[a]].size() != 0 and color[par[a]] != color[a])
				sts[par[a]].insert(*mps[par[a]][color[a]].begin());

			if(color[par[a]] != b)
				sts[par[a]].insert(*mps[par[a]][b].begin());
			//cout << "Contrib from par " <<  *sts[par[a]].begin() << endl;
			if(sts[par[a]].size() != 0)all.insert(*sts[par[a]].begin());
			//cout << all.size() << " ";
			
		}

		if(sts[a].size() != 0)erase(all,*sts[a].begin());
		if(mps[a][color[a]].size() != 0)sts[a].insert(*mps[a][color[a]].begin());
		if(mps[a][b].size() != 0)erase(sts[a],*mps[a][b].begin());
		if(sts[a].size() != 0)all.insert(*sts[a].begin());

		color[a] = b;
		
		cout << *all.begin() << endl;//" " <<  ((par[a]!=0)?*sts[par[a]].begin():-1) << endl;
	}

	return 0;
}