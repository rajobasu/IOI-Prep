/*
SOLUTION: dijsktras. changed pq to queue and got TLE-> AC for some reason. 
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
#include <unordered_map>
#include <map>
#include <complex>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ll long long int
#define ii pair<int,int>
#define il pair<int,ll>
#define li pair<ll,int>

#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const int MOD = 1000000009;
const ll INF = 1e15;
const int MAXN = 20001;

#define cin fin
#define cout fout

vector<ii> g[MAXN];
int hubID[MAXN]; // meaning clear from assignment
int rhubID[MAXN]; // meaning clear from assignment
ll dist[MAXN];
ll distmat[201][MAXN];
int main(){
	ifstream fin;
	ofstream fout;
	fin.open("vacationgold.in");
	fout.open("vacationgold.out");

	int n,m,k,q;
	cin >> n >> m >> k >> q;
	FOR(i,m){
		int a,b,c;
		cin >> a >> b >> c;
		a--;b--;
		g[a].pb(mp(b,c));
		//g[b].pb(mp(a,c));
	}
	FOR(i,n)hubID[i] = rhubID[i] = -1;
	FOR(i,k){
		int a;
		cin >> a;
		a--;
		//cout << a << endl;
		hubID[a] = i;
		rhubID[i] = a;
	}
	//FOR(i,n)cout << hubID[i] << " ";cout << endl;
	// conduct a dijkstra for each hub
	FOR(i,k)FOR(j,n)distmat[i][j] = INF;
	queue<ii> pq;
		
	FOR(i,k){
		FOR(j,n)dist[j] = INF;
		//dist[node] = 0;
		pq.push(mp(0,rhubID[i]));
		while(!pq.empty()){
			ii node = pq.front();pq.pop();
			if(dist[node.ss] <= node.ff)continue;
			dist[node.ss] = node.ff;
			for(auto child: g[node.ss]){
				if(child.ss + dist[node.ss] >= dist[child.ff])continue;

				pq.push({child.ss + dist[node.ss],child.ff});
			}
		}
		while(!pq.empty())pq.pop();
		;
		FOR(j,n){
			distmat[i][j] = dist[j];
		}
	}
	FOR(i,k){
		FOR(j,n){
		//	cout << distmat[i][j] << " ";
		}
		//cout << endl;
	}

	//cout << 1 << "\n" << 20 << endl;
	//return 0;
	int ctr = 0;
	ll sum = 0;

	FOR(i,q){
		int a,b;
		cin >> a >> b;
		//cout << a << " " << b << endl;
		a--;b--;/*
		FOR(i,n)dist[i] = INF;
		while(!pq.empty())pq.pop();
		pq.push(mp(0,a));
		while(!pq.empty()){
			ii node = pq.top();pq.pop();
			if(dist[node.ss] <= node.ff)continue;
			dist[node.ss] = node.ff;
			for(auto child: g[node.ss]){
				pq.push({child.ss + dist[node.ss],child.ff});
			}
		}
		ll d = dist[b];
		if(d == INF){

		}else{
			//cout << a << " " << b << " " << d << endl;
			//ctr ++;
			//sum += d;
		}*/
		//continue;
		if(hubID[a] == -1){
			// is not a hub
			ll mn = INF;
			/*FOR(j,g[a].size()){
				mn = min(mn,g[a][j].ss + distmat[hubID[g[a][j].ff]][b]);
				//cout << a << " " << b << " " << g[a][j].ff << endl;
				//cout << " :: " << g[a][j].ss << " " << distmat[hubID[g[a][j].ff]][b] << endl;
			}
			*/
			for(auto nxt : g[a])
			{
				mn = min(mn,nxt.ss + distmat[hubID[nxt.ff]][b]);
			}
			if(mn < INF){
				//cout << a << " " << b << " " << mn << endl;
				sum += mn;
				ctr++;
			}
		}else{
			// is a hub
			if(distmat[hubID[a]][b] < INF){
				//cout << a << " " << b << " " << distmat[a][b] << endl;
				sum += distmat[hubID[a]][b];
				ctr++;
			}
		}
	}
	
	cout << ctr << endl;
	cout << sum << endl;


	return 0;
}
