#include <bits/stdc++.h>
 
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i = a;i<=b;i++)
#define ll long long int
#define pb push_back
#define vi vector<int>
#define ff first
#define ss second
#define vv vector
#define ii pair<int,int>
 
using namespace std;
 
const int MAXN = 5e5 + 1;
const int LOGN = 20;
 
int n,k;
 
 
vi g[MAXN];
int color[MAXN];
vi verticesOfColor[MAXN];
int sparseTable[LOGN][MAXN];
int depth[MAXN];
int degree[MAXN];
 
void dfs_setup(int node,int p = -1){
	sparseTable[0][node] = p;
	if(p == -1)depth[node] = -1;else depth[node] = depth[p] + 1;
	for(auto e : g[node]){
		if(e != p)dfs_setup(e,node);
	}
}
 
struct DSU{
	int parent[MAXN];
	int ID[MAXN];
	void init(){
		FOR(i,n) parent[i] = i;
		FOR(i,n) ID[i] = i;
	}
	inline int find(int a){
		if(parent[a] != a)parent[a] = find(parent[a]);
		return parent[a];
	}
	inline void merge(int a,int b){
		int pa = find(a);
		int pb = find(b);
		if(depth[pa] > depth[pb])swap(pa,pb);
		parent[pb] = pa;
		//parent[pa] = pb;
		//if(depth[pa] < depth[pb])ID[pb] = pa;else ID[pb] = pa;
	}
	inline int id(int a){
		return find(a);
		//return ID[find(a)];
	}
	inline bool isSame(int a,int b){
		return find(a) == find(b);
	}
} dsu;
 
bool done[MAXN];
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	vv<ii> allE;
	FOR(i,n-1){
		int a,b;cin >> a >> b;a--;b--;
		g[a].pb(b);g[b].pb(a);
		allE.pb({a,b});
	}
	dfs_setup(0);
	FOR(i,n){
		int a;cin >> a;a--;
		color[i] = a;
		verticesOfColor[a].pb(i);
	}
	dsu.init();
	FOR(i,k){
		if(verticesOfColor[i].size() == 1)continue;
		FORE(j,1,(int)verticesOfColor[i].size()-1){
			int node1 = dsu.id(verticesOfColor[i][j]);
			int node2 = dsu.id(verticesOfColor[i][j-1]);
			while(node1 != node2){
				if(depth[node1] > depth[node2])swap(node1,node2);
				int p = dsu.id(sparseTable[0][node2]);
				if(p == -1)p = 0;
				dsu.merge(p,node2);
		//		cout << node2 << " " << node1 << " " << p << endl;
				node2 = p;
				
			}
		}
	}
	//FOR(i,n)cout << dsu.find(i) << endl;
	for(auto e : allE)if(!dsu.isSame(e.ff,e.ss))degree[dsu.find(e.ff)]++,degree[dsu.find(e.ss)]++;
	int cnt = 1;
	FOR(i,n)if(degree[i] == 1)cnt++;
	cout << cnt/2 << endl;
	return 0;
}
 