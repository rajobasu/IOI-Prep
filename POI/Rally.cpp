/*
Generate the toposort. Deleting a node means the path will go "over" that node so take calculate best paths in all prefix and suffix and connect them using an "overhead" edge for each node. Lazy Segtree is too slow. better to use offlinesweep + normal segtree
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
//#define mp make_pair
#define vv vector
#define endl '\n'
 
using namespace std;

const int MAXN = 500*1000 + 5;

struct SegmentTree{
	// range max/ point update
	int st[4*MAXN];
	// for input you are given n. smallest i such that 2^i > n : m = 2^i;; actual size needed = 2*m
	
	int combine(int a,int b){
		return max(a,b);
	}

	void update(int node,int ss,int se,int pos,int val){
		if(pos < ss or se < pos)return;
		// (1)
		if(ss == se){
			st[node] = max(st[node],val);
			return;
		}
		int mid = (ss+se)/2;
		update(node*2+1,ss,mid,pos,val);
		update(node*2+2,mid+1,se,pos,val);
		st[node] = combine(st[node*2+1],st[node*2+2]);
	}
	// [L .... ... [ss...se] .. R]
	int get(int node,int ss,int se,int l,int r){
		if(l > se or r < ss)return 0;
		if(l <= ss and se <= r)return st[node];
		int mid = (ss+se)/2;
		return combine(get(node*2+1,ss,mid,l,r),get(node*2+2,mid+1,se,l,r));
	}
};



vi g[MAXN]; // 0->n-1 = {node, even}, n->2*n-1 = {node, odd};
vi rg[MAXN];

int longest[MAXN];
int rlongest[MAXN];

int longestmax[MAXN];
int rlongestmax[MAXN];

vv<ii> ranges[MAXN]; // ranges[i] means range begins at i;

int topoID[MAXN];
int rtopoID[MAXN];
int deg[MAXN];
bool vis[MAXN];
int TP = 0;
void dfs(int n){
	// generate the topo sort
	FOR(i,n)deg[i] = rg[i].size();
	queue<int> q;
	FOR(i,n)if(deg[i] == 0)q.push(i);

	while(!q.empty()){
		int node = q.front();q.pop();
		if(vis[node])continue;
		vis[node] = 1;
		rtopoID[TP] = node;
		topoID[node] = TP++;
		for(auto e : g[node]){
			deg[e]--;
			if(deg[e] == 0)q.push(e);
		}
	}

}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin >> n >> m;
	vv<ii> all;
	FOR(i,m){
		int a,b;
		cin >> a >> b;
		a--;b--;
		all.pb({a,b});
		g[a].pb(b);
		rg[b].pb(a);
	}

	dfs(n);


	for(int i = n-1;i>=0;i--)
		for(auto e : g[rtopoID[i]])longest[i] = max(longest[i],1+longest[topoID[e]]);
	FOR(i,n)
		for(auto e : rg[rtopoID[i]])rlongest[i] = max(rlongest[i],1+rlongest[topoID[e]]);
	FOR(i,n){
		if(i == 0)rlongestmax[i] = rlongest[i];
		else rlongestmax[i] = max(rlongestmax[i-1],rlongest[i]);
	}
	for(int i = n-1;i>=0;i--){
		if(i == n-1)longestmax[i] = longest[i];
		else longestmax[i] = max(longestmax[i+1],longest[i]);
	}

	SegmentTree segtree;
	
	for(auto x : all){
		auto e = make_pair(topoID[x.ff],topoID[x.ss]);
		if(e.ss-e.ff >= 2){
			ranges[e.ff].pb({e.ss,rlongest[e.ff]+longest[e.ss]+1});
			//segtree.update(0,0,n,e.ff+1,e.ss-1,rlongest[e.ff]+longest[e.ss]+1);
		}
	}
	
	int nd = 0;
	int best = n+1;
	FOR(i,n){

		int v = segtree.get(0,0,n,i+1,n);
		if(i > 0)v = max(v,rlongestmax[i-1]);
		if(i < n-1)v = max(v,longestmax[i+1]);

		if(v < best){
			best = v;
			nd = rtopoID[i];
		}
		for(auto e :ranges[i]){
			segtree.update(0,0,n,e.ff,e.ss);
		}
	}
	cout << nd+1 << " " << best << endl;

	return 0;
}