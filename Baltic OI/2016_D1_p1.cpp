/*
Each node contributes 1*depth to the total sum. we need to root the tree so that this is minimized.
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
#define v vector
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>
#define cd complex<double> 
#define iil pair<ii,ll>

const int INF = 1e9;
using namespace std;
const int MAXN = 151;



int main(){
	int n;
	cin >> n;
	vi g[n];
	FOR(i,n){
		int k;
		cin >> k;
		FOR(j,k){
			int a;cin >> a;
			a--;
			g[a].pb(i);
		}
	}
	int best = n;
	int mnsum = INF;
	FOR(i,n){
		bool vis[n];FOR(i,n)vis[i] = 0;
		int dpt[n];
		queue<ii> q;
		q.push({i,0});
		while(!q.empty()){
			auto e = q.front();q.pop();
			if(vis[e.ff])continue;
			vis[e.ff] = 1;
			dpt[e.ff] = e.ss;
			for(auto v:g[e.ff]){
				q.push({v,e.ss+1});
			}
		} 
		int mx = 0;
		//FOR(j,n)mx =max(mx,dpt[j]);
		int rchd = 0;
		FOR(j,n)if(vis[j])rchd++;
		if(rchd != n)continue;
		int sum = 0;
		FOR(j,n)sum += dpt[j]+1;
		mnsum = min(mnsum,sum);
	}
	cout << mnsum << endl;

	return 0;
}