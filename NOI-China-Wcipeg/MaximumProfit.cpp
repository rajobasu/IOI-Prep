/*
SOLUTION: Model this as a mincut problem. It is identical to this prob.
https://www.hackerearth.com/practice/algorithms/graphs/min-cut/practice-problems/algorithm/mancunian-the-confectioner/
COMPLEXITY: Of that of flow.
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
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define ld long double

using namespace std;

const int MOD = 1000000007;
const ll INF = 1000000000;
//const int MAXN = 1000001;


class Dinic{
	struct edge { int v, rev;ll cap, f; };

	static const int MAXN = 55005;
	//const ll INF = 0x3f3f3f3f;


	std::vector<edge> adj[MAXN];
	ll dist[MAXN], ptr[MAXN];
	public :
	void add_edge(int u, int v, ll cap) {
	  adj[u].push_back((edge){v, (int)adj[v].size(), cap, 0});
	  adj[v].push_back((edge){u, (int)adj[u].size() - 1, 0, 0});
	}

	bool dinic_bfs(int nodes, int source, int sink) {
	  std::fill(dist, dist + nodes, -1);
	  dist[source] = 0;
	  std::queue<int> q;
	  q.push(source);
	  while (!q.empty()) {
	    int u = q.front();
	    q.pop();
	    for (int j = 0; j < (int)adj[u].size(); j++) {
	      edge &e = adj[u][j];
	      if (dist[e.v] < 0 && e.f < e.cap) {
	        dist[e.v] = dist[u] + 1;
	        q.push(e.v);
	      }
	    }
	  }
	  return dist[sink] >= 0;
	}

	ll dinic_dfs(int u, ll f, int sink) {
	  if (u == sink) {
	    return f;
	  }
	  for (; ptr[u] < (int)adj[u].size(); ptr[u]++) {
	    edge &e = adj[u][ptr[u]];
	    if (dist[e.v] == dist[u] + 1 && e.f < e.cap) {
	      ll flow = dinic_dfs(e.v, std::min(f, e.cap - e.f), sink);
	      if (flow > 0) {
	        e.f += flow;
	        adj[e.v][e.rev].f -= flow;
	        return flow;
	      }
	    }
	  }
	  return 0;
	}

	ll dinic(int nodes, int source, int sink) {
	  ll flow, max_flow = 0;
	  while (dinic_bfs(nodes, source, sink)) {
	    std::fill(ptr, ptr + nodes, 0);
	    while ((flow = dinic_dfs(source, INF, sink)) != 0) {
	      max_flow += flow;
	    }
	  }
	  return max_flow;
	}
};

int main(){
	int n,m;
	cin >> n >> m;
	Dinic graph;
	int arr[n];
	FOR(i,n)cin >> arr[i];
	ll sum = 0;
	FOR(i,n){
		graph.add_edge(m+1+i,m+n+1,arr[i]);
	}
	FOR(i,m){
		int a,b,c;
		cin >> a >> b >> c;
		sum += c;
		graph.add_edge(0,i+1,c);
		graph.add_edge(i+1,m+a,INF);
		graph.add_edge(i+1,m+b,INF);
	}
	cout << sum - graph.dinic(m+n+2,0,m+n+1) << endl;


	return 0;
}


