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
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 

const int INF = 1e9;
using namespace std;
const int MAXN = 100*1000 +5;

int nodeVal[MAXN];
int edgesVal[MAXN];
bool marked[MAXN];
vector<ii> g[MAXN];

stack<ii> st;
bool vis[MAXN];
vector<ii> cycle;
bool done = 0;
void markCycle(int node,int p,int pe){
	st.push({node,pe});
	
	if(vis[node]){
		if(done)return;
		done = 1;
		bool got = 0;
	
		while(!st.empty()){

			auto e = st.top();st.pop();
			//marked[e.ff] = 1;
			if(e.ff == node){
				if(got)break;
				got = 1;
				
			}
			cycle.pb(e);
		}
	}else{
		vis[node] = 1;
		for(auto e:g[node]){
			if(e.ff != p){
				markCycle(e.ff,node,e.ss);
			}
		}
	}
	if(!st.empty())st.pop();
}

void dfs(int node,int p,int pe){
	for(auto e:g[node]){
		if(e.ff != p and !marked[e.ff]){
			dfs(e.ff,node,e.ss);
			nodeVal[node] -= nodeVal[e.ff];
		}
	}
	if(pe > -1){
		edgesVal[pe] = nodeVal[node];
	}
}

int main(){
	int n,m;
	cin >> n >> m;
	FOR(i,n)cin >> nodeVal[i];
	FOR(i,m){
		int a,b;
		cin >> a >> b;
		a--;b--;
		g[a].pb({b,i});
		g[b].pb({a,i});
	}
	if(m > n){
		cout << "0" << endl;
	}else if(m < n){
		
		dfs(0,-1,-1);
		FOR(i,m){
			cout << 2*edgesVal[i] << endl;
		}
	}else{
		markCycle(0,-1,-1);
		for(auto e:cycle){
		//	cout << e.ff << " ";
			marked[e.ff] = 1;
		}
		//cout << endl;

		int cnt = 0;
		FOR(i,n){
			if(marked[i]){
				dfs(i,-1,-1);
				cnt++;
			}
		}
		if(cnt%2 == 0){
			cout << 0 << endl;
		}else{
			ll sum = 0;int x = 1;
			for(auto e:cycle){
				sum += nodeVal[e.ff]*x;
				x *= -1;
			}
			edgesVal[cycle.back().ss] = sum/2;
			sum /= 2;
			nodeVal[cycle.back().ff] -= sum;
			nodeVal[cycle.front().ff] -= sum;
			FORE(i,0,(int)cycle.size()-2){
				edgesVal[cycle[i].ss] = nodeVal[cycle[i].ff];
				nodeVal[cycle[i+1].ff] -= edgesVal[cycle[i].ss];
			}
			FOR(i,m){
				cout << 2*edgesVal[i] << endl;
			}
		}
	}
	return 0;
}