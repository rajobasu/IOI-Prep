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
#define vv vector

using namespace std;

int n;
const int MAXN = 50000 + 1;
vi normieEdges[MAXN];
int comp[MAXN];
int sz[MAXN];
vi reverseEdges[MAXN];
vi newG[MAXN];
vv<ii> allE;
stack<int> s;
bool vis[MAXN];
void dfs(int node){
	if(vis[node])return;
	vis[node] = 1;
	for(auto e : normieEdges[node])dfs(e);
	s.push(node);
}
void dfs2(int node,int c){
	if(vis[node])return;
	vis[node] = 1;
	comp[node] = c;
	sz[c]++; 
	for(auto e :reverseEdges[node])dfs2(e,c);
}

void compressScc(){
	FOR(i,n)if(!vis[i])dfs(i);
	FOR(i,n)vis[i] = 0;
	while(!s.empty()){
		int i = s.top();
		s.pop();
		if(vis[i])continue;
		dfs2(i,i);
	}
	for(auto e : allE){
		if(comp[e.ff] == comp[e.ss])continue;
		newG[comp[e.ff]].pb(comp[e.ss]);
	}
}

int dp[MAXN];

void dfs3(int node){
	if(vis[node])return;
	vis[node] = 1;
	dp[node] = newG[node].size() + sz[node]-1;
	for(auto e : newG[node]){
		dfs3(e);
		dp[node] += dp[e];
	}
}

int main(){
	int m;
	cin >> n >> m;
	FOR(i,m){
		int a,b;
		cin >> a >> b;
		a--;b--;
		normieEdges[a].pb(b);
		reverseEdges[b].pb(a);
		allE.pb({a,b});
	}
	compressScc();

	FOR(i,n)vis[i] = 0;
	FOR(i,n)dfs3(i);
	FOR(i,n){
		cout << dp[comp[i]] << endl;
	}

	return 0;
}