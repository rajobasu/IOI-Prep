/*
SOLUTION: DP + Segtree(for simulating the array). Try placing each crossover. There are 
very less such crossovers. The code should be clear.
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

#define FOR(i,n) for(int i = 0;i < n; i++)
#define FORE(i,a,b) for(int i = a; i <= b ; i++)
#define ss second
#define ff first
#define ii pair<int,int>
#define ll long long int
#define piil pair<pair<int,int>,ll> 
#define iii pair<pair<int,int>,int> 
#define vi vector<int>
#define pb push_back
#define mp make_pair
using namespace std;

const ll MOD = 1000000009;
const int INF = 1e9;
const int MAXN = 100001;

#define cin fin
#define cout fout


class SegmentTree{
	int st[4*MAXN];
	void upd(int node,int ss,int se,int i,int val){
		if(i > se or i < ss)return;
		if(ss == se){
			st[node] = val;
			return;
		}
		int mid = (ss+se)/2;
		upd(node*2+1,ss,mid,i,val);
		upd(node*2+2,mid+1,se,i,val);
		st[node] = max(st[node*2+1] , st[node*2+2]);
	}
	int get(int node,int ss,int se,int l,int r){
		if(l > se or r < ss)return 0;
		if(l <= ss and se <= r){
			return st[node];
		}
		int mid  = (ss+se)/2;
		return max(get(node*2+1,ss,mid,l,r),get(node*2+2,mid+1,se,l,r));
	}
	public :
	inline void update(int i,int val){
		upd(0,0,MAXN,i,val);
	}
	inline int query(int l,int r){
		if(r<l)return 0;
		return get(0,0,MAXN,l,r);
	}
};


int main(){
	ifstream fin;
	ofstream fout;
	fin.open("nocross.in");
	fout.open("nocross.out");

	int n;
	cin >> n;
	int a[n];int b[n];
	FOR(i,n)cin >> a[i];
	FOR(i,n)cin >> b[i];
	
	FOR(i,n)a[i]--,b[i]--;
	
	int loc_a[n];
	int loc_b[n];
	
	FOR(i,n)loc_a[a[i]] = i;
	FOR(i,n)loc_b[b[i]] = i;
	//FOR(i,n)cout << a[i] << " ";cout << endl;
	//FOR(i,n)cout << b[i] << " ";cout << endl;

	vi friends[n];
	//cout << "HI" << endl;
	FOR(i,n){
		FORE(j,max(0,a[i]-4),min(n-1,a[i]+4)){
			friends[i].pb(loc_b[j]);
		}
	}
	FOR(i,n)sort(friends[i].begin(), friends[i].end(),greater<int>());
	SegmentTree st;

	FOR(i,n){
		FOR(j,friends[i].size()){
			int back = st.query(0,friends[i][j]-1);
			st.update(friends[i][j],back+1);
		}
		//FOR(i,n)cout << st.query(i,i) << " ";cout << endl;
	}
	int mx = st.query(0,n-1);
	cout << mx << endl;

	return 0;
}