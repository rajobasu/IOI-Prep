/*
SOLUTION: make the prev occurance as -arr[i] and the prevprev to 0. and then calculate best suffix sum from it
like GSS2 kindof
*/

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
#define vi vector<ll>
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define iii pair<int,ii>
#define vv vector
#define endl '\n'

using namespace std;

const int MAXN = 1e6 + 5;

struct SegmentTree{
	// range max/ point update
	ll st[4*MAXN];
	ll lz[4*MAXN];
	// for input you are given n. smallest i such that 2^i > n : m = 2^i;; actual size needed = 2*m
	SegmentTree(){
		FOR(i,4*MAXN)st[i] = 0;
	}
	ll combine(ll a,ll b){
		return max(a,b);
	}

	void pushdown(int node,int ss,int se){ // O(1)
		st[node] += lz[node]; // I update my segmenttree value
		if(ss != se){
			lz[node*2+1] += lz[node];// I push my lazy value to my children.
			lz[node*2+2] += lz[node];
		}
		lz[node] = 0; // I set my own lazy value to 0.
	}

	void update(int node,int ss,int se,int l,int r,ll val){
		// break condition
		if(lz[node]!=0)pushdown(node,ss,se);
		if(l > se or r < ss)return;
		
		// tag condition
		if(l <= ss and se <= r){
			// inside
			lz[node] += val;
			pushdown(node,ss,se);
			return;
		}

		int mid = (ss+se)/2;
		update(node*2+1,ss,mid,l,r,val);
		update(node*2+2,mid+1,se,l,r,val);
		st[node] = max(st[node*2+1],st[node*2+2]);
	}
	
	ll get(int node,int ss,int se,int l,int r){
		pushdown(node,ss,se);
		if(l > se or r < ss)return 0;
		if(l <= ss and se <= r)return st[node];
		int mid = (ss+se)/2;
		return max(get(node*2+1,ss,mid,l,r),get(node*2+2,mid+1,se,l,r));
	}
} segtree;

vi focc[MAXN];
int id[MAXN];
ll arr[MAXN];
ll farr[MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin >> n >> m;
	FOR(i,n)cin >> arr[i];FOR(i,n)arr[i]--;
	FOR(i,m)cin >> farr[i];
	FOR(i,n){
		focc[arr[i]].pb(i);
		int a = focc[arr[i]].size();
		id[i] = a-1;
	}
	ll mx = 0;
	FOR(i,n){
		segtree.update(0,0,n,0,i,farr[arr[i]]);
		if(id[i] > 1){
			segtree.update(0,0,n,0,focc[arr[i]][id[i]-2],farr[arr[i]]);
		}
		if(id[i] > 0){
			segtree.update(0,0,n,0,focc[arr[i]][id[i]-1],-2*farr[arr[i]]);
		}
		mx = max(mx,segtree.get(0,0,n,0,i));
	}
	cout << mx << endl;

	return 0;
}
