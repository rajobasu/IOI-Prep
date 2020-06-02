/*
SOLUTION : do a dijkstra from each node and get the shortest even and odd length paths. Check parity with given d.
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
#define iii pair<ll,ii>
#define pll pair<ll,ll>
#define plll pair<ll,pll>
//#define mp make_pair
#define vv vector
#define endl '\n'
 
using namespace std;

const int MAXN = 10000 + 5;
const short INF = 15000;

vv<short> g[MAXN]; // 0->n-1 = {node, even}, n->2*n-1 = {node, odd};
short dist[MAXN/2][MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,k;
	cin >> n >> m >> k;
	FOR(i,n)FOR(j,2*n)dist[i][j] = INF;
	FOR(i,n)dist[i][i] = 0;
	FOR(i,m){
		int a,b;
		cin >> a >> b;
		a--;b--;
		g[a].pb((short)(b+n));
		g[b].pb((short)(a+n));
		g[a+n].pb((short)(b));
		g[b+n].pb((short)(a));
	}

	FOR(i,n){
		// source is i;
		queue<int> q;
		q.push(i);
		while(!q.empty()){
			int node = q.front();q.pop();
			for(auto e : g[node]){
				if(dist[i][e] <= dist[i][node] + 1)continue;
				dist[i][e] = dist[i][node]+1;
				q.push(e);
			}
		}
	}
	FOR(i,k){
		int a,b,c;
		cin >> a >> b >> c;
		a--;b--;
		if(c%2 == 0){
			if(dist[a][b] == INF){
				cout << "NIE" << endl;
			}else if(a == b and g[a].size() == 0){
				cout << "NIE" << endl;
			}else if(dist[a][b] <= c){
				cout << "TAK" << endl;
			}else{
				cout << "NIE" << endl;
			}
		}else{
			if(dist[a][b+n] == INF){
				cout << "NIE" << endl;
			}else if(dist[a][b+n] <= c){
				cout << "TAK" << endl;
			}else{
				cout << "NIE" << endl;
			}
		}
	}


	return 0;
}