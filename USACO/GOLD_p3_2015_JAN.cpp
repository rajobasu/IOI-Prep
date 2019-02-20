/*
SOLUTION: Find SCC, for each node, compute cost to it from node1, and cost from it to node0. 
		  Now iterate over each edge and get max cost.
COMPLEXITY: O(n)
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
#include <stack>
#include <set>
#include <fstream>

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

#define cin fin
#define cout fout

using namespace std;

const int INF = 1000000000;
const int MAXN = 100001;

vector<ii> g[MAXN];
int n,m;

int parent[MAXN];
void init(int n){
	FOR(i,n)parent[i] = i;
}
inline int find(int a){
	if(a != parent[a])parent[a] = find(parent[a]);
	return parent[a];
}
inline void merge(int a,int b){
	int pa = find(a);
	int pb = find(b);
	parent[pa] = pb;
}

bool vis[MAXN];
stack<int> ltime;
void dfs_SCC(int node){
	if(vis[node])return;
	vis[node] = 1;
	FOR(i,g[node].size()){
		ii child = g[node][i];
		if(child.ss == 0 or vis[child.ff])continue;
		dfs_SCC(child.ff);
	}
	ltime.push(node);
}
void dfs2(int node,int p){
	if(vis[node])return;
	vis[node] = 1;
	merge(node,p);
	FOR(i,g[node].size()){
		ii child = g[node][i];
		if(child.ss == 1 or vis[child.ff])continue;
		dfs2(child.ff,p);
	}
}
void generateSCC(int n){	
	FOR(i,n)vis[i] = 0;
	FOR(i,n)if(!vis[i])dfs_SCC(i);
	FOR(i,n)vis[i] = 0;

	while(!ltime.empty()){
		int node = ltime.top();ltime.pop();
		if(!vis[node])dfs2(node,node);
	}

}

vector<ii> all;
int sz[MAXN];
vector<int> nodes;
vector<ii> SCCedges;
vector<ii> gSCC[MAXN];
void buildSCC(int n){
	init(n);
	generateSCC(n);
	FOR(i,all.size()){
		ii a = all[i];
		if(find(a.ff) != find(a.ss)){
			gSCC[find(a.ff)].pb(mp(find(a.ss),1));
			gSCC[find(a.ss)].pb(mp(find(a.ff),0));
			SCCedges.pb(mp(find(a.ff),find(a.ss)));
		}
	}
	FOR(i,n)sz[find(i)]++;
}


int dpFrom[MAXN];
int dpTo[MAXN];

void dfs_dist_from(int node){
	//cout << node << " ";
	if(node == 0){
		dpFrom[node] = sz[node];
		vis[node] = 1;
		return;
	}
	if(vis[node])return;
	vis[node] = 1;
	FOR(i,gSCC[node].size()){
		ii child = gSCC[node][i];
		if(child.ss == 1)continue;
		if(!vis[child.ff]){
			dfs_dist_from(child.ff);	
		}
		dpFrom[node] = max(dpFrom[node],dpFrom[child.ff] + sz[node]);
	}
	//dpFrom[node] += sz[node];
}

void dfs_dist_to(int node){
	//cout << node << " ";cout << endl;
	if(node == 0){
		dpTo[node] = sz[node];
		vis[node] = 1;
		return;
	}
	if(vis[node])return;
	vis[node] = 1;
	FOR(i,gSCC[node].size()){
		ii child = gSCC[node][i];
		if(child.ss == 0)continue;
		if(vis[child.ff]){

		}else{
			dfs_dist_to(child.ff);
		}

		dpTo[node] = max(dpTo[node],dpTo[child.ff] + sz[node]);
	}
	//dpTo[node] += sz[node];
}

void calculateDP(int n){
	FOR(i,n)dpTo[i] = dpFrom[i] = -INF;
	FOR(i,n)vis[i] = 0;
	FOR(i,n)if(!vis[i])dfs_dist_from(i);
	FOR(i,n)vis[i] = 0;
	FOR(i,n)if(!vis[i])dfs_dist_to(i);
}

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("grass.in");
	fout.open("grass.out");

	
	cin >> n >> m;
	FOR(i,m){
		int a,b;
		cin >> a >> b;
		a--;b--;
		all.pb(mp(a,b));
		g[a].pb(mp(b,1));
		g[b].pb(mp(a,0));
	}
	buildSCC(n);
	calculateDP(n);
	int best = sz[0];
	FOR(i,SCCedges.size()){
		ii edge = SCCedges[i];
		best = max(dpFrom[edge.ss] + dpTo[edge.ff] - sz[0],best);
	}
	/*
	cout << "PARENT : ";
	FOR(i,n){
		cout << find(i) << " ";
	}
	cout << endl;
	FOR(i,n){
		cout << sz[i] << " ";
	}
	cout << endl;
	FOR(i,n)cout << dpTo[i] << " " << dpFrom[i] << endl;

	cout << best << endl;

*/	cout << best << endl;

	return 0;
}