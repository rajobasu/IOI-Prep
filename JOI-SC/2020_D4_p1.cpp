/*
Assume centroid will be present inside the city. Dont assume that the centroid's color will be the final color.
Put all the nodes of that same color in a queue and take their parents. when you encounter a new color, take
all the nodes of that color and see their parents, and so on. If you see any node is not inside the tree of the current
centroid, then exit. 
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <deque>
#include <iomanip>
#include <list>
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
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define il pair<ll,ll>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 200*100*10 + 5;
const ll INF = 1e15;


vi g[MAXN];
int color[MAXN];

int substree[MAXN];
int blocked[MAXN];

vi colorNodes[MAXN];
int parent[MAXN];

bool usedColors[MAXN];

queue<int> centroidQ;

void dfsSetup(int node,int p=-1){
	substree[node] = 1;
	parent[node] = p;
	usedColors[color[node]] = 0;
	for(auto e : g[node]){
		if(e != p and !blocked[e]){
			dfsSetup(e,node);
			substree[node] += substree[e];
		}
	}
}

void dfsDestroy(int node,int p = -1){
	substree[node] = -1;
	for(auto e : g[node]){
		if(e == p or blocked[e])continue;
		dfsDestroy(e,node);
	}
}

int getCentroid(int node,int tot,int p=-1){
	for(auto e: g[node]){
		if(e == p or blocked[e])continue;
		if(substree[e]*2 > tot)return getCentroid(e,tot,node);
	}
	return node;
}
int ans = MAXN;
void processTree(int root){
	dfsSetup(root);
	int c = getCentroid(root,substree[root]);
	dfsSetup(c);
	queue<int> currentColors;
	currentColors.push(color[c]);
	usedColors[color[c]] = 1;	

	int ctr = 0;
	bool bad = 0;
	while(!currentColors.empty()){
		int cc = currentColors.front();
		currentColors.pop();
		ctr++;
		for(auto e : colorNodes[cc]){
			if(substree[e] == -1 or blocked[e]){
				bad = 1;
				break;
			}else if(parent[e] != -1){
				if(!usedColors[color[parent[e]]]){
					currentColors.push(color[parent[e]]);
					usedColors[color[parent[e]]] = 1;
				}
			}
		}
		if(bad)break;
	}
	//cout << ": " << c << " " << bad << " " << ctr << endl;
	if(!bad){
		ans = min(ans,ctr-1);
	}

	for(auto e : g[c])if(!blocked[e])centroidQ.push(e);
	dfsDestroy(root);
	blocked[c] = 1;
}

void centroidDecomp(){
	centroidQ.push(0);
	while(!centroidQ.empty()){
		int item = centroidQ.front();
		centroidQ.pop();
		processTree(item);
		
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n,k;
	
	cin >> n >> k;
	ans = k-1;
	FOR(i,n-1){
		int a,b;
		cin >> a >> b;
		a--;b--;
		g[a].pb(b);
		g[b].pb(a);
	}
	FOR(i,n)cin >> color[i];
	FOR(i,n)colorNodes[color[i]].pb(i);

	centroidDecomp();
	cout << ans << endl;
	return 0;
}