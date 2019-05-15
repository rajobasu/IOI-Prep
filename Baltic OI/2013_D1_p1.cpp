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
#define cd complex<double> 

const ll INF = 4e18;
using namespace std;
const int MAXN = 100005;

vi g[MAXN];
int sparseTable[20][MAXN];
int DPmin[MAXN];
int dpt[MAXN];
int parent[MAXN];
set<ii> s;
int status[MAXN];

void dfs1(int node,int p){
	dpt[node] = ((p!=-1)?dpt[p]+1:0);
	parent[node] = p;
	vector<ii> all;
	DPmin[node] = node;
	for(auto e:g[node]){
		if(e==p)continue;
		dfs1(e,node);
		all.pb({DPmin[e],e});
		DPmin[node] = min(DPmin[node],DPmin[e]);
	}
	sort(all.begin(), all.end());
	g[node].clear();
	for(auto e:all)g[node].pb(e.ss);
	g[node].pb(p);
}
int T = 0;
int __tm__[MAXN];
void dfs2(int node,int p){
	for(auto e:g[node]){
		if(e!=p)dfs2(e,node);
	}
	__tm__[node] = T;
	s.insert({T++,node});
}
void buildSparseTable(int n){
	FOR(i,n)sparseTable[0][i] = parent[i];
	FORE(i,1,19){
		FOR(node,n){
			int p = sparseTable[i-1][node];
			if(p == -1){
				sparseTable[i][node] = -1;
			}else{
				sparseTable[i][node] = sparseTable[i-1][p];
			}
		}
		
	}
}
inline int findFirstAncestor(int n,int a){
	int k = 20;

	while(k--){
		int p = sparseTable[k][a];
		if(p == -1 or status[p] == 0){

		}else{
			a=p;
		}
	}
	return a;
}


int main(){
	int n,q;
	cin >> n >> q;
	int root = 0;
	FOR(i,n){
		int a;
		cin >> a;
		a--;
		if(a >= 0)g[a].pb(i);
		else root = i;
	}

	dfs1(root,-1);
	dfs2(root,-1);
	buildSparseTable(n);
	while(q--){
		int t,a;
		cin >> t >> a;
		if(t == 1){
			int last = 0;
			FOR(i,a){
				ii to = *s.begin();
				s.erase(to);
				status[to.ss] = 1;
				last = to.ss+1;
			}
			cout << last << endl;
		}else{

			a--;
			int p = findFirstAncestor(n,a);
			s.insert({__tm__[p],p});
			status[p] = 0;
			
			cout << dpt[a]-dpt[p] << endl;
		}
	}
	return 0;
}
