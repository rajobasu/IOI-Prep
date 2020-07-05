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

const int MAXN = 50000+5;

set<int> g[MAXN];

bool check(vi all){
	FOR(i,all.size())
		FOR(j,i)
			if(g[all[i]].find(all[j]) == g[all[i]].end())
				return false;
	return true;
}

void solve(){
	int n,k;
	cin >> n >> k;
	FOR(i,n){
		int a;
		cin >> a;
		FOR(j,a){
			int x;
			cin >> x;
			g[i].insert(x);
		}
	}
	priority_queue<ii,vv<ii>, greater<ii> > pq;

	FOR(i,n)pq.push({g[i].size(),i});
	int mx = 1;
	while(!pq.empty()){
		ii item = pq.top();pq.pop();
		if(item.ff != g[item.ss].size())continue;
		//cout << item.ff << " " << item.ss << endl;
		// try to take item in the set;
		if(g[item.ss].size() == 0)continue;
		vi neighbours;
		for(auto e: g[item.ss])neighbours.pb(e);

		int nn = 1 + neighbours.size();
		FOR(mask,1<<nn){
			if(mask == 0)continue;
			vi all;all.pb(item.ss);
			FOR(i,nn){
				if(mask&(1<<i))all.pb(neighbours[i]);
			}
			if(check(all))mx = max(mx,(int)all.size());
		}
		// now lets delete the node from the graph
		for(auto e: neighbours){
			g[e].erase(item.ss);
			g[item.ss].erase(e);
			pq.push({g[e].size(),e});
		}
	}
	cout << mx << endl;
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