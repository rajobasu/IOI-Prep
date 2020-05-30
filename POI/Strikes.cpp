/*
Just keep track of how many neighbours, by marking parents 'affectedChildren' count when marking or unmarking. That should be enough to maintain all the information.
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
#define pll pair<ll,ll>
#define il pair<int,ll>
#define vv vector
#define endl '\n'
#define num ff
#define denom ss

using namespace std;

const int MAXN = 500*100*10 + 5;
const ll INF = 1e15;

int parent[MAXN];
int childrenDegree[MAXN];
int isMarked[MAXN];
vi g[MAXN];
void dfs(int node,int p=-1){
	parent[node] = p;
	for(auto e : g[node])if(e != p)dfs(e,node);
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	FOR(i,n-1){
		int a,b;
		cin >> a >> b;
		a--;b--;
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs(0);
	int q;
	cin >> q;
	int cc = 1;
	while(q--){
		int a;
		cin >> a;
		if(a > 0){
			// need to add;
			a--;
			cc += (((int)g[a].size())- childrenDegree[a]-(parent[a] != -1)) + (parent[a]==-1?0:!isMarked[parent[a]])-1;
			if(parent[a] != -1)childrenDegree[parent[a]]++;
			isMarked[a] = 1;
		}else{
			a = abs(a)-1;
			cc -= (((int)g[a].size())- childrenDegree[a]-(parent[a] != -1)) + (parent[a]==-1?0:!isMarked[parent[a]])-1;
			if(parent[a] != -1)childrenDegree[parent[a]]--;
			isMarked[a] = 0;
		}
		cout << cc << endl;
	}

	return 0;
}