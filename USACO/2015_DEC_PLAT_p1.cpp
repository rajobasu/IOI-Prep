/*
SOLUTION: simple HLD
COMPLEXITY: O(nlognlogn)
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
#define ii pair<ll,ll>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>


using namespace std;

const int MOD = 1000000007;
const int INF = 1000000000;
const int MAXN = 50001;

class SegmentTree{
	int st[4*MAXN];
	int lz[4*MAXN];
	inline int lc(int node){
		return node*2+1;
	}
	inline int rc(int node){
		return node*2+2;
	}
	inline void propagate(int node,int sz){
		st[node] += lz[node];
		if(sz > 1){
			lz[lc(node)] += lz[node];
			lz[rc(node)] += lz[node];
		}
		lz[node] = 0;
	}
	void _update_(int node,int ss,int se,int l,int r,int val){
		propagate(node,se-ss+1);
		if(ss > r or se <l)return;
		if(l <= ss and se <= r){
			lz[node] += val;
			propagate(node,se-ss+1);
			return;
		}
		int mid = (ss+se)/2;
		_update_(lc(node),ss,mid,l,r,val);
		_update_(rc(node),mid+1,se,l,r,val);
		st[node] = max(st[lc(node)] , st[rc(node)]);
	}
	int _query_(int node,int ss,int se,int l,int r){
		propagate(node,se-ss+1);
		if(ss > r or se < l)return 0;
		if(l <= ss and se <= r)return st[node];
		int mid = (ss+se)/2;
		return max(_query_(lc(node),ss,mid,l,r),_query_(rc(node),mid+1,se,l,r));
	}
	public:

	void update(int l,int r,int val){
		if(l>r)swap(l,r);
		_update_(0,0,MAXN,min(l,r),max(l,r),val);
	}
	int query(int l,int r){
		return _query_(0,0,MAXN,min(l,r),max(l,r));
	}
} segtree;


vi g[MAXN];
int subtreeSize[MAXN];
int depth[MAXN];
int parent[20][MAXN];
int head[MAXN];
int T = 0;
int in[MAXN];
void dfs_hld(int node,int p){
	parent[0][node] = p;
	if(p == -1)depth[node] = 0;
	else depth[node] = depth[parent[0][node]]+1;

	int tot = 1;
	FOR(i,g[node].size()){
		int child = g[node][i];
		if(child == p)continue;
		dfs_hld(child,node);
		if(subtreeSize[child]>subtreeSize[g[node][0]]){
			swap(g[node][i],g[node][0]);
		}
		tot += subtreeSize[child];
	}
	subtreeSize[node] = tot;
}
void dfs_euler(int node,int p){
	in[node] = T++;
	if(p == -1)head[node] = node;
	FOR(i,g[node].size()){
		int child = g[node][i];
		if(child == p)continue;
		if(i == 0)head[child] = head[node];
		else head[child] = child;
		dfs_euler(child,node);
	}	
}

void precomputeSparseTable(int n){
	FOR(i,20){
		if(i == 0)continue;
		FOR(j,n){
			int pp = parent[i-1][j];
			if(pp == -1)parent[i][j] = pp;
			else parent[i][j] = parent[i-1][pp];
		}
	}
}
int kthAncestor(int node,int k){
	if(k < 0)return INF;
	int curr = node;
	int ctr = 0;
	while(ctr < 20){
		if((k&(1<<ctr))>0)curr = parent[ctr][curr];
		if(curr == -1)return -1;
		ctr++;
	}
	return curr;
}
int LCA(int a,int b){
	if(depth[a] > depth[b])swap(a,b);
	b = kthAncestor(b,depth[b]-depth[a]);
	if(a == b)return a;
	int ctr = 19;
	while(ctr > -1){
		if(parent[ctr][a] == parent[ctr][b]){
			ctr--;
		}else{
			if(parent[0][a] == parent[0][b]){
				return parent[0][a];
			}else{
				a = parent[ctr][a];
				b = parent[ctr][b];
			}
			ctr--;
		}
	}
	return parent[0][a];
}

void updateChains(int lower,int higher){
	if(lower == INF or higher == INF)return;
	while(lower > -1){
		int headOfCurrentChain = head[lower];
		if(depth[headOfCurrentChain] <= depth[higher]){
			segtree.update(in[lower],in[higher],1);
			break;
		}else{
			segtree.update(in[lower],in[headOfCurrentChain],1);
			lower = parent[0][headOfCurrentChain];
		}
	}
}

void processUpdate(int u,int v){
	int lca = LCA(u,v);
	updateChains(u,lca);
	updateChains(v,kthAncestor(v,depth[v] - depth[lca]-1));// to avoid doublecounting at lca.
}

void initEverything(int n){
	dfs_hld(0,-1);
	dfs_euler(0,-1);
	precomputeSparseTable(n);
}
#define cin fin
#define cout fout

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("maxflow.in");
	fout.open("maxflow.out");
	int n,q;
	cin >> n >> q;
	FOR(i,n-1){
		int a,b;
		cin >> a >> b;
		a--;b--;
		g[a].pb(b);
		g[b].pb(a);
	}
	initEverything(n);
	while(q--){
		int a,b;
		cin >> a >> b;
		a--;b--;
		processUpdate(a,b);
	}
	cout << segtree.query(0,MAXN-1) << endl;
	return 0;
}