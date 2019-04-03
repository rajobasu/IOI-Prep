/*
SOLUTION: Different from intended. For each stall maintain next and previous pointers, and assign cows. 
Also, for cells that get filled, we maintain the nxt pointers from a DSU. This is needed.
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
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#include <stack>
#include <set>
#include <fstream>

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ii pair<int,int>
#define ll long long int
#define piil pair<int ,pair<int,int> > 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;
//using namespace __gnu_pbds;

const int MOD = 1000000009;
const int INF = 1e9;
const int MAXN = 3000000;

#define cin fin
#define cout fout

class DSU{
	int parent[MAXN];
	int nxt[MAXN];
	public : 
	DSU(int n){
		FOR(i,n)parent[i] = i,nxt[i] = (i+1)%n;
	}
	inline int find(int n){
		if(parent[n] != n)parent[n] = find(parent[n]);
		return parent[n];
	}
	inline int getVal(int n){
		return nxt[find(n)];
	}
	inline void merge(int a,int b,int nxtVal){
		int pa = find(a);
		int pb = find(b);
		parent[pa] = pb;
		nxt[pb] = nxtVal;
	}
};



int nxt[MAXN];
int bck[MAXN];
bool filled[MAXN];

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("empty.in");
	fout.open("empty.out");

	int n,k;
	cin >> n >> k;
	vector<ii> all;
	while(k--){
		ll x,y,a,b;
		cin >> x >> y >> a >> b;
		FORE(i,1,y){
			all.pb(mp((int)((a*i + b)%n),(int)x));
		}
	}
	sort(all.begin(), all.end());
	FOR(i,n)nxt[i] = (i+1) % n;
	FOR(i,n)bck[i] = (n+i-1)%n;
	FOR(i,n)filled[i] = 0;
	//cout << 5 << endl;
	//return 0;
	DSU dsu(n);
	for(auto& el:all){
		int PTR = el.ff;
		int num = el.ss;
		if(filled[PTR]){
			PTR = dsu.getVal(PTR);
		}
		while(num > 0){
			if(!filled[PTR]){
				num--;
				filled[PTR] = 1;
				nxt[bck[PTR]] = nxt[PTR];
				bck[nxt[PTR]] = bck[PTR];
				if(filled[(n+PTR-1)%n]){
					dsu.merge(PTR,(n+PTR-1)%n , nxt[PTR]);
				}
				if(filled[(PTR+1)%n]){
					dsu.merge(PTR,(PTR+1)%n , nxt[PTR]);
				}
			}
			PTR = nxt[PTR];
		}
	}
	int i;
	FOR(j,n){
		if(!filled[j]){
			i = j;
			break;
		}
	}
	cout << i << endl;

	return 0;
}