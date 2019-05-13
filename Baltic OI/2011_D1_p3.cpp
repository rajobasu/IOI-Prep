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

const int INF = 1e9;

using namespace std;
const int MAXN = 502*502;

vector<ii> g[MAXN];
bool vis[MAXN];
int main(){
	int n,m;
	cin >> n >> m;
	FOR(i,n){
		string s;
		cin >> s;
		FOR(j,m){
			int from1 = i*(m+1) + j+1;
			int to1 = (i+1)*(m+1) + j;
			int from2 = i*(m+1)+j;
			int to2 = (i+1)*(m+1)+j+1;

			if(s[j] == '/'){
				g[from1].pb({to1,0});
				g[to1].pb({from1,0});

				g[from2].pb({to2,1});
				g[to2].pb({from2,1});

			}else{
				g[from2].pb({to2,0});
				g[to2].pb({from2,0});

				g[from1].pb({to1,1});
				g[to1].pb({from1,1});
				
			}
		}
	}

	priority_queue<ii, vector<ii> , greater<ii> > pq;
	pq.push({0,0});

	while(!pq.empty()){
		ii node = pq.top();pq.pop();
		if(node.ss == n*(m+1)+m){
			cout << node.ff << endl;
			return 0;
		}
		if(vis[node.ss])continue;
		vis[node.ss] = 1;
		for(auto e : g[node.ss]){
			if(!vis[e.ff]){
				pq.push({e.ss+node.ff,e.ff});
			}
		}
	}
	cout << "NO SOLUTION" << endl;

    return 0;
}