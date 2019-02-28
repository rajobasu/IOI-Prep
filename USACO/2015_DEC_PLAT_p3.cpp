/*
SOLUTION: simple lazy segtree
COMPLEXITY: O(nlognlogn)
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
#define ii pair<ll,ll>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define pll pair<ll,ll>


using namespace std;

const int MOD = 1000000007;
const ll INF = 100000000000000000;
const int MAXN = 200001;

class SegmentTree{
	ll st[4*MAXN];
	ll st2[4*MAXN];
	ll lz[4*MAXN];
	inline int lc(int node){
		return node*2+1;
	}
	inline int rc(int node){
		return node*2+2;
	}
	inline void propagate(int node,int sz){
		st[node] += lz[node];
		st2[node] += lz[node]*sz;
		if(sz > 1){
			lz[lc(node)] += lz[node];
			lz[rc(node)] += lz[node];
		}
		lz[node] = 0;
	}
	void _update_(int node,int ss,int se,int l,int r,ll val){
		propagate(node,se-ss+1);
		if(ss > r or se <l)return;
		if(l <= ss and se <= r){
			lz[node] += val;
			propagate(node,se-ss+1);
			return;
		}
		int mid = (ss+se)/2;
		_update_(lc(node),ss,mid,l,r,val);
		_update_(rc(node),mid+1,se,l,r,val);
		st[node] = min(st[lc(node)] , st[rc(node)]);
		st2[node] = st2[lc(node)] + st2[rc(node)];
	}
	ll _query_min(int node,int ss,int se,int l,int r){
		propagate(node,se-ss+1);
		if(ss > r or se < l)return INF;
		if(l <= ss and se <= r)return st[node];
		int mid = (ss+se)/2;
		return min(_query_min(lc(node),ss,mid,l,r),_query_min(rc(node),mid+1,se,l,r));
	}
	ll _query_sum(int node,int ss,int se,int l,int r){
		propagate(node,se-ss+1);
		if(ss > r or se < l)return 0;
		if(l <= ss and se <= r)return st2[node];
		int mid = (ss+se)/2;
		return _query_sum(lc(node),ss,mid,l,r)+_query_sum(rc(node),mid+1,se,l,r);
	}

	public:

	void update(int l,int r,ll val){
		if(l>r)swap(l,r);
		_update_(0,0,MAXN,min(l,r),max(l,r),val);
	}
	ll queryMin(int l,int r){
		return _query_min(0,0,MAXN,min(l,r),max(l,r));
	}
	ll querySum(int l,int r){
		return _query_sum(0,0,MAXN,min(l,r),max(l,r));
	}
} segtree;

#define cin fin
#define cout fout

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("haybales.in");
	fout.open("haybales.out");
	int n,q;
	cin >> n >> q;
	FOR(i,n){
		int c;cin >> c;
		segtree.update(i,i,c);
	}
	FOR(qq,q){
		char c;
		cin >> c;
		switch(c){
			case 'P':{
				int a,b,c;
				cin >> a >> b >> c;
				a--;b--;
				segtree.update(a,b,c);
				break;
			}
			case 'M':{
				int a,b;
				cin >> a >> b;
				a--;b--;
				cout << segtree.queryMin(a,b) << endl;
				break;
			}
			case 'S':{
				int a,b;
				cin >> a >> b;
				a--;b--;
				cout << segtree.querySum(a,b) << endl;
			}
		}
	}
	return 0;
}