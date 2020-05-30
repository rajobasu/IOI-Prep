/*
First, identify which all nodes have value 1. In particular, everything that is a sequence of left childs from original root should be treated separately. After that, *2 and *2+1 all give different numbers. 
Simultaneously search on each of the roots of the trees that we get from here on.
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

const int MAXN = 200*100*10 + 5;
const ll INF = 1e15;




int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	int depth[n];
	int fromLeft[n];
	bool isDist0[n];

	FOR(i,n)depth[i] = fromLeft[i] = isDist0[i] = 0;
	int l[n];
	int r[n];
	FOR(i,n){
		int a,b;
		cin >> a >> b;
		a--;b--;
		l[i] = a;
		r[i] = b;
	}
	vi allRoots;
	int rootNow = 0;
	while(rootNow != -1){
		isDist0[rootNow] = 1;
		if(r[rootNow]!=-1){
			allRoots.pb(r[rootNow]);
		}
		rootNow = l[rootNow];
	}
	//for(auto e : allRoots){
	queue<pair<vi,int> > qu;
	qu.push({allRoots,1});
	int prev = -1;
	int ctr = 1;
	while(!qu.empty()){
		auto node = qu.front();qu.pop();
		
		if(node.ss == prev)ctr++;
		else ctr = 1;

		vi lft;
		vi rght;

		for(auto e : node.ff){
			depth[e] = node.ss;
			fromLeft[e] = ctr;
			if(l[e] != -1)lft.pb(l[e]);
			if(r[e] != -1)rght.pb(r[e]);
		}
		prev = node.ss;
		if(!lft.empty())qu.push({lft,node.ss+1});
		if(!rght.empty())qu.push({rght,node.ss+1});
	}

	//FOR(i,n)cout << isDist0[i];cout << endl;
	//FOR(i,n)cout << depth[i] << " ";cout << endl;
	//FOR(i,n)cout << fromLeft[i] << " ";cout << endl;

	int q;
	cin >> q;
	while(q--){
		int a,b;
		cin >> a >> b;
		a--;b--;
		if(a == b)cout << "TAK" << endl;
		else if(isDist0[a] and isDist0[b])cout << "TAK" << endl;
		else if(isDist0[b])cout << "TAK" << endl;
		else if(isDist0[a])cout << "NIE" << endl;
		else if(depth[a] > depth[b])cout << "TAK" << endl;
		else if(depth[a] == depth[b] and fromLeft[a] >= fromLeft[b])cout << "TAK" << endl;
		else cout << "NIE" << endl;
	}

	return 0;
}