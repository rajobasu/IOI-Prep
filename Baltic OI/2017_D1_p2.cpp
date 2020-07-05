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
//#define int long long
#define ld long double
#define vi deque<int>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define il pair<int,ll>
#define pll pair<ll,ll>
#define _path pair<ll,pair<ll,int> > 
#define vv deque
//#define endl '\n'
#define mp make_pair

using namespace std;

const int MAXN = 100000+5;
const int LOGN = 18;

vi g[MAXN];
int depth[MAXN];
int parent[LOGN][MAXN];
void dfs(int node,int p=-1){
	parent[0][node] = p;
	for(auto e: g[node]){
		if(e != p){
			depth[e] = depth[node] + 1;
			dfs(e,node);
		}
	}
}

void buildSparseTable(int n){
	FOR(i, LOGN){
		if(i == 0)continue;
		FOR(j,n){
			int x = parent[i-1][j];
			if(x == -1)parent[i][j] = -1;
			else parent[i][j] = parent[i-1][x];
		}
	}
}

int LCA(int a,int b){
	if(depth[a] < depth[b])swap(a,b);
	for(int i = LOGN-1;i >= 0;i--)if(parent[i][a] != -1 and depth[parent[i][a]] >= depth[b])a = parent[i][a];
	//now they are at the same level;
	if(a == b)return a;
	for(int i = LOGN -1 ; i>=0 ;i--){
		if(parent[i][a] != -1){
			if(parent[i][a] != parent[i][b]){
				a = parent[i][a];
				b = parent[i][b];
			}
		}
	}	
	return parent[0][a];
}
int k;
set<int> toAdd[MAXN];
set<int> toSub[MAXN];
bool includeParent[MAXN];
set<int>* active[MAXN];
void dfsAgain(int node,int p = -1){
	if(g[node].size() == 1 and p != -1){
		active[node] = new set<int>();
	}
	int id = 0;
	for(auto e: g[node]){
		if(e == p)continue;
		dfsAgain(e,node);
		if(active[node] == NULL)active[node] = active[e], id = e;
		else if(active[node]->size() < active[e]->size())active[node] = active[e], id = e;
	}
	for(auto e: g[node]){
		if(e == p or e == id)continue;
		for(auto f: *active[e])active[node]->insert(f);
	}

	for(auto e: toAdd[node])active[node]->insert(e);
	for(auto e: toSub[node])active[node]->erase(e);

	if(active[node]->size() >= k)includeParent[node] = true;
}

void solve(){
	int n,m;
	cin >> n >> m >> k;
	vv<ii> all;
	FOR(i,n-1){
		int a,b;
		cin >> a >> b;
		a--;b--;
		all.pb({a,b});
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs(0);
	buildSparseTable(n);	
	FOR(i,n)active[i] = NULL;

	FOR(i,m){
		int x;
		cin >> x;
		int lca = -1;
		FOR(j,x){
			int a;
			cin >> a;
			a--;
			if(lca == -1)lca = a;
			else lca = LCA(lca,a);
			toAdd[a].insert(i);
		}
		toSub[lca].insert(i);
	}
	vi finalList;
	dfsAgain(0);
	FOR(i,all.size()){
		auto e = all[i];
		if(depth[e.ff] >= depth[e.ss] and includeParent[e.ff])finalList.pb(i);
		else if(includeParent[e.ss])finalList.pb(i);
	
	}

	cout << finalList.size() << endl;
	for(auto e: finalList){
		cout << e+1 << " ";
	}
	cout << endl;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	//cin >> t;
	while(t--){
		solve();
	}
	return 0;
}