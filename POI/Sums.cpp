#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <cmath>
#include <stdio.h>
#include <set>


#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i,a,b) for(int i = a;i<=b;i++)
#define ii pair<int,int>
#define ff first
#define ss second
#define ll int 
#define vv vector
#define vi vector<int>
#define pb push_back

const int MAXN = 50000;
const ll INF = 1e9+7;

using namespace std;

vv<ii> g[MAXN];
set<int> gg[MAXN];
#define endl '\n'

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	ll arr[n];
	ll arr2[n];
	FOR(i,n)cin >> arr[i];
	ll mn = INF;
	FOR(i,n)mn = min(mn,arr[i]);
	FOR(i,n)arr2[i] = arr[i]%mn;
	int dd[mn];

	FOR(i,mn)dd[i] = INF;
	FOR(i,n)dd[arr2[i]] = min(dd[arr2[i]],arr[i]);
	vv<ii> ddd;
	FOR(i,mn)if(dd[i] != INF)ddd.pb({i,dd[i]});

	priority_queue<ii,vv<ii>,greater<ii> > pq;
	//queue<ii> pq;
	
	ll dist[mn+1];
	FOR(i,mn)dist[i] = INF;

	FOR(i,n)pq.push({arr[i],arr2[i]});
	FOR(i,n)dist[arr2[i]] = min(dist[arr2[i]],arr[i]);
	//cout << "WHY THO" << endl;
	while(!pq.empty()){
		ii node = pq.top();pq.pop();
		swap(node.ff,node.ss);
		if(dist[node.ff] > node.ss)continue;
		for(auto e : ddd){
			ll d = e.ss + node.ss;
			int x = (node.ff + e.ff)%mn;
			if(dist[x] > d)pq.push({d,x}),dist[x] = d;
		}

	}
	//FOR(i,mn)cout << dist[i] << " ";cout << endl;
	//cout << "HOLA" << endl;
	int k;cin >> k;
	FOR(i,k){
		ll a;cin >> a;
		if(a == 0){
			cout << "TAK" << endl;
			continue;
		}
		if(dist[a%mn] > a){
			cout << "NIE" << endl;
		}else{
			cout << "TAK" << endl;
		}
	}


	return 0;
}
