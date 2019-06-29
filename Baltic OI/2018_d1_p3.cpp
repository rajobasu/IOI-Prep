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
#include <random>
#include <stack>
#include <chrono>
#include <set>

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i=a;i<=b;i++)
#define ll long long int
#define vi vector<int>
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define il pair<int,ll>
#define li pair<ll,int>
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define ld long double
#define pld pair<ld,ld>
#define iii pair<ii,ll>
#define vv vector

using namespace std;

const ll INF = 1e16+10;
const int MAXN = 100*100*10+10;
const int B = 430;

int n,e,s;
bool sp[MAXN];
vi special;
vv<il> g[MAXN];
vv<iii> edges;

int parent[20][MAXN];
ll dist[MAXN];
int dpt[MAXN];
int st[MAXN];
int en[MAXN];
int T = -1;
void dfs1(int node,int p = -1){
	parent[0][node] = p;
	dpt[node] = (p==-1)?0:dpt[p]+1;
	st[node] = ++T; 
	for(auto e : g[node]){
		if(e.ff == p)continue;
		dist[e.ff] = dist[node] + e.ss;
		dfs1(e.ff,node);

	}
	en[node] = ++T;
}

ll dist2[20][MAXN];
void dfs2(int node,int p=-1){
	if(sp[node])dist2[0][node] = dist[node];
	else dist2[0][node] = 10*INF;

	for(auto e  : g[node]){
		if(e.ff == p)continue;
		dfs2(e.ff,node);
		dist2[0][node] = min(dist2[0][node],dist2[0][e.ff]);
	}
	
}

void computeSparseTable(){

	FORE(j,1,19){
		FOR(i,n){
			int x = parent[j-1][i];
			if(x == -1)parent[j][i] = -1;
			else parent[j][i] = parent[j-1][x];
		}
	}

	FORE(j,1,19){
		FOR(i,n){
			int x = parent[j-1][i];
			if(x != -1)dist2[j][i] = min(dist2[j-1][i],dist2[j-1][x]);
			else dist2[j][i] = dist2[j-1][i];
		}
	}

}

inline bool isEscapePoss(int np,int node){
	bool isOut1 = st[np]>st[node] or en[np]<st[node];
	bool isOut2 = st[np]>st[e] or en[np]<st[e];
	return !(isOut1^isOut2);
}

ll getMin(int node,int p){
	ll mn = INF;
	/*while(p != node){
		cout << node << " " << dist2[0][node] << endl;
		mn = min(mn,dist2[0][node]);
		node = parent[0][node];
		if(node == -1)break;
	}
	cout << endl;
	return mn;*/
	for(int j = 18;j>=0;j--){
		if(node == -1)continue;

		if(parent[j][node] == -1)continue;
//		cout << node << " " << parent[j][node] << endl;  
		if(dpt[parent[j][node]] <= dpt[p])continue;
//		cout << node << endl;
		mn = min(mn,dist2[j][node]);
		node = parent[j][node];
	}
//	cout << node << "::" << dist2[0][node]<< endl;
	mn = min(mn,dist2[0][node]);
	return mn;
}


#define endl '\n'
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> n >> s >> q >> e;
	e--;
	FOR(i,n-1){
		int a,b,c;
		cin >> a >> b >> c;
		a--;b--;
		edges.pb({{a,b},c});
		g[a].pb({b,c});
		g[b].pb({a,c});
	}
	FOR(i,20)FOR(j,n)dist2[i][j] = 10*INF;
	FOR(i,s){
		int x;cin >> x;x--;special.pb(x);
		sp[x] = 1;
	}
	// proprocess the tree.
	dfs1(e);
	dfs2(e);
	FOR(i,n)dist2[0][i] -= 2*dist[i];
	//FOR(i,n)cout << dist[i] << " ";cout << endl;
	computeSparseTable();
	
	FOR(i,q){
		int a,b;
		cin >> a >> b;
		a--;b--;
		int x = (dist[edges[a].ff.ff] > dist[edges[a].ff.ss])?edges[a].ff.ff : edges[a].ff.ss;
		int y = (dist[edges[a].ff.ff] <= dist[edges[a].ff.ss])?edges[a].ff.ff : edges[a].ff.ss;
		if(isEscapePoss(x,b)){
			cout << "escaped" << endl;
		}else{
			ll dt = min(getMin(b,y),dist2[0][x]) + dist[b];
			if(dt >= INF){
				cout << "oo" << endl;
			}else{
				cout << dt << endl;
			}
		}
	}
	return 0;
}
